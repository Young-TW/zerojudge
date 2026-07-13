#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N) {
        for (int t = 1; t <= N; ++t) {
            double sum = 0.0;
            for (int i = 0; i < 12; ++i) {
                double val;
                cin >> val;
                sum += val;
            }
            double avg = sum / 12.0;
            char buf[256];
            snprintf(buf, sizeof(buf), "%.2f", avg + 1e-9);
            
            string s = buf;
            size_t dot = s.find('.');
            string int_part = s.substr(0, dot);
            string dec_part = s.substr(dot);
            
            string formatted_int = "";
            int count = 0;
            int len = int_part.length();
            for (int j = len - 1; j >= 0; --j) {
                formatted_int = int_part[j] + formatted_int;
                count++;
                if (count % 3 == 0 && j > 0) {
                    formatted_int = "," + formatted_int;
                }
            }
            cout << t << " $" << formatted_int << dec_part << "\n";
        }
    }
    return 0;
}
