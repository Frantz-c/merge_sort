#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_data   t_data;

struct  s_data
{
    int     (*cmp)(void*, void*);
    size_t  esize;
};

void    sort_subarray(void *t, const int halflen, const int max2, t_data *data)
{
    void        *t2;
    void        *t1;
    int         curs1;
    int         curs2;

    t2 = t + halflen;
    t1 = malloc(halflen);
    memcpy(t1, t, halflen);
    curs1 = 0;
    curs2 = 0;
    while (curs1 < halflen)
    {
        if (curs2 < max2 && data->cmp(t1 + curs1, t2 + curs2) > 0)
        {
            memmove(t + curs1 + curs2, t2 + curs2, data->esize);
            curs2 += data->esize;
            continue ;
        }
        if (curs2)
            memmove(t + curs1 + curs2, t1 + curs1, data->esize);
        curs1 += data->esize;
    }
    free(t1);
}

void    merge_sort(void *t, size_t esize, int length, int (*cmp)(void*,void*))
{
    t_data  data;
    int     sortsiz;
    int     sortpos;

    data.esize = esize;
    data.cmp = cmp;
    sortsiz = 2;
    while (sortsiz <= length)
    {
        sortpos = 0;
        while ((sortpos + sortsiz) <= length)
        {
            sort_subarray(t + (sortpos * esize), (sortsiz * esize) / 2,
                        (sortsiz * esize) / 2, &data);
            sortpos += sortsiz;
        }
        if (sortpos < length && length - sortpos > 1)
            sort_subarray(t + sortpos, ((length - sortpos) * esize) / 2,
                        ((length - sortpos) * esize) / 2, &data);
        sortsiz *= 2;
    }
    if (sortsiz > length)
        sort_subarray(t, (sortsiz * esize) / 2,
                    (length - (sortsiz / 2)) * esize, &data);
}

int     cmp_func(void *a, void *b)
{
    return (*(int*)a - *(int*)b);
}

int     main(void)
{
    int     t[7] = {6, 3, 5, 4, 1, 0, 2};

    merge_sort(t, sizeof(int), 7, cmp_func);
    int i = 0;
    while (i < 7)
    {
        printf("%d\n", t[i]);
        i++;
    }
    return (0);
}
