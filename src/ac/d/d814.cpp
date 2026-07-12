#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 130005;
int arr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        for (int i = 0; i < N; ++i) {
            arr[i] = i + 1;
        }
        for (int i = 0; i < M; ++i) {
            int l, r;
            cin >> l >> r;
            reverse(arr + l - 1, arr + r);
        }
        for (int i = 0; i < N; ++i) {
            cout << arr[i];
            if (i < N - 1) cout << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}
