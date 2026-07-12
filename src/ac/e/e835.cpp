#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        int area, base, seats;
        if (N <= 2500) {
            area = 1;
            base = 0;
            seats = 25;
        } else if (N <= 7500) {
            area = 2;
            base = 2500;
            seats = 50;
        } else {
            area = 3;
            base = 7500;
            seats = 25;
        }
        
        int index = N - base;
        int row = (index - 1) / seats + 1;
        int col = (index - 1) % seats + 1;
        
        cout << area << " " << row << " " << col << "\n";
    }
    
    return 0;
}
