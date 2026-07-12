#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    bool first_case = true;
    while (cin >> n >> m) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;

        vector<pair<string, string>> cars(n);
        for (int i = 0; i < n; ++i) {
            cin >> cars[i].first >> cars[i].second;
        }

        for (int i = 0; i < m; ++i) {
            string type, value;
            cin >> type >> value;
            for (int j = 0; j < n; ++j) {
                if (type == "brand") {
                    if (cars[j].first == value) {
                        cout << cars[j].first << " " << cars[j].second << "\n";
                    }
                } else if (type == "color") {
                    if (cars[j].second == value) {
                        cout << cars[j].first << " " << cars[j].second << "\n";
                    }
                }
            }
        }
    }

    return 0;
}
