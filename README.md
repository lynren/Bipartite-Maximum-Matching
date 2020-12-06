# Intro to Graph Theory: Final Project
## Find a maximum matching in a bipartite graph

## Requirements
All C++ files are written with C++11.

To create a graphic using ```run.sh```, [PyGraphviz](https://pygraphviz.github.io/) and Python3.7 must be installed. This can be accomplished with ```pip install -r requirements.txt```

## Usage
### Input Graph File
The file containing the graph nodes and edges uses the following structure:

* The first line contains the vertices of the partite set X, separated by spaces.
* The second line contains the vertices of the partite set Y, separated by spaces.
* Up to |X|*|Y| lines may follow, each containing a single edge of the graph represented as two vertices separated by a space. The first vertex must be a vertex in X.

### Running
Use ```./run.sh <input_file>``` where ```<input_file>``` has the structure described above.

To produce a matching without visuals, compile ```matchings.cxx``` and run with an input file redirected into the executable.

## Example
```
./run.sh examples/octopus
Maximum matching found:
{(x11, y7), (x10, y6), (x9, y5), (x8, y4), (x7, y11), (x6, y10), (x5, y9), (x4, y8), (x3, y3), (x2, y2), (x1, y1), (x0, y0)}
```
matching.png:

![ocotopus matching](https://i.imgur.com/XH6rQf5.png)

## Files

### run.sh
Runs ```matchings.cxx``` executable with the given argument, then runs ```visualize.py``` to produce the image (visuals do not work very well for disconnected graphs).

### algo_3.2.1.cxx
Implements Algorithm 3.2.1 from the [textbook](https://faculty.math.illinois.edu/~west/igt/).

### matching.cxx
Uses Algorithm 3.2.1 to find M-augmenting paths in a biparite graph, starting with an empty matching M. For each M-augmenting path found, it flips the matching edges on the path in order to make it not an M-augmenting path. This step repeats until no more M-augmenting paths are found. M is then written to the standard output and to ```matching.txt```.

### visualize.py
Reads graph edges and nodes from ```graph_data.txt``` and matching edges from ```matching.txt```. It then saves an image of the graph with colored matching to ```matching.png```.

### knm.cxx
Produces input data for the complete bipartite graph with partite sets of size n and m. The data is written to the standard output. To use, redirect two integers into the executable.
