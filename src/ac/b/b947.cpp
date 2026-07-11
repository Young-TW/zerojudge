#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        string name1, name2;
        cin >> name1 >> name2;
        
        long long votes1 = 0, votes2 = 0;
        for (int i = 0; i < N; ++i) {
            long long S, V1, V2;
            cin >> S >> V1 >> V2;
            if (V1 > V2) {
                votes1 += S;
            } else {
                votes2 += S;
            }
        }
        
        if (votes1 > votes2) {
            cout << name1 << "\n";
        } else if (votes2 > votes1) {
            cout << name2 << "\n";
        } else {
            cout << "Tie\n";
        }
    }
    
    return 0;
}
