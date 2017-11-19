class Queue:
    def __init__(self):
        self.list = []

    def push(self, value):
        """"""
        self.list.append(value)

    def pop(self):
        """"""
        return self.list.pop()

    def is_empty(self):
        """"""
        return len(self.list) == 0
