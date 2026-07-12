#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    map<string, int> monthDays;
    monthDays["JAN"] = 31;
    monthDays["FEB"] = 28;
    monthDays["MAR"] = 31;
    monthDays["APR"] = 30;
    monthDays["MAY"] = 31;
    monthDays["JUN"] = 30;
    monthDays["JUL"] = 31;
    monthDays["AUG"] = 31;
    monthDays["SEP"] = 30;
    monthDays["OCT"] = 31;
    monthDays["NOV"] = 30;
    monthDays["DEC"] = 31;
    
    map<string, int> dayNum;
    dayNum["SUN"] = 0;
    dayNum["MON"] = 1;
    dayNum["TUE"] = 2;
    dayNum["WED"] = 3;
    dayNum["THU"] = 4;
    dayNum["FRI"] = 5;
    dayNum["SAT"] = 6;
    
    int T;
    if (cin >> T) {
        while (T--) {
            string mth, day;
            if (!(cin >> mth >> day)) break;
            int D = monthDays[mth];
            int W = dayNum[day];
            int count = 0;
            for (int i = 0; i < D; ++i) {
                int cur = (W + i) % 7;
                if (cur == 5 || cur == 6) {
                    count++;
                }
            }
            cout << count << "\n";
        }
    }
    
    return 0;
}
