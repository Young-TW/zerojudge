#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    int caseNo = 1;
    while (cin >> T) {
        for (int i = 0; i < T; i++) {
            int t1, t2, fin, att, c1, c2, c3;
            cin >> t1 >> t2 >> fin >> att >> c1 >> c2 >> c3;
            vector<int> v;
            v.push_back(c1);
            v.push_back(c2);
            v.push_back(c3);
            sort(v.begin(), v.end());
            int classScore = (v[1] + v[2]) / 2;
            int total = t1 + t2 + fin + att + classScore;
            char grade;
            if (total >= 90) grade = 'A';
            else if (total >= 80) grade = 'B';
            else if (total >= 70) grade = 'C';
            else if (total >= 60) grade = 'D';
            else grade = 'F';
            cout << "Case " << caseNo << ": " << grade << "\n";
            caseNo++;
        }
    }
    return 0;
}
