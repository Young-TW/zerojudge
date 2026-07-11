#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            int gender, age, height, weight;
            cin >> gender >> age >> height >> weight;
            double bmr;
            if (gender == 1) {
                bmr = 66.0 + 13.7 * weight + 5.0 * height - 6.8 * age;
            } else {
                bmr = 655.0 + 9.6 * weight + 1.8 * height - 4.7 * age;
            }
            cout << fixed << setprecision(2) << bmr << "\n";
        }
    }
    
    return 0;
}
