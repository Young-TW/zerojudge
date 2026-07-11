#include <iostream>
#include <string>

using namespace std;

string pre, in, post;

void buildTree(int preStart, int inStart, int len) {
    if (len <= 0) return;
    char root = pre[preStart];
    int rootIdxIn = inStart;
    while (in[rootIdxIn] != root) {
        rootIdxIn++;
    }
    int leftLen = rootIdxIn - inStart;
    int rightLen = len - leftLen - 1;
    
    buildTree(preStart + 1, inStart, leftLen);
    buildTree(preStart + 1 + leftLen, rootIdxIn + 1, rightLen);
    post += root;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> pre >> in) {
        post = "";
        buildTree(0, 0, pre.length());
        cout << post << "\n";
    }
    return 0;
}
