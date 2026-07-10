#include "cachelab.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "assert.h"

int copy_addr_until_comma(char (*dst)[16], const char *src) {
    int i;
    for (i = 0; i < 16; i++) {
        if (src[i] == ',') {
            (*dst)[i] = '\0';
            return i;
        }
        (*dst)[i] = src[i];
    }
    return -1;
}

void parse_trace_line(char *op, char (*addr)[16], int *bytes, const char *src) {
    assert(src != NULL);
    assert(src[0] == ' ');
    *op = src[1];
    int addr_len = copy_addr_until_comma(addr, src + 3);
    *bytes = atoi(src + 3 + addr_len + 1);
}

int main()
{
    FILE *f = fopen("traces/yi.trace", "r");

    char *lineptr = NULL;
    size_t n;
    ssize_t len;
    while ((len = getline(&lineptr, &n, f)) != -1)
    {
        assert(lineptr != NULL);
        assert(lineptr[0] == ' ');

        lineptr[len - 1] = '\0';
        len--;

        char op;
        char addr[16];
        int bytes;
        parse_trace_line(&op, &addr, &bytes, lineptr);
        printf("op: %c, addr: %s, bytes %d\n", op, addr, bytes);

        free(lineptr);
        lineptr = NULL;
        n = 0;
    }

    free(lineptr);
    fclose(f);
    return 0;
}
