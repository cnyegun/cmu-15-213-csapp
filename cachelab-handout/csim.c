#include "cachelab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

typedef struct {
    int valid;
    unsigned long tag;
    time_t last_used;
} cache_line_t;

int main(int argc, char *argv[])
{
    int verbose = 0;
    int help = 0;

    /* This computer is running 64 bit operating system */
    int m = 64;

    int t, s, b;

    int S = -1;
    int E = -1;
    int B = -1;

    char *trace_file = NULL;

    // Loop through the args, optarg is the getopt's global variable 
    int opt;
    while ((opt = getopt(argc, argv, "s:E:b:t:hv")) != -1) {
        switch (opt) {
            case 's':
                s = atoi(optarg);
                S = (int) pow(s, 2);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                B = (int) pow(b, 2);
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

    t = m - (s + b);

    if (S == -1 || E == -1 || B == -1 || trace_file == NULL) {
        printf("Usage: %s [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("  s: %d, S: %d\n", s, S);
    printf("  E: %d\n", E);
    printf("  b: %d, B: %d\n", b, B);
    printf("  t: %d bits\n", t);
    printf("  m: %d bit\n", t + s + b);
    printf("  Total cache size: %d bytes\n", S * E * B);

    /* Init the cache array
     * 2D array of sets and lines
     */

    cache_line_t *C = calloc(sizeof(cache_line_t), S * E);

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

        /* STEP 1: Parse the opcode, address and bytes 
         * from the given instruction
         */
        char op;
        unsigned long addr;
        int bytes;
        sscanf(lineptr, " %c %lx,%d", &op, &addr, &bytes);
        
        printf("---------------------------------\n");
        printf("Parsing line:%s\n", lineptr);

        /* STEP 2: Calculating the cache index from the given address 
         * Using the address, divide its bit pattern into segment,
         * first are t bits for Tag,
         * then s bits for Set index
         * then b bits for Block offset
         */
        unsigned long tag = addr >> (s + b);
        unsigned long set_index = (addr << t) >> (t + b);
        unsigned long block_starts_at = addr & ~((1UL << b) - 1);

        printf("Tag: 0x%lx\n", tag);
        printf("Set index: %lu\n", set_index);
        printf("Block starts at: 0x%lx\n", block_starts_at);

        /* STEP 3: Modify the cache's array
         * First check if the given address's cache entry are valid?
         * If yes, check if the tag are the same? No -> Miss; Yes -> Hit
         */

        cache_line_t *set = C + (set_index * E);
        
        // Loop through every line in a set to find a hit 
        // if couldn't find an invalid line, use the least recently used index to store

        int hit_flag = 0;
        int found_invalid = 0;
        int invalid_idx = -1;

        int lru_idx = 0;
        time_t lru = time(NULL);

        for (int i = 0; i < E; i++) {
            // Hit case
            if (set[i].valid && set[i].tag == tag) {
                printf("Hit!\n");
                hit_flag = 1;
                set[i].last_used = time(NULL);
                break;
            }
            // Store invalid index in case its a miss
            else if (!set[i].valid) {
                invalid_idx = i;
                found_invalid = 1;
            }
            // Store lru index in case there's no invalid slot
            else if (set[i].valid) {
                if (set[i].last_used < lru) {
                    lru = set[i].last_used;
                    lru_idx = i;
                }
            }
        }
        
        if (hit_flag) {
            free(lineptr);
            lineptr = NULL;
            n = 0;
        };

        if (found_invalid) {
            printf("Miss\n");
            set[invalid_idx].valid = 1;
            set[invalid_idx].tag = tag;
            set[invalid_idx].last_used = time(NULL);
        } 

        // Eviction
        else {
            printf("Eviction\n");
            set[lru_idx].valid = 1;
            set[lru_idx].tag = tag;
            set[lru_idx].last_used = time(NULL);
        }

        free(lineptr);
        lineptr = NULL;
        n = 0;
    }
    printf("---------------------------------\n");

    free(lineptr);
    free(C);
    fclose(f);
    printSummary(hits, misses, evictions);
    return 0;
}
