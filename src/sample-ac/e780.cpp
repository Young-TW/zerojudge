#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        int x = 0;
        int count = 0;
        for (int i = 0; i < N; ++i) {
            string cmd;
            cin >> cmd;
            if (cmd == "L") {
                --x;
            } else if (cmd == "R") {
                ++x;
            } else if (cmd == "Gift") {
                int y;
                cin >> y;
                if (x == y) {
                    ++count;
                }
            }
        }
        cout << count << "\n";
    }
    
    return 0;
}
