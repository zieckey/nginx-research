
/*
 * Copyright (C) Igor Sysoev
 * Modify by zieckey@gmail.com
 * Date : 2015.01.06
 */

#include "cg_pool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#if ( defined(WIN32) || defined(WIN64) )
    #include <Windows.h>
    int getpagesize();
    #define snprintf _snprintf
#else
    #include <unistd.h>
#endif


#if defined(_DEBUG) && defined(__cplusplus)
//    #define TEST_POOL_MEMORY_ALLOC
#endif

#ifdef H_OS_WINDOWS
    #ifndef TEST_POOL_MEMORY_ALLOC
        #define TEST_POOL_MEMORY_ALLOC
    #endif
#endif

#ifdef TEST_POOL_MEMORY_ALLOC
    #include <map>
    #include <string>
    typedef std::map<void*, std::string> pointerstringmap;
    pointerstringmap* mallocmap = NULL;
#endif//#ifdef TEST_POOL_MEMORY_ALLOC

static void *cg_palloc_block(cg_pool_t *pool, size_t size);
static void *cg_palloc_large(cg_pool_t *pool, size_t size);

//malloc memory directly from OS memory
static void *_cg_alloc(size_t size );
static void *_cg_alloc4(size_t size, const char* funcname, const char* filename, int nLine);
static void _cg_free( void* p );

int cg_pagesize = 4096;

static cg_alloc_pt cg_alloc = &_cg_alloc;
static cg_free_pt cg_free = &_cg_free;

void* _cg_alloc(size_t size)
{/*{{{*/
    return _cg_alloc4(size, NULL, NULL, 0);
}/*}}}*/

void* _cg_alloc4(size_t size, const char* funcname, const char* filename, int nLine)
{/*{{{*/
    void* p = malloc(size);
    
#ifdef TEST_POOL_MEMORY_ALLOC
    if ( !funcname ) funcname = "";
    if ( !filename ) filename = "";
    char buf[4096] = {'\0'};
    snprintf( buf, sizeof(buf), "malloc p=%p size=%d, %s %s:%d\n", 
                    p, (int)size, funcname, filename, nLine );
    printf("%s\n", buf);
    mallocmap->insert( pointerstringmap::value_type( p, buf ) );
#else
    (void)funcname; (void)filename; (void)nLine;
#endif//#ifdef TEST_POOL_MEMORY_ALLOC

    return p;
}/*}}}*/

void _cg_free( void* p )
{/*{{{*/
    if ( p )
    {
        free(p);
            
#ifdef TEST_POOL_MEMORY_ALLOC
        printf("free p=0x%p\n", p );
        mallocmap->erase( p );
#endif//#ifdef TEST_POOL_MEMORY_ALLOC  

    }
}/*}}}*/




cg_pool_t *
cg_create_pool(size_t size)
{/*{{{*/
    cg_pool_t  *p = NULL;

#ifdef TEST_POOL_MEMORY_ALLOC
    mallocmap = new pointerstringmap();
#endif//#ifdef TEST_POOL_MEMORY_ALLOC
    
    size = cg_align( size, CG_POOL_ALIGNMENT );

#ifdef _DEBUG
    p = (cg_pool_t*)_cg_alloc4(size, __FUNCTION__, __FILE__, __LINE__ );
#else
    p = (cg_pool_t*)cg_alloc(size);
#endif
    
    if (p == NULL) {
        return NULL;
    }

    p->d.last = (unsigned char *) p + sizeof(cg_pool_t);
    p->d.end = (unsigned char *) p + size;
    p->d.next = NULL;
    p->d.failed = 0;

    size = size - sizeof(cg_pool_t);
    p->max = (unsigned int)(size < (size_t)CG_MAX_ALLOC_FROM_POOL ? size : (size_t)CG_MAX_ALLOC_FROM_POOL);
    if (p->max < sizeof(cg_pool_large_t)) {
        // Avoid infinite recursion loop calling cg_palloc_large when cg_palloc
        p->max = sizeof(cg_pool_large_t) << 3;
    }

    p->current = p;
    p->large = NULL;
    p->cleanup = NULL;


    cg_pagesize = getpagesize();

    return p;
}/*}}}*/


void
cg_destroy_pool(cg_pool_t *pool)
{/*{{{*/
    cg_pool_t          *p, *n;
    cg_pool_large_t    *l;
    cg_pool_cleanup_t  *c;

    for (c = pool->cleanup; c; c = c->next) {
        if (c->handler) {
            c->handler(c->data);
        }
    }

    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            cg_free(l->alloc);
        }
    }

