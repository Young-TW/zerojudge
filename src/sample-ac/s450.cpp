#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

const double EPS = 1e-12;
const double PI = acos(-1.0);

struct Point {
    long long x, y;
    Point() : x(0), y(0) {}
    Point(long long x, long long y) : x(x), y(y) {}
    double angle() const {
        return atan2(y, x);
    }
    double dist() const {
        return hypot(x, y);
    }
};

double perpendicular_distance(const Point& p, double theta, double c) {
    double a = sin(theta);
    double b = -cos(theta);
    return abs(a * p.x + b * p.y - c) / hypot(a, b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long R;
    while (cin >> N >> R) {
        vector<Point> points(N);
        for (int i = 0; i < N; ++i) {
            cin >> points[i].x >> points[i].y;
        }

        vector<double> angles;
        for (const auto& p : points) {
            angles.push_back(p.angle());
        }
        sort(angles.begin(), angles.end());

        vector<double> unique_angles;
        for (int i = 0; i < N; ++i) {
            if (i == 0 || abs(angles[i] - angles[i-1]) > EPS) {
                unique_angles.push_back(angles[i]);
            }
        }
        for (double& angle : unique_angles) {
            angle += PI;
        }
        sort(unique_angles.begin(), unique_angles.end());

        double min_hazard = numeric_limits<double>::max();

        auto check = [&](double theta) {
            double a = sin(theta);
            double b = -cos(theta);
            double c = R * hypot(a, b);
            double max_dist = 0.0;
            for (const auto& p : points) {
                double dist = perpendicular_distance(p, theta, c);
                if (dist > max_dist) {
                    max_dist = dist;
                }
            }
            if (max_dist < min_hazard) {
                min_hazard = max_dist;
            }
        };

        for (int i = 0; i < (int)unique_angles.size(); ++i) {
            double theta = unique_angles[i];
            check(theta);
            if (i > 0) {
                double theta1 = unique_angles[i-1];
                double theta2 = unique_angles[i];
                double mid = (theta1 + theta2) / 2.0;
                check(mid);
            }
        }

        double theta1 = unique_angles.back();
        double theta2 = unique_angles[0] + 2 * PI;
        double mid = (theta1 + theta2) / 2.0;
        check(mid);

        cout << fixed << setprecision(10) << min_hazard << '\n';
    }

    return 0;
}
