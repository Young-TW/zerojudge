#include <iostream>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long s, e, a;
    while(cin >> s >> e >> a){
        long long d = 1;
        // s < 3 時 s/3 與 s/10 皆為 0,永遠不會成長
        if(s < e && s >= 3){
            while(s < e){
                if(d % 10 == 1){          // 每 10 天需一包肥料才能繼續
                    if(a == 0) break;
                    a--;
                }
                if(d % 10 != 9 && d % 10 != 0){  // 9,10,19,20... 日休息
                    if(d % 3 == 0) s += s / 3;
                    else           s += s / 10;
                }
                d++;
            }
        }
        if(s < e) cout << "unsalable\n";
        else      cout << d << "\n";
    }
    return 0;
}
