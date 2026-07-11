#include <iostream>

using namespace std;

int parent[20005];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void unite(int i, int j) {
    int rootI = find(i);
    int rootJ = find(j);
    if (rootI != rootJ) {
        parent[rootI] = rootJ;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        for (int i = 0; i < 2 * N; ++i) {
            parent[i] = i;
        }
        
        int c, x, y;
        while (cin >> c >> x >> y) {
            if (c == 0 && x == 0 && y == 0) break;
            
            if (c == 1) { // setFriends
                if (find(x) == find(y + N) || find(x + N) == find(y)) {
                    cout << "-1\n";
                } else {
                    unite(x, y);
                    unite(x + N, y + N);
                }
            } else if (c == 2) { // setEnemies
                if (find(x) == find(y) || find(x + N) == find(y + N)) {
                    cout << "-1\n";
                } else {
                    unite(x, y + N);
                    unite(x + N, y);
                }
            } else if (c == 3) { // areFriends
                if (find(x) == find(y)) {
                    cout << "1\n";
                } else {
                    cout << "0\n";
                }
            } else if (c == 4) { // areEnemies
                if (find(x) == find(y + N)) {
                    cout << "1\n";
                } else {
                    cout << "0\n";
                }
            }
        }
    }
    return 0;
}
