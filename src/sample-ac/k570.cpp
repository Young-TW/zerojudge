#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        long long total = 0;
        for (int i = 0; i < N; ++i) {
            int id, h, m, a;
            cin >> id >> h >> m >> a;
            
            int time = h * 60 + m;
            if (h == 0 && m == 0) {
                time = 24 * 60;
            }
            
            int discounted_price = a;
            if (id == 0) {
                if (time >= 18 * 60 && time <= 24 * 60) {
                    discounted_price = a * 7 / 10;
                }
            } else if (id == 1) {
                if (time >= 10 * 60 && time <= 24 * 60) {
                    discounted_price = a * 7 / 10;
                }
            } else if (id == 2) {
                if ((time >= 10 * 60 && time <= 17 * 60) || (time >= 20 * 60 && time <= 24 * 60)) {
                    discounted_price = a * 65 / 100;
                }
            } else if (id == 3) {
                if (time >= 16 * 60 + 30 && time <= 22 * 60 + 30) {
                    discounted_price = a * 6 / 10;
                }
            }
            total += discounted_price;
        }
        cout << total << "\n";
    }
    
    return 0;
}
