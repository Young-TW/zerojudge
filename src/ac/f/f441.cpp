#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<int> correct(N);
        for (int i = 0; i < N; i++) {
            cin >> correct[i];
        }
        int K;
        cin >> K;
        while (K--) {
            int cnt = 0;
            for (int i = 0; i < N; i++) {
                int x;
                cin >> x;
                if (x == correct[i]) cnt++;
            }
            cout << (long long)cnt * M << "\n";
        }
    }
    return 0;
}
