#include <iostream>
#include <vector>

using namespace std;

class BIT {
    vector<int> tree;
    int size;
public:
    BIT(int n) : size(n), tree(n + 1, 0) {}
    
    void update(int i, int delta) {
        for (; i <= size; i += i & (-i))
            tree[i] += delta;
    }
    
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & (-i))
            sum += tree[i];
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        BIT bit(N);
        for (int i = 0; i < N; ++i) {
            int M;
            cin >> M;
            int greater_count = bit.query(N) - bit.query(M);
            cout << greater_count + 1 << "\n";
            bit.update(M, 1);
        }
    }
    return 0;
}
