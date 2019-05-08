import numpy as np
from nodes import *
from debug import log
import math

__emptyNode__ = -1

def resolveIndex(i,j):
    return j + 3*i;

class GraphFactory:
    def __init__(self):
        pass

    def create3x3_matrix(self, size = 3):
        ret = np.empty((size,size))

        counter = 0
        for i in range(0,size):
            for j in range (0,size):
                ret[i][j] = counter
                counter = counter + 1
        return ret

    def createMatrix(self, size = 3, addStart = True):
        matrix = self.create3x3_matrix(size)
        arr = list()
        links = list()
        for i in range(0,size):
            for j in range(0,size):
                arr.append(Node(matrix[i][j]))

        for i in range(0,size):
            for j in range(0,size):
                links = np.empty(size*size,dtype=Node);
                if(i - 1 >= 0):
                    index = resolveIndex(i-1,j)
                    links[index] = arr[index]
                if(i + 1< size):
                    index = resolveIndex(i+1,j)
                    links[index] = arr[index]
                if(j - 1 >= 0):
                    index = resolveIndex(i,j-1)
                    links[index] = arr[index]
                if(j + 1 < 3):
                    index = resolveIndex(i,j+1)
                    links[index] = arr[index]
                index = resolveIndex(i,j)
                arr[index].links = links

                if addStart and index == (size*size) - 1:
                    arr[index].leave()
        return np.array(arr)

    def deepCopy(self,original):
        size = len(original)
        arr = np.empty(size, dtype = Node)
        for i in range(0,size):
            arr[i] = Graph.Node(original[i].node)

        for i in range(0, size):
            links = np.empty(size, dtype=Node)
            for j in range(0, size):
                print(i,j)
                if not original[i].links[j] == None:
                    links[j] = arr[j]
            print("")
        return arr




        # for i in range(0,size):
        #     for j in range(0,size):
        #         arr.append(Graph.Node(matrix[i][j]))
        #         node = Graph.Node(matrix[i][j])
        # if i+1 < size:
        #     print(matrix[i][j], matrix[i+1][j])
        # if i-1 >= 0:
        #     print(matrix[i][j], matrix[i-1][j])

instanceOfFactory = GraphFactory()

deepCopy = instanceOfFactory.deepCopy
