#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        priority_queue<double, vector<double>, greater<double>> pq;
        for (int i = 0; i < n; ++i) {
            string ch;
            double p;
            cin >> ch >> p;
            pq.push(p);
        }
        
        double ans = 0.0;
        while (pq.size() > 1) {
            double a = pq.top(); pq.pop();
            double b = pq.top(); pq.pop();
            double sum = a + b;
            ans += sum;
            pq.push(sum);
        }
        
        cout << fixed << setprecision(2) << ans << "\n";
    }
    return 0;
}
