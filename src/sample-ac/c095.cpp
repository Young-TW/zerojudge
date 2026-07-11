#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int M;
    if (cin >> M) {
        for (int t = 0; t < M; ++t) {
            int N, K;
            cin >> N >> K;
            vector<int> state(N + 1, 3); // 3: unknown, 1: heavy, 2: light, 0: impossible
            
            for (int k = 0; k < K; ++k) {
                int P;
                cin >> P;
                vector<int> left(P), right(P);
                for (int i = 0; i < P; ++i) cin >> left[i];
                for (int i = 0; i < P; ++i) cin >> right[i];
                string op;
                cin >> op;
                
                if (op == "=") {
                    for (int i = 0; i < P; ++i) {
                        state[left[i]] = 0;
                        state[right[i]] = 0;
                    }
                } else {
                    vector<bool> inWeighing(N + 1, false);
                    for (int i = 0; i < P; ++i) {
                        inWeighing[left[i]] = true;
                        inWeighing[right[i]] = true;
                    }
                    for (int i = 1; i <= N; ++i) {
                        if (!inWeighing[i]) {
                            state[i] = 0;
                        }
                    }
                    
                    if (op == "<") {
                        for (int i = 0; i < P; ++i) {
                            state[left[i]] &= 2;  // left can only be light
                            state[right[i]] &= 1; // right can only be heavy
                        }
                    } else if (op == ">") {
                        for (int i = 0; i < P; ++i) {
                            state[left[i]] &= 1;  // left can only be heavy
                            state[right[i]] &= 2; // right can only be light
                        }
                    }
                }
            }
            
            int ans = 0;
            int count = 0;
            for (int i = 1; i <= N; ++i) {
                if (state[i] != 0) {
                    count++;
                    ans = i;
                }
            }
            
            if (t > 0) cout << "\n";
            if (count == 1) {
                cout << ans << "\n";
            } else {
                cout << 0 << "\n";
            }
        }
    }
    
    return 0;
}
