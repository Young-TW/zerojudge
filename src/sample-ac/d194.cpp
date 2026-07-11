#include <iostream>
#include <cstdio>

using namespace std;

const int HASH_SIZE = 2000003;
int hash_key[HASH_SIZE];
int hash_val[HASH_SIZE];
int hash_time[HASH_SIZE];
int current_time = 0;

inline int query(int key) {
    int h = key % HASH_SIZE;
    while (hash_time[h] == current_time && hash_key[h] != key) {
        h = (h + 1) % HASH_SIZE;
    }
    if (hash_time[h] == current_time && hash_key[h] == key) {
        return hash_val[h];
    }
    return -1;
}

inline void update(int key, int val) {
    int h = key % HASH_SIZE;
    while (hash_time[h] == current_time && hash_key[h] != key) {
        h = (h + 1) % HASH_SIZE;
    }
    hash_key[h] = key;
    hash_val[h] = val;
    hash_time[h] = current_time;
}

inline int readInt() {
    int x = 0;
    char c = getchar();
    while (c != EOF && (c < '0' || c > '9')) {
        c = getchar();
    }
    if (c == EOF) return -1;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

int main() {
    int T = readInt();
    while (T--) {
        int n = readInt();
        current_time++;
        int max_len = 0;
        int left = 0;
        for (int i = 0; i < n; ++i) {
            int x = readInt();
            int last = query(x);
            if (last >= left) {
                left = last + 1;
            }
            update(x, i);
            if (i - left + 1 > max_len) {
                max_len = i - left + 1;
            }
        }
        cout << max_len << "\n";
    }
    return 0;
}
