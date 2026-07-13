#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int evaluate(const string& name) {
    int score = 0;
    int nameLen = name.length();
    for (int i = 0; i < nameLen; ++i) {
        int charCode = (int)name[i];
        score += (charCode * 1123) % 1002;
        while (charCode > 0) {
            score += charCode % 10;
            charCode /= 10;
        }
    }
    return score % 101;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<pair<string, int>> arr(N);
        for (int i = 0; i < N; ++i) {
            cin >> arr[i].first;
            arr[i].second = evaluate(arr[i].first);
        }
        
        stable_sort(arr.begin(), arr.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second < b.second;
        });
        
        for (int i = 0; i < N; ++i) {
            cout << arr[i].first << " " << arr[i].second << "\n";
        }
    }
    
    return 0;
}
