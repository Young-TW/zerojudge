#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    while (cin >> N >> K) {
        priority_queue<int> max_heap;
        priority_queue<int, vector<int>, greater<int>> min_heap;

        max_heap.push(0);

        bool first_output = true;

        for (int i = 1; i <= N; ++i) {
            int x;
            cin >> x;

            if (x <= max_heap.top()) {
                max_heap.push(x);
            } else {
                min_heap.push(x);
            }

            if (max_heap.size() > min_heap.size() + 1) {
                min_heap.push(max_heap.top());
                max_heap.pop();
            } else if (min_heap.size() > max_heap.size()) {
                max_heap.push(min_heap.top());
                min_heap.pop();
            }

            if (i % K == 0) {
                if (!first_output) {
                    cout << " ";
                }
                cout << max_heap.top();
                first_output = false;
            }
        }
        cout << "\n";
    }

    return 0;
}
