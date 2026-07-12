#include <iostream>

using namespace std;

struct Dice {
    long long top, bottom, north, south, east, west;
};

void roll(Dice &d, char dir) {
    long long t = d.top, b = d.bottom, n = d.north, s = d.south, e = d.east, w = d.west;
    if (dir == 'N') {
        d.top = s;
        d.north = t;
        d.bottom = n;
        d.south = b;
    } else if (dir == 'S') {
        d.top = n;
        d.south = t;
        d.bottom = s;
        d.north = b;
    } else if (dir == 'E') {
        d.top = w;
        d.east = t;
        d.bottom = e;
        d.west = b;
    } else if (dir == 'W') {
        d.top = e;
        d.west = t;
        d.bottom = w;
        d.east = b;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        Dice cur = {1, 6, 2, 5, 3, 4};
        long long total_sum = 0;
        
        for (int i = 0; i < N; ++i) {
            char d;
            long long x;
            cin >> d >> x;
            
            Dice temp = cur;
            long long cycle_sum = 0;
            long long tops[4];
            for (int j = 0; j < 4; ++j) {
                roll(temp, d);
                tops[j] = temp.top;
                cycle_sum += tops[j];
            }
            
            long long k = x / 4;
            long long r = x % 4;
            
            total_sum += k * cycle_sum;
            for (int j = 0; j < r; ++j) {
                total_sum += tops[j];
            }
            
            for (int j = 0; j < r; ++j) {
                roll(cur, d);
            }
        }
        
        cout << total_sum << "\n";
    }
    
    return 0;
}
