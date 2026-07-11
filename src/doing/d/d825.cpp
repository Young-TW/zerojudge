#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n == 0) break;
        vector<int> st;
        st.reserve(n);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int w, h;
            cin >> w >> h;
            while (!st.empty() && st.back() > h) {
                st.pop_back();
            }
            if (st.empty() || st.back() < h) {
                ++ans;
                st.push_back(h);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
