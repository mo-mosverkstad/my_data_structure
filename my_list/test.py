#!/usr/bin/env python

from myList import MyList

l = MyList()
l.append(1)
l.append('Steffan')
l.append(5)
l.append('Johan')
print(f'{l}')

print

print(f'{l.get(0)}')
print(f'{l.get(3)}')
print(f'{l.get(-1)}')
print(f'{l.get(8)}')

print

l.insert(1, 'Martin')
l.insert(4, 'Peter')
print(f'{l}')

print(f'length : {l.length}')

print
print(f'{l.index("1")}')

print(f'{l[1]}')
l[1] = 'Mike'
print(f'{l[1]}')
print(f'{l}')