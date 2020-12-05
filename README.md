# Intro to Graph Theory: Final Project
## Find a maximum matching in a bipartite graph

## Requirements
Running ```matchings.cxx``` requires C++11.

Run pip3 install -r requirements.txt to install ```visualize.py``` requirements.

## Usage
### Input Graph File
The file containing the graph nodes and edges uses the following structure:

* The first line contains the vertices of the partite set X, separated by spaces.
* The second line contains the vertices of the partite set Y, separated by spaces.
* Up to |X|*|Y| lines may follow, each containing a single edge of the graph represented as two vertices separated by a space. The first vertex must be a vertex in X.

### Running
Use ```./run.sh <input_file>``` where ```<input_file>``` has the structure described above.

To produce a matching without visuals, compile ```matchings.cxx``` and run with an input file redirected into the executable.

### run.sh
Runs ```matchings.cxx``` executable with the given argument, then runs ```visualize.py``` to produce the image.

### algo_3.2.1.cxx
Implements Algorithm 3.2.1 from the textbook.

### matchings.cxx
Uses Algorithm 3.2.1 to find M-augmenting paths in a biparite graph, starting with an empty matching M.

### visualize.py
Reads graph edges and nodes from ```graph_data.txt``` and matching edges from ```matching.txt```. It then displays the graph with the edges in the matching colored in red, and nodes belonging to different partite sets colored differently.
