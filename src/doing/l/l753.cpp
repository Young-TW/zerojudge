#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Solver {
    string digits;
    vector<char> ops;
    long long target;
    int t;
    int L;
    bool found;
    string result_expr;

    Solver(const string& d, const vector<char>& o, long long tar) 
        : digits(d), ops(o), target(tar), t(o.size()), L(d.length()), found(false) {}

    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    struct Node {
        bool is_num;
        string num_str;
        char op;
        Node* left;
        Node* right;
        Node(const string& s) : is_num(true), num_str(s), op(0), left(nullptr), right(nullptr) {}
        Node(char o, Node* l, Node* r) : is_num(false), num_str(""), op(o), left(l), right(r) {}
    };

    string build_expr(Node* node, char parent_op = 0, bool is_right = false) {
        if (node->is_num) {
            return node->num_str;
        }
        string left_str = build_expr(node->left, node->op, false);
        string right_str = build_expr(node->right, node->op, true);
        string s = left_str + node->op + right_str;
        if (parent_op == 0) return s;
        int prec_node = precedence(node->op);
        int prec_parent = precedence(parent_op);
        if (prec_node > prec_parent) {
            return s;
        } else if (prec_node < prec_parent) {
            return "(" + s + ")";
        } else {
            if (is_right) {
                return "(" + s + ")";
            } else {
                return s;
            }
        }
    }

    bool run_dp(const vector<long long>& nums, const vector<string>& num_strs) {
        int n = nums.size();
        vector<vector<unordered_map<long long, Node*>>> dp(n, vector<unordered_map<long long, Node*>>(n));
        for (int i = 0; i < n; ++i) {
            dp[i][i][nums[i]] = new Node(num_strs[i]);
        }
        if (n == 1) {
            if (dp[0][0].count(target)) {
                result_expr = build_expr(dp[0][0][target]);
                found = true;
                return true;
            }
            return false;
        }
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len <= n; ++i) {
                int j = i + len - 1;
                for (int k = i; k < j; ++k) {
                    char op = ops[k];
                    for (const auto& lv_pair : dp[i][k]) {
                        long long lv = lv_pair.first;
                        Node* ln = lv_pair.second;
                        for (const auto& rv_pair : dp[k+1][j]) {
                            long long rv = rv_pair.first;
                            Node* rn = rv_pair.second;
                            if (op == '/' && rv == 0) continue;
                            long long res;
                            if (op == '+') res = lv + rv;
                            else if (op == '-') res = lv - rv;
                            else if (op == '*') res = lv * rv;
                            else if (op == '/') res = lv / rv;
                            if (dp[i][j].find(res) == dp[i][j].end()) {
                                dp[i][j][res] = new Node(op, ln, rn);
                            }
                        }
                    }
                }
                if (i == 0 && j == n-1 && dp[i][j].count(target)) {
                    result_expr = build_expr(dp[i][j][target]);
                    found = true;
                    return true;
                }
            }
        }
        return false;
    }

    void dfs_partition(int start, int numbers_left, vector<long long>& nums, vector<string>& num_strs) {
        if (found) return;
        if (numbers_left == 1) {
            if (start >= L) return;
            string sub = digits.substr(start);
            if (sub.length() > 1 && sub[0] == '0') return;
            long long val;
            try {
                val = stoll(sub);
            } catch (...) {
                return;
            }
            nums.push_back(val);
            num_strs.push_back(sub);
            if (run_dp(nums, num_strs)) {
                return;
            }
            nums.pop_back();
            num_strs.pop_back();
            return;
        }
        if (L - start < numbers_left) return;
        for (int end = start + 1; end <= L - (numbers_left - 1); ++end) {
            string sub = digits.substr(start, end - start);
            if (sub.length() > 1 && sub[0] == '0') continue;
            long long val;
            try {
                val = stoll(sub);
            } catch (...) {
                continue;
            }
            nums.push_back(val);
            num_strs.push_back(sub);
            dfs_partition(end, numbers_left - 1, nums, num_strs);
            if (found) return;
            nums.pop_back();
            num_strs.pop_back();
        }
    }

    string solve() {
        vector<long long> nums;
        vector<string> num_strs;
        dfs_partition(0, t + 1, nums, num_strs);
        return result_expr + "=" + to_string(target);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string n;
    while (cin >> n) {
        int t;
        if (!(cin >> t)) break;
        vector<char> ops(t);
        for (int i = 0; i < t; ++i) {
            cin >> ops[i];
        }
        long long target;
        cin >> target;
        Solver solver(n, ops, target);
        cout << solver.solve() << "\n";
    }
    return 0;
}
