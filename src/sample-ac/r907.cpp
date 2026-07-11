#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    long long L;
    while (cin >> N >> L) {
        vector<long long> prefix(N+1);
        prefix[0] = 0;
        for (int i = 1; i <= N; i++) {
            long long a;
            cin >> a;
            prefix[i] = prefix[i-1] + a;
        }
        
        // start[i] = smallest j > i such that prefix[j] - prefix[i-1] > L, or N+1 if none
        vector<int> start(N+2);
        start[N+1] = N+1;
        int j = 1;
        for (int i = 1; i <= N; i++) {
            if (j <= i) j = i + 1;
            while (j <= N && prefix[j] - prefix[i-1] <= L) {
                j++;
            }
            start[i] = j;
        }
        
        // Binary lifting
        int LOG = 18;
        vector<vector<int>> jump(N+2, vector<int>(LOG+1));
        for (int i = 1; i <= N+1; i++) {
            jump[i][0] = start[i];
        }
        for (int k = 1; k <= LOG; k++) {
            for (int i = 1; i <= N+1; i++) {
                jump[i][k] = jump[jump[i][k-1]][k-1];
            }
        }
        
        for (int x = 1; x <= N; x++) {
            int pos = x;
            int count = 0;
            for (int k = LOG; k >= 0; k--) {
                if (jump[pos][k] <= N) {
                    pos = jump[pos][k];
                    count += (1 << k);
                }
            }
            count += 1;
            long long lastWeight = prefix[N] - prefix[pos-1];
            cout << count << " " << lastWeight << "\n";
        }
    }
    
    return 0;
}
