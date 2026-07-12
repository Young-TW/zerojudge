#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        map<string, string> first_submit;
        set<string> ac_users;
        
        for (int i = 0; i < n; ++i) {
            string user, status;
            cin >> user >> status;
            first_submit[user] = status;
            if (status == "AC") {
                ac_users.insert(user);
            }
        }
        
        int ac_count = ac_users.size();
        int kill_count = 0;
        for (const auto& user : ac_users) {
            if (first_submit[user] == "AC") {
                kill_count++;
            }
        }
        
        cout << kill_count * 100 / ac_count << "%\n";
    }
    
    return 0;
}
