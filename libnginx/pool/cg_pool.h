
/*
 * Copyright (C) Igor Sysoev
 * Modify by zieckey@gmail.com
 * Date : 2015.01.06
 */


#ifndef CODEG_POOL_ALLOC_H_
#define CODEG_POOL_ALLOC_H_

#ifndef CODEG_MEMORY_POOL
    #define CODEG_MEMORY_POOL
#endif

#include <stdio.h>

#define cg_align(size, boundary) (((size) + ((boundary) - 1)) & ~((boundary) - 1))

#ifndef uintptr_t
    #if ( defined( __linux__ ) || defined( __gnu_linux__ ) )
        #include <stdint.h>
        typedef uint64_t uintptr_t;
    #endif
#endif

#define cg_align_ptr(p, a)                                                   \
    (unsigned char*) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))


/*
 * CG_MAX_ALLOC_FROM_POOL should be (cg_pagesize - 1), i.e. 4095 on x86.
 * On Windows NT it decreases a number of locked pages in a kernel.
 */
#define CG_MAX_ALLOC_FROM_POOL  (cg_pagesize - 1)

#define CG_DEFAULT_POOL_SIZE    (16 * 1024)
#define CG_ALIGNMENT (sizeof(unsigned long))
#define CG_POOL_ALIGNMENT       (16)
#define CG_MIN_POOL_SIZE                                        \
    cg_align((sizeof(cg_pool_t) + 2 * sizeof(cg_pool_large_t)), \
             CG_POOL_ALIGNMENT)



#ifdef __cplusplus
extern "C" {
#endif

extern int cg_pagesize;

typedef void  ( *cg_pool_cleanup_pt )( void *data );

typedef void* ( *cg_alloc_pt )( size_t size );
typedef void  ( *cg_free_pt )( void* p );



typedef struct cg_pool_cleanup_s       cg_pool_cleanup_t;
typedef struct cg_pool_s               cg_pool_t;
typedef struct cg_pool_large_s         cg_pool_large_t;
typedef struct cg_str_s                cg_str_t;
typedef struct cg_pool_data_s          cg_pool_data_t;

struct cg_pool_cleanup_s
{
    cg_pool_cleanup_pt handler;
    void              *data;
    cg_pool_cleanup_t *next;
};

struct cg_pool_large_s
{
    cg_pool_large_t *next;
    void            *alloc;
};

struct cg_str_s
{
    size_t         len;
    unsigned char *data;
};

struct cg_pool_data_s
{
    unsigned char *last;
    unsigned char *end;
    cg_pool_t     *next;
    unsigned int   failed;
};


struct cg_pool_s
{
    cg_pool_data_t     d;
    unsigned int       max;//the max size of memory allocated from pool
    cg_pool_t         *current;
    cg_pool_large_t   *large;
    cg_pool_cleanup_t *cleanup;
};

/**
 * @param pool_size - the pool size
 */
cg_pool_t *cg_create_pool( size_t pool_size );
void cg_destroy_pool( cg_pool_t *pool );
void cg_reset_pool( cg_pool_t *pool );

//malloc memory from cg_pool_t
void *cg_palloc( cg_pool_t *pool, size_t size );
void *cg_pnalloc( cg_pool_t *pool, size_t size );
void *cg_pcalloc( cg_pool_t *pool, size_t size );
void *cg_pmemalign( cg_pool_t *pool, size_t size, size_t alignment );
int   cg_pfree( cg_pool_t *pool, void *p );


cg_pool_cleanup_t *cg_pool_cleanup_add( cg_pool_t *p, size_t size );


void cg_set_alloc( cg_alloc_pt alloc_pt );
void cg_set_free( cg_free_pt free_pt );

int cg_dbgprint( const char* fmt, ... );

#ifdef __cplusplus
} // end of extern "C" {
#endif

/** define some micro to make it no change to using Nginx code */
#define NGX_MAX_ALLOC_FROM_POOL CG_MAX_ALLOC_FROM_POOL
#define NGX_DEFAULT_POOL_SIZE   CG_DEFAULT_POOL_SIZE
#define NGX_ALIGNMENT           CG_ALIGNMENT
#define NGX_POOL_ALIGNMENT      CG_POOL_ALIGNMENT
#define NGX_MIN_POOL_SIZE       CG_MIN_POOL_SIZE

#define ngx_pagesize            cg_pagesize

#define ngx_align               cg_align
#define ngx_align_ptr           cg_align_ptr

#define ngx_pool_cleanup_s      cg_pool_cleanup_s
#define ngx_pool_s              cg_pool_s
#define ngx_pool_large_s        cg_pool_large_s
#define ngx_str_s               cg_str_s
#define ngx_pool_data_s         cg_pool_data_s

#define ngx_pool_cleanup_t      cg_pool_cleanup_t
#define ngx_pool_t              cg_pool_t
#define ngx_pool_large_t        cg_pool_large_t
#define ngx_str_t               cg_str_t
#define ngx_pool_data_t         cg_pool_data_t

#define ngx_create_pool         cg_create_pool
#define ngx_destroy_pool        cg_destroy_pool
#define ngx_reset_pool          cg_reset_pool
#define ngx_palloc              cg_palloc
#define ngx_pnalloc             cg_pnalloc
#define ngx_pcalloc             cg_pcalloc
#define ngx_pmemalign           cg_pmemalign
#define ngx_pfree               cg_pfree
#define ngx_pool_cleanup_add    cg_pool_cleanup_add



#ifdef __cplusplus
#if ( defined(WIN32) || defined(WIN64) )
#include <memory>
#else
#include <tr1/memory>
#endif
namespace cg
{
    class Pool
    {
    public:
        Pool(size_t pool_size) {
            pool_ = cg_create_pool(pool_size);
        }

        ~Pool() {
            cg_destroy_pool(pool_);
            pool_ = NULL;
        }

        cg_pool_t* pool() const {
            return pool_;
        }

        char* alloc(size_t len) {
            return static_cast<char*>(cg_palloc(pool_, len));
        }

        void free(void* p) {
            cg_pfree(pool_, p);
        }

    private:
        cg_pool_t * pool_;
    };
    typedef std::tr1::shared_ptr<Pool> PoolPtr;
}
#endif

#endif /* _CG_PALLOC_H_INCLUDED_ */


