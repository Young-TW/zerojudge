#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x;
    priority_queue<int> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;
    
    while (cin >> x) {
        if (max_heap.empty() || x <= max_heap.top()) {
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
        
        if (max_heap.size() > min_heap.size()) {
            cout << max_heap.top() << "\n";
        } else {
            cout << ((long long)max_heap.top() + min_heap.top()) / 2 << "\n";
        }
    }
    
    return 0;
}
