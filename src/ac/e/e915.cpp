#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Customer {
    long long a;
    long long b;
};

bool cmp(const Customer& x, const Customer& y) {
    return x.a * y.b > y.a * x.b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<Customer> customers(N);
        for (int i = 0; i < N; ++i) {
            cin >> customers[i].a >> customers[i].b;
        }
        
        sort(customers.begin(), customers.end(), cmp);
        
        long long current_time = 0;
        long long total_anger = 0;
        
        for (int i = 0; i < N; ++i) {
            current_time += customers[i].b;
            total_anger += customers[i].a * current_time;
        }
        
        cout << total_anger << "\n";
    }
    
    return 0;
}
