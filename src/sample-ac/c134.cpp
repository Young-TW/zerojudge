#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        bool first_case = true;
        while (T--) {
            int N;
            cin >> N;
            vector<int> ans;
            int sum = 0;
            for (int i = 2; sum + i <= N; ++i) {
                ans.push_back(i);
                sum += i;
            }
            int diff = N - sum;
            if (diff > 0) {
                for (int i = (int)ans.size() - 1; i >= 0 && diff > 0; --i) {
                    ans[i]++;
                    diff--;
                }
                if (diff > 0) {
                    ans.back() += diff;
                }
            }
            
            if (!first_case) {
                cout << "\n";
            }
            first_case = false;
            
            for (size_t i = 0; i < ans.size(); ++i) {
                cout << ans[i] << (i + 1 == ans.size() ? "" : " ");
            }
            cout << "\n";
        }
    }
    return 0;
}
