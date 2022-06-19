from my_list import *
from my_queue_stack import *
from my_queue_stack.my_array_queue import my_array_queue

"""
al = my_linear_list(8)
al.append("aa")
print(al.array)

al.append("bb")
al.append("cc")
al.append("dd")
al.append("ee")
print(al.__dict__)
al.insert(1, "1")
print(al.__dict__)
al.insert(4, "41")
print(al.__dict__)
al.insert(4, "42")
print(al.__dict__)

del al[2]
print(al.__dict__)

del al[3]
print(al.__dict__)
"""


"""
al.insert(4, "43")
print(al.__dict__)
"""

"""
cl = my_linked_list()
cl.append("aa")
cl.append("bbb")
cl.append("cc")
cl.append("dd")
cl.append("eee")
cl.append("ff")
print(cl)
print(cl.get(3).value)
print(cl.get(1000) == None)

cl.insert(0, "a1")
print(cl)

cl.insert(2, "a1")
print(cl)

del cl[3]
print(cl)

print(cl[3])
cl[4] = "a4"

print(cl)

try:
    cl[1000] = 1
    print('Everything is ok, continue.')
except IndexError:
    raise TypeError('I think you are wrong, it should be type error')
"""

"""
q = my_queue()
q.enqueue("aaa")
q.enqueue("bbbbb")
q.enqueue("ccc")
q.enqueue("ddddd")
q.enqueue("eeeee")
print(q)
q.dequeue()
q.dequeue()
print(q)
print(q.front(), q.rear())
print(q)
"""

"""
s = my_stack()
s.push(2)
s.push(9)
s.push(11)
print(s.peek())
s.pop()
print(s.peek())
s.pop()
print(s.peek())
"""

aq = my_array_queue(5)

aq.enqueue("First item")
aq.enqueue("Second item")
aq.enqueue("Third item")
aq.enqueue("Fourth item")
aq.enqueue("Fifth item")

print(aq)
print("Is empty", aq.is_empty(), ", is full", aq.is_full())

print(aq.dequeue())
print(aq.dequeue())
print(aq.dequeue())
aq.enqueue("Sixth item")
#aq.enqueue("Seventh item")

print(aq)
print("Is empty", aq.is_empty(), ", is full", aq.is_full())
print(aq.front(), aq.rear())
print(len(aq))