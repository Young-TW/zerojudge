#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        while (N--) {
            long long X1, Y1, X2, Y2, X3, Y3;
            cin >> X1 >> Y1 >> X2 >> Y2 >> X3 >> Y3;
            
            long long cross = (X2 - X1) * (Y3 - Y1) - (Y2 - Y1) * (X3 - X1);
            bool on_segment = false;
            
            if (cross == 0) {
                if (min(X1, X2) <= X3 && X3 <= max(X1, X2) && 
                    min(Y1, Y2) <= Y3 && Y3 <= max(Y1, Y2)) {
                    on_segment = true;
                }
            }
            
            if (on_segment) {
                cout << "該死的東西!竟敢想讓我死！\n";
            } else {
                cout << "父親大人!母親大人!我快到了！\n";
            }
        }
    }
    
    return 0;
}
