#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

struct Figure {
    char type;
    double x1, y1, x2, y2; // for rectangle
    double cx, cy, r;      // for circle
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Figure> figures;
    char type;
    while (cin >> type && type != '*') {
        Figure fig;
        fig.type = type;
        if (type == 'r') {
            cin >> fig.x1 >> fig.y1 >> fig.x2 >> fig.y2;
        } else if (type == 'c') {
            cin >> fig.cx >> fig.cy >> fig.r;
        }
        figures.push_back(fig);
    }

    double px, py;
    int pointIdx = 1;
    while (cin >> px >> py) {
        if (px == 9999.9 && py == 9999.9) {
            break;
        }

        bool contained = false;
        for (int i = 0; i < (int)figures.size(); ++i) {
            const Figure& fig = figures[i];
            bool inside = false;
            if (fig.type == 'r') {
                double minX = min(fig.x1, fig.x2);
                double maxX = max(fig.x1, fig.x2);
                double minY = min(fig.y1, fig.y2);
                double maxY = max(fig.y1, fig.y2);
                if (px > minX && px < maxX && py > minY && py < maxY) {
                    inside = true;
                }
            } else if (fig.type == 'c') {
                double dx = px - fig.cx;
                double dy = py - fig.cy;
                if (dx * dx + dy * dy < fig.r * fig.r) {
                    inside = true;
                }
            }

            if (inside) {
                cout << "Point " << pointIdx << " is contained in figure " << i + 1 << "\n";
                contained = true;
            }
        }

        if (!contained) {
            cout << "Point " << pointIdx << " is not contained in any figure\n";
        }
        pointIdx++;
    }

    return 0;
}
