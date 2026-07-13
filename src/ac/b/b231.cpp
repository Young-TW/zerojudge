#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    bool first_case = true;
    while (cin >> n) {
        vector<pair<int, int>> books(n);
        for (int i = 0; i < n; ++i) {
            cin >> books[i].first >> books[i].second;
        }
        
        sort(books.begin(), books.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        });
        
        long long current_time = 0;
        long long max_time = 0;
        for (int i = 0; i < n; ++i) {
            current_time += books[i].first;
            if (current_time + books[i].second > max_time) {
                max_time = current_time + books[i].second;
            }
        }
        
        if (!first_case) {
            cout << "\n";
        }
        cout << max_time << "\n";
        first_case = false;
    }
    
    return 0;
}
