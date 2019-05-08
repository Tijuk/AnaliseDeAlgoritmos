from debug import log
import factory
from graph import Graph
from output import *

#try:
if  __name__ == '__main__':
    Factory = factory.GraphFactory()
    # graph = Factory.create3x3()
    graph = Graph()
    g = graph.createStateGraph()
    # log.success(drawAsMatrix(graph.createStateGraph()))
    # print(drawAsMatrix(graph))
    #
    # print(g)

    # for state in g:
    #     log.success(drawAsMatrix(state))
    # position = g[len(g)-1]
    # print(position)
    # moves = [6,5,4,1,2,7]
    # for move in moves:
    #     position = position.moveTo(move)
    #     log.success(drawAsMatrix(g))
    #     log.split()


# except Exception as error:
#     log.error(str(error))