#if defined(_DEBUG) && defined(TEST_POOL_MEMORY_ALLOC)
    /*
     * we could allocate the pool->log from this pool
     * so we can not use this log while the free()ing the pool
     */
    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        cg_dbgprint( "free: %x, unused: %d\n", p, (int)(p->d.end - p->d.last) );
        if (n == NULL) {
            break;
        }
    }

#endif

    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        cg_free(p);

        if (n == NULL) {
            break;
        }
    }


#ifdef TEST_POOL_MEMORY_ALLOC
    pointerstringmap::iterator it (mallocmap->begin());
    pointerstringmap::iterator ite(mallocmap->end());
    if ( it != ite )
    {
        printf( "Memory leak!!!!!!\n" );
        for ( ; it != ite; ++it )
        {
            printf( "%p %s\n", it->first, it->second.c_str() );
        }
        assert( false );
    }
    else
    {
        printf("No memory leak! Great!\n");
    }
    delete mallocmap;
    mallocmap = NULL;
#endif//#ifdef TEST_POOL_MEMORY_ALLOC

}/*}}}*/


void
cg_reset_pool(cg_pool_t *pool)
{/*{{{*/
    cg_pool_t        *p;
    cg_pool_large_t  *l;

    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            cg_free(l->alloc);
        }
    }

    pool->large = NULL;

    for (p = pool; p; p = p->d.next) {
        p->d.last = (unsigned char *) p + sizeof(cg_pool_t);
    }
}/*}}}*/


void *
cg_palloc(cg_pool_t *pool, size_t size)
{/*{{{*/
    unsigned char      *m;
    cg_pool_t  *p;

    if (size <= pool->max) {

        p = pool->current;

        do {
            m = cg_align_ptr(p->d.last, CG_ALIGNMENT);

            if ((size_t) (p->d.end - m) >= size) {
                p->d.last = m + size;

                return m;
            }

            p = p->d.next;

        } while (p);

        return cg_palloc_block(pool, size);
    }

    return cg_palloc_large(pool, size);
}/*}}}*/


void *
cg_pnalloc(cg_pool_t *pool, size_t size)
{/*{{{*/
    unsigned char      *m;
    cg_pool_t  *p;

    if (size <= pool->max) {

        p = pool->current;

        do {
            m = p->d.last;

            if ((size_t) (p->d.end - m) >= size) {
                p->d.last = m + size;

                return m;
            }

            p = p->d.next;

        } while (p);

        return cg_palloc_block(pool, size);
    }

    return cg_palloc_large(pool, size);
}/*}}}*/


static void *
cg_palloc_block(cg_pool_t *pool, size_t size)
{/*{{{*/
    unsigned char      *m;
    size_t       psize;
    cg_pool_t  *p, *npool, *current;

    psize = (size_t) (pool->d.end - (unsigned char *) pool);

#ifdef _DEBUG
    m = (unsigned char*)_cg_alloc4( cg_align(psize, CG_POOL_ALIGNMENT), __FUNCTION__, __FILE__, __LINE__ );
#else
    m = (unsigned char*)cg_alloc( cg_align(psize, CG_POOL_ALIGNMENT) );
#endif

    if (m == NULL) {
        return NULL;
    }

    npool = (cg_pool_t *) m;

    npool->d.end = m + psize;
    npool->d.next = NULL;
    npool->d.failed = 0;

    m += sizeof(cg_pool_data_t);
    m = cg_align_ptr(m, CG_ALIGNMENT);
    npool->d.last = m + size;

    current = pool->current;

    for (p = current; p->d.next; p = p->d.next) {
        if (p->d.failed++ > 4) {
            current = p->d.next;
        }
    }

    p->d.next = npool;

    pool->current = current ? current : npool;

    return m;
}/*}}}*/


