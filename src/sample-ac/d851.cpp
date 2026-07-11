#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A, B;
    if (!(cin >> A >> B)) return 0;

    vector<pair<string, string>> rules;
    string a, b;
    while (cin >> a >> b) {
        rules.push_back({a, b});
    }

    unordered_map<string, int> dist;
    queue<string> q;
    q.push(A);
    dist[A] = 0;

    while (!q.empty()) {
        string curr = q.front();
        q.pop();

        if (curr == B) {
            cout << dist[curr] << "\n";
            return 0;
        }

        if (dist[curr] == 10) continue;

        for (auto const& rule : rules) {
            const string& from = rule.first;
            const string& to = rule.second;
            size_t pos = curr.find(from);
            while (pos != string::npos) {
                string next = curr;
                next.replace(pos, from.length(), to);
                if (next.length() <= 300 && dist.find(next) == dist.end()) {
                    dist[next] = dist[curr] + 1;
                    q.push(next);
                }
                pos = curr.find(from, pos + 1);
            }
        }
    }

    cout << "no answer!\n";
    return 0;
}
