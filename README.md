## Development of signed graph balance checking algorithms
Development of signed graph balance checking algorithms is the main subject of the present thesis. An option of graphically representing a graph is also provided.

### Install
For a simple installation, run:

	$ git clone https://github.com/kargakis/signedgraph
	$ cd signedgraph
	$ make 

For more interesting results though, it is advised to have all the [prerequisites](https://github.com/kargakis/signedgraph#prerequisites-for-graph-visualization) and run the following version of ```make```:

	$ make viz

### Use

	$ signedgraph <3-18000>

Although, theoretically, our algorithms are graph-size agnostic, meaning they can work on any size of graph, we are constraining the size of our generated graphs from three (smallest closed graph there can be) up to 18k nodes due to memory limitations some computers may have. Below there is an 1k-vertices graph.

![](https://raw.githubusercontent.com/kargakis/signedgraph/master/img/1k-nodes.png)

### Prerequisites for graph visualization
* [Graphviz](http://www.graphviz.org/)
* [Evince](https://wiki.gnome.org/Apps/Evince) (or your favorite document viewer)
* ```make viz```

Evince was chosen amongst a wide variety of document viewers (Adobe Reader, Foxit, Nitro, et al) because it is open-source and more lightweight than the rest but if you want to use a different viewer just replace [evince](https://github.com/kargakis/signedgraph/blob/b81b9259d202949bc30d69bf0bfa4db9cbd1d8b7/src/main.c#L170) with the command that runs the viewer of your choice before building the source.
By using Graphviz and the DOT language, we can visualize our graphs like the following graph, which represents our ```balancedGraph``` used for testing. Windows users need to set up their ```PATH``` to point to the ```neato``` and ```evince``` executables.

![](https://raw.githubusercontent.com/kargakis/signedgraph/master/img/example.png)

### Testing
Testing of the algorithms can be done with the execution of the following commands:

	$ make test
	$ signedgraph
	
### History
Signed graphs were first introduced by [Frank Harary](http://en.wikipedia.org/wiki/Frank_Harary) to handle a problem in social psychology (Cartwright and Harary, 1956). They have been rediscovered many times because they come up naturally in many unrelated areas. For instance, they enable one to describe and analyze the geometry of subsets of the classical root systems. They appear in topological graph theory and group theory. They are a natural context for questions about odd and even cycles in graphs. They appear in computing the ground state energy in the non-ferromagnetic Ising model; for this one needs to find a largest balanced edge set in Σ. They have been applied to data classification in correlation clustering.
