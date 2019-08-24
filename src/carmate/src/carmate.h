#pragma once

#include <infrastructure/queue.h>
#include <system/types.h>
#include <pthread.h>

extern void loop_gps_reader();
extern void loop_tracker();
extern void loop_clock();
extern void loop_syncer();

#define QUEUE_SYNCER_BUFFER_SIZE 1*1024
#define QUEUE_TRACKER_BUFFER_SIZE 1*1024

static uint8_t queue_syncer_buffer[QUEUE_SYNCER_BUFFER_SIZE];
static uint8_t queue_tracker_buffer[QUEUE_TRACKER_BUFFER_SIZE];

#define QUEUE_SYNCER_ELEMENT_SIZE 1
#define QUEUE_TRACKER_ELEMENT_SIZE sizeof(struct gps_info)

struct queue queue_syncer = QUEUE_INIT(QUEUE_SYNCER_BUFFER_SIZE,QUEUE_SYNCER_ELEMENT_SIZE,queue_syncer_buffer);
struct queue queue_tracker = QUEUE_INIT(QUEUE_TRACKER_BUFFER_SIZE,QUEUE_TRACKER_ELEMENT_SIZE,queue_syncer_buffer);

struct queue * queue_gps_reader_gps_update = &queue_tracker;
struct queue * queue_tracker_sync_signal = &queue_syncer;
struct queue * queue_clock_minute_signal = &queue_syncer;

static pthread_t gps_reader_thread;
static pthread_t tracker_thread;
static pthread_t clock_thread;
static pthread_t syncer_thread;
