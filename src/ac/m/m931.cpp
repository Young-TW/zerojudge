#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Role {
    int a;
    int d;
    long long power;
};

bool compareRoles(const Role& r1, const Role& r2) {
    return r1.power > r2.power;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<Role> roles(n);
        for (int i = 0; i < n; ++i) {
            cin >> roles[i].a >> roles[i].d;
            roles[i].power = (long long)roles[i].a * roles[i].a + (long long)roles[i].d * roles[i].d;
        }
        
        sort(roles.begin(), roles.end(), compareRoles);
        
        cout << roles[1].a << " " << roles[1].d << "\n";
    }
    
    return 0;
}
