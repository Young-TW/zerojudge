#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unordered_map<string, char> wordToDigit = {
        {"ONE", '1'}, {"TWO", '2'}, {"THREE", '3'}, {"FOUR", '4'}, {"FIVE", '5'},
        {"SIX", '6'}, {"SEVEN", '7'}, {"EIGHT", '8'}, {"NINE", '9'}
    };
    
    int N;
    while (cin >> N) {
        vector<pair<long long, char>> rooms;
        rooms.reserve(N);
        for (int i = 0; i < N; ++i) {
            string word;
            long long value;
            cin >> word >> value;
            rooms.emplace_back(value, wordToDigit[word]);
        }
        sort(rooms.begin(), rooms.end(),
             [](const pair<long long, char>& a, const pair<long long, char>& b) {
                 return a.first < b.first;
             });
        for (const auto& p : rooms) {
            cout << p.second;
        }
        cout << '\n';
    }
    return 0;
}
