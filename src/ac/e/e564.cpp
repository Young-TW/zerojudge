#include <iostream>
#include <deque>
#include <string>
#include <vector>
using namespace std;

int teamOf[1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    int scenario = 1;
    while (cin >> t) {
        if (t == 0) break;
        
        vector<deque<int>> teamQueues(t);
        deque<int> mainQueue;
        
        for (int i = 0; i < t; i++) {
            int n;
            cin >> n;
            for (int j = 0; j < n; j++) {
                int x;
                cin >> x;
                teamOf[x] = i;
            }
        }
        
        cout << "Scenario #" << scenario << "\n";
        
        string cmd;
        while (cin >> cmd) {
            if (cmd == "STOP") break;
            if (cmd == "ENQUEUE") {
                int x;
                cin >> x;
                int team = teamOf[x];
                if (teamQueues[team].empty()) {
                    mainQueue.push_back(team);
                }
                teamQueues[team].push_back(x);
            } else if (cmd == "DEQUEUE") {
                int team = mainQueue.front();
                int x = teamQueues[team].front();
                teamQueues[team].pop_front();
                if (teamQueues[team].empty()) {
                    mainQueue.pop_front();
                }
                cout << x << "\n";
            }
        }
        
        cout << "\n";
        scenario++;
    }
    return 0;
}
