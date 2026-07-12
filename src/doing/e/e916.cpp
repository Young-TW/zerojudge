#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Segment {
    long long l, r;
    
    // 計算這段區間中，最佳選擇的位置
    long long get_pos() const {
        if (l == 1 && r == 1) return 1; // 特殊情况：只有1间厕所且未被占用（实际上不会发生，因为l,r是已占用的边界）
        if (l + 1 == r) return -1; // 没有空位
        
        // 第一个选l，第二个选r的情况已经在外部处理
        // 这里处理的是中间的空位
        // 如果左边是0(虚拟)，右边是n+1(虚拟)，则第一个选1，第二个选n
        // 但我们的segment是已占用点之间的区间
        
        // 对于区间 (l, r)，可选位置是 l+1 到 r-1
        // 根据规则：
        // 1. min(i-l, r-i) 最大
        // 2. max(i-l, r-i) 最大
        // 3. i 最小
        
        // 最优位置通常是中点
        long long best_pos = -1;
        long long best_min_dist = -1;
        long long best_max_dist = -1;
        
        // 实际上，对于连续区间，最优解是中点
        // 如果长度是奇数，中点唯一
        // 如果长度是偶数，有两个中点，需要比较
        
        long long len = r - l - 1;
        if (len <= 0) return -1;
        
        // 尝试两个候选点（如果是偶数长度）
        vector<long long> candidates;
        long long mid1 = l + (len + 1) / 2;
        candidates.push_back(mid1);
        if (len % 2 == 0) {
            long long mid2 = mid1 - 1;
            if (mid2 > l && mid2 < r) {
                candidates.push_back(mid2);
            }
        }
        
        for (long long pos : candidates) {
            long long left_dist = pos - l;
            long long right_dist = r - pos;
            long long min_dist = min(left_dist, right_dist);
            long long max_dist = max(left_dist, right_dist);
            
            if (min_dist > best_min_dist ||
                (min_dist == best_min_dist && max_dist > best_max_dist) ||
                (min_dist == best_min_dist && max_dist == best_max_dist && (best_pos == -1 || pos < best_pos))) {
                best_min_dist = min_dist;
                best_max_dist = max_dist;
                best_pos = pos;
            }
        }
        
        return best_pos;
    }
    
    // 计算这个区间的优先级值，用于比较
    // 返回一个 tuple: (min_dist, max_dist, -pos) 以便用标准比较
    // 但我们用自定义比较函数
    long long get_min_dist() const {
        long long pos = get_pos();
        if (pos == -1) return -1;
        return min(pos - l, r - pos);
    }
    
    long long get_max_dist() const {
        long long pos = get_pos();
        if (pos == -1) return -1;
        return max(pos - l, r - pos);
    }
    
    long long get_best_pos() const {
        return get_pos();
    }
};

// 自定义比较函数
bool operator<(const Segment& a, const Segment& b) {
    long long pos_a = a.get_best_pos();
    long long pos_b = b.get_best_pos();
    
    if (pos_a == -1 && pos_b == -1) return false;
    if (pos_a == -1) return false; // a无效，b有效，b优先
    if (pos_b == -1) return true;  // a有效，b无效，a优先
    
    long long min_a = min(pos_a - a.l, a.r - pos_a);
    long long min_b = min(pos_b - b.l, b.r - pos_b);
    
    if (min_a != min_b) {
        return min_a < min_b; // min大的优先，所以<返回true表示a优先级低
    }
    
    long long max_a = max(pos_a - a.l, a.r - pos_a);
    long long max_b = max(pos_b - b.l, b.r - pos_b);
    
    if (max_a != max_b) {
        return max_a < max_b; // max大的优先
    }
    
    return pos_a > pos_b; // pos小的优先，所以>返回true表示a优先级低
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        long long n, k;
        cin >> n >> k;
        
        if (k == 1) {
            cout << 1 << "\n";
            continue;
        }
        if (k == 2) {
            cout << n << "\n";
            continue;
        }
        
        // 使用优先队列存储区间
        priority_queue<Segment> pq;
        
        // 初始状态：第一个人选了1，第二个人选了n
        // 所以有三个区间：(0,1), (1,n), (n,n+1)
        // 但(0,1)和(n,n+1)没有空位，只有(1,n)有空位
        if (n > 2) {
            pq.push({1, n});
        }
        
        long long result = -1;
        
        // 已经选了2个人
        for (long long person = 3; person <= k; ++person) {
            if (pq.empty()) {
                // 没有可用区间，这不应该发生
                break;
            }
            
            Segment best = pq.top();
            pq.pop();
            
            long long pos = best.get_best_pos();
            result = pos;
            
            if (person == k) {
                break;
            }
            
            // 分割区间
            if (pos - best.l > 1) {
                pq.push({best.l, pos});
            }
            if (best.r - pos > 1) {
                pq.push({pos, best.r});
            }
        }
        
        if (result == -1) {
            // 特殊情况处理
            if (k == 1) result = 1;
            else if (k == 2) result = n;
        }
        
        cout << result << "\n";
    }
    
    return 0;
}
