#!/usr/bin/env python

class Node:
    def __init__(self, value):
        self.value = value
        self.next  = None

    """
    def __str__(self):
        return str(self.value)
    """

class my_linked_list:
    def __init__(self):
        self.head = None
        self.tail = None
        self.length = 0

    def append(self, value):
        node = Node(value)
        if self.tail != None:
            self.tail.next = node
        else:
            self.head = node
        self.tail = node
        self.length += 1

    def get(self, index):
        current_index = 0
        current_node = self.head
        while current_node != None and current_index < index:
            current_node = current_node.next
            current_index = current_index + 1
        return current_node if current_index == index else None

    def __check_index__(self, index):
        if type(index) != int:
            raise IndexError("Index is not an integer")
        elif index >= self.length:
            raise IndexError("Link list out of range (over link list length)")
        elif index < 0:
            raise IndexError("Link list out of range (negative index)")
        else:
            pass

    def insert(self, index, value):
        self.__check_index__(index)
        print("Inserting index", index, "with value", value)
        node = Node(value)
        if index == 0:
            node.next = self.head
            self.head = node
        else:
            previous_node = self.get(index-1)
            node.next = previous_node.next
            previous_node.next = node
        self.length += 1


    def __getitem__(self, index):
        self.__check_index__(index)
        return self.get(index).value

    def __setitem__(self, index, value):
        self.__check_index__(index)
        self.get(index).value = value

    def __delitem__(self, index):
        self.__check_index__(index)
        if self.length == 1:
            self.head = None
            self.tail = None
            self.length = 0
        else:
            previous_node = self.get(index-1)
            current_node = previous_node.next
            previous_node.next = previous_node.next.next
            current_node.next = None
            self.length = self.length - 1

    def __len__(self):
        return self.length

    def __repr__(self):
        node = self.head
        in_middle = True
        result = "my_linked_list(" + str(self.length) + ")["
        while in_middle:
            result = result + node.value + ", "
            node = node.next
            if node == None:
                in_middle = False
        return result[:-2] + "]"
