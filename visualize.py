import networkx as nx
import matplotlib.pyplot as plt


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

G = nx.Graph()
# add nodes to G
for x in X:
    G.add_node(x)
for y in Y:
    G.add_node(y)
# add edges to G
for x, y in edges.difference(matching):
    G.add_edge(x, y, color="black")
for x, y in matching:
    G.add_edge(x, y, color="red")

edge_colors = nx.get_edge_attributes(G, 'color').values()

pos = nx.kamada_kawai_layout(G)

nx.draw_networkx_nodes(G, pos=pos, nodelist=list(X), node_color="lightgreen")
nx.draw_networkx_nodes(G, pos=pos, nodelist=list(Y), node_color="lightblue")
nx.draw_networkx_edges(G, pos=pos, edge_color=edge_colors)
nx.draw_networkx_labels(G, pos=pos, font_color="black", labels=labels)

plt.savefig("matching_image.png")
plt.show()