static void *
cg_palloc_large(cg_pool_t *pool, size_t size)
{/*{{{*/
    void                  *p = NULL;
    int                    n = 0;
    cg_pool_large_t  *large = NULL;

#ifdef _DEBUG
    p = (cg_pool_t*)_cg_alloc4(size, __FUNCTION__, __FILE__, __LINE__ );
#else
    p = (cg_pool_t*)cg_alloc(size);
#endif

    if (p == NULL) {
        return NULL;
    }

    for (large = pool->large; large; large = large->next) {
        if (large->alloc == NULL) {
            large->alloc = p;
            return p;
        }

        if (n++ > 3) {
            break;
        }
    }

    large = (cg_pool_large_t*)cg_palloc(pool, sizeof(cg_pool_large_t));
    if (large == NULL) {
        cg_free(p);
        return NULL;
    }

    large->alloc = p;
    large->next = pool->large;
    pool->large = large;

    return p;
}/*}}}*/


void *
cg_pmemalign(cg_pool_t *pool, size_t size, size_t alignment)
{/*{{{*/
    void              *p;
    cg_pool_large_t  *large;

#ifdef _DEBUG
    p = (cg_pool_large_t*)_cg_alloc4( cg_align(size, alignment), __FUNCTION__, __FILE__, __LINE__ );
#else
    p = (cg_pool_large_t*)cg_alloc( cg_align(size, alignment) );
#endif

    if (p == NULL) {
        return NULL;
    }

    large = (cg_pool_large_t*)cg_palloc(pool, sizeof(cg_pool_large_t));
    if (large == NULL) {
        cg_free(p);
        return NULL;
    }

    large->alloc = p;
    large->next = pool->large;
    pool->large = large;

    return p;
}/*}}}*/


int
cg_pfree(cg_pool_t *pool, void *p)
{/*{{{*/

    /**
     * modify the original implementation 
     */
    cg_pool_large_t  *pre = pool->large;
    cg_pool_large_t  *l = pool->large;

    for ( ; l; pre = l, l = l->next) {
        if (p == l->alloc) {
            cg_free(l->alloc);
            l->alloc = NULL;
            if ( pool->large == l )
            {
                pool->large = l->next;
            }
            else
            {
                pre->next = l->next;
            }
            return 0;
        }
    }

    /**  
    //original nginx implementation

    cg_pool_large_t  *l;

    for (l = pool->large; l; l = l->next) {
        if (p == l->alloc) {
            cg_free(l->alloc);
            l->alloc = NULL;
            return 0;
        }
    }
    */


    return -1;
}/*}}}*/


void *
cg_pcalloc(cg_pool_t *pool, size_t size)
{/*{{{*/
    void *p;

    p = cg_palloc(pool, size);
    if (p) {
        memset(p, 0, size);
    }

    return p;
}/*}}}*/


cg_pool_cleanup_t *
cg_pool_cleanup_add(cg_pool_t *p, size_t size)
{/*{{{*/
    cg_pool_cleanup_t  *c;

    c = (cg_pool_cleanup_t*)cg_palloc(p, sizeof(cg_pool_cleanup_t));
    if (c == NULL) {
        return NULL;
    }

    if (size) {
        c->data = cg_palloc(p, size);
        if (c->data == NULL) {
            return NULL;
        }

    } else {
        c->data = NULL;
    }

    c->handler = NULL;
    c->next = p->cleanup;

    p->cleanup = c;

    return c;
}/*}}}*/


void cg_set_alloc( cg_alloc_pt alloc_pt )
{/*{{{*/
    if ( alloc_pt )
    {
        cg_alloc = alloc_pt;
    }
    else
    {
        cg_alloc = &_cg_alloc;
    }
}/*}}}*/

void cg_set_free( cg_free_pt free_pt )
{/*{{{*/
    if ( free_pt )
    {
        cg_free = free_pt;
    }
    else
    {
        cg_free = &_cg_free;
    }
}/*}}}*/


int cg_dbgprint( const char* fmt, ... )
{/*{{{*/
#ifdef _DEBUG
#define _XX_BUF_SIZE 80960
    int n = 0;
    va_list ap;
    char str[_XX_BUF_SIZE];
    va_start(ap,fmt);
    vsnprintf(str, _XX_BUF_SIZE, fmt, ap);
    n = printf(str);
    va_end(ap);
    return n;
#undef _XX_BUF_SIZE
#else
    (void)fmt;
    return 0;
#endif
}/*}}}*/

#if ( defined(WIN32) || defined(WIN64) )
/* getpagesize for windows */
int getpagesize(void) {
    static int g_pagesize = 0;
    if (! g_pagesize) {
        SYSTEM_INFO system_info;
        GetSystemInfo (&system_info);
        g_pagesize = (int)system_info.dwPageSize;
    }
    return g_pagesize;
}
#endif


