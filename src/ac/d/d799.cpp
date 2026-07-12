#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 500005;
long long tree[MAXN * 4];
long long lazy[MAXN * 4];
int arr[MAXN];

void push_up(int node) {
    tree[node] = tree[node << 1] + tree[node << 1 | 1];
}

void push_down(int node, int start, int end) {
    if (lazy[node]) {
        int mid = (start + end) >> 1;
        int left_child = node << 1;
        int right_child = node << 1 | 1;
        
        lazy[left_child] += lazy[node];
        tree[left_child] += lazy[node] * (mid - start + 1);
        
        lazy[right_child] += lazy[node];
        tree[right_child] += lazy[node] * (end - mid);
        
        lazy[node] = 0;
    }
}

void build(int node, int start, int end) {
    lazy[node] = 0;
    if (start == end) {
        tree[node] = arr[start];
        return;
    }
    int mid = (start + end) >> 1;
    build(node << 1, start, mid);
    build(node << 1 | 1, mid + 1, end);
    push_up(node);
}

void update_range(int node, int start, int end, int l, int r, long long val) {
    if (l <= start && end <= r) {
        tree[node] += val * (end - start + 1);
        lazy[node] += val;
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) >> 1;
    if (l <= mid) {
        update_range(node << 1, start, mid, l, r, val);
    }
    if (r > mid) {
        update_range(node << 1 | 1, mid + 1, end, l, r, val);
    }
    push_up(node);
}

long long query_range(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node];
    }
    push_down(node, start, end);
    int mid = (start + end) >> 1;
    long long sum = 0;
    if (l <= mid) {
        sum += query_range(node << 1, start, mid, l, r);
    }
    if (r > mid) {
        sum += query_range(node << 1 | 1, mid + 1, end, l, r);
    }
    return sum;
}

const int BUF_SIZE = 1 << 20;
char buf[BUF_SIZE];
int buf_pos = 0;
int buf_len = 0;

inline char get_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, BUF_SIZE, stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return buf[buf_pos++];
}

inline int readInt() {
    char c = get_char();
    while (c != EOF && (c < '0' || c > '9')) {
        c = get_char();
    }
    if (c == EOF) return -1;
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return x;
}

char out_buf[BUF_SIZE];
int out_pos = 0;

inline void flush_out() {
    if (out_pos > 0) {
        fwrite(out_buf, 1, out_pos, stdout);
        out_pos = 0;
    }
}

inline void write_char(char c) {
    if (out_pos == BUF_SIZE) {
        flush_out();
    }
    out_buf[out_pos++] = c;
}

inline void writeLL(long long x) {
    if (x == 0) {
        write_char('0');
        write_char('\n');
        return;
    }
    char temp[20];
    int p = 0;
    while (x > 0) {
        temp[p++] = x % 10 + '0';
        x /= 10;
    }
    while (p > 0) {
        write_char(temp[--p]);
    }
    write_char('\n');
}

int main() {
    int n = readInt();
    if (n <= 0) return 0;
    for (int i = 1; i <= n; ++i) {
        arr[i] = readInt();
    }
    build(1, 1, n);
    
    int q = readInt();
    while (q--) {
        int v = readInt();
        if (v == 1) {
            int x = readInt();
            int y = readInt();
            int k = readInt();
            update_range(1, 1, n, x, y, k);
        } else {
            int x = readInt();
            int y = readInt();
            long long res = query_range(1, 1, n, x, y);
            writeLL(res);
        }
    }
    flush_out();
    return 0;
}
