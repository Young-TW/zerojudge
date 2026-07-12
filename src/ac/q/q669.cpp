#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        int myScore;
        cin >> myScore;
        int higher = 0, same = 1;
        for (int i = 1; i < N; i++) {
            int s;
            cin >> s;
            if (s > myScore) higher++;
            else if (s == myScore) same++;
        }
        if (higher + same <= 5) {
            cout << "Top 5\n";
        } else if (higher < 5) {
            cout << "Maybe Top 5\n";
        } else if (higher < 10) {
            cout << "Top 10\n";
        } else {
            cout << "Thank You\n";
        }
    }
    return 0;
}
