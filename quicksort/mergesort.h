
/* Functions to compare a and b */
int int_cmp(const void *a, const void *b);
int dbl_cmp(const void *a, const void *b);
int str_cmp(const void *a, const void *b);

/* Main sorting algorithm you need to implement */
void mergesort(void *array,
               size_t len,
               size_t elem_sz,
               int (*comp)(const void *, const void *));
