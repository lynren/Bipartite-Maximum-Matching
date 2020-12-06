import pygraphviz as pgv

f = open("graph_data.txt", "r")
m = open("matching.txt", "r")
edges = set()
matching = set()
X = set()
Y = set()
labels = dict()

# read in x vertices
for v in f.readline().rstrip().split(" "):
    X.add(v)
    labels[v] = v

# read in y vertices
for y in f.readline().rstrip().split(" "):
    Y.add(y)
    labels[y] = y

# read in edges
for line in f:
    if line == '\n':
        break
    c = line.split(" ")
    edges.add((c[0], c[1].rstrip()))

# read in edges in the matching
for line in m:
    c = line.split(" ")
    matching.add((c[0], c[1].rstrip()))

G = pgv.AGraph()
# add nodes to G
for x in X:
    G.add_node(x, color="lightgreen")

for y in Y:
    G.add_node(y, color="lightblue")

# add edges to G
for x, y in edges.difference(matching):
    G.add_edge(x, y, color="black")
for x, y in matching:
    G.add_edge(x, y, color="red")

G.node_attr['style'] = 'filled'
G.node_attr['shape'] = 'circle'
G.layout()
G.draw("matching.png")


# pos = nx.kamada_kawai_layout(G)
