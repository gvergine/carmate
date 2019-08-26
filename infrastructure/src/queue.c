#include <infrastructure/queue.h>
#include <string.h>

#define QUEUE_IS_FULL (q->tail == (q->head - 1))
#define QUEUE_IS_EMPTY (q->tail == q->head)

void queue_push(struct queue *q, uint32_t datatype, void * data)
{
    pthread_mutex_lock( &q->mutex );
    
    while(QUEUE_IS_FULL)
    {
        q->cond_not_full_waiters++;
        pthread_cond_wait(&q->cond_not_full, &q->mutex);
        q->cond_not_full_waiters--; 
    }        

    uint64_t offset = q->tail*(q->data_size+4);
    memcpy(q->buffer+offset,&datatype,4);
    memcpy(q->buffer+offset+4,data,q->data_size);
    q->tail = (q->tail + 1) % (q->buffer_size/(q->data_size+4));

    if (q->cond_not_empty_waiters) pthread_cond_signal(&q->cond_not_empty);

    pthread_mutex_unlock( &q->mutex );
}

void queue_pop(struct queue *q, uint32_t * datatype,  void * data)
{
    pthread_mutex_lock( &q->mutex );

    while(QUEUE_IS_EMPTY)
    {
        q->cond_not_empty_waiters++;
        pthread_cond_wait(&q->cond_not_empty, &q->mutex);
        q->cond_not_empty_waiters--; 
    }
    
    uint64_t offset = q->head*(q->data_size+4);
    memcpy(datatype,q->buffer+offset,4);
    memcpy(data,q->buffer+offset+4,q->data_size);
    q->head = (q->head + 1) % (q->buffer_size/(q->data_size+4));

    if (q->cond_not_full_waiters) pthread_cond_signal(&q->cond_not_full);

    pthread_mutex_unlock( &q->mutex );
}
