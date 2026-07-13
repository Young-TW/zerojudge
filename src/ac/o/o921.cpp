#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int m1, d1, m2, d2;
    
    while (cin >> m1 >> d1 >> m2 >> d2) {
        int day1 = d1;
        for (int i = 1; i < m1; ++i) {
            day1 += days_in_month[i];
        }
        
        int day2 = d2;
        for (int i = 1; i < m2; ++i) {
            day2 += days_in_month[i];
        }
        
        cout << (day2 - day1 + 365) % 365 << "\n";
    }
    
    return 0;
}
