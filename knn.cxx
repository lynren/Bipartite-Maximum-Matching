/* Input: an integer x, the size of the partite set X, followed by a space.
 * An integer y, the size of the partite set Y, follows the space.
 *
 * Output:
 * First line of output contains the vertices of X separated by spaces
 * Second line of output contains the vertices of Y separated by spaces
 * The following |X||Y| lines each contain one edge in the complete X,Y-bigraph.
 */

#include <iostream>

using namespace std;

int main(){
        int X_size, Y_size;
        cin >> X_size >> Y_size;
        for(int i = 0; i < X_size; ++i) cout << 'x'  << i << ' ';
        cout << '\n';
        for(int i = 0; i < Y_size; ++i) cout << 'y' << i << ' ';
        cout << '\n';
        for(int i = 0; i < X_size; ++i)
                for(int j = 0; j < Y_size; ++j)
                        cout << 'x' << i << " y" << j << '\n';

        return 0;
}
