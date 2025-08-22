import unittest
from my_queue_stack import my_array_queue

class Test_array_queue(unittest.TestCase):
    def setUp(self):
        self.queue = my_array_queue(5)
        self.queue.enqueue(0)
        self.queue.enqueue(1)
        self.queue.enqueue(2)
        self.assertEqual(len(self.queue), 3)
        self.assertEqual(self.queue.front(), 0)
        self.assertEqual(self.queue.rear(),2)

    def __check_dequeue(self, rear, new_rear, new_len):
        self.assertEqual(self.queue.dequeue(), rear)
        self.assertEqual(len(self.queue), new_len)
        self.assertEqual(self.queue.front(), new_rear)

    def test_enqueue(self):
        self.queue.enqueue(3)
        self.assertEqual(self.queue.rear(), 3)
        self.queue.enqueue(4)
        self.assertEqual(self.queue.rear(), 4)
        self.assertTrue(self.queue.is_full())

    def test_dequeue_1(self):
        self.__check_dequeue(0, 1, 2)

    def test_dequeue_2(self):
        self.__check_dequeue(0, 1, 2)
        self.__check_dequeue(1, 2, 1)

    def test_dequeue_3(self):
        self.__check_dequeue(0, 1, 2)
        self.__check_dequeue(1, 2, 1)
        self.assertEqual(self.queue.dequeue(), 2)
        self.assertEqual(len(self.queue), 0)
        try:
            self.assertEqual(self.queue.front(), None)
            self.fail()
        except:
            self.assertTrue(True)
        self.assertEqual(len(self.queue), 0)
        self.assertTrue(self.queue.is_empty())

    def test_cycle_operation_1(self):
        self.queue.enqueue(3)
        self.queue.enqueue(4)
        self.assertEqual(self.queue.dequeue(), 0)
        self.assertEqual(len(self.queue), 4)
        self.assertFalse(self.queue.is_full())

        self.queue.enqueue(5)
        self.assertEqual(len(self.queue), 5)
        self.assertTrue(self.queue.is_full())

    def test_cycle_operation_2(self):
        self.queue.enqueue(3)
        self.queue.enqueue(4)
        self.assertEqual(self.queue.dequeue(), 0)
        self.queue.enqueue(5)
        self.assertEqual(self.queue.dequeue(), 1)
        self.assertEqual(self.queue.dequeue(), 2)
        self.assertEqual(self.queue.dequeue(), 3)
        self.assertEqual(self.queue.dequeue(), 4)
        self.assertEqual(self.queue.front(), 5)
        self.assertEqual(self.queue.rear(), 5)
        self.assertEqual(len(self.queue), 1)
        self.queue.enqueue(6)
        self.queue.enqueue(7)
        self.assertEqual(self.queue.front(), 5)
        self.assertEqual(self.queue.rear(), 7)
        self.assertEqual(len(self.queue), 3)






if __name__ == '__main__':
    unittest.main()
