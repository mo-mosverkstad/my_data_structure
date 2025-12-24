struct linked_queue;
struct linked_queue *linked_queue_create();
void linked_queue_destroy(struct linked_queue *queue);
void linked_queue_enqueue(struct linked_queue *queue, const void *item);
const void *linked_queue_dequeue(struct linked_queue *queue);
