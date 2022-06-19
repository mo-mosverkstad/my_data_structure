class my_linear_list(object):
    def __init__(self, size):
        self.max_size = size
        self.array = [None] * self.max_size
        self.head = 0
        self.tail = -1

    def __check_index_out_of_max_size__(self, index):
        if (index >= self.max_size):
            raise IndexError("Linear list index out of range")

    def __check_index_out_of_tail__(self, index):
        if (index > self.tail):
            raise IndexError("Linear list index out of range")

    def __setitem__(self, index, value):
        self.__check_index_out_of_max_size__(index)
        if (self.tail < index):
            self.tail = index
        self.array[index] = value

    def __getitem__(self, index):
        self.__check_index_out_of_max_size__(index)
        return self.array[index]

    def append(self, value):
        self.__check_index_out_of_max_size__(self.tail + 1)
        self.tail = self.tail + 1
        self.array[self.tail] = value
        
    def insert(self, index, value):
        self.__check_index_out_of_max_size__(self.tail + 1)
        self.__check_index_out_of_tail__(index)
        for i in range(self.tail, index - 1, -1):
            self.array[i+1] = self.array[i]
        self.array[index] = value
        self.tail = self.tail + 1

    def __delitem__(self, index):
        self.__check_index_out_of_tail__(index)
        for i in range(index, self.tail):
            self.array[i] = self.array[i+1]
        self.tail = self.tail - 1

    def __len__(self):
        return self.tail + 1

    """
    def __repr__(self):
        return f'{type(self).__name__}'
    """



