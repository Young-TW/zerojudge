#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>
#include <utility>

using namespace std;

struct Rect {
    int x1, y1, x2, y2;
    int r, g, b;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        if (N == 0) continue;
        vector<Rect> rects(N);
        vector<int> xs, ys;
        for (int i = 0; i < N; ++i) {
            int x1, y1, x2, y2, r, g, b;
            cin >> x1 >> y1 >> x2 >> y2 >> r >> g >> b;
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            rects[i] = {x1, y1, x2, y2, r, g, b};
            xs.push_back(x1);
            xs.push_back(x2);
            ys.push_back(y1);
            ys.push_back(y2);
        }
        
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        
        map<tuple<int, int, int>, long long> area_map;
        
        for (size_t i = 0; i + 1 < xs.size(); ++i) {
            for (size_t j = 0; j + 1 < ys.size(); ++j) {
                int x_start = xs[i];
                int x_end = xs[i+1];
                int y_start = ys[j];
                int y_end = ys[j+1];
                
                long long area = (long long)(x_end - x_start) * (y_end - y_start);
                
                long long sum_r = 0, sum_g = 0, sum_b = 0;
                int count = 0;
                
                for (int k = 0; k < N; ++k) {
                    if (rects[k].x1 <= x_start && x_end <= rects[k].x2 &&
                        rects[k].y1 <= y_start && y_end <= rects[k].y2) {
                        sum_r += rects[k].r;
                        sum_g += rects[k].g;
                        sum_b += rects[k].b;
                        count++;
                    }
                }
                
                if (count > 0) {
                    int avg_r = (sum_r + count - 1) / count;
                    int avg_g = (sum_g + count - 1) / count;
                    int avg_b = (sum_b + count - 1) / count;
                    area_map[make_tuple(avg_r, avg_g, avg_b)] += area;
                }
            }
        }
        
        long long max_area = -1;
        tuple<int, int, int> best_color;
        
        for (auto const& x : area_map) {
            if (x.second > max_area) {
                max_area = x.second;
                best_color = x.first;
            }
        }
        
        cout << get<0>(best_color) << " " << get<1>(best_color) << " " << get<2>(best_color) << " \n";
    }
    
    return 0;
}
