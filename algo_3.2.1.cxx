/* Lyndon Renaud 104 566 776
 * Final Project
 *
 * INPUT:
 * - The first line of input contains the vertices of X,
 *   separated by spaces
 * - The second line of input contains the vertices of Y,
 *   separated by spaces
 * - Up to |X||Y| lines follow, each containing an edge of G
 *   represented as two vertices separated by a space.
 * - An empty line follows
 * - Up to |X| lines follow, each containing an edge of G
 *   belonging to the matching M
 * - An empty line follows
 * - Up to |X|-|M| lines follow, each containing a vertex of U,
 *   the set of vertices in X not saturated by M
 */

#include "Bigraph.cxx"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <sstream>
#include <string>

using namespace std;
#define DEBUG 0


int main(){
        // X, Y are the partite sets of bigraph G
        // U is the set of vertices in X unsaturated by the matching
        vector<int> X, Y, U;
        // the edges (x, y) of G, where x is in X
        vector<pair<int, int>> edges;
        // a matching M mapping a vertex in X to a vertex in Y
        // Mi is the inverse of M, mapping a vertex in Y to a vertex in X
        unordered_map<int, int> M, Mi;
        // idX and idY map the string representation of vertices in X and Y respectively
        // to an integer from 0 to |X| and 0 to |Y| respectively
        unordered_map<string, int> idX, idY;
        // idYi and idXi is the inverse of idX and idY. These are only used for displaying
        // the output properly.
        unordered_map<int, string> idYi, idXi;

        string line;
        string vertex, vertex2;
        // populate X set
        getline(cin, line);
        stringstream in(line);
        while(in >> vertex){
                idX[vertex] = idX.size();
                idXi[idX.size()-1] = vertex;
                X.push_back(idX[vertex]);
        }
        in.clear();

        // populate Y set
        getline(cin, line);
        in.str(line);
        while(in >> vertex){
                idY[vertex] = idY.size();
                idYi[idY.size()-1] = vertex;
                Y.push_back(idY[vertex]);
        }
        in.clear();

        // populate edge set
        while(getline(cin, line) && !line.empty()){
                in.str(line);
                in >> vertex >> vertex2;
                edges.push_back({idX[vertex], idY[vertex2]});
                in.clear();
        }

        // Create Graph object G, the X,Y-bigraph
        Bigraph G(X, Y, edges);

        // populate matching hash map M and M inverse
        while(getline(cin, line) && !line.empty()){
                in.str(line);
                in >> vertex >> vertex2; in.clear();
                M[idX[vertex]] = idY[vertex2];
                Mi[idY[vertex2]] = idX[vertex];
        }

        // populate U, the set of vertices in X unsaturated by M
        while(cin >> vertex) U.push_back(idX[vertex]);

        // Now the input has been processed, so we can begin the algorithm
        // First we initialize S = U and T = {}
        set<int> S(U.begin(), U.end()), T;

        // unmarked is the set of unmarked vertices of S
        // marked is the set of marked vertices in S
        // initially, all vertices in S are unmarked
        set<int> unmarked(S.begin(), S.end()), marked;

        // augmenting path flag. set to true if an augmenting path is found
        bool aug = false;
        int endpoint;   // M-augmenting path endpoint in Y

        // Repeat iteration while S has unmarked vertices
        while(unmarked.size() > 0){
                int x = *unmarked.begin(); // pick some unmarked vertex in S
                for(int y : G.getNeighbors(x)){
                        // if edge xy is not in M and y in Y is saturated by M
                        if((M.find(x) == M.end() || M[x] != y) && Mi.find(y) != Mi.end()){
                                // include y in T (reached from x)
                                T.insert(x);
                                // include w in S (reached from y)
                                S.insert(Mi[y]);
                                if(marked.find(Mi[y]) == marked.end())
                                        unmarked.insert(Mi[y]);
                        }
                        // if edge xy is not in M and y in Y is unsaturated by M
                        else if((M.find(x) == M.end() || M[x] != y) && Mi.find(y) == Mi.end()){
                                aug = true; // there exists an M augmenting path from U to y
                                endpoint = y;   // store M-augmenting path endpoint in Y
                                break;
                        }
                }
                if(aug) break; // loop exit condition met (M-augmenting path found)
                // we are done exploring all such edges incident to x.
                // Mark x in S and iterate
                unmarked.erase(x);
                marked.insert(x);
        }
        if(aug){
                cout << "There is an M-augmenting path from U = {";
                for(auto v = U.begin(); v != U.end(); ++v){
                        cout << idXi[*v];
                        if(distance(v, U.end()) > 1) cout << ", ";
                }
                cout << "} to " << idYi[endpoint] << '\n';
        }
        else{
                // T union (X-S) is a minimum cover
                set<int> min_cover_y(T.begin(), T.end()), min_cover_x;
                for(int v : X) if(S.find(v) == S.end()) min_cover_x.insert(v); // min_cover = min_cover union X-S

                // report M as a maximum matching
                cout << "M is a maximum matching in G.\n"
                        << "A minimum vertex cover in G is T union (X-S) = {";
                for(auto v = min_cover_x.begin(); v != min_cover_x.end(); ++v){
                        cout << idXi[*v];
                        if(distance(v, min_cover_x.end()) > 1) cout << ", ";
                        else if(!min_cover_y.empty()) cout << ", ";
                }
                for(auto v = min_cover_y.begin(); v != min_cover_y.end(); ++v){
                        cout << idYi[*v];
                        if(distance(v, min_cover_y.end()) > 1) cout << ", ";
                }
                cout << "}\n";
        }

        return 0;
}
