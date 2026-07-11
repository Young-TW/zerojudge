#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct River {
    int id;
    double u, v;
};

const double EPS = 1e-9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    vector<River> rivers;
    int river_count = 0;

    for (int i = 0; i < N; ++i) {
        char type;
        cin >> type;
        if (type == 'A') {
            double u, v;
            cin >> u >> v;
            river_count++;
            rivers.push_back({river_count, u, v});
        } else if (type == 'Q') {
            double x, y;
            cin >> x >> y;

            vector<pair<double, int>> intersections;
            bool on_river = false;

            for (const auto& r : rivers) {
                double x_intersect = r.u + (r.v - r.u) * y;
                if (fabs(x - x_intersect) < EPS) {
                    on_river = true;
                    break;
                }
                intersections.push_back({x_intersect, r.id});
            }

            if (on_river) {
                cout << "[?, ?]\n";
            } else {
                sort(intersections.begin(), intersections.end());
                
                int lower_bound = 0;
                int upper_bound = 0;
                
                bool found_lower = false;
                for (int j = 0; j < (int)intersections.size(); ++j) {
                    if (intersections[j].first < x) {
                        lower_bound = intersections[j].second;
                        found_lower = true;
                    } else {
                        upper_bound = intersections[j].second;
                        break;
                    }
                }

                cout << "[";
                if (found_lower) {
                    cout << lower_bound;
                } else {
                    cout << "S";
                }
                cout << ", ";
                if (upper_bound != 0) {
                    cout << upper_bound;
                } else {
                    cout << "M";
                }
                cout << "]\n";
            }
        }
    }

    return 0;
}
