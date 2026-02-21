void print(tree *tr) {
stack *stk = create_stack();
node *cur = tr->root;
// move to the leftmost node
while(cur != NULL) {
// print value of node
if( cur->right != NULL) {
// move to the leftmost node, push nodes as you go
} else {
// pop a node from the stack
}
}
}
}