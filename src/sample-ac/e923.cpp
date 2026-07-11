#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        while (N--) {
            int W, M, D;
            cin >> W >> M >> D;
            
            int day_of_year = 0;
            for (int i = 1; i < M; ++i) {
                day_of_year += days_in_month[i];
            }
            day_of_year += D;
            
            int week_day = (W + day_of_year - 2) % 7 + 1;
            
            int first_monday;
            if (W <= 4) {
                first_monday = 2 - W;
            } else {
                first_monday = 9 - W;
            }
            
            int week_num;
            if (day_of_year < first_monday) {
                week_num = -1;
            } else {
                int diff = day_of_year - first_monday;
                week_num = diff / 7 + 1;
                if (week_num == 53) {
                    if (W == 1 || W == 2) {
                        week_num = 1;
                    }
                }
            }
            
            cout << week_num << " " << week_day << "\n";
        }
    }
    
    return 0;
}
