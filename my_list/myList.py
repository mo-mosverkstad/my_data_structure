#!/usr/bin/env python

class Node:
    def __init__(self, value):
        self.value = value
        self.next  = None

    def __str__(self):
        return str(self.value)

class MyList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.length = 0

    def append(self, value):
        n = Node(value)
        if self.tail != None: self.tail.next = n
        self.tail = n
        if self.head == None: self.head = n
        self.length += 1

    def get(self, index):
        v = self.head
        i = 0
        while i < index and v != None:
            v = v.next
            i += 1
        if i == index: return v.value
        else: return None

    def insert(self, index, value):
        n = Node(value)
        h = self.head
        i = 0
        index = index-1
        while i < index:
            h = h.next
            i += 1
        n.next = h.next
        h.next = n
        self.length += 1

    def index(self, value):
        h = self.head
        i = 0
        while h != None and h.value != value:
            h = h.next
            i += 1
        if h == None: return -1
        elif h.value == value: return i

    def __getitem__(self, index):
        return self.get(index)

    def __setitem__(self, index, value):
        v = self.head
        i = 0
        while i < index and v != None:
            v = v.next
            i += 1
        if i == index: v.value = value

    def __str__(self):
        n = self.head
        i = 0
        strValue = ''
        while n != None:
            strValue += str(i) + ': ' + str(n) + '\n'
            n = n.next
            i += 1
        return strValue
