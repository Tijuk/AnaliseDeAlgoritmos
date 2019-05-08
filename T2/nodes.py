from output import *

class Node:
    def __init__(self, node, notEmpty = True):
        self.node = int(node+1)
        self.notEmpty = notEmpty
        self.links = None

    def isRelated(self, otherNode):
        return otherNode in self.links

    def moveTo(self, node):
        self.visit()
        try:
            return self.links[node-1].leave()
        except:
            raise Exception(f"Illegal Move from [{self.node}] to [{node-1}]")
        # if self.links[node-1] == None:
        #     raise Exception(f"Illegal Move from [{self.node}] to [{node-1}]")
        # return self.links[node-1].leave()

    def visit(self):
        self.notEmpty = True
        return self

    def leave(self):
        self.notEmpty = False
        return self

    def __str__(self):
        lks = ""
        for node in self.links:
            if not node == None:
                lks = f"{lks} {int(node.node)},"
        return f"{self.node} - [{lks} ] - {self.notEmpty}"


class StateNode:
    def __init__(self, config, index):
        self.index = index
        self.config = config
        self.links = None

    def moveTo(self, destIndex):
        try:
            return self.links[destIndex]
        except:
            raise Exception(f"Illegal Move from [{self.index}] to [{destIndex}]")
        # if self.links[destIndex] == None:
        #     raise Exception(f"Illegal Move from [{self.index}] to [{destIndex}]")
        # return self.links[destIndex]

    def __str__(self):
        ret = f"Index: {self.index}\nConfig:\n{drawAsMatrix(self.config)}"
        lks = ""
        for node in self.links:
            if not node == None:
                lks = f"{lks} {int(node)},"
        return f"{ret}\nLinks: [{lks} ]"
