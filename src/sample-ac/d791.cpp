#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int p, e, i, d;
    int case_num = 1;
    
    while (cin >> p >> e >> i >> d) {
        if (p == -1 && e == -1 && i == -1 && d == -1) {
            break;
        }
        
        p %= 23;
        e %= 28;
        i %= 33;
        
        int x = (5544 * p + 14421 * e + 1288 * i) % 21252;
        
        if (x <= d) {
            x += 21252;
        }
        
        cout << "Case " << case_num << ": the next triple peak occurs in " << x - d << " days.\n";
        case_num++;
    }
    
    return 0;
}
