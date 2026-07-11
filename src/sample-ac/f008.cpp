#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve(int n) {
    if (n == 1) {
        cout << "1\n0 0 1\n";
        return;
    }

    vector<int> sizes;
    int total = 0;
    int k = 1;
    while (total < n) {
        sizes.push_back(k);
        total += k;
        k *= 2;
    }

    if (total > n) {
        sizes.pop_back();
        sizes.push_back(n - (total - k/2));
    }

    vector<pair<int, pair<int, int>>> spells;
    int x = 0, y = 0;
    for (int size : sizes) {
        spells.push_back({size, {x, y}});
        x += size;
        y += size;
    }

    cout << spells.size() << "\n";
    for (auto& spell : spells) {
        cout << spell.second.first << " " << spell.second.second << " " << spell.first << "\n";
    }

    int remaining = n - sizes.back();
    if (remaining > 0) {
        vector<pair<int, pair<int, int>>> additional;
        int current = sizes.back();
        int start = 0;
        while (start < n) {
            if (start + current > n) {
                current = n - start;
            }
            for (int i = 0; i < current; ++i) {
                additional.push_back({current, {start, start + i}});
                additional.push_back({current, {start + i, start}});
            }
            start += current;
        }

        for (auto& spell : additional) {
            if (spell.second.first + spell.first <= n && spell.second.second + spell.first <= n) {
                bool found = false;
                for (auto& s : spells) {
                    if (s.second.first == spell.second.first && s.second.second == spell.second.second && s.first == spell.first) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    spells.push_back(spell);
                }
            }
        }
    }

    if (spells.size() == sizes.size()) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || j == 0 || i == n-1 || j == n-1) continue;
                bool covered = false;
                for (auto& spell : spells) {
                    int x = spell.second.first;
                    int y = spell.second.second;
                    int r = spell.first;
                    if (i >= x && i < x + r && j >= y && j < y + r) {
                        covered = true;
                        break;
                    }
                }
                if (!covered) {
                    spells.push_back({1, {i, j}});
                }
            }
        }
    }

    vector<pair<int, pair<int, int>>> unique_spells;
    for (auto& spell : spells) {
        bool found = false;
        for (auto& us : unique_spells) {
            if (us.second.first == spell.second.first && us.second.second == spell.second.second && us.first == spell.first) {
                found = true;
                break;
            }
        }
        if (!found) {
            unique_spells.push_back(spell);
        }
    }

    cout << unique_spells.size() << "\n";
    for (auto& spell : unique_spells) {
        cout << spell.second.first << " " << spell.second.second << " " << spell.first << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        if (n == 1) {
            cout << "1\n0 0 1\n";
        } else if (n == 2) {
            cout << "3\n0 0 1\n0 0 2\n1 1 1\n";
        } else if (n == 3) {
            cout << "4\n0 0 2\n0 1 2\n1 0 2\n1 1 2\n";
        } else {
            vector<int> sizes;
            int total = 0;
            int k = 1;
            while (total < n) {
                sizes.push_back(k);
                total += k;
                k *= 2;
            }

            if (total > n) {
                sizes.pop_back();
                sizes.push_back(n - (total - k/2));
            }

            vector<pair<int, pair<int, int>>> spells;
            int x = 0, y = 0;
            for (int size : sizes) {
                spells.push_back({size, {x, y}});
                x += size;
                y += size;
            }

            int remaining = n - sizes.back();
            if (remaining > 0) {
                int current = sizes.back();
                int start = 0;
                while (start < n) {
                    if (start + current > n) {
                        current = n - start;
                    }
                    for (int i = 0; i < current; ++i) {
                        spells.push_back({current, {start, start + i}});
                        spells.push_back({current, {start + i, start}});
                    }
                    start += current;
                }
            }

            vector<pair<int, pair<int, int>>> unique_spells;
            for (auto& spell : spells) {
                bool found = false;
                for (auto& us : unique_spells) {
                    if (us.second.first == spell.second.first && us.second.second == spell.second.second && us.first == spell.first) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    unique_spells.push_back(spell);
                }
            }

            cout << unique_spells.size() << "\n";
            for (auto& spell : unique_spells) {
                cout << spell.second.first << " " << spell.second.second << " " << spell.first << "\n";
            }
        }
    }
    return 0;
}
