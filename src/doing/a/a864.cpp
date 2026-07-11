#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string name;
    double mB, mV;
    
    while (cin >> name) {
        if (name == "END") break;
        cin >> mB >> mV;
        
        long long b = lround(mB * 100);
        long long v = lround(mV * 100);
        long long bv = b - v;
        
        char type;
        if (bv < -4) {
            type = 'O';
        } else if (bv < 0) {
            type = 'B';
        } else if (bv < 42) {
            type = 'A';
        } else if (bv < 58) {
            type = 'F';
        } else if (bv < 81) {
            type = 'G';
        } else if (bv < 140) {
            type = 'K';
        } else {
            type = 'M';
        }
        
        cout << name << " " << fixed << setprecision(2) << (double)bv / 100.0 << " " << type << "\n";
    }
    
    return 0;
}
