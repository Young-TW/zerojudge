#include <bits/stdc++.h>
using namespace std;

struct Node {
    int child[2];
    char ch;
    Node() {
        child[0] = child[1] = -1;
        ch = 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // ----- build the trie -------------------------------------------------
    vector<Node> trie(1);               // node 0 = root
    auto add = [&](const string& code, char c) {
        int cur = 0;
        for (char bit : code) {
            int b = bit - '0';
            if (trie[cur].child[b] == -1) {
                trie[cur].child[b] = (int)trie.size();
                trie.emplace_back();
            }
            cur = trie[cur].child[b];
        }
        trie[cur].ch = c;               // leaf
    };
    
    // table taken from the statement
    add("00",               ' ');
    add("010010",           '.');
    add("01011101000",      '!');
    add("01011110",         ',');
    add("0101111100100",    '?');
    add("010111011",        '0');
    add("110111100",        '1');
    add("010111000",        '2');
    add("11011110111",      '3');
    add("010111110011",     '4');
    add("0101110101",       '5');
    add("11011110100",      '6');
    add("01011101001",      '7');
    add("11011110101",      '8');
    add("0101111100101",    '9');
    add("1000",             'A');
    add("110110",           'B');
    add("10110",            'C');
    add("11010",            'D');
    add("1111",             'E');
    add("01010",            'F');
    add("010110",           'G');
    add("10101",            'H');
    add("0110",             'I');
    add("01011111000",      'J');
    add("010111111",        'K');
    add("10100",            'L');
    add("01000",            'M');
    add("0111",             'N');
    add("1001",             'O');
    add("010011",           'P');
    add("010111001",        'Q');
    add("11100",            'R');
    add("11101",            'S');
    add("1100",             'T');
    add("101111",           'U');
    add("11011111",         'V');
    add("1101110",          'W');
    add("0101111101",       'X');
    add("101110",           'Y');
    add("11011110110",      'Z');
    
    // ----- process each test case -----------------------------------------
    string s;
    while (cin >> s) {
        int cur = 0;
        string out;
        out.reserve(s.size() / 2);          // rough estimate
        for (char bit : s) {
            int b = bit - '0';
            cur = trie[cur].child[b];
            // leaf reached
            if (trie[cur].ch) {
                out.push_back(trie[cur].ch);
                cur = 0;                     // start next character
            }
        }
        cout << out << '\n';
    }
    return 0;
}
