#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    while (cin >> n >> m >> q) {
        string dummy;
        getline(cin, dummy);
        
        set<int> alive;
        for (int i = 1; i <= n; ++i) {
            alive.insert(i);
        }
        
        vector<int> alive_count(n + 2, 0);
        vector<vector<int>> alive_people(n + 2);
        vector<int> eliminated_round(n + 2, -1);
        
        alive_count[0] = n;
        for (int i = 1; i <= n; ++i) {
            alive_people[0].push_back(i);
        }
        
        int round = 0;
        int n_prime = n;
        
        for (int i = 0; i < m; ++i) {
            if (n_prime <= 1) {
                string line;
                getline(cin, line);
                continue;
            }
            
            string line;
            if (!getline(cin, line)) break;
            stringstream ss(line);
            int k;
            if (!(ss >> k)) continue;
            
            vector<int> people;
            int p;
            while (ss >> p) {
                people.push_back(p);
            }
            
            bool eliminated = false;
            if (people.size() >= 2) {
                eliminated = true;
                for (int person : people) {
                    alive.erase(person);
                    eliminated_round[person] = round + 1;
                }
            } else if (people.size() == 1) {
                if (k == n_prime) {
                    eliminated = true;
                    int person = people[0];
                    alive.erase(person);
                    eliminated_round[person] = round + 1;
                }
            }
            
            if (eliminated) {
                round++;
                n_prime = alive.size();
                alive_count[round] = n_prime;
                for (int person : alive) {
                    alive_people[round].push_back(person);
                }
            }
        }
        
        for (int i = 0; i < q; ++i) {
            char type;
            int val;
            cin >> type >> val;
            if (type == 'a') {
                cout << alive_count[val] << "\n";
            } else if (type == 'b') {
                for (size_t j = 0; j < alive_people[val].size(); ++j) {
                    if (j > 0) cout << " ";
                    cout << alive_people[val][j];
                }
                cout << "\n";
            } else if (type == 'c') {
                cout << eliminated_round[val] << "\n";
            }
        }
    }
    
    return 0;
}
