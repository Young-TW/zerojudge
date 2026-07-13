#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

int main() {
    string line;
    bool first = true;
    while (getline(cin, line)) {
        if (line.find("範例") != string::npos) {
            if (!first) cout << "\n";
            first = false;
            cout << line << "\n";
        } else {
            istringstream iss(line);
            int M;
            if (iss >> M) {
                for (int i = 0; i < M; i++) {
                    string l2;
                    while (getline(cin, l2)) {
                        istringstream iss2(l2);
                        int a, b, c;
                        if (iss2 >> a >> b >> c) {
                            long long d = (long long)b * b - 4LL * a * c;
                            bool rational = false;
                            if (d >= 0) {
                                long long s = (long long)floor(sqrt((double)d) + 0.5);
                                for (long long k = s - 2; k <= s + 2; k++) {
                                    if (k >= 0 && k * k == d) {
                                        rational = true;
                                        break;
                                    }
                                }
                            }
                            cout << (rational ? "Yes" : "No") << "\n";
                            break;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
