#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

struct Node {
    map<char,int> ch;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        vector<Node> trie(1); // root = 0
        for (int i=0;i<N;i++){
            string s;
            cin >> s;
            int cur=0;
            for (char c: s){
                auto it = trie[cur].ch.find(c);
                if (it==trie[cur].ch.end()){
                    int idx = (int)trie.size();
                    trie.emplace_back();
                    trie[cur].ch[c]=idx;
                    cur=idx;
                } else {
                    cur=it->second;
                }
            }
        }
        // iterative preorder print
        struct Frame{int node; char c; int depth; int sib;};
        vector<Frame> st;
        st.push_back({0,' ',0,0});
        string out;
        while(!st.empty()){
            Frame f = st.back(); st.pop_back();
            if (f.sib>0){
                out.push_back('\n');
                out.append((size_t)f.depth*3,' ');
            }
            out.push_back('[');
            out.push_back(f.c);
            out.push_back(']');
            Node &nd = trie[f.node];
            int cnt = (int)nd.ch.size();
            int idx=cnt-1;
            for (auto rit = nd.ch.rbegin(); rit!=nd.ch.rend(); ++rit){
                st.push_back({rit->second, rit->first, f.depth+1, idx});
                idx--;
            }
        }
        out.push_back('\n');
        cout << out;
    }
    return 0;
}
