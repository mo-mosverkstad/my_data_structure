class my_array_queue:
    def __init__(self, max_size):
        self.array = [None] * max_size
        self.head = 0
        self.tail = 0
        self.max_size = max_size

    def index_of(self, index):
        return index % self.max_size

    def is_full(self):
        return self.index_of(self.tail) == self.index_of(self.head) and self.head != self.tail

    def is_empty(self):
        return self.index_of(self.tail) == self.index_of(self.head) and self.head == self.tail

    def enqueue(self, item):
        if self.is_full():
            raise Exception("The queue is full")
        self.array[self.index_of(self.tail)] = item
        self.tail = self.tail + 1

    def dequeue(self):
        if self.is_empty():
            raise Exception("The queue is empty")
        item = self.array[self.index_of(self.head)]
        self.head = self.head + 1
        return item

    def front(self):
        return self.array[self.index_of(self.head)]

    def rear(self):
        return self.array[self.index_of(self.tail-1)]

    def __len__(self):
        return self.tail - self.head

    def __repr__(self):
        return str(self.__dict__)