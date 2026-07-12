#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        stack<int> s;
        queue<int> q;
        priority_queue<int> pq;

        bool is_stack = true;
        bool is_queue = true;
        bool is_pq = true;

        for (int i = 0; i < n; ++i) {
            int type, x;
            cin >> type >> x;

            if (type == 1) {
                s.push(x);
                q.push(x);
                pq.push(x);
            } else if (type == 2) {
                if (is_stack) {
                    if (!s.empty() && s.top() == x) {
                        s.pop();
                    } else {
                        is_stack = false;
                    }
                }
                if (is_queue) {
                    if (!q.empty() && q.front() == x) {
                        q.pop();
                    } else {
                        is_queue = false;
                    }
                }
                if (is_pq) {
                    if (!pq.empty() && pq.top() == x) {
                        pq.pop();
                    } else {
                        is_pq = false;
                    }
                }
            }
        }

        int possible_count = 0;
        if (is_stack) possible_count++;
        if (is_queue) possible_count++;
        if (is_pq) possible_count++;

        if (possible_count == 0) {
            cout << "impossible\n";
        } else if (possible_count > 1) {
            cout << "not sure\n";
        } else {
            if (is_stack) cout << "stack\n";
            else if (is_queue) cout << "queue\n";
            else if (is_pq) cout << "priority queue\n";
        }
    }

    return 0;
}
