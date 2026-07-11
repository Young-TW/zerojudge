#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string a, b;
    int score_yu = 0, score_li = 0;
    
    while (cin >> a >> b) {
        if (a == b) {
            continue;
        }
        bool yu_wins = (a == "A" && b == "C") || 
                       (a == "B" && b == "A") || 
                       (a == "C" && b == "B");
        if (yu_wins) {
            score_yu++;
        } else {
            score_li++;
        }
    }
    
    cout << score_yu << "\n";
    cout << score_li << "\n";
    if (score_yu > score_li) {
        cout << "肥余\n";
    } else if (score_li > score_yu) {
        cout << "肥李\n";
    } else {
        cout << "打平\n";
    }
    
    return 0;
}
