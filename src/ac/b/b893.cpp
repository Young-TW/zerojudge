#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

double evaluate(const vector<int>& coeff, double x) {
    double result = 0.0;
    for (int i = 0; i < coeff.size(); ++i) {
        result = result * x + coeff[i];
    }
    return result;
}

void find_roots(const vector<int>& coeff) {
    vector<pair<int, int>> roots;
    const int MAX_RANGE = 100000;
    const double EPS = 1e-9;

    for (int x = -MAX_RANGE; x <= MAX_RANGE; ++x) {
        double y1 = evaluate(coeff, x);
        double y2 = evaluate(coeff, x + 1);

        if (fabs(y1) < EPS) {
            roots.emplace_back(x, x);
            continue;
        }
        if (fabs(y2) < EPS) {
            continue;
        }

        if (y1 * y2 < 0) {
            roots.emplace_back(x, x + 1);
        }
    }

    if (roots.empty()) {
        bool all_zero = true;
        for (int c : coeff) {
            if (c != 0) {
                all_zero = false;
                break;
            }
        }
        if (all_zero) {
            cout << "Too many... ==\n";
        } else {
            cout << "N0THING! >\\\\<" << endl;
        }
        return;
    }

    sort(roots.begin(), roots.end());
    roots.erase(unique(roots.begin(), roots.end()), roots.end());

    for (const auto& root : roots) {
        cout << root.first << " " << root.second << endl;
    }
}

int main() {
    vector<int> coeff(6);
    while (cin >> coeff[0] >> coeff[1] >> coeff[2] >> coeff[3] >> coeff[4] >> coeff[5]) {
        find_roots(coeff);
    }
    return 0;
}
