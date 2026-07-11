#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N && N) {
        vector<int> ans;
        bool has_non_zero = false;
        for (int i = 0; i < N; ++i) {
            int x;
            cin >> x;
            if (x != 0) {
                ans.push_back(x);
                has_non_zero = true;
            }
        }
        
        if (!has_non_zero) {
            cout << "0\n";
        } else {
            for (size_t i = 0; i < ans.size(); ++i) {
                if (i > 0) cout << " ";
                cout << ans[i];
            }
            cout << "\n";
        }
    }
    return 0;
}
