#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, d, r;
    while (cin >> n >> d >> r) {
        if (n == 0 && d == 0 && r == 0) {
            break;
        }
        
        vector<int> morning(n);
        vector<int> evening(n);
        
        for (int i = 0; i < n; ++i) {
            cin >> morning[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> evening[i];
        }
        
        sort(morning.begin(), morning.end());
        sort(evening.begin(), evening.end(), greater<int>());
        
        int total_overtime_pay = 0;
        for (int i = 0; i < n; ++i) {
            int total_hours = morning[i] + evening[i];
            if (total_hours > d) {
                total_overtime_pay += (total_hours - d) * r;
            }
        }
        
        cout << total_overtime_pay << "\n";
    }
    
    return 0;
}
