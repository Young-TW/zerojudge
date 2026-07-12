#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct Customer {
    int age;
    int totalAmount;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        int categoryAmount[128] = {0};
        map<string, Customer> customers;

        for (int i = 0; i < N; ++i) {
            string name;
            char gender;
            char category;
            int age;
            int amount;
            cin >> name >> gender >> category >> age >> amount;
            categoryAmount[category] += amount;
            customers[name].age = age;
            customers[name].totalAmount += amount;
        }

        // (1) 最高總消費金額的圖書類別
        char maxCategory = 'A';
        for (char c = 'B'; c <= 'E'; ++c) {
            if (categoryAmount[c] > categoryAmount[maxCategory]) {
                maxCategory = c;
            }
        }
        cout << maxCategory << "\n";

        // (2) 年齡層與總消費金額等級的客戶數分布表
        int dist[10][10] = {0};
        for (auto& p : customers) {
            int age = p.second.age;
            int amount = p.second.totalAmount;
            int ageIdx = (age - 1) / 10;
            if (ageIdx < 0) ageIdx = 0;
            if (ageIdx > 9) ageIdx = 9;
            
            int amountIdx = 0;
            if (amount > 0) {
                amountIdx = (amount - 1) / 1000;
            }
            if (amountIdx > 9) amountIdx = 9;
            
            dist[amountIdx][ageIdx]++;
        }

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                cout << dist[i][j];
                if (j < 9) cout << " ";
            }
            cout << "\n";
        }

        // (3) 總消費金額最高的五位客戶
        vector<pair<string, int>> v;
        for (auto& p : customers) {
            v.push_back({p.first, p.second.totalAmount});
        }
        sort(v.begin(), v.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });

        int limit = min(5, (int)v.size());
        for (int i = 0; i < limit; ++i) {
            cout << v[i].first << " " << v[i].second << "\n";
        }
        if ((int)v.size() > 5) {
            int fifthAmount = v[4].second;
            for (int i = 5; i < (int)v.size(); ++i) {
                if (v[i].second == fifthAmount) {
                    cout << v[i].first << " " << v[i].second << "\n";
                } else {
                    break;
                }
            }
        }
    }

    return 0;
}
