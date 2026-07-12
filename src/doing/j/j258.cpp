#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cstdlib>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Precompute handicap values
    vector<int> handicapValues;
    handicapValues.push_back(1); // 1先
    handicapValues.push_back(2); // 2先
    handicapValues.push_back(3); // 3先
    
    vector<vector<int>> pieceGroups = {
        {5},               // horse
        {5},               // cannon
        {10},              // rook
        {5,5},             // double horse
        {2,2,2,2,1,1,1,1,1}, // nine pieces
        {10,5},            // rook+horse
        {10,5},            // rook+cannon
        {10,5,5}           // rook+horse+cannon
    };
    
    for (const auto& group : pieceGroups) {
        int base = 0;
        for (int p : group) base += p;
        if (group.size() == 9) { // nine pieces: only base, no 先
            handicapValues.push_back(base);
        } else {
            for (int k = 0; k <= 3; ++k) {
                handicapValues.push_back(base + k);
            }
        }
    }
    
    int N;
    while (cin >> N) {
        vector<int> brain(N);
        for (int i = 0; i < N; ++i) cin >> brain[i];
        
        vector<int> rank(N);
        for (int i = 0; i < N; ++i) {
            string token;
            cin >> token;
            if (token == "level") {
                int y;
                cin >> y;
                rank[i] = 13 - y;
            } else {
                int x = stoi(token);
                string pieces;
                cin >> pieces; // should be "pieces"
                rank[i] = 12 + x;
            }
        }
        
        vector<int> score(N, 0);
        int lastResult = 0; // 0: not played, 1: Dry wins, 2: Wet wins, 3: draw
        
        for (int round = 0; round < 5; ++round) {
            vector<int> order(N);
            iota(order.begin(), order.end(), 0);
            sort(order.begin(), order.end(), [&](int a, int b) {
                if (brain[a] != brain[b]) return brain[a] > brain[b];
                return a < b;
            });
            
            for (int k = 0; k < N; k += 2) {
                int i = order[k];
                int j = order[k+1];
                
                // Determine giver (higher-ranked or higher id if same rank)
                int giver, receiver;
                if (rank[i] > rank[j]) {
                    giver = i;
                    receiver = j;
                } else if (rank[i] < rank[j]) {
                    giver = j;
                    receiver = i;
                } else {
                    // Same rank: higher id gives
                    if (i > j) {
                        giver = i;
                        receiver = j;
                    } else {
                        giver = j;
                        receiver = i;
                    }
                }
                
                int d = abs(rank[i] - rank[j]);
                if (d == 0) d = 1;
                int idx = d - 1;
                int handicapValue = handicapValues[idx];
                
                brain[giver] = max(0, brain[giver] - handicapValue);
                
                // Determine winner
                if (brain[i] > brain[j]) {
                    score[i] += 2;
                    if ((i == 0 && j == 1) || (i == 1 && j == 0)) {
                        lastResult = (i == 0) ? 1 : 2;
                    }
                } else if (brain[i] < brain[j]) {
                    score[j] += 2;
                    if ((i == 0 && j == 1) || (i == 1 && j == 0)) {
                        lastResult = (j == 0) ? 1 : 2;
                    }
                } else {
                    score[i] += 1;
                    score[j] += 1;
                    if ((i == 0 && j == 1) || (i == 1 && j == 0)) {
                        lastResult = 3;
                    }
                }
            }
        }
        
        // Output scores
        for (int i = 0; i < N; ++i) {
            if (i > 0) cout << ' ';
            cout << score[i];
        }
        cout << "\n";
        
        // Output brain powers
        for (int i = 0; i < N; ++i) {
            if (i > 0) cout << ' ';
            cout << brain[i];
        }
        cout << "\n";
        
        // Output result
        if (lastResult == 1) {
            cout << "10 minutes has passed!\n";
        } else if (lastResult == 2) {
            cout << "I just mopped the floor!\n";
        } else {
            cout << "Liquid-gas interface\n";
        }
    }
    
    return 0;
}
