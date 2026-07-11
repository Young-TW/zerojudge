#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    long long a, b, c;
    while (cin >> a >> b >> c) {
        long long sides[3] = {a, b, c};
        sort(sides, sides + 3);
        long long x = sides[0];
        long long y = sides[1];
        long long z = sides[2];
        
        long long sum_xy = x * x + y * y;
        long long sum_z = z * z;
        
        if (sum_xy > sum_z) {
            cout << "acute triangle" << endl;
        } else if (sum_xy == sum_z) {
            cout << "right triangle" << endl;
        } else {
            cout << "obtuse triangle" << endl;
        }
    }
    return 0;
}
