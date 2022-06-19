from my_list import *

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

raise Exception("I am tired, I need a rest.")

try:
    cl[1000] = 1
    print('Everything is ok, continue.')
except IndexError:
    raise TypeError('I think you are wrong, it should be type error')