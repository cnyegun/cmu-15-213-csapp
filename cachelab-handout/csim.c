#include "cachelab.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "assert.h"

int main()
{
    FILE *f = fopen("traces/yi.trace", "r");

    char *lineptr = NULL;
    size_t n;
    ssize_t len;
    while ((len = getline(&lineptr, &n, f)) != -1)
    {
        lineptr[len - 1] = '\0';
        len--;

        char op;
        unsigned long addr;
        int bytes;
        sscanf(lineptr, " %c %lx,%d", &op, &addr, &bytes);
        
        printf("op: %c, addr: 0x%lx, bytes %d\n", op, addr, bytes);

        free(lineptr);
        lineptr = NULL;
        n = 0;
    }

    free(lineptr);
    fclose(f);
    return 0;
}
