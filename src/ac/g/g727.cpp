#include <iostream>

using namespace std;

int parent[100005];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    while (cin >> n >> k) {
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
        int C = n;
        for (int i = 0; i < k; i++) {
            int x, y;
            cin >> x >> y;
            int rx = find(x);
            int ry = find(y);
            if (rx != ry) {
                parent[rx] = ry;
                C--;
            }
        }
        cout << k - n + C << "\n";
    }
    return 0;
}
