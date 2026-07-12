#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <functional>
#include <numeric>

using namespace std;

int heap[2005];
int heap_size;
int type;

void heapify(int i) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int target = i;
    
    if (type == 1) { // MinHeap
        if (left <= heap_size && heap[left] < heap[target]) {
            target = left;
        }
        if (right <= heap_size && heap[right] < heap[target]) {
            target = right;
        }
    } else { // MaxHeap
        if (left <= heap_size && heap[left] > heap[target]) {
            target = left;
        }
        if (right <= heap_size && heap[right] > heap[target]) {
            target = right;
        }
    }
    
    if (target != i) {
        swap(heap[i], heap[target]);
        heapify(target);
    }
}

void push_up(int i) {
    while (i > 1) {
        int parent = i / 2;
        if (type == 1) { // MinHeap
            if (heap[i] < heap[parent]) {
                swap(heap[i], heap[parent]);
                i = parent;
            } else {
                break;
            }
        } else { // MaxHeap
            if (heap[i] > heap[parent]) {
                swap(heap[i], heap[parent]);
                i = parent;
            } else {
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    bool first_case = true;
    while (cin >> type) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        
        int N;
        cin >> N;
        heap_size = N;
        for (int i = 1; i <= N; i++) {
            cin >> heap[i];
        }
        
        for (int i = heap_size / 2; i >= 1; i--) {
            heapify(i);
        }
        
        int M;
        cin >> M;
        for (int i = 0; i < M; i++) {
            int cmd;
            cin >> cmd;
            if (cmd == 1) {
                int x, y;
                cin >> x >> y;
                if (y > heap_size) {
                    y = heap_size;
                }
                for (int j = x; j <= y; j++) {
                    cout << heap[j];
                    if (j < y) {
                        cout << " ";
                    }
                }
                cout << "\n";
            } else if (cmd == 2) {
                int x;
                cin >> x;
                heap_size++;
                heap[heap_size] = x;
                push_up(heap_size);
            } else if (cmd == 3) {
                if (heap_size > 0) {
                    heap[1] = heap[heap_size];
                    heap_size--;
                    if (heap_size > 0) {
                        heapify(1);
                    }
                }
            }
        }
    }
    
    return 0;
}
