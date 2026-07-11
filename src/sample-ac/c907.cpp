#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<int> h(n);
        for (int i = 0; i < n; ++i) {
            cin >> h[i];
        }

        stack<int> s;
        long long max_area = 0;
        
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && h[s.top()] > h[i]) {
                int top = s.top();
                s.pop();
                long long width = s.empty() ? i : (long long)(i - s.top() - 1);
                max_area = max(max_area, (long long)h[top] * width);
            }
            s.push(i);
        }

        while (!s.empty()) {
            int top = s.top();
            s.pop();
            long long width = s.empty() ? n : (long long)(n - s.top() - 1);
            max_area = max(max_area, (long long)h[top] * width);
        }

        cout << max_area << "\n";
    }

    return 0;
}
