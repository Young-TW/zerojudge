#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<int> movies(N);
        for (int i = 0; i < N; ++i) {
            int h, m;
            cin >> h >> m;
            movies[i] = h * 60 + m;
        }
        int ah, am;
        cin >> ah >> am;
        int arrival = ah * 60 + am + 20;
        
        int best = 1e9;
        for (int i = 0; i < N; ++i) {
            if (movies[i] >= arrival && movies[i] < best) {
                best = movies[i];
            }
        }
        
        if (best == 1e9) {
            cout << "Too Late\n";
        } else {
            int h = best / 60;
            int m = best % 60;
            cout << setw(2) << setfill('0') << h << " " << setw(2) << setfill('0') << m << "\n";
        }
    }
    return 0;
}
