#include <iostream>
#include <string>

using namespace std;

void solve(const string& in_order, const string& post_order) {
    if (in_order.empty()) return;
    char root = post_order.back();
    cout << root;
    size_t pos = in_order.find(root);
    string left_in = in_order.substr(0, pos);
    string right_in = in_order.substr(pos + 1);
    string left_post = post_order.substr(0, pos);
    string right_post = post_order.substr(pos, right_in.length());
    solve(left_in, left_post);
    solve(right_in, right_post);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string in_order, post_order;
    while (cin >> in_order >> post_order) {
        solve(in_order, post_order);
        cout << "\n";
    }
    return 0;
}
