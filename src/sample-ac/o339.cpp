#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int BUFFER_SIZE = 1 << 20;
char input_buffer[BUFFER_SIZE];
int input_pos = 0, input_len = 0;
char output_buffer[BUFFER_SIZE];
int output_pos = 0;

inline char get_char() {
    if (input_pos == input_len) {
        input_len = fread(input_buffer, 1, BUFFER_SIZE, stdin);
        input_pos = 0;
        if (input_len == 0) return EOF;
    }
    return input_buffer[input_pos++];
}

inline void flush_output() {
    if (output_pos > 0) {
        fwrite(output_buffer, 1, output_pos, stdout);
        output_pos = 0;
    }
}

inline void write_char(char c) {
    if (output_pos == BUFFER_SIZE) flush_output();
    output_buffer[output_pos++] = c;
}

template<typename T>
inline void read_int(T &x) {
    x = 0;
    char c = get_char();
    while (c < '0' || c > '9') {
        if (c == EOF) return;
        c = get_char();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
}

template<typename T>
inline void write_int(T x) {
    if (x == 0) {
        write_char('0');
        return;
    }
    char temp[25];
    int len = 0;
    while (x > 0) {
        temp[len++] = '0' + (x % 10);
        x /= 10;
    }
    while (len > 0) {
        write_char(temp[--len]);
    }
}

const int MAXN = 1000005;
const int MAX_SHOP = 2000005;

int parent[MAX_SHOP];
long long salary[MAX_SHOP];
int emp_to_shop[MAXN];

int find(int x) {
    int root = x;
    while (parent[root] != root) {
        root = parent[root];
    }
    while (parent[x] != root) {
        int next = parent[x];
        parent[x] = root;
        x = next;
    }
    return root;
}

int main() {
    int T;
    read_int(T);
    while (T--) {
        int N, Q;
        read_int(N);
        read_int(Q);
        
        int shop_cnt = N;
        for (int i = 1; i <= N; ++i) {
            read_int(salary[i]);
            parent[i] = i;
            emp_to_shop[i] = i;
        }
        for (int i = N + 1; i <= N + Q + 1; ++i) {
            parent[i] = i;
            salary[i] = 0;
        }

        for (int i = 0; i < Q; ++i) {
            int k;
            read_int(k);
            if (k == 1) {
                int a, b;
                read_int(a);
                read_int(b);
                int shop_a = emp_to_shop[a];
                int shop_b = emp_to_shop[b];
                int root_a = find(shop_a);
                int root_b = find(shop_b);
                if (root_a != root_b) {
                    parent[root_b] = root_a;
                }
            } else if (k == 2) {
                int a;
                long long R;
                read_int(a);
                read_int(R);
                int shop_a = emp_to_shop[a];
                int root_a = find(shop_a);
                salary[root_a] += R;
            } else if (k == 3) {
                int a;
                long long C;
                read_int(a);
                read_int(C);
                shop_cnt++;
                emp_to_shop[a] = shop_cnt;
                salary[shop_cnt] = C;
                parent[shop_cnt] = shop_cnt;
            }
        }

        for (int i = 1; i <= N; ++i) {
            int shop_i = emp_to_shop[i];
            int root_i = find(shop_i);
            write_int(salary[root_i]);
            write_char(i == N ? '\n' : ' ');
        }
    }
    flush_output();
    return 0;
}
