#include <iostream>
#include <string>
#include <list>
#include <cctype>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s, cmd;
    while(getline(cin, s)){
        getline(cin, cmd);
        
        list<char> text(s.begin(), s.end());
        list<char>::iterator cur = text.begin();
        
        size_t i = 0;
        while(i < cmd.size()){
            char c = cmd[i];
            if(c == '0'){
                cur = text.begin();
                i++;
            } else if(c == '$'){
                cur = text.end();
                i++;
            } else if(c == 'x'){
                if(cur != text.end()){
                    cur = text.erase(cur);
                }
                i++;
            } else if(c == 's'){
                if(cur != text.end()){
                    list<char>::iterator nxt = cur;
                    ++nxt;
                    if(nxt != text.end()){
                        swap(*cur, *nxt);
                    }
                }
                i++;
            } else if(c == 'i'){
                i++;
                if(i < cmd.size()){
                    char ch = cmd[i];
                    text.insert(cur, ch);
                    i++;
                }
            } else if(c == 'u'){
                if(cur != text.end()){
                    if(isalpha((unsigned char)*cur)){
                        *cur = toupper((unsigned char)*cur);
                    }
                    ++cur;
                }
                i++;
            } else if(c == '+'){
                if(cur != text.end()) ++cur;
                i++;
            } else if(c == '-'){
                if(cur != text.begin()) --cur;
                i++;
            } else {
                i++;
            }
        }
        
        string result(text.begin(), text.end());
        cout << result << "\n";
    }
    return 0;
}
