#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    map<string,int> mon;
    mon["January"]=1; mon["February"]=2; mon["March"]=3; mon["April"]=4;
    mon["May"]=5; mon["June"]=6; mon["July"]=7; mon["August"]=8;
    mon["September"]=9; mon["October"]=10; mon["November"]=11; mon["December"]=12;

    int T;
    cin >> T;
    for (int t=1; t<=T; t++) {
        string m1, m2;
        long long d1, y1, d2, y2;
        char c;
        cin >> m1 >> d1 >> c >> y1;
        cin >> m2 >> d2 >> c >> y2;
        int mo1 = mon[m1], mo2 = mon[m2];

        auto leapUp = [](long long Y)->long long {
            return Y/4 - Y/100 + Y/400;
        };
        auto isLeap = [](long long Y)->bool {
            return (Y%4==0 && Y%100!=0) || (Y%400==0);
        };
        auto L = [&](long long y, int mo, long long d)->long long {
            long long base = leapUp(y-1);
            if (isLeap(y)) {
                if (mo > 2 || (mo==2 && d==29)) base += 1;
            }
            return base;
        };

        long long l1 = L(y1, mo1, d1);
        long long l2 = L(y2, mo2, d2);
        bool date1IsLeapDay = (mo1==2 && d1==29);
        long long ans = l2 - l1 + (date1IsLeapDay?1:0);
        cout << "Case " << t << ": " << ans << endl;
    }
    return 0;
}
