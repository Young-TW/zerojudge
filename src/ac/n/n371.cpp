#include <iostream>

using namespace std;

const int MAXN = 1000005;
int parent[MAXN];
bool dead[MAXN];
int N;

int find(int i) {
    if (i > N) return N + 1;
    int root = i;
    while (parent[root] != root) {
        root = parent[root];
    }
    while (i != root) {
        int nxt = parent[i];
        parent[i] = root;
        i = nxt;
    }
    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M;
    while (cin >> N >> M) {
        for (int i = 1; i <= N + 1; ++i) {
            parent[i] = i;
            dead[i] = false;
        }
        for (int i = 0; i < M; ++i) {
            int x;
            cin >> x;
            if (dead[x]) {
                cout << "我大意了啊~沒有閃\n";
            } else {
                int first = find(x + 1);
                if (first > N) {
                    cout << "來~ 騙\n";
                } else {
                    int second = find(first + 1);
                    if (second > N) {
                        cout << "來~ 騙\n";
                    } else {
                        cout << second << "\n";
                        dead[second] = true;
                        parent[second] = find(second + 1);
                    }
                }
            }
        }
    }
    return 0;
}
