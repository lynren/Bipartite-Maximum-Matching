#include "Bigraph.hxx"

Bigraph::Bigraph(std::vector<int> X, std::vector<int> Y, std::vector<std::pair<int, int>> edges)
        : X(X), Y(Y), adjMat(X.size(), std::vector<int>(Y.size()))
{
        for(std::pair<int, int> edge : edges){
                int x_vertex = edge.first, y_vertex = edge.second;
                adjMat[x_vertex][y_vertex] = 1;
        }
}

Bigraph::Bigraph() : X(), Y(), adjMat(0, std::vector<int>(0)){}

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

const std::vector<std::vector<int>> &Bigraph::getAdjMat() const{
        return adjMat;
}

const std::vector<int> &Bigraph::getX() const { return X; }
const std::vector<int> &Bigraph::getY() const { return Y; }

void Bigraph::addX(int x){
        X.push_back(x);
        adjMat.emplace_back(Y.size());
}

void Bigraph::addY(int y){
        Y.push_back(y);
        for(std::vector<std::vector<int>>::iterator it = adjMat.begin(); it != adjMat.end(); ++it){
                it->push_back(0);
        }
}
