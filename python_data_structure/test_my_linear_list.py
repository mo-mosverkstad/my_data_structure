import unittest
from my_list import my_linear_list

class Test_linear_list(unittest.TestCase):
    def setUp(self):
        self.max_size = 10
        self.my_linear_list_obj = my_linear_list(self.max_size)

    def precondition(self):
        self.my_linear_list_obj[0] = 0
        self.my_linear_list_obj[1] = 1
        self.my_linear_list_obj[3] = 3
        self.my_linear_list_obj[2] = 2

    def test_get_set(self):
        self.my_linear_list_obj[0] = 0
        self.assertEqual(self.my_linear_list_obj[0], 0)
        self.assertEqual(len(self.my_linear_list_obj), 1)

        self.my_linear_list_obj[1] = 1
        self.assertEqual(self.my_linear_list_obj[1], 1)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,None,None,None,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 2)

        self.my_linear_list_obj[3] = 3
        self.assertEqual(self.my_linear_list_obj[3], 3)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,None,3,None,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 4)

        self.my_linear_list_obj[2] = 2
        self.assertEqual(self.my_linear_list_obj[2], 2)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,2,3,None,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 4)

    def test_insert_1(self):
        self.precondition()
        self.my_linear_list_obj.insert(2,11)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,11,2,3,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 5)

    def test_insert_2(self):
        self.precondition()
        self.my_linear_list_obj.insert(2,11)
        self.my_linear_list_obj.insert(4,12)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,11,2,12,3,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 6)

    def test_insert_3(self):
        self.precondition()
        self.my_linear_list_obj.insert(2,11)
        self.my_linear_list_obj.insert(4,12)
        try:
            self.my_linear_list_obj.insert(6,13)
            self.assertTrue(False)
        except IndexError:
            self.assertTrue(True)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,11,2,12,3,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 6)

    def test_insert_4(self):
        self.precondition()
        self.my_linear_list_obj.insert(2,11)
        self.my_linear_list_obj.insert(4,12)
        self.my_linear_list_obj.insert(0,14)
        self.assertEqual(self.my_linear_list_obj.array, [14,0,1,11,2,12,3,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 7)

    def test_delete_4(self):
        self.precondition()
        self.my_linear_list_obj.insert(2,11)
        self.my_linear_list_obj.insert(4,12)
        self.my_linear_list_obj.insert(0,14)
        del self.my_linear_list_obj[0]
        self.assertEqual(self.my_linear_list_obj.array, [0,1,11,2,12,3,3,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 6)

    def test_delete_2(self):
        self.precondition()
        self.my_linear_list_obj.insert(2,11)
        self.my_linear_list_obj.insert(4,12)
        self.my_linear_list_obj.insert(0,14)
        del self.my_linear_list_obj[0]
        del self.my_linear_list_obj[4]
        self.assertEqual(self.my_linear_list_obj.array, [0,1,11,2,3,3,3,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 5)

    def test_delete_1(self):
        self.precondition()
        self.my_linear_list_obj.insert(2,11)
        self.my_linear_list_obj.insert(4,12)
        self.my_linear_list_obj.insert(0,14)
        del self.my_linear_list_obj[0]
        del self.my_linear_list_obj[4]
        del self.my_linear_list_obj[2]
        self.assertEqual(self.my_linear_list_obj.array, [0,1,2,3,3,3,3,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 4)

    def test_get_set_out_of_range_1(self):
        try:
            self.my_linear_list_obj[self.max_size] = 21
            self.assertTrue(False)
        except IndexError:
            self.assertTrue(True)
        self.assertEqual(len(self.my_linear_list_obj), 0)

    def test_get_set_out_of_range_2(self):
        try:
            _ = self.my_linear_list_obj[self.max_size]
            self.assertTrue(False)
        except IndexError:
            self.assertTrue(True)
        self.assertEqual(len(self.my_linear_list_obj), 0)

    def test_insert_abnormal_1(self):
        self.precondition()
        try:
            self.my_linear_list_obj.insert(7,7)
            self.assertTrue(False)
        except IndexError:
            self.assertTrue(True)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,2,3,None,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 4)

    def test_insert_abnormal_2(self):
        self.precondition()
        try:
            self.my_linear_list_obj.insert(self.max_size,17)
            self.assertTrue(False)
        except IndexError:
            self.assertTrue(True)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,2,3,None,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 4)

    def test_delete_abnormal_1(self):
        self.precondition()
        try:
            del self.my_linear_list_obj[7]
            self.assertTrue(False)
        except IndexError:
            self.assertTrue(True)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,2,3,None,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 4)

    def test_delete_abnormal_2(self):
        self.precondition()
        try:
            del self.my_linear_list_obj[self.max_size]
            self.assertTrue(False)
        except IndexError:
            self.assertTrue(True)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,2,3,None,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 4)

    def test_delete_abnormal_3(self):
        self.precondition()
        del self.my_linear_list_obj[0]
        self.assertEqual(self.my_linear_list_obj.array, [1,2,3,3,None, None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 3)

        del self.my_linear_list_obj[0]
        self.assertEqual(self.my_linear_list_obj.array, [2,3,3,3,None,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 2)

        del self.my_linear_list_obj[0]
        self.assertEqual(self.my_linear_list_obj.array, [3,3,3,3,None,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 1)

        del self.my_linear_list_obj[0]
        self.assertEqual(self.my_linear_list_obj.array, [3,3,3,3,None,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 0)

        try:
            del self.my_linear_list_obj[0]
            self.assertTrue(False)
        except IndexError:
            self.assertTrue(True)
        self.assertEqual(self.my_linear_list_obj.array, [3,3,3,3,None,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 0)

        try:
            del self.my_linear_list_obj[0]
            self.assertTrue(False)
        except IndexError:
            self.assertTrue(True)
        self.assertEqual(self.my_linear_list_obj.array, [3,3,3,3,None,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 0)

    def test_append(self):
        self.precondition()
        self.my_linear_list_obj.append(4)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,2,3,4,None,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 5)

        self.my_linear_list_obj.append(5)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,2,3,4,5,None,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 6)

        self.my_linear_list_obj.append(6)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,2,3,4,5,6,None,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 7)

        self.my_linear_list_obj.append(7)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,2,3,4,5,6,7,None,None])
        self.assertEqual(len(self.my_linear_list_obj), 8)

        self.my_linear_list_obj.append(8)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,2,3,4,5,6,7,8,None])
        self.assertEqual(len(self.my_linear_list_obj), 9)

        self.my_linear_list_obj.append(9)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,2,3,4,5,6,7,8,9])
        self.assertEqual(len(self.my_linear_list_obj), 10)

        try:
            self.my_linear_list_obj.append(10)
            self.assertTrue(False)
        except IndexError:
            self.assertTrue(True)
        self.assertEqual(self.my_linear_list_obj.array, [0,1,2,3,4,5,6,7,8,9])
        self.assertEqual(len(self.my_linear_list_obj), 10)



if __name__ == '__main__':
    unittest.main()
