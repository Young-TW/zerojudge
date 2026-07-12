#include <iostream>
#include <string>
#include <set>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        set<string> depts;
        for (int i = 0; i < N; ++i) {
            string d;
            cin >> d;
            depts.insert(d);
        }
        
        int error_count = 0;
        for (int i = 0; i < 10; ++i) {
            string id;
            cin >> id;
            bool valid = true;
            if (id.length() != 9) {
                valid = false;
            } else {
                if (id[0] != 'B') {
                    valid = false;
                } else if (!(id[1] >= '0' && id[1] <= '9') || !(id[2] >= '0' && id[2] <= '9')) {
                    valid = false;
                } else if (!(id[7] >= '0' && id[7] <= '9') || !(id[8] >= '0' && id[8] <= '9')) {
                    valid = false;
                } else {
                    string dept = id.substr(3, 4);
                    if (depts.find(dept) == depts.end()) {
                        valid = false;
                    }
                }
            }
            
            if (valid) {
                cout << "Y\n";
            } else {
                cout << "N\n";
                error_count++;
            }
        }
        cout << fixed << setprecision(1) << (error_count / 10.0) << "\n";
    }
    
    return 0;
}
