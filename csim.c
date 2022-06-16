#include "cachelab.h"
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>


csim_stats_t *make_csim_stats(unsigned long hits, unsigned long misses,
                              unsigned long evictions,unsigned long dirty_bytes,
                              unsigned long dirty_evictions) {
    csim_stats_t *new = malloc(sizeof(csim_stats_t));
    new->hits = hits;
    new->misses = misses;
    new->evictions = evictions;
    new->dirty_bytes = dirty_bytes;
    new->dirty_eviction = dirty_eviction;
    return new;
}

typedef struct {
    unsigned long called;      //to record the number of times the line is used
    unsigned long v;
    unsigned long d;
    unsigned long tag;
    line_t *next
} line_t;

typedef struct {
    unsigned long set_index;
    line_t *line;
    set_t *next;
} set_t;

typedef struct {
    unsigned long set_num;
    unsigned long set_bit;
    unsigned long line_num;
    unsigned long block_bit;
    set_t *head_set;
} cache_t

cache_t create_cache(unsigned long s, unsigned long E, unsigned long b) {
    unsigned long S = 1 << s;
    cache_t *cache = malloc(sizeof(cache_t));      //creat the cache
    cache->set_num = S;
    cache->set_bit = s;
    cache->line_num = E;
    cache->block_bit = b;
    set_t *set_h = malloc(sizeof(set_t));     //create the first set
    cache->head_set = set_h;
    set_t *cur = cache->head_set;
    //loop through S to create S sets
    for (unsigned long i = 0; i < S; i++) {
        cur->set_index = i;
        cur->line = malloc(sizeof(line_t));
        line_head = cur->line;
        //loop through E to create E ways in each set
        for (unsigned long j = 0; j < E; j++) {
            line_head->called = 0;
            line_head->v = 0;
            line_head->d = 0;
            line_head->tag = 0;
            if (j != E-1) {
                line_t *line_next = malloc(sizeof(line_t));
                line_head->next = line_next;
                line_head = line_head->next;
            } else line_head->next = NULL;
        }
        if (i != S-1) {
            set_t *next = malloc(sizeof(set_t));
            cur->next = next;
            cur = cur->next;
        } else cur->next = NULL;
    }
    return cache;
}

void free_cache(cache_t *cache){
    set_t *cur = cache->head_set;
    cache->set_num = 0;
    cache->set->bit = 0;
    cache->line_num = 0;
    cache->block_bit = 0;
    set_t *prev = cur;
    //free all the sets in cache
    while (cur != NULL) {
        cur->set_index = 0;
        cur_line = cur->line;
        prev_line = cur_line;
        //free all the lines in each set
        while (cur_line != NULL) {
            cur_line->v = 0;
            cur_line->tag = 0;
            cur_line->d = 0;
            cur_line->called = 0;
            cur_line = cur_line->next;
            free(prev_line);
            prev_line = cur_line;
        }
        cur = cur->next;
        free(prev);
        prev = cur;
    }
    free(cache);
}

void calculate_cache(csim_stats_t *stats, set_t *cache, char c, 
                     unsigned long address) {
    //find out the set number
    unsigned long mask_set = 0;
    for (unsigned long i = 0; i < cache->set_bit; i++) {
        mask_set = mask_set << 1 + 1;
    }
    mask_set = mask_set << cache->block_bit;
    unsigned long s = address & mask_set;

    //find out the tag value
    unsigned long tag_bit = cache->block_bit + cache->set_bit;
    unsigned long mask_tag = 0xFFFFFFFFFFFFFFFF << tag->bit;
    unsigned long t = address & mask_tag;

    //find out the line in the cache
    set = cache->head_set;
    while (set->set_index != s) set = set->next;
    bool hit = false;
    line *cur_line = set->line;
    while (cur_line != NULL) {
        //hit
        if (cur_line->v == 1 && cur_line->tag == t) {
            hit = true;
            cure_line->called ++;
            stats->hits ++;
            break;
        }
        cur_line = cur_line->next;
    }
    //miss
    if (!hit) {
        stats->misses ++;
        if (c == 'L') {
            
        } else if (c == 'S') {

        } else return;
    }
}
fopen()
fscanf()
int main(int argc, char *argv[]) {
    size_t s = 0;
    size_t E = 0;
    size_t b = 0;
    while ((opt = getopt(argc, argv, ":hvs:E:b:t:")) != -1) {
        switch(opt) {
            case 'h':
                break;
            case 'v':
                break;
            case 's':
                break;
            case 'E':
                break;
            case 'b':
                break;
            case 't':
                FILE *new = fopen(optarg, 'r');
                while (fscanf(new, "%c %lx,%lx", c, address, size) != EOF) {
                    //calculate
                }
                break;
        }

    }

}