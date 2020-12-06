/* Lyndon Renaud
 * Final Project
 *
 * INPUT:
 * - The first line of input contains the vertices of X,
 *   separated by spaces
 * - The second line of input contains the vertices of Y,
 *   separated by spaces
 * - Up to |X||Y| lines follow, each containing an edge of G
 *   represented as two vertices separated by a space.
 */

//=============================================================================

#include "Bigraph.cxx"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <sstream>
#include <string>
#include <fstream>

//=============================================================================

using namespace std;

int main(){
        ofstream outf;
        outf.open("matching.txt", ios::binary | ios::out); // write matching here
        Bigraph G; // Bigraph object storing our graph
        // M is a mapping from vertices in X to vertices in Y, representing
        // a matching. Mi is the inverse of M.
        unordered_map<int, int> M, Mi;
        // idX, idY map the string representation of vertices to a number from 0
        // to |X| and 0 to |Y| respectively. idXi, idYi are the inverse.
        unordered_map<string, int> idX, idY;
        unordered_map<int, string> idYi, idXi;

        string line;
        string vertex, vertex2;
        // populate X set
        getline(cin, line);
        stringstream in(line);
        while(in >> vertex){
                tie(idX[vertex], idXi[idX.size()]) = make_tuple(idX.size(), vertex);
                G.addX(idX[vertex]);
        }
        in.clear();

        // populate Y set
        getline(cin, line);
        in.str(line);
        while(in >> vertex){
                tie(idY[vertex], idYi[idY.size()]) = make_tuple(idY.size(), vertex);
                G.addY(idX[vertex]);
        }

        // populate edge set
        while(cin >> vertex >> vertex2) G.addEdge(idX[vertex], idY[vertex2]);

        // U = set of vertices in X unsaturated by M
        // Initially M = {} => U = X
        set<int>U(G.getX().begin(), G.getX().end()), T, S;

        // augmenting path flag. set to true if an augmenting path is found
        bool aug;

        do{
                aug = false; // intially, we have found no augmenting path
                vector<int> aug_path; // store the path being traversed

                // Algorithm 3.2.1
                // Find an M-augmenting path
                // First we initialize S = U and T = {}
                S = U;
                // unamrked is the set of unmarked vertices of S
                // marked is the set of marked vertices in S
                // initially, all vertices in S are unmarked
                set<int> unmarked(S.begin(), S.end()), marked;
                // Repeat iteration while S has unmarked vertices
                while(unmarked.size() > 0){
                        int x = *unmarked.begin(); // pick an unmarked vertex x
                        aug_path.push_back(x); // append x to the path

                        // for each neighbor y of x
                        for(int y : G.getNeighbors(x)){
                                // if edge xy is not in M
                                if((M.find(x) == M.end() || M[x] != y)){
                                        // Since we start at a vertex in X,
                                        // current path must be of odd length before
                                        // visiting a vertex in Y
                                        // if prev vertex on path is in Y, pop it
                                        if(aug_path.size() % 2 == 0) aug_path.pop_back();
                                        aug_path.push_back(y); // append the vertex to path
                                        // if y is saturated by M
                                        if(Mi.find(y) != Mi.end()){
                                                // include y in T (reached from x)
                                                T.insert(x);
                                                // include w in S (reached from y)
                                                S.insert(Mi[y]);
                                                // check if y has previously been marked
                                                // if not, add it to the unmarked set
                                                if(marked.find(Mi[y]) == marked.end())
                                                        unmarked.insert(Mi[y]);
                                        }
                                        // else y is unsaturated by M
                                        else{
                                                aug = true; // there exists an M augmenting path from U to y
                                                break;
                                        }
                                }
                        }
                        if(aug) break; // loop exit condition met (M-augmenting path found)
                        // we are done exploring all such edges incident to x.
                        // Mark x and iterate
                        unmarked.erase(x);
                        marked.insert(x);
                }
                // end Algorithm 3.2.1

                if(aug){// if an augmenting path has been found
                        // flip augmented path edges in M
                        int v1 = aug_path[0], v2 = aug_path[1];
                        Mi.erase(v2);
                        M.erase(v1);
                        if(G.getAdjMat()[v1][v2] == 1){
                                M[v1] = v2;
                                Mi[v2] = v1;
                                U.erase(v1);
                        }
                        for(size_t i = 2; i < aug_path.size(); i+=2){
                                v1 = aug_path[i], v2 = aug_path[i+1];

                                // remove edge in M from current to prev vertex in path
                                // add edge from current vertex to next to M
                                Mi.erase(v2);
                                M.erase(v1);
                                if(G.getAdjMat()[v1][v2] == 1){
                                        M[v1] = v2;
                                        Mi[v2] = v1;
                                }
                        }
                }
        }while(aug); // iterate while an M-augmenting path exists in G

        // output the matching & write matching file
        cout << "Maximum matching found: \n{";
        for(auto v = M.begin(); v != M.end(); ++v){
                cout << '(' << idXi[v->first] << ", " << idYi[v->second] << ')';
                if(next(v) != M.end()) cout << ", ";
                outf << idXi[v->first] << ' ' << idYi[v->second] << '\n';
        }
        outf.close();
        cout << "}\n";
        return 0;
}
