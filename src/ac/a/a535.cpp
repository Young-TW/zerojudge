#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    int n, p;
    int caseNo = 0;
    bool first = true;
    string tmp;
    while (cin >> n >> p) {
        if (n == 0 && p == 0) break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (int i = 0; i < n; i++) getline(cin, tmp);
        string bestName;
        double bestPrice = 0.0;
        int bestMet = -1;
        for (int i = 0; i < p; i++) {
            string name;
            getline(cin, name);
            double d;
            int r;
            cin >> d >> r;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            for (int j = 0; j < r; j++) getline(cin, tmp);
            if (r > bestMet || (r == bestMet && d < bestPrice)) {
                bestMet = r;
                bestPrice = d;
                bestName = name;
            }
        }
        if (!first) cout << "\n";
        first = false;
        ++caseNo;
        cout << "RFP #" << caseNo << "\n" << bestName << "\n";
    }
    return 0;
}
