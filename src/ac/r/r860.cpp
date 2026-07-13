#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<int> text(N), pattern(M);
        for (int i = 0; i < N; i++) cin >> text[i];
        for (int i = 0; i < M; i++) cin >> pattern[i];
        
        if (M == 0) {
            cout << 1 << "\n";
            continue;
        }
        if (N < M) {
            cout << "not found\n";
            continue;
        }
        
        // KMP failure function
        vector<int> fail(M, -1);
        for (int i = 1; i < M; i++) {
            int j = fail[i - 1];
            while (j >= 0 && pattern[j + 1] != pattern[i]) j = fail[j];
            if (pattern[j + 1] == pattern[i]) fail[i] = j + 1;
            else fail[i] = -1;
        }
        
        // KMP search
        int j = -1;
        int ans = -1;
        for (int i = 0; i < N; i++) {
            while (j >= 0 && pattern[j + 1] != text[i]) j = fail[j];
            if (pattern[j + 1] == text[i]) j++;
            if (j == M - 1) {
                ans = i - M + 1; // 0-indexed start
                break;
            }
        }
        
        if (ans == -1) cout << "not found\n";
        else cout << ans + 1 << "\n"; // 1-indexed
    }
    
    return 0;
}
