#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Data {
    long long a, n;
    double value;
};

bool compare(const Data &x, const Data &y) {
    if (x.value != y.value) {
        return x.value > y.value;
    } else {
        return x.a > y.a;
    }
}

int main() {
    vector<Data> datas;
    long long a, n;
    while (cin >> a >> n) {
        double value = n * log(a);
        datas.push_back({a, n, value});
    }

    sort(datas.begin(), datas.end(), compare);

    for (const auto &data : datas) {
        cout << data.a << " " << data.n << "\n";
    }

    return 0;
}
