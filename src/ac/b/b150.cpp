#include <iostream>
using namespace std;

int main() {
    int budget[12];
    int count = 0;
    bool first = true;
    while (cin >> budget[count]) {
        count++;
        if (count == 12) {
            if (!first) cout << endl;
            int current = 0;
            int total_deposit = 0;
            bool failed = false;
            for (int i = 0; i < 12; i++) {
                current += 300;
                if (current < budget[i]) {
                    cout << -(i + 1) << endl;
                    failed = true;
                    break;
                }
                current -= budget[i];
                int deposit = (current / 100) * 100;
                current -= deposit;
                total_deposit += deposit;
            }
            if (!failed) {
                cout << current + total_deposit * 6 / 5 << endl;
            }
            first = false;
            count = 0;
        }
    }
    return 0;
}
