#include <bits/stdc++.h>
using namespace std;

// Editing a word under replace/remove/addhead/addtail.
// Efficient approach: each occurrence stores a "group id".
// A DSU lets replace merge groups in ~O(alpha); groups carry a displayed char
// or a dead flag. This keeps every command near O(alpha) instead of O(|word|).

static const int MAXG = 200005;
int par[MAXG];
int gch[MAXG];   // displayed char, or -1 if this group was removed
int gcnt;

int findr(int x){ while(par[x]!=x){ par[x]=par[par[x]]; x=par[x]; } return x; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    while (cin >> S) {                 // a fresh word begins each test block
        int charToGroup[256];
        for (int i=0;i<256;i++) charToGroup[i] = -1;
        gcnt = 0;
        deque<int> word;

        auto makeGroup = [&](int c)->int{
            int g = gcnt++;
            par[g] = g;
            gch[g] = c;
            return g;
        };
        auto insertChar = [&](int c, bool head){
            int g = charToGroup[c];
            if (g == -1) { g = makeGroup(c); charToGroup[c] = g; }
            if (head) word.push_front(g); else word.push_back(g);
        };

        for (unsigned char ch : S) insertChar(ch, false);

        string cmd;
        bool terminated = false;
        while (cin >> cmd) {
            if (cmd == "end") {
                string out; out.reserve(word.size());
                for (int g : word) { int r = findr(g); if (gch[r] != -1) out.push_back((char)gch[r]); }
                cout << out << '\n';
                break;
            } else if (cmd == "replace") {
                string a,b; cin >> a >> b;
                int x = (unsigned char)a[0], y = (unsigned char)b[0];
                if (x == y) continue;
                int gx = charToGroup[x];
                if (gx == -1) continue;      // no x present
                charToGroup[x] = -1;         // x no longer displayed by this group
                int gy = charToGroup[y];
                if (gy == -1) { gch[gx] = y; charToGroup[y] = gx; }  // relabel group to y
                else { par[gx] = gy; }        // merge x-group into existing y-group
            } else if (cmd == "remove") {
                string a; cin >> a;
                int x = (unsigned char)a[0];
                int gx = charToGroup[x];
                if (gx == -1) continue;
                gch[gx] = -1;                 // mark removed
                charToGroup[x] = -1;
            } else if (cmd == "addhead") {
                string a; cin >> a; insertChar((unsigned char)a[0], true);
            } else if (cmd == "addtail") {
                string a; cin >> a; insertChar((unsigned char)a[0], false);
            } else {
                cout << "invalid command " << cmd << '\n';
                terminated = true;
                break;
            }
        }
        if (terminated) return 0;   // invalid command halts the whole program
    }
    return 0;
}
