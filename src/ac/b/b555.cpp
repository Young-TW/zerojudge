#include <cstdio>

using namespace std;

const int MAXN = 1005;
int parent[MAXN][MAXN];
int N, M, Q;

int find(int i, int j) {
    if (j > M) return M + 1;
    int root = j;
    while (parent[i][root] != root) {
        root = parent[i][root];
    }
    while (parent[i][j] != root) {
        int next = parent[i][j];
        parent[i][j] = root;
        j = next;
    }
    return root;
}

inline int readInt() {
    int x = 0;
    char c = getchar();
    if (c == EOF) return -1;
    while (c < '0' || c > '9') {
        c = getchar();
        if (c == EOF) return -1;
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

char output_buf[25000005];
int out_pos = 0;

inline void writeInt(int x) {
    if (x == 0) {
        output_buf[out_pos++] = '0';
        return;
    }
    char temp[12];
    int len = 0;
    while (x) {
        temp[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len > 0) {
        output_buf[out_pos++] = temp[--len];
    }
}

inline void writeChar(char c) {
    output_buf[out_pos++] = c;
}

inline void writeCoord(int x, int y) {
    writeChar('(');
    writeInt(x);
    writeChar(',');
    writeChar(' ');
    writeInt(y);
    writeChar(')');
}

int main() {
    while (true) {
        N = readInt();
        if (N == -1) break;
        M = readInt();
        Q = readInt();

        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M + 1; ++j) {
                parent[i][j] = j;
            }
        }

        static int coords_x[1000005];
        static int coords_y[1000005];

        for (int q = 0; q < Q; ++q) {
            int lx = readInt();
            int ly = readInt();
            int rx = readInt();
            int ry = readInt();

            int coord_count = 0;

            for (int i = lx; i <= rx; ++i) {
                int j = find(i, ly);
                while (j <= ry) {
                    coords_x[coord_count] = i;
                    coords_y[coord_count] = j;
                    coord_count++;
                    parent[i][j] = find(i, j + 1);
                    j = find(i, j);
                }
            }

            writeInt(coord_count);
            for (int i = 0; i < coord_count; ++i) {
                writeChar(' ');
                writeCoord(coords_x[i], coords_y[i]);
            }
            writeChar('\n');
        }

        fwrite(output_buf, 1, out_pos, stdout);
        out_pos = 0;
    }

    return 0;
}
