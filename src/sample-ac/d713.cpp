#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    priority_queue<int> max_heap; // stores smaller half, top is max
    priority_queue<int, vector<int>, greater<int>> min_heap; // stores larger half, top is min
    
    int x;
    while (cin >> x) {
        if (max_heap.empty() || x <= max_heap.top()) {
            max_heap.push(x);
        } else {
            min_heap.push(x);
        }
        
        // rebalance
        if (max_heap.size() > min_heap.size() + 1) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        } else if (min_heap.size() > max_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
        
        // output median
        if (max_heap.size() == min_heap.size()) {
            cout << (max_heap.top() + min_heap.top()) / 2 << '\n';
        } else {
            cout << max_heap.top() << '\n';
        }
    }
    
    return 0;
}
