from my_queue_stack import my_queue, my_stack

class my_rpn(object):

    def __compare_operator(self, peek, char):
        if peek == '(' or char == '(': return 1
        if char == '+' or char == '-': return -1
        if char == '*' and (peek == '*' or peek == '/'): return -1
        if char == '/' and (peek == '*' or peek == '/'): return -1
        return 1

    def create_rpn(self, expr) -> my_queue:
        stack = my_stack()
        queue = my_queue()
        isNumber = False
        number = 0

        for char in expr:
            if char.isnumeric():
                current = int(char)
                number = number * 10 + current if isNumber else current
                isNumber = True
            else:
                if isNumber: queue.enqueue(number)
                isNumber = False
                number = 0
                if char == ' ': continue
                elif char == ')':
                    while len(stack) != 0 and stack.peek() != '(': queue.enqueue(stack.pop())
                    if stack.peek() == '(': stack.pop()
                else:
                    while len(stack) != 0 and self.__compare_operator(stack.peek(), char) < 0: queue.enqueue(stack.pop())
                    stack.push(char)

        if isNumber: queue.enqueue(number)
        while len(stack) != 0:
            queue.enqueue(stack.pop())

        return queue

    def __calculate_operand(self, operand_a:int, operand_b:int, operator:str):
        if operator == '+': return operand_a + operand_b
        elif operator == '-': return operand_a - operand_b
        elif operator == '*': return operand_a * operand_b
        elif operator == '/': return operand_a / operand_b
        else: pass
        return 0

    def calculate_rpn(self, queue:my_queue):
        result = my_stack()
        
        while len(queue) > 0:
            char = queue.dequeue()
            if type(char) == str:
                operand_b = result.pop()
                operand_a = result.pop()
                result.push(self.__calculate_operand(operand_a, operand_b, char))
            else:
                result.push(char)

        return result.pop()
