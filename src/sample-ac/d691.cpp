#include <iostream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string lineA, lineB;
    while (getline(cin, lineA)) {
        if (!getline(cin, lineB)) break;
        
        set<long long> A, B;
        stringstream ssA(lineA);
        long long x;
        while (ssA >> x) {
            A.insert(x);
        }
        
        stringstream ssB(lineB);
        while (ssB >> x) {
            B.insert(x);
        }
        
        size_t common = 0;
        for (long long val : A) {
            if (B.count(val)) {
                common++;
            }
        }
        
        if (A == B) {
            cout << "A equals B\n";
        } else if (common == A.size() && A.size() < B.size()) {
            cout << "A is a proper subset of B\n";
        } else if (common == B.size() && B.size() < A.size()) {
            cout << "B is a proper subset of A\n";
        } else if (common == 0) {
            cout << "A and B are disjoint\n";
        } else {
            cout << "I'm confused!\n";
        }
    }
    
    return 0;
}
