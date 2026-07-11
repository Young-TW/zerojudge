#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int BUFFER_SIZE = 1 << 20;
char buf[BUFFER_SIZE];
int buf_pos = 0, buf_len = 0;

inline char get_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, BUFFER_SIZE, stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return buf[buf_pos++];
}

inline long long readLL() {
    long long x = 0;
    char c = get_char();
    while (c < '0' || c > '9') {
        if (c == EOF) return -1;
        c = get_char();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return x;
}

inline int readInt() {
    int x = 0;
    char c = get_char();
    while (c < '0' || c > '9') {
        if (c == EOF) return -1;
        c = get_char();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return x;
}

int main() {
    int N, K;
    vector<long long> heap;
    
    while ((N = readInt()) != -1) {
        K = readInt();
        if (K == -1) break;
        
        if (K >= N) {
            long long maxT = 0;
            for (int i = 0; i < N; ++i) {
                long long T = readLL();
                if (T > maxT) maxT = T;
            }
            cout << maxT << "\n";
        } else {
            if ((int)heap.size() < K) {
                heap.resize(K);
            }
            fill(heap.begin(), heap.begin() + K, 0);
            
            for (int i = 0; i < N; ++i) {
                long long T = readLL();
                long long new_val = heap[0] + T;
                heap[0] = new_val;
                
                int cur = 0;
                while (true) {
                    int left = 2 * cur + 1;
                    int right = 2 * cur + 2;
                    int smallest = cur;
                    if (left < K && heap[left] < heap[smallest]) smallest = left;
                    if (right < K && heap[right] < heap[smallest]) smallest = right;
                    if (smallest == cur) break;
                    swap(heap[cur], heap[smallest]);
                    cur = smallest;
                }
            }
            
            long long ans = 0;
            for (int i = 0; i < K; ++i) {
                if (heap[i] > ans) ans = heap[i];
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
