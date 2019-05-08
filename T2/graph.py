import numpy as np
import copy
from nodes import *
from factory import GraphFactory
from pprint import pprint

Factory = GraphFactory()

class Graph:
    def __init__(self, size = 3):
        self.vec = 0
        self.size = size * size
        self.rootSize = size

    def createStateGraph(self):
        states = np.empty(self.size, dtype = StateNode)

        for i in range(0,self.size):
            graph = Factory.createMatrix(self.rootSize,False)
            links = np.empty(self.size)
            print()
            graph[i].leave()
            state = StateNode(graph, i)

            for link_index in range(0,self.size):
                if not (graph[i].links[link_index] == None):
                    print(graph[i].links[link_index].node)
                    links[link_index] = link_index
            state.links = links
            states[i] = state

        for s in states:
            print(s)
            # for l in s.links:
            #     ss = ""
            #     if l:
            #         ss = f"{ss}  {l.node}"
            #     ss = f"[{ss}]"
            # print(f"{c} > {ss}")
            # c = c + 1

        return states
