class my_queue:
    def __init__(self):
        self.__queue = []

    def enqueue(self, item):
        self.__queue.append(item)

    def dequeue(self):
        return self.__queue.pop(0)

    def front(self):
        return self.__queue[0]

    def rear(self):
        return self.__queue[-1]

    def __len__(self):
        return len(self.__queue)

    def __repr__(self):
        return "my_queue(" + str(len(self)) + ")[" + str(self.front()) + " ... " + str(self.rear()) + "]"

    def get(self):
        return self.__queue