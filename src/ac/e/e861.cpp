#include <cstdio>
#include <climits>

using namespace std;

const int MAXQ = 2000005;
const int BUFFER_SIZE = 1 << 20;

struct Node {
    int val;
    int prev;
};

Node nodes[MAXQ];
int head[MAXQ];
int node_cnt = 0;

char input_buffer[BUFFER_SIZE];
int input_pos = 0;
int input_len = 0;

inline char get_char() {
    if (input_pos == input_len) {
        input_len = fread(input_buffer, 1, BUFFER_SIZE, stdin);
        input_pos = 0;
        if (input_len == 0) return EOF;
    }
    return input_buffer[input_pos++];
}

inline int readInt() {
    char c = get_char();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == EOF) return INT_MIN;
        c = get_char();
    }
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = get_char();
    }
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return neg ? -x : x;
}

char output_buffer[BUFFER_SIZE];
int output_pos = 0;

inline void flush_output() {
    if (output_pos > 0) {
        fwrite(output_buffer, 1, output_pos, stdout);
        output_pos = 0;
    }
}

inline void writeChar(char c) {
    if (output_pos == BUFFER_SIZE) {
        flush_output();
    }
    output_buffer[output_pos++] = c;
}

inline void writeInt(int x) {
    if (x < 0) {
        writeChar('-');
        x = -x;
    }
    if (x == 0) {
        writeChar('0');
        return;
    }
    char temp[12];
    int len = 0;
    while (x > 0) {
        temp[len++] = '0' + (x % 10);
        x /= 10;
    }
    while (len > 0) {
        writeChar(temp[--len]);
    }
}

int main() {
    nodes[0].prev = 0;
    nodes[0].val = 0;
    head[0] = 0;

    int op_cnt = 0;
    int op;
    while ((op = readInt()) != INT_MIN) {
        op_cnt++;
        if (op == 0) {
            int v = readInt();
            head[op_cnt] = head[v];
        } else if (op == 1) {
            int x = readInt();
            node_cnt++;
            nodes[node_cnt].val = x;
            nodes[node_cnt].prev = head[op_cnt - 1];
            head[op_cnt] = node_cnt;
        } else if (op == 2) {
            head[op_cnt] = nodes[head[op_cnt - 1]].prev;
        } else if (op == 3) {
            head[op_cnt] = head[op_cnt - 1];
            int curr = head[op_cnt];
            int count = 0;
            int vals[3];
            while (curr != 0 && count < 3) {
                vals[count++] = nodes[curr].val;
                curr = nodes[curr].prev;
            }
            if (count == 0) {
                writeChar(']');
                writeChar('\n');
            } else if (count < 3) {
                for (int i = 0; i < count; ++i) {
                    writeInt(vals[i]);
                    writeChar(' ');
                }
                writeChar(']');
                writeChar('\n');
            } else {
                for (int i = 0; i < 3; ++i) {
                    writeInt(vals[i]);
                    writeChar(' ');
                }
                if (curr != 0) {
                    writeChar('.'); writeChar('.'); writeChar('.'); writeChar(' ');
                }
                writeChar(']');
                writeChar('\n');
            }
        }
    }
    flush_output();
    return 0;
}
