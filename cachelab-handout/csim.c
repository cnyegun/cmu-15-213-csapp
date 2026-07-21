#define _POSIX_C_SOURCE 200809L
#include "cachelab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

static int verbose = 0;
static unsigned long clk = 0;
#define VERB(...) do { if (verbose) printf(__VA_ARGS__); } while (0)

typedef struct {
    int valid;
    unsigned long tag;
    unsigned long last_used;
} cache_line_t;

int main(int argc, char *argv[])
{
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
                S = 1 << s;
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                B = 1 << b;
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
    (void)help;

    t = m - (s + b);

    if (S == -1 || E == -1 || B == -1 || trace_file == NULL) {
        printf("Usage: %s [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Init the cache array
     * 2D array of sets and lines
     */

    cache_line_t *C = calloc(sizeof(cache_line_t), S * E);

    int hits = 0, misses = 0, evictions = 0;
    FILE *f = fopen(trace_file, "r");

    char *lineptr = NULL;
    size_t n = 0;
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
        
        VERB("%c %lx,%d ", op, addr, bytes);

        /* STEP 2: Calculating the cache index from the given address 
         * Using the address, divide its bit pattern into segment,
         * first are t bits for Tag,
         * then s bits for Set index
         * then b bits for Block offset
         */
        unsigned long tag = addr >> (s + b);
        unsigned long set_index = (addr << t) >> (t + b);
        // unsigned long block_starts_at = addr & ~((1UL << b) - 1);

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
        unsigned long lru = ++clk;

        for (int i = 0; i < E; i++) {
            // Hit case
            if (set[i].valid && set[i].tag == tag) {
                hit_flag = 1;
                set[i].last_used = ++clk;
                if (op == 'M') {
                    VERB("hit ");
                    hits++;
                }
                hits++;
                VERB("hit\n");
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
            continue;
        };

        if (found_invalid) {
            misses++;
            set[invalid_idx].valid = 1;
            set[invalid_idx].tag = tag;
            set[invalid_idx].last_used = ++clk;
            if (op == 'M') {
                VERB("miss hit\n");
                hits++;
            }
            else {
                VERB("miss\n");
            }
        } 

        // Eviction
        else {
            misses++;
            evictions++;
            set[lru_idx].valid = 1;
            set[lru_idx].tag = tag;
            set[lru_idx].last_used = ++clk;
            if (op == 'M') {
                VERB("miss eviction hit\n");
                hits++;
            }
            else {
                VERB("miss eviction\n");
            }

        }
    }

    free(lineptr);
    free(C);
    fclose(f);
    printSummary(hits, misses, evictions);
    return 0;
}
