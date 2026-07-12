#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Figure {
    char type;
    double x1, y1, x2, y2, x3, y3, r;
};

bool isInside(const Figure& fig, double px, double py) {
    double eps = 1e-9;
    if (fig.type == 'r') {
        double minx = min(fig.x1, fig.x2);
        double maxx = max(fig.x1, fig.x2);
        double miny = min(fig.y1, fig.y2);
        double maxy = max(fig.y1, fig.y2);
        return px > minx + eps && px < maxx - eps && py > miny + eps && py < maxy - eps;
    } else if (fig.type == 'c') {
        double dx = px - fig.x1;
        double dy = py - fig.y1;
        return dx * dx + dy * dy < fig.r * fig.r - eps;
    } else if (fig.type == 't') {
        double c1 = (fig.x2 - fig.x1) * (py - fig.y1) - (fig.y2 - fig.y1) * (px - fig.x1);
        double c2 = (fig.x3 - fig.x2) * (py - fig.y2) - (fig.y3 - fig.y2) * (px - fig.x2);
        double c3 = (fig.x1 - fig.x3) * (py - fig.y3) - (fig.y1 - fig.y3) * (px - fig.x3);
        if (c1 > eps && c2 > eps && c3 > eps) return true;
        if (c1 < -eps && c2 < -eps && c3 < -eps) return true;
        return false;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    char type;
    vector<Figure> figs;
    while (cin >> type && type != '*') {
        Figure fig;
        fig.type = type;
        if (type == 'r') {
            cin >> fig.x1 >> fig.y1 >> fig.x2 >> fig.y2;
        } else if (type == 'c') {
            cin >> fig.x1 >> fig.y1 >> fig.r;
        } else if (type == 't') {
            cin >> fig.x1 >> fig.y1 >> fig.x2 >> fig.y2 >> fig.x3 >> fig.y3;
        }
        figs.push_back(fig);
    }
    
    double px, py;
    int point_idx = 1;
    while (cin >> px >> py) {
        if (px == 9999.9 && py == 9999.9) break;
        
        bool contained = false;
        for (size_t i = 0; i < figs.size(); ++i) {
            if (isInside(figs[i], px, py)) {
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
