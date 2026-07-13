#include <iostream>
#include <vector>

using namespace std;

int find(vector<int>& dsu, int i) {
    int root = i;
    while (dsu[root] != root) {
        root = dsu[root];
    }
    while (i != root) {
        int next = dsu[i];
        dsu[i] = root;
        i = next;
    }
    return root;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        if (n == 1) {
            cout << arr[0] << "\n";
            continue;
        }
        vector<int> nxt(n), pre(n), dsu(n);
        for (int i = 0; i < n; ++i) {
            nxt[i] = (i + 1) % n;
            pre[i] = (i - 1 + n) % n;
            if (arr[i] % 2 == 0) {
                dsu[i] = i;
            } else {
                dsu[i] = nxt[i];
            }
        }
        int alive = n;
        int curr = find(dsu, 0);
        while (alive > 1) {
            int victim = nxt[curr];
            int next_of_victim = nxt[victim];
            nxt[curr] = next_of_victim;
            pre[next_of_victim] = curr;
            dsu[victim] = next_of_victim;
            alive--;
            curr = find(dsu, next_of_victim);
        }
        cout << arr[curr] << "\n";
    }
    return 0;
}
