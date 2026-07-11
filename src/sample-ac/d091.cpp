#include <iostream>
#include <vector>

using namespace std;

struct Rect {
    double x1, y1, x2, y2;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char type;
    vector<Rect> rects;

    while (cin >> type && type == 'r') {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rects.push_back({x1, y1, x2, y2});
    }

    double px, py;
    int point_idx = 1;
    while (cin >> px >> py) {
        if (px > 9999.8 && py > 9999.8) break;

        bool contained = false;
        for (int i = 0; i < rects.size(); ++i) {
            const Rect& r = rects[i];
            if (px > r.x1 && px < r.x2 && py < r.y1 && py > r.y2) {
                cout << "Point " << point_idx << " is contained in figure " << i + 1 << "\n";
                contained = true;
            }
        }
        if (!contained) {
            cout << "Point " << point_idx << " is not contained in any figure\n";
        }
        point_idx++;
    }

    return 0;
}
