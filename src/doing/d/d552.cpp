#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main() {
    int n, k, m;
    while (cin >> n >> k >> m) {
        vector<int> c(n);
        for (int i = 0; i < n; ++i) {
            cin >> c[i];
        }

        list<int> people;
        for (int i = 0; i < n; ++i) {
            people.push_back(i);
        }

        auto it = people.begin();
        int killed = 0;
        int swap_count = 0;

        while (people.size() > 1) {
            for (int i = 1; i < k; ++i) {
                ++it;
                if (it == people.end()) {
                    it = people.begin();
                }
            }

            auto to_erase = it;
            ++it;
            if (it == people.end()) {
                it = people.begin();
            }
            people.erase(to_erase);
            killed++;

            if (killed % m == 0) {
                vector<int> temp(people.begin(), people.end());
                for (int i = 0; i < temp.size(); ++i) {
                    int pos = c[temp[i]];
                    if (pos >= 0 && pos < temp.size()) {
                        swap(temp[i], temp[pos]);
                    }
                }
                people.assign(temp.begin(), temp.end());
                it = people.begin();
                for (int i = 0; i < swap_count; ++i) {
                    ++it;
                    if (it == people.end()) {
                        it = people.begin();
                    }
                }
            }
            swap_count = 0;
            for (auto cur = people.begin(); cur != it; ++cur) {
                swap_count++;
            }
        }

        cout << people.front() << endl;
    }
    return 0;
}
