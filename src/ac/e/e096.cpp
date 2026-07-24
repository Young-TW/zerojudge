#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
using namespace std;

struct Star {
    int x, y, z;
    bool operator==(const Star& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

namespace std {
    template<>
    struct hash<Star> {
        size_t operator()(const Star& s) const {
            return hash<int>()(s.x) ^ hash<int>()(s.y) ^ hash<int>()(s.z);
        }
    };
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Star> stars;
    unordered_map<Star, int> count_map;

    while (n--) {
        int op, x, y, z;
        cin >> op >> x >> y >> z;
        Star s = {x, y, z};

        if (op == 0) {
            int k;
            cin >> k;
            if (stars.empty()) {
                cout << "(not found)\n";
                continue;
            }

            vector<int> distances;
            distances.reserve(stars.size());
            for (const auto& star : stars) {
                int dx = abs(star.x - x);
                int dy = abs(star.y - y);
                int dz = abs(star.z - z);
                distances.push_back(dx + dy + dz);
            }

            if (k > distances.size()) {
                cout << "(not found)\n";
            } else {
                nth_element(distances.begin(), distances.begin() + k - 1, distances.end());
                cout << "(" << distances[k - 1] << ")\n";
            }
        } else if (op == 1) {
            stars.push_back(s);
            count_map[s]++;
        } else if (op == 2) {
            if (count_map.find(s) != count_map.end() && count_map[s] > 0) {
                count_map[s]--;
                auto it = find(stars.begin(), stars.end(), s);
                if (it != stars.end()) {
                    stars.erase(it);
                }
            }
        }
    }

    return 0;
}
