#include <iostream>
#include <string>
using namespace std;

int main(){
    string tok;
    string bin;
    int flag = 0;
    while(cin >> tok){
        if(tok == "~") break;
        if(tok == "#"){
            long long val = 0;
            for(size_t i = 0; i < bin.size(); ++i)
                val = val * 2 + (bin[i] - '0');
            cout << val << "\n";
            bin.clear();
            flag = 0;
            continue;
        }
        int len = (int)tok.size();
        if(len == 1) flag = 1;
        else if(len == 2) flag = 0;
        else {
            int cnt = len - 2;
            char c = (char)('0' + flag);
            bin.append((size_t)cnt, c);
        }
    }
    return 0;
}
