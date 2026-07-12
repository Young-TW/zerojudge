#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    if (!(cin >> N)) return 0;
    for (int caseNum = 1; caseNum <= N; ++caseNum) {
        string s;
        cin >> s;
        int L = s.length();
        vector<int> draw_height(L);
        int current_height = 0;
        for (int i = 0; i < L; ++i) {
            if (s[i] == 'R') {
                draw_height[i] = current_height;
                current_height++;
            } else if (s[i] == 'F') {
                current_height--;
                draw_height[i] = current_height;
            } else { // 'C'
                draw_height[i] = current_height;
            }
        }
        int min_h = *min_element(draw_height.begin(), draw_height.end());
        int max_h = *max_element(draw_height.begin(), draw_height.end());
        int shift = 1 - min_h;
        int max_row = max_h + shift; // = max_h - min_h + 1
        
        vector<int> shifted(L);
        for (int i = 0; i < L; ++i) {
            shifted[i] = draw_height[i] + shift;
        }
        
        cout << "Case #" << caseNum << ":\n";
        for (int r = max_row; r >= 1; --r) {
            cout << '|' << ' ';
            for (int i = 0; i < L; ++i) {
                if (shifted[i] == r) {
                    if (s[i] == 'R') cout << '/';
                    else if (s[i] == 'F') cout << '\\';
                    else cout << '_';
                } else {
                    cout << ' ';
                }
            }
            cout << '\n';
        }
        cout << '+';
        for (int i = 0; i < L + 2; ++i) {
            cout << '-';
        }
        cout << '\n';
        
        if (caseNum != N) cout << '\n';
    }
    return 0;
}
