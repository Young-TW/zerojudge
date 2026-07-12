#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int K;
    while (cin >> K && K != 0) {
        int N, M;
        cin >> N >> M;
        for (int i = 0; i < K; ++i) {
            int X, Y;
            cin >> X >> Y;
            if (X == N || Y == M) {
                cout << "divisa\n";
            } else if (X > N && Y > M) {
                cout << "NE\n";
            } else if (X < N && Y > M) {
                cout << "NO\n";
            } else if (X > N && Y < M) {
                cout << "SE\n";
            } else {
                cout << "SO\n";
            }
        }
    }
    
    return 0;
}
