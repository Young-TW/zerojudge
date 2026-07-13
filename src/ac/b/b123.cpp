#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    while (cin >> M >> N) {
        vector<int> heights(N, 0);
        int max_area = 0;

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                int val;
                cin >> val;
                if (val == 1) {
                    heights[j]++;
                } else {
                    heights[j] = 0;
                }
            }

            vector<int> h = heights;
            h.push_back(0);
            h.insert(h.begin(), 0);

            stack<int> st;
            for (int j = 0; j < (int)h.size(); ++j) {
                while (!st.empty() && h[j] < h[st.top()]) {
                    int height = h[st.top()];
                    st.pop();
                    int width = j - st.top() - 1;
                    max_area = max(max_area, height * width);
                }
                st.push(j);
            }
        }

        cout << max_area << "\n";
    }

    return 0;
}
