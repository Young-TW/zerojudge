#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int main() {
    int N;
    if (!(cin >> N)) return 0;
    cin.ignore();
    while (N--) {
        string line;
        if (!getline(cin, line)) break;
        istringstream iss(line);
        vector<int> v;
        int x;
        while (iss >> x) v.push_back(x);
        int best = 1;
        for (size_t i = 0; i < v.size(); i++)
            for (size_t j = i + 1; j < v.size(); j++)
                best = max(best, gcd(v[i], v[j]));
        cout << best << "\n";
    }
    return 0;
}
