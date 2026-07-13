#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    list<string> lst;
    unordered_map<string, list<string>::iterator> mp;
    string cmd;
    
    while (cin >> cmd) {
        if (cmd == "ADD") {
            string x;
            cin >> x;
            lst.push_back(x);
            auto it = lst.end();
            --it;
            mp[x] = it;
        } else if (cmd == "INSERT") {
            string x, n;
            cin >> x >> n;
            auto it_n = mp.find(n);
            if (it_n != mp.end()) {
                auto it_x = lst.insert(it_n->second, x);
                mp[x] = it_x;
            }
        } else if (cmd == "REMOVE") {
            string x;
            cin >> x;
            auto it_x = mp.find(x);
            if (it_x != mp.end()) {
                lst.erase(it_x->second);
                mp.erase(it_x);
            }
        } else if (cmd == "SHOW") {
            bool first = true;
            for (const string& s : lst) {
                if (!first) cout << " ";
                cout << s;
                first = false;
            }
            cout << "\n";
            break;
        }
    }
    
    return 0;
}
