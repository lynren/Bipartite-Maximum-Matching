// X,Y-Bigraph class
#ifndef BIGRAPH_H
#define BIGRAPH_H

//===========================================

#include <vector>

//===========================================

class Bigraph
{
        private:
                std::vector<int> X;     // Partite set X
                std::vector<int> Y;     // Partite set Y
                std::vector<std::vector<int>> adjMat;   // X x Y adjacency matrix
        public:
                // construct a Bigraph with partite sets X, Y and edges
                Bigraph(std::vector<int> X, std::vector<int> Y, std::vector<std::pair<int, int>> edges);

                // construct an empty Bigraph
                Bigraph();

                // get neighborhood of vertex x in X
                std::vector<int> getNeighbors(int vertex);

                // add an edge with endpoints x, y, where x in X and y in Y
                void addEdge(int x, int y);

                // remove the edge with endpoints x, y, where x in X and y in Y
                void removeEdge(int x, int y);

                // get adjacency matrix of Bigraph
                const std::vector<std::vector<int>> &getAdjMat() const;

                // get partite set X
                const std::vector<int> &getX() const;
                // get partite set Y
                const std::vector<int> &getY() const;

                // add a vertex to partite set X
                void addX(int x);
                // add a vertex to partite set Y
                void addY(int y);
};
#endif
