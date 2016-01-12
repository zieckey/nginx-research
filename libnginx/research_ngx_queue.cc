#include "allinc.h"

namespace {
    struct QueueElement {
        const char* name;
        int id;
        ngx_queue_t queue;
    };

    static int ids[] = { 5, 8, 1, 9, 2, 6, 0, 3, 7, 4 };
    static const char* names[] = { "codeg", "jane", "zieckey", "codeg4", "codeg5", "codeg6", "codeg7", "codeg8", "codeg9", "codeg10" };
}

void dump_queue_from_tail(ngx_queue_t *que)
{
    ngx_queue_t *q = ngx_queue_last(que);

    printf("(0x%p: (0x%p, 0x%p)) <==> \n", que, que->prev, que->next);

    for (; q != ngx_queue_sentinel(que); q = ngx_queue_prev(q))
    {
        QueueElement *u = ngx_queue_data(q, QueueElement, queue);
        printf("(0x%p: (id=%d %s), 0x%p: (0x%p, 0x%p)) <==> \n", u, u->id,
            u->name, &u->queue, u->queue.prev, u->queue.next);
    }
}

void dump_queue_from_head(ngx_queue_t *que)
{
    ngx_queue_t *q = ngx_queue_head(que);

    printf("(0x%p: (0x%p, 0x%p)) <==> \n", que, que->prev, que->next);

    for (; q != ngx_queue_sentinel(que); q = ngx_queue_next(q))
    {
        QueueElement *u = ngx_queue_data(q, QueueElement, queue);
        printf("(0x%p: (id=%d %s), 0x%p: (0x%p, 0x%p)) <==> \n", u, u->id,
            u->name, &u->queue, u->queue.prev, u->queue.next);
    }
}

//sort from small to big  
ngx_int_t my_point_cmp(const ngx_queue_t* lhs, const ngx_queue_t* rhs)
{
    QueueElement *pt1 = ngx_queue_data(lhs, QueueElement, queue);
    QueueElement *pt2 = ngx_queue_data(rhs, QueueElement, queue);

    if (pt1->id < pt2->id)
        return 0;
    return 1;
}

TEST_UNIT_P(ngx_queue)
{
    printf("--------------------------------\n");
    printf("a new pool created:\n");
    printf("--------------------------------\n");
    pool = ngx_create_pool(1024, NULL);
    dump_pool(pool);

    ngx_queue_t *myque;

    myque = (ngx_queue_t*)ngx_palloc(pool, sizeof(ngx_queue_t));  //alloc a queue head  
    ngx_queue_init(myque);  //init the queue  

    //insert  some points into the queue  
    for (int i = 0; i < (int)H_ARRAYSIZE(names); i++)
    {
        QueueElement *e = (QueueElement*)ngx_palloc(pool, sizeof(QueueElement));
        e->name = names[i];
        e->id = ids[i];
        ngx_queue_init(&e->queue);

        //insert this point into the points queue  
        ngx_queue_insert_head(myque, &e->queue);
    }

    dump_queue_from_tail(myque);
    printf("\n");

    printf("--------------------------------\n");
    printf("sort the queue:\n");
    printf("--------------------------------\n");
    ngx_queue_sort(myque, my_point_cmp);
    dump_queue_from_head(myque);
    printf("\n");

    printf("--------------------------------\n");
    printf("the pool at the end:\n");
    printf("--------------------------------\n");
    dump_pool(pool);
}

