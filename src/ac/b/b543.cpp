#include <iostream>
#include <cstring>

using namespace std;

const int MAX_N = 5005;
int a[MAX_N], b[MAX_N], c[MAX_N];
bool visited[MAX_N];
int q[MAX_N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            for (int i = 1; i <= N; ++i) {
                cin >> a[i] >> b[i] >> c[i];
            }
            int s;
            cin >> s;
            
            memset(visited, 0, sizeof(bool) * (N + 1));
            
            int head = 0, tail = 0;
            q[tail++] = s;
            visited[s] = true;
            int count = 1;
            
            while (head < tail) {
                int u = q[head++];
                int au = a[u], bu = b[u];
                for (int v = 1; v <= N; ++v) {
                    if (!visited[v]) {
                        if (a[v] < au && c[v] < bu) {
                            visited[v] = true;
                            q[tail++] = v;
                            count++;
                        }
                    }
                }
            }
            cout << count << "\n";
        }
    }
    
    return 0;
}
