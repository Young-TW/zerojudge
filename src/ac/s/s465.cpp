#include <iostream>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        long long max_C0 = LLONG_MIN;
        long long min_C1 = LLONG_MAX;
        
        for (int i = 0; i < N; ++i) {
            long long C;
            int D;
            cin >> C >> D;
            if (D == 0) {
                if (C > max_C0) {
                    max_C0 = C;
                }
            } else {
                if (C < min_C1) {
                    min_C1 = C;
                }
            }
        }
        
        if (max_C0 >= min_C1) {
            cout << "I am a robot.\n";
        } else {
            cout << min_C1 - max_C0 << "\n";
        }
    }
    
    return 0;
}
