class Node {
	constructor(node) {
		this.node = node;
		this.child = [];
	}

	appendChild(nodeA) {
		this.child.push( new Node(nodeA) )
	}
}

class Graph {
	constructor(nos, arestas) {
		const grafo = {};
		for(let i = 0; i < nos.length ; i++) {
			grafo[nos[i]] = (new Node(nos[i]));
		}
		for(let i = 0; i < arestas.length; i++) {
			grafo[arestas[i][0]].appendChild(arestas[i][1]);
			grafo[arestas[i][1]].appendChild(arestas[i][0]);
		}
		this.content = grafo;
	}
}

class Operations {
	GrafoToArray(grafo) {
		const nosKeys = Object.keys(grafo);
		const grafoAsArray = {}
		for(let i = 0; i < nosKeys.length; i++) {
			const g = grafo[nosKeys[i]]
			grafoAsArray[g.node] = grafoAsArray[g.node] || [];
			this.part2(g, grafoAsArray);
		}
		return grafoAsArray;
	}

	part2(g, grafoAsArray) {
		for( let i = 0; i < g.child.length ; i++ ) {
			if(!grafoAsArray[g.child[i].node]) continue;
			if(grafoAsArray[g.child[i].node].includes(g.node)) continue;
			if(!grafoAsArray[g.node]) continue;
			if(grafoAsArray[g.node].includes(g.child[i].node)) continue;
			grafoAsArray[g.child[i].node].push(g.node);
			this.part2(g.child[i], grafoAsArray);
		}
	}

	createGraph(nos, arestas) {
		const grafo = {};
		for(let i = 0; i < nos.length; i++) {
			grafo[nos[i]] = (new Node(nos[i]));
		}
		for(let i = 0; i < arestas.length; i++) {
			grafo[arestas[i][0]].appendChild(arestas[i][1]);
			grafo[arestas[i][1]].appendChild(arestas[i][0]);
		}
		return grafo;
	}
}

const operations = new Operations();
const grafo = new Graph(['A', 'B', 'C', 'D', 'E','F','G','H'], [['A','B'],['B','C'],['C','D'],['D','E'],['E','A'],['F', 'G']]);
const bws = operations.GrafoToArray(grafo.content);
console.log(bws);