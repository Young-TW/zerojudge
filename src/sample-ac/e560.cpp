#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int M, N;
    while (cin >> M >> N && (M || N)) {
        vector<int> h(N, 0);
        int max_area = 0;
        
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                int val;
                cin >> val;
                if (val == 0) {
                    h[j]++;
                } else {
                    h[j] = 0;
                }
            }
            
            vector<int> st;
            for (int j = 0; j <= N; ++j) {
                int cur_h = (j == N) ? 0 : h[j];
                while (!st.empty() && h[st.back()] > cur_h) {
                    int height = h[st.back()];
                    st.pop_back();
                    int width;
                    if (st.empty()) {
                        width = j;
                    } else {
                        width = j - st.back() - 1;
                    }
                    max_area = max(max_area, height * width);
                }
                st.push_back(j);
            }
        }
        cout << max_area << "\n";
    }
    
    return 0;
}
