import unittest
from my_list import my_linked_list

class Test_linked_list(unittest.TestCase):
    def setUp(self):
        self.my_linked_list_obj = my_linked_list()
        self.my_linked_list_obj.append(0)
        self.my_linked_list_obj.append(1)
        self.my_linked_list_obj.append(2)
        self.assertEqual(len(self.my_linked_list_obj), 3)
        self.assertTrue(self.__compare_list([0,1,2]))

    def __compare_list(self, expected_results):
        if len(self.my_linked_list_obj) != len(expected_results): return False
        for i in range(len(self.my_linked_list_obj)):
            if self.my_linked_list_obj[i] != expected_results[i]:
                return False
        return True

    def test_get_set(self):
        for i in range(len(self.my_linked_list_obj)):
            self.my_linked_list_obj[i] = self.my_linked_list_obj[i] + 10
        self.assertTrue(self.__compare_list([10,11,12]))

    def test_append(self):
        self.my_linked_list_obj.append(3)
        self.my_linked_list_obj.append(4)
        self.assertTrue(self.__compare_list([0,1,2,3,4]))

    def test_insert(self):
        self.my_linked_list_obj.insert(2,12)
        self.assertTrue(self.__compare_list([0,1,12,2]))

        self.my_linked_list_obj.insert(1,11)
        self.assertTrue(self.__compare_list([0,11,1,12,2]))

        self.my_linked_list_obj.insert(0,10)
        self.assertTrue(self.__compare_list([10,0,11,1,12,2]))

        self.my_linked_list_obj.insert(3,13)
        self.assertTrue(self.__compare_list([10,0,11,13,1,12,2]))

        try:
            self.my_linked_list_obj.insert(7,17)
            self.fail()
        except IndexError:
            self.assertTrue(True)
        self.assertTrue(self.__compare_list([10,0,11,13,1,12,2]))

    def test_delete(self):
        del self.my_linked_list_obj[1]
        self.assertTrue(self.__compare_list([0,2]))

        del self.my_linked_list_obj[1]
        self.assertTrue(self.__compare_list([0]))

        del self.my_linked_list_obj[0]
        self.assertTrue(self.__compare_list([]))



if __name__ == '__main__':
    unittest.main()
