import unittest
from rpn import my_rpn

class Test_rpn(unittest.TestCase):
    def __check_rpn_result(self, expr, expected_queue, expected_result):
        my_rpn_obj = my_rpn()
        queue = my_rpn_obj.create_rpn(expr)
        self.assertEqual(queue.get(), expected_queue)
        self.assertEqual(my_rpn_obj.calculate_rpn(queue), expected_result)

    def test_rpn_1(self):
        self.__check_rpn_result('2+3*(6*8*7+2)-1', [2, 3, 6, 8, '*', 7, '*', 2, '+', '*', '+', 1, '-'], 1015)

if __name__ == '__main__':
    unittest.main()
