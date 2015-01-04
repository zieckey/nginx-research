#include "allinc.h"

namespace {
    struct ListElement {
        ngx_str_t name;
        int id;
    };

    static const char* names[] = { "codeg", "jane", "zieckey", "codeg4", "codeg5", "codeg6", "codeg7", "codeg8", "codeg9", "codeg10" };
}

TEST_UNIT_P(ngx_list)
{
    ngx_uint_t nalloc = 4;
    ngx_list_t *list = ngx_list_create(pool, nalloc, sizeof(ListElement));

    // insert element to the list
    for (size_t i = 0; i < H_ARRAYSIZE(names); i++)
    {
        ListElement* u = (ListElement*)ngx_list_push(list);
        u->id = i;
        u->name.data = (u_char*)names[i];
        u->name.len = strlen(names[i]);
    }
    
    H_TEST_ASSERT(list->nalloc == nalloc);
    H_TEST_ASSERT(list->last->next == NULL);
    H_TEST_ASSERT(list->last->nelts == H_ARRAYSIZE(names) % nalloc);
    H_TEST_ASSERT(list->last == list->part.next->next);

    // traverse the list
    int count = 0;
    for (ngx_list_part_t* part = &list->part; part; part = part->next)
    {
        for (ngx_uint_t n = 0; n < part->nelts; ++n)
        {
            ListElement* u = (ListElement*)(part->elts) + n;
            //printf("id=%d name=%s\n", u->id, (char*)u->name.data);
            H_TEST_ASSERT(strncmp((char*)u->name.data, names[count++], u->name.len) == 0);
        }
    }
    H_TEST_ASSERT(count == H_ARRAYSIZE(names));
}