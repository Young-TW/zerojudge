#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdint>
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

// RNG
static uint32_t rng_state = 123456789;
inline uint32_t rng() {
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 17;
    rng_state ^= rng_state << 5;
    return rng_state;
}

// Global buffer for all inserted strings
static const int MAX_BUFFER = 2 * 1024 * 1024 + 100;
static char buffer[MAX_BUFFER];
static int buffer_size = 0;

// Treap node
struct Node {
    Node* left;
    Node* right;
    uint32_t priority;
    int offset;
    int length;
    int size;
    
    Node(int off, int len) : left(nullptr), right(nullptr), priority(rng()),
                              offset(off), length(len), size(len) {}
};

inline int getSize(Node* n) { return n ? n->size : 0; }

inline void update(Node* n) {
    n->size = getSize(n->left) + n->length + getSize(n->right);
}

void split(Node* root, int k, Node*& L, Node*& R) {
    if (!root) { L = R = nullptr; return; }
    int leftSize = getSize(root->left);
    if (k <= leftSize) {
        split(root->left, k, L, root->left);
        update(root);
        R = root;
    } else if (k >= leftSize + root->length) {
        split(root->right, k - leftSize - root->length, root->right, R);
        update(root);
        L = root;
    } else {
        int off = k - leftSize;
        Node* leftNode = new Node(root->offset, off);
        Node* rightNode = new Node(root->offset + off, root->length - off);
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

void rangeOutput(Node* node, int start, int k, int n) {
    if (!node || n <= 0) return;
    int leftSize = getSize(node->left);
    int chunkStart = start + leftSize;
    int chunkEnd = chunkStart + node->length;
    
    if (k < chunkStart) {
        rangeOutput(node->left, start, k, n);
    }
    
    int overlapStart = max(k, chunkStart);
    int overlapEnd = min(k + n, chunkEnd);
    if (overlapStart < overlapEnd) {
        writeStr(buffer + node->offset + (overlapStart - chunkStart),
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
            int off = buffer_size;
            int count = 0;
            while (count < n) {
                int c = readChar();
                if (c == '\n' || c == '\r' || c == EOF) continue;
                buffer[buffer_size++] = (char)c;
                count++;
            }
            Node *L, *R;
            split(root, cursor, L, R);
            Node* newNode = new Node(off, n);
            root = merge(L, merge(newNode, R));
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
