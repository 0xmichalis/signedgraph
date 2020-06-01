## Development of signed graph balance checking algorithms

Development of signed graph balance checking algorithms is the main subject of the present thesis.
An option of graphically representing a graph is also provided.

### Install

For a simple installation, run:

```
git clone https://github.com/kargakis/signedgraph
cd signedgraph
make
```

Build a binary that can generate DOT output:
```
make dot
```

### Run

For a 5-node graph, run:
```
./signedgraph 5
```

If you have built with DOT support, you can use Graphviz to visualize the generated graph:
```
neato -Tps graph.dot -o graph.ps
```

![](https://raw.githubusercontent.com/kargakis/signedgraph/master/img/example.png)

Although, theoretically, our algorithms are graph-size agnostic,
meaning they can work on any size of graph,
we are constraining the size of our generated graphs
from three (smallest closed graph there can be) up to 18k nodes
due to memory limitations some systems may have.
Below there is an 1k-vertices graph.

![](https://raw.githubusercontent.com/kargakis/signedgraph/master/img/1k-nodes.png)

### Test

Testing of the algorithms can be done with the execution of the following commands:
```
make test
./signedgraph
```
	
### History

Signed graphs were first introduced by [Frank Harary](http://en.wikipedia.org/wiki/Frank_Harary)
to handle a problem in social psychology (Cartwright and Harary, 1956).
They have been rediscovered many times
because they come up naturally in many unrelated areas.
For instance,
they enable one to describe and
analyze the geometry of subsets of the classical root systems.
They appear in topological graph theory and group theory.
They are a natural context for questions about odd and even cycles in graphs.
They appear in computing the ground state energy in the non-ferromagnetic Ising model;
for this one needs to find a largest balanced edge set in Σ.
They have been applied to data classification in correlation clustering.
