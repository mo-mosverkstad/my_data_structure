#include <stdbool.h>

struct array_queue;
struct array_queue *array_queue_create();
void array_queue_destroy(struct array_queue *queue);
bool array_queue_is_empty(struct array_queue *queue);
bool array_queue_is_full(struct array_queue *queue);
void array_queue_enqueue(struct array_queue *queue, void *item);
void *array_queue_dequeue(struct array_queue *queue);