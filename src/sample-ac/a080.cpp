#include <iostream>
#include <string>

using namespace std;

int trie[33000][26];
int nodeCount = 0;

void insert(const string& s) {
    int curr = 0;
    for (int i = 0; i < (int)s.length(); ++i) {
        int idx = s[i] - 'A';
        if (trie[curr][idx] == 0) {
            trie[curr][idx] = ++nodeCount;
        }
        curr = trie[curr][idx];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        insert(s);
    }
    
    cout << nodeCount + 1 << "\n";
    return 0;
}
