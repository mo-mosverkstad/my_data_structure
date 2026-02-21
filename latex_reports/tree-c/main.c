#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <limits.h>

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
    // Freeing the tree means freeing all nodes in it.
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

/* Iterative BST insertion - O(log N) average, O(N) worst case
 * Traverses tree to find insertion point, tracking parent and direction */
void add(tree *tr, int value){
    bool left = true;  /* Track whether to insert as left or right child */
    node* parent = NULL;
    node* nd = tr->root;
    
    /* Find insertion point */
    while (nd != NULL){
        if (value < nd->value){
            parent = nd;
            nd = nd->left;
            left = true;  /* CRITICAL: Must set to true when going left */
        }
        else if (value > nd->value){
            parent = nd;
            nd = nd->right;
            left = false;
        }
        else{
            return;  /* Value already exists */
        }
    }
    
    /* Insert new node */
    node* new_node = construct_node(value);
    if (parent == NULL){
        tr->root = new_node;  /* Tree was empty */
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


/* Iterative BST lookup - O(log N) average, O(N) worst case
 * Returns true if value exists in tree, false otherwise */
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

bool binsearch_array(const int *arr, size_t n, int key) {
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

static long calculate_time(void (*work_func)(void*), void *context, size_t repeat, void (*cleanup_func)(void*)) {
    struct timespec t0, t1;
    long min_time = LONG_MAX;
    for (size_t count = 0; count < repeat; ++count) {
        clock_gettime(CLOCK_MONOTONIC, &t0);
        work_func(context);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        long elapsed = nanoseconds(t0, t1);
        if (elapsed < min_time) min_time = elapsed;
        if (cleanup_func) cleanup_func(context);
    }
    return min_time;
}

typedef struct {
    tree *tr;
    int *vals;
    size_t N;
    void (*add_func)(tree*, int);
} build_context;

typedef struct {
    const tree *tr;
    int *vals;
    size_t N;
} lookup_context;

typedef struct {
    const int *arr_sorted;
    int *vals;
    size_t N;
} binsearch_context;

static void do_build(void *ctx) {
    build_context *bc = (build_context*)ctx;
    for (size_t i = 0; i < bc->N; ++i)
        bc->add_func(bc->tr, bc->vals[i]);
}

static void cleanup_build(void *ctx) {
    build_context *bc = (build_context*)ctx;
    free_node(bc->tr->root);
    bc->tr->root = NULL;
}

static void do_lookup(void *ctx) {
    lookup_context *lc = (lookup_context*)ctx;
    for (size_t i = 0; i < lc->N; ++i)
        tree_lookup_iterative(lc->tr, lc->vals[i]);
}

static void do_binsearch(void *ctx) {
    for (size_t i = 0; i < bc->N; ++i)
        binsearch_array(bc->arr_sorted, bc->N, bc->vals[i]);
}

static long benchmark_build(tree *tr, int *vals, size_t N, size_t repeat, void (*add_func)(tree*, int)) {
    build_context ctx = {tr, vals, N, add_func};
    return calculate_time(do_build, &ctx, repeat, cleanup_build);
}

static long benchmark_lookup(const tree *tr, int *vals, size_t N, size_t repeat) {
    lookup_context ctx = {tr, vals, N};
    return calculate_time(do_lookup, &ctx, repeat, NULL);
}

static long benchmark_binsearch(const int *arr_sorted, int *vals, size_t N, size_t repeat) {
    binsearch_context ctx = {arr_sorted, vals, N};
    return calculate_time(do_binsearch, &ctx, repeat, NULL);
}

static void run_benchmark(void) {
    size_t sizes[] = {1024, 2048, 4096, 8192, 16384, 32768, 65535, 131072};
    size_t nsizes = sizeof(sizes) / sizeof(sizes[0]);
    size_t repeat = 1000;

/*
    printf("=== BUILD BENCHMARK ===\n");
    printf("Columns: N | build_ns(rec) | build_ns(iter)\n");

    for (size_t s = 0; s < nsizes; ++s) {
        size_t N = sizes[s];

        int *vals = make_range(N);
        shuffle(vals, N);

        // --- Build using recursive add ---
        tree *tr_rec = construct_tree();
        long build_rec_ns = benchmark_build(tr_rec, vals, N, repeat, recursive_add);

        // --- Build using iterative add ---
        tree *tr_it = construct_tree();
        long build_it_ns = benchmark_build(tr_it, vals, N, repeat, add);

        printf("%7zu | %13ld | %14ld\n", N, build_rec_ns, build_it_ns);

        free_tree(tr_rec);
        free_tree(tr_it);
        free(vals);
    }*/

    printf("\n=== LOOKUP BENCHMARK ===\n");
    printf("Columns: N | lookup_ns(BST) | lookup_ns(binsearch)\n");

    for (size_t s = 0; s < nsizes; ++s) {
        size_t N = sizes[s];

        /* Create shuffled insertion order to build balanced BST */
        int *vals = make_range(N);
        shuffle(vals, N);

        /* Build BST with shuffled values for balanced tree */
        tree *tr_it = construct_tree();
        for (size_t i = 0; i < N; ++i)
            add(tr_it, vals[i]);

        /* Create sorted array for binary search comparison */
        int *arr_sorted = (int *)malloc(N * sizeof(int));
        if (!arr_sorted) { perror("malloc sorted"); exit(EXIT_FAILURE); }
        for (size_t i = 0; i < N; ++i) arr_sorted[i] = (int)i;
        qsort(arr_sorted, N, sizeof(int), cmp_int);

        /* Create random search keys to ensure O(log N) behavior
         * (searching in sorted order would cause O(N) BST traversal) */
        int *search_keys = make_range(N);
        shuffle(search_keys, N);

        /* Benchmark BST lookup: O(log N) expected */
        long lookup_bst_ns = benchmark_lookup(tr_it, search_keys, N, repeat);

        /* Benchmark array binary search: O(log N) expected */
        long lookup_arr_ns = benchmark_binsearch(arr_sorted, search_keys, N, repeat);

        printf("%7zu | %15ld | %20ld\n", N, lookup_bst_ns, lookup_arr_ns);
			   
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
        free(search_keys);
        free(arr_sorted);
        free_tree(tr_it);
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