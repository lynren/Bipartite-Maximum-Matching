// X,Y-Bigraph class
#ifndef BIGRAPH_H
#define BIGRAPH_H

//===========================================

#include <vector>

//===========================================

class Bigraph
{
        private:
                std::vector<std::vector<int>> adjMat;   // X x Y adjacency matrix
                std::vector<int> X;     // Partite set X
                std::vector<int> Y;     // Partite set Y
        public:
                Bigraph(std::vector<int> X, std::vector<int> Y, std::vector<std::pair<int, int>> edges);
                std::vector<int> getNeighbors(int vertex);
                void addEdge(int x, int y);
                void removeEdge(int x, int y);
                std::vector<std::vector<int>> getAdjMat();
};
#endif
