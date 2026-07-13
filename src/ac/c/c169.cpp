#include <iostream>

using namespace std;

bool is_leap(int y) {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    if (y % 4 == 0) return true;
    return false;
}

int get_days(int y, int m) {
    if (m == 2) {
        return is_leap(y) ? 29 : 28;
    }
    if (m == 4 || m == 6 || m == 9 || m == 11) {
        return 30;
    }
    return 31;
}

int reverse4(int n) {
    int r = 0;
    for (int i = 0; i < 4; ++i) {
        r = r * 10 + n % 10;
        n /= 10;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int date1, date2;
    int tc = 0;
    while (cin >> date1 >> date2) {
        if (tc > 0) cout << "\n";
        tc++;
        
        int y1 = date1 / 10000;
        int y2 = date2 / 10000;
        int ans = 0;
        
        for (int y = y1; y <= y2; ++y) {
            int mmdd = reverse4(y);
            int month = mmdd / 100;
            int day = mmdd % 100;
            
            if (month >= 1 && month <= 12) {
                if (day >= 1 && day <= get_days(y, month)) {
                    int current_date = y * 10000 + mmdd;
                    if (current_date >= date1 && current_date <= date2) {
                        ans++;
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
