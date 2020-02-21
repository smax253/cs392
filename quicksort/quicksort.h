/*******************************************************************************
 * Name        : quicksort.h
 * Author      : Max Shi
 * Date        : 2/21/2020
 * Description : Quicksort header.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
/**
 * TODO - put all non-static function prototypes from quicksort.c inside
 * wrapper #ifndef.
 */
#ifndef QUICKSORT_H_
#define QUICKSORT_H_
#include <stdlib.h>
int int_cmp(const void *a, const void *b);
int str_cmp(const void *a, const void *b);
int dbl_cmp(const void *a, const void *b);
void quicksort(void *array, size_t len, size_t elem_sz,
               int (*comp) (const void*, const void*));
#endif
