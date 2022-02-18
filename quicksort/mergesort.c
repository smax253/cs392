#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mergesort.h"

/**
 * Compares two char arrays passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to char* pointers (i.e. char**).
 * Returns the result of calling strcmp on them.
 */
int str_cmp(const void *a, const void *b)
{
    char *first = (char *)a;
    char *second = (char *)b;
    return strcmp(first, second);
}

/**
 * Compares two integers passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to int pointers.
 * Returns:
 * -- 0 if the integers are equal
 * -- a positive number if the first integer is greater
 * -- a negative if the second integer is greater
 */
int int_cmp(const void *a, const void *b)
{
    int *first = (int *)a;
    int *second = (int *)b;
    return *first - *second;
}

/**
 * Compares two doubles passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to double pointers.
 * Returns:
 * -- 0 if the doubles are equal
 * -- 1 if the first double is greater
 * -- -1 if the second double is greater
 */
int dbl_cmp(const void *a, const void *b)
{
    double *first = (double *)a;
    double *second = (double *)b;

    double diff = *first - *second;
    if (diff == 0)
        return 0;
    else if (diff > 0)
        return 1;
    else
        return -1;
}

void copy(void *toArray, void *fromArray, size_t toIndex, size_t fromIndex, size_t elem_sz)
{
    char *toArrayPtr = toArray, *fromArrayPtr = fromArray;
    for (size_t i = 0; i < elem_sz; i++)
    {
        toArrayPtr[toIndex * elem_sz + i] = fromArrayPtr[fromIndex * elem_sz + i];
    }
}

void mergesort_helper(void *array, size_t l, size_t m, size_t r, size_t elem_sz, int (*comp)(const void *, const void *))
{
    int n1 = m - l + 1;
    int n2 = r - m;
    char *L = malloc(n1 * elem_sz);
    char *R = malloc(n2 * elem_sz);
    for (size_t i = 0; i < n1; i++)
    {
        copy(L, array, i, l + i, elem_sz);
    }
    for (size_t i = 0; i < n2; i++)
    {
        copy(R, array, i, m + 1 + i, elem_sz);
    }
    size_t i = 0, j = 0;
    // Initial index of merged subarray array
    int k = l;
    while (i < n1 && j < n2)
    {
        if (comp(L + i * elem_sz, R + j * elem_sz) <= 0)
        {
            copy(array, L, k, i, elem_sz);
            i++;
        }
        else
        {
            copy(array, R, k, j, elem_sz);
            j++;
        }
        k++;
    }

    /* Copy remaining elements of L[] if any */
    while (i < n1)
    {
        copy(array, L, k, i, elem_sz);
        i++;
        k++;
    }

    /* Copy remaining elements of R[] if any */
    while (j < n2)
    {
        copy(array, R, k, j, elem_sz);
        j++;
        k++;
    }
    free(L);
    free(R);
}

void sort(void *arr, size_t l, size_t r, size_t elem_sz, int (*comp)(const void *, const void *))
{
    if (l < r)
    {
        // Find the middle point
        int m = l + (r - l) / 2;

        // Sort first and second halves
        sort(arr, l, m, elem_sz, comp);
        sort(arr, m + 1, r, elem_sz, comp);

        // Merge the sorted halves
        mergesort_helper(arr, l, m, r, elem_sz, comp);
    }
}

void mergesort(void *array, size_t len, size_t elem_sz, int (*comp)(const void *, const void *))
{
    sort(array, 0, len - 1, elem_sz, comp);
}