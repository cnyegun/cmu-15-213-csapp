#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef long data_t;
#define IDENT 0
#define OP +

typedef struct {
    size_t len;
    data_t *data;
} vec_rec, *vec_ptr;

vec_ptr new_vec(size_t len) {
    vec_ptr r = (vec_ptr) malloc(sizeof(vec_rec));
    if (!r) return NULL;
    r->len = len;

    if (len > 0) {
        data_t *data = (data_t *) malloc(sizeof(data_t) * len);
        if (!data) {
            free(r);
            return NULL;
        }
        r->data = data;
    }
    else 
        r->data = NULL;
    return r;
}

/* Retrieve vector element at index and store at dest
 * returns 0 (out of bound), 1 (successful)
 */
int get_vec_element(vec_ptr v, long int index, data_t *dest) {
    int n;
    if (index < 0 || index >= v->len) 
        return 0;
    *dest = v->data[index];
    return 1;
}

/* return length of vector */
long int vec_length(vec_ptr v) {
    return v->len;
}

void combine1(vec_ptr v, data_t *dest)
{
    long int i;
    *dest = IDENT;
    for (i = 0; i < vec_length(v); i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

void my_combine(const vec_ptr v, data_t *dest) {
    size_t i;
    size_t len = vec_length(v);
    data_t A1 = IDENT, A2 = IDENT, A3 = IDENT, A4 = IDENT;
    for (i = 0; i < len; i += 4) {
        A1 = A1 OP v->data[i];
        A2 = A2 OP v->data[i + 1];
        A3 = A3 OP v->data[i + 2];
        A4 = A4 OP v->data[i + 3];
    }

    for (; i < len; i++) {
        A4 = A4 OP v->data[i];
    }
    *dest = (A1 OP A2) OP (A3 OP A4);
}

int main() {
    srandom(1337); 
    vec_rec v;
    v.len = 1000000;
    v.data = (data_t *) malloc(sizeof(data_t) * v.len);
    for (int i = 0; i < v.len; i++) {
        v.data[i] = (data_t) ((float) random() / (float) RAND_MAX);
    }
    
    float t1, t2;
    clock_t start, end;
    start = clock();
    volatile data_t sink = 0;
    for (int i = 0; i < 100; i++) {
        data_t x;
        combine1(&v, &x); 
        sink += x;
    }
    end = clock();
    t1 = (float) (end - start) / CLOCKS_PER_SEC;
    printf("combine1(): %f\n", t1);

    start = clock();
    for (int i = 0; i < 100; i++) {
        data_t x;
        my_combine(&v, &x); 
        sink += x;
    }
    end = clock();
    t2 = (float) (end - start) / CLOCKS_PER_SEC;
    printf("my_combine(): %f\n", t2);
    printf("optimization %.2fx\n", t1/t2);
}
