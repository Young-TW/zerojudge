#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

static inline bool isalphac(int c){
    return (c>='a'&&c<='z')||(c>='A'&&c<='Z');
}

int main(){
    int c;
    // Pass 1: skip line 1 (friend list), then read line 2 (queries).
    while((c=getchar())!=EOF && c!='\n'){}

    unordered_map<string,int> cnt;   // query name -> occurrences in friend list
    vector<string> order;            // queries in input order (may repeat)
    string tok;
    // read line 2 until newline or EOF
    while((c=getchar())!=EOF){
        if(c=='\n') break;
        if(isalphac(c)){
            tok.push_back((char)c);
        } else {
            if(!tok.empty()){
                order.push_back(tok);
                cnt.emplace(tok, 0);
                tok.clear();
            }
        }
    }
    if(!tok.empty()){
        order.push_back(tok);
        cnt.emplace(tok, 0);
        tok.clear();
    }

    // Pass 2: rewind and count occurrences in line 1 only.
    rewind(stdin);
    while((c=getchar())!=EOF){
        if(c=='\n') break;              // end of friend list line
        if(isalphac(c)){
            tok.push_back((char)c);
        } else {
            if(!tok.empty()){
                auto it=cnt.find(tok);
                if(it!=cnt.end()) it->second++;
                tok.clear();
            }
        }
    }
    if(!tok.empty()){
        auto it=cnt.find(tok);
        if(it!=cnt.end()) it->second++;
        tok.clear();
    }

    string out;
    for(auto &q: order){
        int v=cnt[q];
        if(v==0) out += "No\n";
        else if(v==1) out += "Yes\n";
        else out += "Pathetic\n";
    }
    fputs(out.c_str(), stdout);
    return 0;
}
