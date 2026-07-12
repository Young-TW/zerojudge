#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> heap;
    char op;
    int a;
    
    while (cin >> op) {
        if (op == 'I') {
            cin >> a;
            heap.push_back(a);
            int idx = heap.size() - 1;
            while (idx > 0) {
                int parent = (idx - 1) / 2;
                if (heap[idx] > heap[parent]) {
                    swap(heap[idx], heap[parent]);
                    idx = parent;
                } else {
                    break;
                }
            }
        } else if (op == 'D') {
            cout << heap[0] << "\n";
            heap[0] = heap.back();
            heap.pop_back();
            if (!heap.empty()) {
                int idx = 0;
                int n = heap.size();
                while (true) {
                    int left = 2 * idx + 1;
                    int right = 2 * idx + 2;
                    int largest = idx;
                    if (left < n && heap[left] > heap[largest]) {
                        largest = left;
                    }
                    if (right < n && heap[right] > heap[largest]) {
                        largest = right;
                    }
                    if (largest != idx) {
                        swap(heap[idx], heap[largest]);
                        idx = largest;
                    } else {
                        break;
                    }
                }
            }
        }
    }
    
    return 0;
}
