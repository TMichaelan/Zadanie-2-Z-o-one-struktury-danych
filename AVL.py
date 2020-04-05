import math
import time
import sys

czasPoczatkowy = 0
czasKoncowy = 0

class Node:
    def __init__(self, value=None, left=None, right=None, height=None, parent=None):
        self.parent = parent
        self.height = height
        self.value = value
        self.left = left
        self.right = right
        self.bf = 0


    def SetValue(self, value):
        self.value = value


class createNode:

    # Constructor to create a new node
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None



class AVL:
    mainRoot = 100

    def __init__(self, array):
        global y
        y = sorted(array)
        self.mainRoot = self.Create(y, None)



    def Create(self, array, parent):
        if not array:
            return None
        n = math.floor(len(array) / 2)
        root = Node(array[n], None, None, None, parent)
        root.left = self.Create(array[:n], root)
        root.right = self.Create(array[n + 1:], root)
        if root.left is None and root.right is None:
            root.height = 1
        elif root.left is None and root.right is not None:
            root.height = root.right.height + 1
        elif root.left is not None and root.right is None:
            root.height = root.left.height + 1
        else:
            root.height = max(root.left.height, root.right.height) + 1
        if root.left is None:
            left = 0
        else:
            left = root.left.height
        if root.right is None:
            right = 0
        else:
            right = root.right.height
        root.bf = left - right
        return root


    def minVal(self):
        print("min Value:",y[0])


    def maxVal(self):
        print("max Value:",y[-1])


    def PathMaxVal(self):
        # self.__PathMaxVal(self.mainRoot)
        pass
    def __PathMaxVal(self,index):
        pass
        # if index.right is not None:
        #     self.__PathMaxVal(index.right)
        # print(index.value, end=', ')


    def PathMinVal(self):
        pass

    def __PathMinVal(self):
        pass

    def __Inorder(self, index):
        if index.left is not None:
            self.__Inorder(index.left)
        print(index.value,end=', ')
        if index.right is not None:
            self.__Inorder(index.right)

    def Inorder(self):
        print("In-order: [", end='')
        self.__Inorder(self.mainRoot)
        print("\b\b]")

    def PreOrder(self, beginning=None):
        if self.mainRoot is None:
            print("Drzewo nie istnieje.")
            return
        if beginning is None:
            beginning = self.mainRoot
        print("Pre-order: [", end='')
        self.__PreOrder(beginning, False)
        print("]")

    def __PreOrder(self, index, boolean):
        if boolean:
            print(", ", end='')
        print(index.value, end='')
        if index.left is not None:
            self.__PreOrder(index.left, True)
        if index.right is not None:
            self.__PreOrder(index.right, True)

    def PostOrderDelete(self):
        if self.mainRoot is None:
            print("Drzewo nie istnieje.")
            return
        print("Usuwane elementy: [", end='')
        self.mainRoot = [self.mainRoot]
        self.__PostOrderDelete(self.mainRoot)
        self.mainRoot = None
        print("\b\b]")

    def __PostOrderDelete(self, index):
        if index[0].left is not None:
            self.__PostOrderDelete([index[0].left])
        if index[0].right is not None:
            self.__PostOrderDelete([index[0].right])
        print(index[0].value, end=', ')
        index[0] = None

    def Find(self, value):
        if self.mainRoot is None:
            print("Drzewo nie istnieje.")
            return None
        self.mainRoot = [self.mainRoot]
        n = self.__Find(value, self.mainRoot)
        self.mainRoot = self.mainRoot[0]
        return n[0]

    def __Find(self, value, index):
        if index[0].value == value:
            return index
        if index[0].left is not None:
            n = self.__Find(value, [index[0].left])
            if n is not None and n[0].value == value:
                return n
        if index[0].right is not None:
            n = self.__Find(value, [index[0].right])
            if n is not None and n[0].value == value:
                return n
        return None

# t = list(map(int, input().split()))
t = [100,80,90,70,30,40,50,60,20,30,40,200,400,1]

root = AVL(t)
root.PreOrder()
root.Inorder()
root.PostOrderDelete()
root.minVal()
root.maxVal()
root.PathMaxVal()
root.PathMinVal()




def AVLMain(tablicaWejsciowa):
    root = AVL(tablicaWejsciowa)
    while True:
        print("Wybierz operacje.")
        print("1- Wypisz element najmniejszy i najwiekszy.")
        print("2- Usun n elementow drzewa.")
        print("3- Wypisanie elementow (in-order)")
        print("4- Wypisanie elementow (pre-order)")
        print("5- Usuniecie drzewa (post-order)")
        print("6- Wypisanie drzewa o podanym kluczu. (pre-order)")
        print("7- Rownowazenie drzewa.")
        print("8- Wyjscie")
        try:
            n = int(input())
        except ValueError:
            print("Nieprawidlowe zapytanie.")
            continue
        if n == 1:
            pass
        elif n == 2:
            pass
        elif n == 3:
            pass
        elif n == 4:
            root.PreOrder()
        elif n == 5:
            root.PostOrderDelete()
        elif n == 6:
            while True:
                print("Podaj klucz.")
                try:
                    x = int(input())
                except ValueError:
                    print("Nieprawidlowy klucz")
                    continue
                k = root.Find(x)
                if k is None:
                    print("Element nie istnieje")
                    continue
                break
            root.PreOrder(k)
        elif n == 7:
            pass
        elif n == 8:
            break

sys.setrecursionlimit(1000000)
if len(sys.argv) > 1:
    for i in range(1, len(sys.argv)):
        try:
            f = open(sys.argv[i], "r+")
            tablicaWejsciowa = list(map(int, f.readline().split()))
        except ValueError:
            print("Nieprawidlowe dane")
            continue
        czyNaturalne = True
        for j in range(len(tablicaWejsciowa)):
            if tablicaWejsciowa[j] < 0:
                print("Nieprawidlowe dane")
                czyNaturalne = False
                break
        if czyNaturalne == False:
            continue
        AVLMain(tablicaWejsciowa)
else:
    while True:
        try:
            tablicaWejsciowa = list(map(int, input().split()))
        except ValueError:
            print("Nieprawidlowe dane")
            continue
        if len(tablicaWejsciowa) > 10:
            print("Nieprawidlowe dane")
            continue
        czyNaturalne = True
        for i in range(len(tablicaWejsciowa)):
            if tablicaWejsciowa[i] < 0:
                print("Nieprawidlowe dane")
                czyNaturalne = False
                break
        if czyNaturalne == False:
            continue
        break
    AVLMain(tablicaWejsciowa)
