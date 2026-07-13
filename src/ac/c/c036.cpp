#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int H, U, D, F;
    while (cin >> H >> U >> D >> F && H != 0) {
        double current_height = 0.0;
        double climb_distance = U;
        double fatigue_drop = U * F / 100.0;
        int day = 0;
        
        while (true) {
            day++;
            if (climb_distance > 0) {
                current_height += climb_distance;
            }
            
            if (current_height > H) {
                cout << "success on day " << day << "\n";
                break;
            }
            
            current_height -= D;
            
            if (current_height < 0) {
                cout << "failure on day " << day << "\n";
                break;
            }
            
            climb_distance -= fatigue_drop;
        }
    }
    
    return 0;
}
