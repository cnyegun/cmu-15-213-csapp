#include "cachelab.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "assert.h"
#include "unistd.h"

int main(int argc, char *argv[])
{
    int verbose = 0;
    int help = 0;

    int cache_sets = -1, 
        cache_lines = -1,
        cache_blocks = -1;

    char *trace_file = NULL;

    // Loop through the args, optarg is the C's global variable 
    int opt;
    while ((opt = getopt(argc, argv, "s:E:b:t:hv")) != -1) {
        switch (opt) {
            case 's':
                cache_sets = atoi(optarg);
                break;
            case 'E':
                cache_lines = atoi(optarg);
                break;
            case 'b':
                cache_blocks = atoi(optarg);
                break;
            case 't':
                trace_file = optarg;
                break;
            case 'h':
                help = 1;
                break;
            case 'v':
                verbose = 1;
                break;
        }
    }

    int tag_bits = 64 - (cache_blocks + cache_sets);

    if (cache_sets == -1 || cache_lines == -1 || cache_blocks == -1 || trace_file == NULL) {
        printf("Usage: ./csim [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n");
        exit(EXIT_FAILURE);
    }

    int hits = 0, misses = 0, evictions = 0;
    FILE *f = fopen(trace_file, "r");

    char *lineptr = NULL;
    size_t n;
    ssize_t len;
    while ((len = getline(&lineptr, &n, f)) != -1)
    {
        // remove '\n' from the end of the line
        lineptr[len - 1] = '\0';
        len--;

        // need to ignores line starts with 'I'
        // because it's an instruction load
        if (lineptr[0] == 'I') continue;

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
    printSummary(hits, misses, evictions);
    return 0;
}
