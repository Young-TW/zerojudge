#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <functional>
#include <numeric>
#include <cstring>

using namespace std;

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {}
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    long long cross(const Point& p) const { return x * p.y - y * p.x; }
};

void normalize(vector<Point>& p) {
    int n = p.size();
    long long area = 0;
    for (int i = 0; i < n; i++) {
        area += p[i].cross(p[(i + 1) % n]);
    }
    if (area < 0) {
        reverse(p.begin(), p.end());
    }
    int lowest = 0;
    for (int i = 1; i < n; i++) {
        if (p[i].y < p[lowest].y || (p[i].y == p[lowest].y && p[i].x < p[lowest].x)) {
            lowest = i;
        }
    }
    rotate(p.begin(), p.begin() + lowest, p.end());
}

vector<Point> minkowski_sum(const vector<Point>& P, const vector<Point>& Q) {
    int n = P.size(), m = Q.size();
    vector<Point> res;
    res.push_back(P[0] + Q[0]);
    int i = 0, j = 0;
    while (i < n || j < m) {
        Point edge_P = P[(i + 1) % n] - P[i % n];
        Point edge_Q = Q[(j + 1) % m] - Q[j % m];
        long long cross = edge_P.cross(edge_Q);
        if (i >= n) cross = -1;
        if (j >= m) cross = 1;
        
        if (cross > 0) {
            res.push_back(res.back() + edge_P);
            i++;
        } else if (cross < 0) {
            res.push_back(res.back() + edge_Q);
            j++;
        } else {
            res.push_back(res.back() + edge_P + edge_Q);
            i++;
            j++;
        }
    }
    res.pop_back();
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    while (cin >> T) {
        for (int t = 1; t <= T; t++) {
            int N, M;
            cin >> N;
            vector<Point> A(N);
            for (int i = 0; i < N; i++) {
                cin >> A[i].x >> A[i].y;
                A[i].x = -A[i].x;
                A[i].y = -A[i].y;
            }
            cin >> M;
            vector<Point> B(M);
            for (int i = 0; i < M; i++) {
                cin >> B[i].x >> B[i].y;
            }
            
            normalize(A);
            normalize(B);
            
            vector<Point> C = minkowski_sum(A, B);
            
            long long area2 = 0;
            int k = C.size();
            for (int i = 0; i < k; i++) {
                area2 += C[i].cross(C[(i + 1) % k]);
            }
            if (area2 < 0) area2 = -area2;
            
            printf("Case #%d: %.1f\n", t, area2 / 2.0);
        }
    }
    return 0;
}
