from .tree_binary_node import tree_binary_node
from my_queue_stack.my_queue import my_queue

class my_binary_tree:

    @staticmethod
    def build_tree(node_value, left = None, right = None) -> tree_binary_node:
        node = tree_binary_node(node_value)
        node.left = left
        node.right = right
        return node

    @staticmethod
    def traverse_in_order(root):
        if not root: return
        print(root.value)
        traverse_in_order(root.left)
        traverse_in_order(root.right)

    @staticmethod
    def traverse_pre_order(root):
        if not root: return
        traverse_pre_order(root.left)
        print(root.value)
        traverse_pre_order(root.right)

    @staticmethod
    def traverse_post_order(root):
        if not root: return
        traverse_post_order(root.left)
        traverse_post_order(root.right)
        print(root.value)

    @staticmethod
    def traverse_width(root):
        traverse_queue = my_queue()
        traverse_queue.enqueue(root)
        while len(traverse_queue) != 0:
            node = traverse_queue.dequeue()
            print(node.value)
            if node.left:
                traverse_queue.enqueue(node.left)
            if node.right:
                traverse_queue.enqueue(node.right)

