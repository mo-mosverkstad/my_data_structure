#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

typedef struct node {
    int value;
    struct node *right;
    struct node *left;
} node;

typedef struct tree {
    node *root;
} tree;

node *construct_node(int val) {
    node *nd = (node*) malloc(sizeof(node));
    nd->value = val;
    nd->left = NULL;
    nd->right = NULL;
    return nd;
}

void free_node(node *nd) {
    // Freeing the nodes could be done recursively.
    if (nd != NULL) {
        free_node(nd->left);
        free_node(nd->right);
        free(nd);
    }
}

tree *construct_tree() {
    tree *tr = (tree*) malloc(sizeof(tree));
    tr->root = NULL;
    return tr;
}

void free_tree(tree *tr) {
    if (tr != NULL){
        free_node(tr->root);
        free(tr);
    }
}

node* add_node(node *nd, int value){
    // helper function (recursive)
    if (nd == NULL){
        return construct_node(value);
    }
    if (value < nd->value){
        nd->left = add_node(nd->left, value);
    }
    else if (value > nd->value){
        nd->right = add_node(nd->right, value);
    }
    return nd;
}

void recursive_add(tree *tr, int value){
    // recursive
    tr->root = add_node(tr->root, value);
}

void add(tree *tr, int value){
    // TODO: implement the non-recursive approach
    bool left = true;
    node* parent = NULL;
    node* nd = tr->root;
    while (nd != NULL){
        if (value < nd->value){
            parent = nd;
            nd = nd->left;
        }
        else if (value > nd->value){
            parent = nd;
            nd = nd->right;
            left = false;
        }
        else{
            return;
        }
    }
    node* new_node = construct_node(value);
    if (parent == NULL){
        tr->root = new_node;
    }
    else{
        if (left){
            parent->left = new_node;
        }
        else{
            parent->right = new_node;
        }        
    }
}

bool lookup_node(node *nd, int value){
    if (nd == NULL) return false;
    if (value < nd->value) return lookup_node(nd->left, value);
    else if (value > nd->value) return lookup_node(nd->right, value);
    return true;
}

bool recursive_lookup(tree *tr, int value){
    return lookup_node(tr->root, value);
}


bool tree_lookup_iterative(const tree *tr, int value) {
    const node *nd = tr->root;
    while (nd != NULL) {
        if (value == nd->value) return true;
        nd = (value < nd->value) ? nd->left : nd->right;
    }
    return false;
}

static void print(node *nd) {
    if (nd != NULL) {
        print(nd->left);
        printf("%d ", nd->value);
        print(nd->right);
    }
}
void print_tree(tree *tr) {
    if (tr->root != NULL)
        print(tr->root);
    printf("\n");
}

/* --------------------- In-order using an explicit stack ------------------- */


/* -- Dynamic stack implementation -- */

typedef struct stack {
    node **elements;
    size_t capacity;
    size_t top; /* index of next free slot */
} stack;

static stack *stack_create() {
    stack *stk = (stack *) malloc(sizeof(stack));
    if (stk == NULL) {
        perror("Malloc stack control block failure");
        exit(EXIT_FAILURE);
    }
    stk->capacity = 16;
    stk->top = 0;
    stk->elements = (node **) malloc(stk->capacity * sizeof(node *));
    if (stk->elements == NULL) {
        perror("Malloc array elements failure");
        exit(EXIT_FAILURE);
    }
    return stk;
}

static void stack_free(stack *stk) {
    if (stk != NULL) {
        free(stk->elements);
        free(stk);
    }
}

static void stack_push(stack *stk, node *nd) {
    if (stk->top == stk->capacity) {
        // Grow the stack by doubling its capacity
        size_t new_capacity = stk->capacity * 2;
        node **new_elements = (node **) realloc(stk->elements, new_capacity * sizeof(node *));
        if (new_elements == NULL) {
            perror("Stack growth by realloc failure");
            exit(EXIT_FAILURE);
        }
        stk->elements = new_elements;
        stk->capacity = new_capacity;
    }
    stk->elements[stk->top++] = nd;
}

static bool stack_empty(const stack *stk) {
    return stk->top == 0;
}

static node *stack_pop(stack *stk) {
    if (stk->top == 0) return NULL;
    return stk->elements[--stk->top];
}


/* Implementation of inorder print using explicit stack */
/* Invariant per assignment:
 * "Left subtree of a node popped from the stack has been printed; node value
 * has not; right subtree has not." We push the path down-left; on pop, print
 * node, then proceed to its right branch and again push down-left path.       */

void tree_print_inorder_stack(const tree *tr) {
    stack *stk = stack_create();
    node *nd = tr->root;

    /* move to leftmost path initially */
    while (nd != NULL) {
        stack_push(stk, nd);
        nd = nd->left;
    }

    while (!stack_empty(stk)) {
        node *nd = stack_pop(stk);
        printf("%d ", nd->value);  /* left handled, now visit node */

        /* then handle right subtree: push its left path */
        node *r = nd->right;
        while (r != NULL) {
            stack_push(stk, r);
            r = r->left;
        }
    }
    stack_free(stk);
    printf("\n");
}










/* ------------------------------- Benchmark -------------------------------- */

static int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

