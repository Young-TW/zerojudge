#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

void push_min_heap(vector<int>& heap, int val) {
    heap.push_back(val);
    int i = heap.size() - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent] > heap[i]) {
            swap(heap[parent], heap[i]);
            i = parent;
        } else {
            break;
        }
    }
}

void push_max_heap(vector<int>& heap, int val) {
    heap.push_back(val);
    int i = heap.size() - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent] < heap[i]) {
            swap(heap[parent], heap[i]);
            i = parent;
        } else {
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> min_heap;
        vector<int> max_heap;
        min_heap.reserve(n);
        max_heap.reserve(n);
        
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            push_min_heap(min_heap, x);
            push_max_heap(max_heap, x);
        }
        
        for (int i = 0; i < n; ++i) {
            cout << min_heap[i];
            if (i < n - 1) cout << " ";
        }
        cout << "\n";
        
        for (int i = 0; i < n; ++i) {
            cout << max_heap[i];
            if (i < n - 1) cout << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
