#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <algorithm>
using namespace std;

// Fast input
static char ibuf[1 << 16];
static int ipos = 0, ilen = 0;

inline int readChar() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return EOF;
    }
    return ibuf[ipos++];
}

inline bool readInt(int& x) {
    int c = readChar();
    while (c != EOF && (c < '0' || c > '9') && c != '-') c = readChar();
    if (c == EOF) return false;
    bool neg = false;
    if (c == '-') { neg = true; c = readChar(); }
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = readChar();
    }
    if (neg) x = -x;
    return true;
}

inline bool readWord(char* buf) {
    int c = readChar();
    while (c != EOF && c <= ' ') c = readChar();
    if (c == EOF) return false;
    int i = 0;
    while (c > ' ') {
        buf[i++] = (char)c;
        c = readChar();
    }
    buf[i] = '\0';
    return true;
}

// Fast output
static char obuf[1 << 22];
static int opos = 0;

inline void writeChar(char c) {
    if (opos == (int)sizeof(obuf)) {
        fwrite(obuf, 1, opos, stdout);
        opos = 0;
    }
    obuf[opos++] = c;
}

inline void writeStr(const char* s, int len) {
    while (len > 0) {
        int remaining = (int)sizeof(obuf) - opos;
        if (len <= remaining) {
            memcpy(obuf + opos, s, len);
            opos += len;
            return;
        }
        memcpy(obuf + opos, s, remaining);
        fwrite(obuf, 1, sizeof(obuf), stdout);
        opos = 0;
        s += remaining;
        len -= remaining;
    }
}

inline void flushOut() {
    if (opos > 0) fwrite(obuf, 1, opos, stdout);
}

// RNG (xorshift32)
static uint32_t rng_state = 123456789;
inline uint32_t rng() {
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 17;
    rng_state ^= rng_state << 5;
    return rng_state;
}

// Treap rope node
struct Node {
    Node* left;
    Node* right;
    uint32_t priority;
    int chunkSize;
    int size;
    char* data;

    Node(const char* s, int len)
        : left(nullptr), right(nullptr), priority(rng()),
          chunkSize(len), size(len) {
        data = new char[len];
        memcpy(data, s, len);
    }
};

inline int getSize(Node* n) { return n ? n->size : 0; }

inline void update(Node* n) {
    n->size = getSize(n->left) + n->chunkSize + getSize(n->right);
}

// Split tree into (L, R) where L has first k characters
void split(Node* root, int k, Node*& L, Node*& R) {
    if (!root) { L = R = nullptr; return; }
    int leftSize = getSize(root->left);
    if (k <= leftSize) {
        split(root->left, k, L, root->left);
        update(root);
        R = root;
    } else if (k >= leftSize + root->chunkSize) {
        split(root->right, k - leftSize - root->chunkSize, root->right, R);
        update(root);
        L = root;
    } else {
        int offset = k - leftSize;
        Node* leftNode = new Node(root->data, offset);
        Node* rightNode = new Node(root->data + offset, root->chunkSize - offset);
        leftNode->left = root->left;
        rightNode->right = root->right;
        update(leftNode);
        update(rightNode);
        L = leftNode;
        R = rightNode;
    }
}

Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->priority > b->priority) {
        a->right = merge(a->right, b);
        update(a);
        return a;
    } else {
        b->left = merge(a, b->left);
        update(b);
        return b;
    }
}

// Output characters in range [k, k+n) from subtree starting at position 'start'
void rangeOutput(Node* node, int start, int k, int n) {
    if (!node || n <= 0) return;
    int leftSize = getSize(node->left);
    int chunkStart = start + leftSize;
    int chunkEnd = chunkStart + node->chunkSize;

    if (k < chunkStart) {
        rangeOutput(node->left, start, k, n);
    }

    int overlapStart = max(k, chunkStart);
    int overlapEnd = min(k + n, chunkEnd);
    if (overlapStart < overlapEnd) {
        writeStr(node->data + (overlapStart - chunkStart),
                 overlapEnd - overlapStart);
    }

    if (k + n > chunkEnd) {
        rangeOutput(node->right, chunkEnd, k, n);
    }
}

int main() {
    int t;
    char cmd[20];

    if (!readInt(t)) return 0;
    Node* root = nullptr;
    int cursor = 0;

    while (t--) {
        readWord(cmd);

        if (cmd[0] == 'I') { // Insert
            int n;
            readInt(n);
            char* s = new char[n];
            int count = 0;
            while (count < n) {
                int c = readChar();
                if (c == '\n' || c == '\r' || c == EOF) continue;
                s[count++] = (char)c;
            }
            Node *L, *R;
            split(root, cursor, L, R);
            Node* newNode = new Node(s, n);
            root = merge(L, merge(newNode, R));
            delete[] s;
        } else if (cmd[0] == 'D') { // Delete
            int n;
            readInt(n);
            Node *L, *R;
            split(root, cursor, L, R);
            Node *M, *RR;
            split(R, n, M, RR);
            root = merge(L, RR);
        } else if (cmd[0] == 'G') { // Get
            int n;
            readInt(n);
            rangeOutput(root, 0, cursor, n);
            writeChar('\n');
        } else if (cmd[0] == 'M') { // Move
            readInt(cursor);
        } else if (cmd[0] == 'P') { // Prev
            cursor--;
        } else if (cmd[0] == 'N') { // Next
            cursor++;
        }
    }

    flushOut();
    return 0;
}