static int *make_range(size_t n) {
    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) { perror("malloc range"); exit(EXIT_FAILURE); }
    for (size_t i = 0; i < n; ++i) arr[i] = (int)i;
    return arr;
}

static void shuffle(int *arr, size_t n) {
    for (size_t i = n; i > 1; --i) {
        size_t j = (size_t) (rand() % i);
        int tmp = arr[i - 1];
        arr[i - 1] = arr[j];
        arr[j] = tmp;
    }
}

static long nanoseconds(struct timespec a, struct timespec b) {
    long sec = (long) (b.tv_sec - a.tv_sec);
    long nsec = (long) (b.tv_nsec - a.tv_nsec);
    return sec * 1000000000L + nsec;
}

static bool binsearch_array(const int *arr, size_t n, int key) {
    size_t lo = 0, hi = n;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        int v = arr[mid];
        if (key == v) return true;
        if (key < v) hi = mid;
        else lo = mid + 1;
    }
    return false;
}

static void run_benchmark(void) {
    size_t sizes[] = {1024, 2048, 4096, 8192, 16384, 32768, 65535, 131072};
    size_t nsizes = sizeof(sizes) / sizeof(sizes[0]);
    size_t repeat = 16;

    printf("Benchmark: shuffled inserts into BST vs. array binary search\n");
    printf("Columns: N | build_ms(rec) | build_ms(iter) | lookup_ms(BST) | lookup_ms(binsearch)\n");

    for (size_t s = 0; s < nsizes; ++s) {
        size_t N = sizes[s];

        int *vals = make_range(N);
        shuffle(vals, N); /* avoid degeneracy per assignment guidance */

        /* --- Build using recursive add --- */
        tree *tr_rec = construct_tree();
        struct timespec t0, t1;

        clock_gettime(CLOCK_MONOTONIC, &t0);
        for (size_t count = 0; count < repeat; ++count)
            for (size_t i = 0; i < N; ++i) 
                recursive_add(tr_rec, vals[i]);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        long build_rec_ms = nanoseconds(t0, t1) / repeat;

        /* --- Build using iterative add --- */
        tree *tr_it = construct_tree();
        clock_gettime(CLOCK_MONOTONIC, &t0);
		for (size_t count = 0; count < repeat; ++count)
            for (size_t i = 0; i < N; ++i)
                add(tr_it, vals[i]);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        long build_it_ms = nanoseconds(t0, t1) / repeat;

        /* --- Lookup timings on BST (iterative) --- */
        const size_t Q = N; /* look up all values */
        clock_gettime(CLOCK_MONOTONIC, &t0);
        volatile size_t hits_bst = 0;
		for (size_t count = 0; count < repeat; ++count){
            for (size_t i = 0; i < Q; ++i) {
                hits_bst += tree_lookup_iterative(tr_it, vals[i]);
            }
		}
        clock_gettime(CLOCK_MONOTONIC, &t1);
        long lookup_bst_ms = nanoseconds(t0, t1) / repeat;

        /* --- Prepare sorted array + binary search timings --- */
        int *arr_sorted = (int *)malloc(N * sizeof(int));
        if (!arr_sorted) { perror("malloc sorted"); exit(EXIT_FAILURE); }
        memcpy(arr_sorted, vals, N * sizeof(int));
        qsort(arr_sorted, N, sizeof(int), cmp_int);

        clock_gettime(CLOCK_MONOTONIC, &t0);
        size_t hits_arr = 0;
		for (size_t count = 0; count < repeat; ++count){
            for (size_t i = 0; i < Q; ++i) {
                hits_arr += binsearch_array(arr_sorted, N, vals[i]);
            }
		}
        clock_gettime(CLOCK_MONOTONIC, &t1);
        long lookup_arr_ms = nanoseconds(t0, t1) / repeat;

        printf("%7zu | %ld | %ld | %ld | %ld\n", N, build_rec_ms, build_it_ms, lookup_bst_ms, lookup_arr_ms);
			   
        /* For small trees, visually verify traversal order matches (sorted) */
        if (N <= 50) {
            printf("In-order (recursive): ");
            print_tree(tr_it);
            printf("In-order (stack)    : ");
            tree_print_inorder_stack(tr_it);
            printf("\n");
        }

        /* Clean up */
        free(vals);
        free(arr_sorted);
        free_tree(tr_rec);
        free_tree(tr_it);

        /* Notes (not printed): For ordered inserts, height ~ N, so O(N) lookup.
           Shuffled inserts give average height ~ O(log N) (but still unbalanced). */
    }
}

/* ---------------------------------- main ---------------------------------- */

int main() {
    /* Make timings repeatable-ish; change seed for different runs */
    srand(123456u);

    run_benchmark();
    return 0;
}

/*
int main(){
    tree *myTree = construct_tree();

    add(myTree, 5);
    add(myTree, 3);
    add(myTree, 7);
    add(myTree, 4);
    add(myTree, 6);

    print_tree(myTree);

    printf("Lookup 4: %d\n", recursive_lookup(myTree, 4));
    printf("Lookup 10: %d\n", recursive_lookup(myTree, 10));
    
    tree_print_inorder_stack(myTree);

    free_tree(myTree);
    return 0;
}
*/