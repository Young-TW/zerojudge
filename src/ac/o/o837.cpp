#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int get_abs(int x) {
    return x < 0 ? -x : x;
}

int get_sign(int x) {
    return x > 0 ? 1 : -1;
}

bool can_dance(int a, int b) {
    // Must be opposite signs
    if (get_sign(a) == get_sign(b)) return false;
    int sum = get_abs(a) + get_abs(b);
    return is_prime(sum);
}

vector<int> target_state() {
    return {1, 2, 3, 4, 5, 6, 7, 8};
}

bool is_target(const vector<int>& state) {
    for (int i = 0; i < 8; ++i) {
        if (get_abs(state[i]) != i + 1) return false;
    }
    return true;
}

string state_to_key(const vector<int>& state) {
    string key = "";
    for (int i = 0; i < 8; ++i) {
        key += to_string(state[i]) + ",";
    }
    return key;
}

int solve(vector<int> start) {
    if (is_target(start)) return 0;

    queue<pair<vector<int>, int>> q;
    map<string, int> visited;

    q.push({start, 0});
    visited[state_to_key(start)] = 0;

    while (!q.empty()) {
        vector<int> curr = q.front().first;
        int dist = q.front().second;
        q.pop();

        // Try all possible moves
        // For each digit, try to invite any other digit it can dance with
        // The inviting digit moves to left or right of the invited digit
        
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (i == j) continue;
                
                if (can_dance(curr[i], curr[j])) {
                    // curr[i] invites curr[j]
                    // curr[i] can move to left of curr[j] or right of curr[j]
                    
                    vector<int> next_state;
                    
                    // Create new state without curr[i]
                    vector<int> temp;
                    for (int k = 0; k < 8; ++k) {
                        if (k != i) temp.push_back(curr[k]);
                    }
                    
                    // Find position of curr[j] in temp
                    int pos_j = -1;
                    for (int k = 0; k < 7; ++k) {
                        if (temp[k] == curr[j]) {
                            pos_j = k;
                            break;
                        }
                    }
                    
                    // Option 1: Insert curr[i] to the left of curr[j]
                    next_state = temp;
                    next_state.insert(next_state.begin() + pos_j, curr[i]);
                    
                    string key1 = state_to_key(next_state);
                    if (visited.find(key1) == visited.end()) {
                        if (is_target(next_state)) return dist + 1;
                        visited[key1] = dist + 1;
                        q.push({next_state, dist + 1});
                    }
                    
                    // Option 2: Insert curr[i] to the right of curr[j]
                    next_state = temp;
                    next_state.insert(next_state.begin() + pos_j + 1, curr[i]);
                    
                    string key2 = state_to_key(next_state);
                    if (visited.find(key2) == visited.end()) {
                        if (is_target(next_state)) return dist + 1;
                        visited[key2] = dist + 1;
                        q.push({next_state, dist + 1});
                    }
                }
            }
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> input(8);
    int case_num = 1;

    while (cin >> input[0]) {
        if (input[0] == 0) break;
        
        for (int i = 1; i < 8; ++i) {
            cin >> input[i];
        }

        int result = solve(input);
        cout << "Case " << case_num++ << ": " << result << "\n";
    }

    return 0;
}
