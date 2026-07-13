#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int s1, e1, s2, e2, s3, e3;
    while (cin >> s1 >> e1 >> s2 >> e2 >> s3 >> e3) {
        bool overlap = false;
        if (s1 < e2 && s2 < e1) overlap = true;
        if (s1 < e3 && s3 < e1) overlap = true;
        if (s2 < e3 && s3 < e2) overlap = true;
        
        if (overlap) {
            cout << "QQ\n";
        } else {
            cout << "Happy\n";
        }
    }
    
    return 0;
}
