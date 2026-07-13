#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const double PI = acos(-1.0);
    const double eps = 1e-9;
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            vector<double> x(N), y(N), r(N);
            for (int i = 0; i < N; ++i) {
                cin >> x[i] >> y[i] >> r[i];
            }
            
            double total_perimeter = 0.0;
            
            for (int i = 0; i < N; ++i) {
                bool dead = false;
                for (int j = 0; j < N; ++j) {
                    if (i == j) continue;
                    double d2 = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
                    double d = sqrt(d2);
                    if (d + r[i] <= r[j] + eps) {
                        dead = true;
                        break;
                    }
                }
                if (dead) continue;
                
                vector<pair<double, double>> intervals;
                for (int j = 0; j < N; ++j) {
                    if (i == j) continue;
                    double d2 = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
                    double d = sqrt(d2);
                    
                    if (d + r[j] <= r[i] + eps) {
                        continue;
                    }
                    if (d >= r[i] + r[j] - eps) {
                        continue;
                    }
                    
                    double alpha = atan2(y[j] - y[i], x[j] - x[i]);
                    if (alpha < 0) alpha += 2 * PI;
                    double cos_beta = (d2 + r[i] * r[i] - r[j] * r[j]) / (2.0 * d * r[i]);
                    if (cos_beta > 1.0) cos_beta = 1.0;
                    if (cos_beta < -1.0) cos_beta = -1.0;
                    double beta = acos(cos_beta);
                    
                    double L = alpha - beta;
                    double R = alpha + beta;
                    
                    if (L < 0) {
                        intervals.push_back(make_pair(L + 2 * PI, 2 * PI));
                        L = 0.0;
                    }
                    if (R > 2 * PI) {
                        intervals.push_back(make_pair(0.0, R - 2 * PI));
                        R = 2 * PI;
                    }
                    intervals.push_back(make_pair(L, R));
                }
                
                sort(intervals.begin(), intervals.end());
                double covered = 0.0;
                double cur_start = -1.0, cur_end = -1.0;
                for (const auto& p : intervals) {
                    if (p.first > cur_end + eps) {
                        if (cur_end >= 0.0) {
                            covered += cur_end - cur_start;
                        }
                        cur_start = p.first;
                        cur_end = p.second;
                    } else {
                        cur_end = max(cur_end, p.second);
                    }
                }
                if (cur_end >= 0.0) {
                    covered += cur_end - cur_start;
                }
                
                double uncovered = 2.0 * PI - covered;
                if (uncovered < 0) uncovered = 0.0;
                total_perimeter += uncovered * r[i];
            }
            
            int b = 0;
            double a = total_perimeter;
            if (a > 0) {
                b = (int)floor(log10(a));
                a = a / pow(10.0, b);
                if (a >= 9.995) {
                    a /= 10.0;
                    b++;
                }
            } else {
                a = 0.0;
                b = 0;
            }
            
            cout << fixed;
            cout.precision(2);
            cout << a << " " << b << "\n";
        }
    }
    
    return 0;
}
