#include "Bigraph.hxx"

Bigraph::Bigraph(std::vector<int> X, std::vector<int> Y, std::vector<std::pair<int, int>> edges)
        : adjMat(X.size(), std::vector<int>(Y.size())), X(X), Y(Y)
{
        for(std::pair<int, int> edge : edges){
                int x_vertex = edge.first, y_vertex = edge.second;
                adjMat[x_vertex][y_vertex] = 1;
        }
}

void Bigraph::addEdge(int x, int y){
        adjMat[x][y] = 1;
}

void Bigraph::removeEdge(int x, int y){
        adjMat[x][y] = 0;
}

std::vector<int> Bigraph::getNeighbors(int x_vertex){
        std::vector<int> neighbors;
        for(std::vector<int>::iterator it = adjMat[x_vertex].begin();
                        it != adjMat[x_vertex].end(); ++it){
                if(*it == 1)
                        neighbors.push_back(std::distance(adjMat[x_vertex].begin(), it));
        }
        return neighbors;
}

std::vector<std::vector<int>> Bigraph::getAdjMat(){
        return adjMat;
}
