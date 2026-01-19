/*
int main() {
    stack *stk = stack(4);
    int n = 10;
    for(int i = 0; i < n; i++) {
        push(stk, i+30);
    }
    for(int i = 0; i < stk->top; i++) {
        printf("stack[%d] : %d\n", i, stk->array[i]);
    }
    int val = pop(stk);
    while(val != 0) { // assuming 0 is returned when the stack is empty
        printf("pop : %d\n", val);
        val = pop(stk);
    }
}
*/

int main() {
    stack *stk = stack();
    printf("HP-35 pocket calculator\n");
    int n = 10;
    char *buffer = malloc(n);
    bool running = true;
    while(running) {
        printf(" > ");
        fgetc(buffer, n, stdin);
    if (strcmp(buffer, "\n") == 0) {
        running = false;
    }
    else if (strcmp(buffer, "+\n") == 0) {
        int a = pop(stk);
        int b = pop(stk);
        push(stk, a+b);
    }
    else
        // add something here???...
    } else {
        int val = atoi(buffer);
    push(stk, val);
    }
}
printf("the result is: %d\n\n", pop(stk));
printf("I love reversed polish notation, don't you?\n");
}
