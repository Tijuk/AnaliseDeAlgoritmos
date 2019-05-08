
def printGraph(graph):
    for node in graph:
        print(node.toString())

def drawAsMatrix(graph, size = 3):
    ret = list()
    line = list()
    lastLine = 0
    for i in range(0, len(graph)):
        ii = int(i/size)
        if not lastLine == ii:
            ret.append(line)
            lastLine = ii
            line = list()
        if(graph[i].notEmpty):
            line.append(' ')
        else:
            line.append('O')
    ret.append(line)

    finished = ""
    for i in range(0,size):
        line = ""
        for j in range(0,size):
            if(j == 0):
                line = f"{ret[size-i-1][j]}"
            else:
                line = f"{line} ][ {ret[size-i-1][j]}"
        finished = f"{finished}\n[ {line} ]"
    return finished;
