#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

struct queue {
    pthread_cond_t cond_not_full;
    pthread_cond_t cond_not_empty;
    pthread_mutex_t mutex;
    uint32_t const buffer_size;
    uint32_t const data_size;
    uint32_t head;
    uint32_t tail;
    uint8_t * const buffer;
};


#define QUEUE_INIT(a,b,c) {PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, (a), (b), 0, 0, (c)}

void queue_push(struct queue *queue, uint32_t datatype, void * data);
void queue_pop(struct queue *queue, uint32_t* datatype, void * data);
