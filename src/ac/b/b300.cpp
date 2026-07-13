#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string d0;
    long long M;
    while (cin >> d0 >> M) {
        int y0 = stoi(d0.substr(0, 4));
        int m0 = stoi(d0.substr(5, 2));
        int month0 = y0 * 12 + m0;
        
        vector<string> cityNames;
        map<string, long long> cityIncome;
        string name;
        while (cin >> name && name != "----") {
            long long r;
            cin >> r;
            cityNames.push_back(name);
            cityIncome[name] = r;
        }
        
        long long X, Y;
        cin >> X >> Y;
        
        map<int, vector<pair<string, string>>> events;
        string k, c, h;
        while (cin >> k && k != "----") {
            cin >> c >> h;
            int yk = stoi(k.substr(0, 4));
            int mk = stoi(k.substr(5, 2));
            int monthK = yk * 12 + mk;
            events[monthK].push_back({c, h});
        }
        
        string d1;
        cin >> d1;
        int y1 = stoi(d1.substr(0, 4));
        int m1 = stoi(d1.substr(5, 2));
        int month1 = y1 * 12 + m1;
        
        long long totalIncome = 0;
        for (const auto& cn : cityNames) {
            totalIncome += cityIncome[cn];
        }
        
        for (int month = month0 + 1; month <= month1; month++) {
            M += totalIncome;
            
            if (events.count(month)) {
                for (const auto& ev : events[month]) {
                    const string& city = ev.first;
                    const string& change = ev.second;
                    long long oldIncome = cityIncome[city];
                    if (change == "BUILT") {
                        cityIncome[city] += X;
                    } else if (change == "BOOST") {
                        cityIncome[city] += X * X;
                    } else if (change == "DAMAGE") {
                        cityIncome[city] -= Y;
                        if (cityIncome[city] < 0) cityIncome[city] = 0;
                    } else if (change == "RUIN") {
                        cityIncome[city] = 0;
                    }
                    totalIncome += cityIncome[city] - oldIncome;
                }
            }
        }
        
        vector<pair<long long, int>> sortedCities;
        for (int i = 0; i < (int)cityNames.size(); i++) {
            sortedCities.push_back({cityIncome[cityNames[i]], i});
        }
        sort(sortedCities.begin(), sortedCities.end(), [](const pair<long long,int>& a, const pair<long long,int>& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second < b.second;
        });
        
        cout << d1 << " " << M << "\n";
        for (const auto& sc : sortedCities) {
            cout << cityNames[sc.second] << " " << sc.first << "\n";
        }
    }
    return 0;
}
