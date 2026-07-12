#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            int N;
            cin >> N;
            map<string, int> subjects;
            for (int i = 0; i < N; ++i) {
                string name;
                int days;
                cin >> name >> days;
                subjects[name] = days;
            }
            int D;
            cin >> D;
            string target;
            cin >> target;
            
            cout << "Case " << t << ": ";
            map<string, int>::iterator it = subjects.find(target);
            if (it != subjects.end()) {
                int days = it->second;
                if (days <= D) {
                    cout << "Yesss\n";
                } else if (days <= D + 5) {
                    cout << "Late\n";
                } else {
                    cout << "Do your own homework!\n";
                }
            } else {
                cout << "Do your own homework!\n";
            }
        }
    }
    
    return 0;
}
