#pragma once
#include "arrayqueue.h"

typedef struct sequence{
    arrayqueue* queue;
} sequence;

sequence *create_sequence(tree *tr);
int next(sequence *seq);