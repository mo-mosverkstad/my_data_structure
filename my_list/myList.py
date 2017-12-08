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

    def append(self, value):
        n = Node(value)
        if self.tail != None: self.tail.next = n
        self.tail = n
        if self.head == None: self.head = n

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
        
        

    def __str__(self):
        n = self.head
        i = 0
        strValue = ''
        while n != None:
            strValue += str(i) + ': ' + str(n) + '\n'
            n = n.next
            i += 1
        return strValue
        
