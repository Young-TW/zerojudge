#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, T;
    while (cin >> N >> T) {
        vector<vector<int>> signals(N, vector<int>(T));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < T; ++j) {
                cin >> signals[i][j];
            }
        }
        
        vector<int> and_res(T, 1);
        vector<int> or_res(T, 0);
        vector<int> xor_res(T, 0);
        
        for (int j = 0; j < T; ++j) {
            int cnt1 = 0;
            for (int i = 0; i < N; ++i) {
                if (signals[i][j] == 1) {
                    cnt1++;
                } else {
                    and_res[j] = 0;
                }
                or_res[j] = or_res[j] | signals[i][j];
            }
            xor_res[j] = cnt1 % 2;
        }
        
        cout << "AND:";
        for (int j = 0; j < T; ++j) {
            cout << " " << and_res[j];
        }
        cout << "\n";
        
        cout << " OR:";
        for (int j = 0; j < T; ++j) {
            cout << " " << or_res[j];
        }
        cout << "\n";
        
        cout << "XOR:";
        for (int j = 0; j < T; ++j) {
            cout << " " << xor_res[j];
        }
        cout << "\n";
    }
    
    return 0;
}
