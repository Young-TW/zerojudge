#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    while (N--) {
        int K;
        cin >> K;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        long long prices[256] = {0};
        for (int i = 0; i < K; ++i) {
            char c = cin.get();
            long long v;
            cin >> v;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            prices[(unsigned char)c] = v;
        }

        int M;
        cin >> M;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        long long total = 0;
        for (int i = 0; i < M; ++i) {
            string line;
            getline(cin, line);
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            for (char c : line) {
                total += prices[(unsigned char)c];
            }
        }

        cout << total / 100 << "." << setw(2) << setfill('0') << total % 100 << "$\n";
    }

    return 0;
}
