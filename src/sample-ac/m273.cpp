#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (n--) {
            string L1, L2;
            getline(cin, L1);
            getline(cin, L2);
            
            if (!L1.empty() && L1.back() == '\r') L1.pop_back();
            if (!L2.empty() && L2.back() == '\r') L2.pop_back();
            
            size_t p1 = L1.find('<');
            size_t p2 = L1.find('>', p1);
            size_t p3 = L1.find('<', p2);
            size_t p4 = L1.find('>', p3);
            
            string S1 = L1.substr(0, p1);
            string S2 = L1.substr(p1 + 1, p2 - p1 - 1);
            string S3 = L1.substr(p2 + 1, p3 - p2 - 1);
            string S4 = L1.substr(p3 + 1, p4 - p3 - 1);
            string S5 = L1.substr(p4 + 1);
            
            cout << S1 << S2 << S3 << S4 << S5 << "\n";
            
            if (L2.length() >= 3 && L2.substr(L2.length() - 3) == "...") {
                L2 = L2.substr(0, L2.length() - 3);
            }
            cout << L2 << S4 << S3 << S2 << S5 << "\n";
        }
    }
    return 0;
}
