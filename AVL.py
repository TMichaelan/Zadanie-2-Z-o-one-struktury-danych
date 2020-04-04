import math


class Node:
    def __init__(self, value=None, left=None, right=None, height=None, parent=None):
        self.parent = parent
        self.height = height
        self.value = value
        self.left = left
        self.right = right

    def SetValue(self, value):
        self.value = value


class AVL:
    mainRoot = 0

    def __init__(self, array):
        self.mainRoot = self.Create(sorted(array), None, 0)

    def Create(self, array, parent, height):
        if not array:
            return None
        n = math.floor(len(array) / 2)
        root = Node(array[n], None, None, height, parent)
        root.left = self.Create(array[:n], root, height + 1)
        root.right = self.Create(array[n + 1:], root, height + 1)
        return root

    def PreOrder(self):
        print("Pre-order: [", end='')
        self.__PreOrder(self.mainRoot)
        print("]")

    def __PreOrder(self, index):
        if index is not self.mainRoot:
            print(", ", end='')
        print(index.value, end='')
        if index.left is not None:
            self.__PreOrder(index.left)
        if index.right is not None:
            self.__PreOrder(index.right)

    def PostOrderDelete(self):
        print("Usuwane elementy: [", end='')
        self.__PostOrderDelete(self.mainRoot)
        print("\b\b]")

    def __PostOrderDelete(self, index):
        if index.left is not None:
            self.__PostOrderDelete(index.left)
        if index.right is not None:
            self.__PostOrderDelete(index.right)
        print(index.value, end=', ')
        del index


t = list(map(int, input().split()))
root = AVL(t)
root.PreOrder()
root.PostOrderDelete()
