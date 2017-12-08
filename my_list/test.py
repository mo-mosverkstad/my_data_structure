#!/usr/bin/env python

from myList import MyList

l = MyList()
l.append(1)
l.append('Steffan')
l.append(5)
l.append('Johan')
print str(l)

print

print l.get(0)
print l.get(3)
print l.get(-1)
print l.get(8)

print

l.insert(1, 'Martin')
l.insert(4, 'Peter')
print str(l)
