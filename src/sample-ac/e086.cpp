#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Record {
    string student_id;
    string student_name;
    string subject_id;
    string subject_name;
    int score;
};

bool cmp(const Record& a, const Record& b) {
    if (a.student_id != b.student_id) return a.student_id < b.student_id;
    return a.subject_id < b.subject_id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        map<string, pair<string, string>> subjects;
        map<string, string> students;
        
        for (int i = 0; i < n; ++i) {
            string id, name, ans;
            cin >> id >> name >> ans;
            subjects[id] = {name, ans};
        }
        
        for (int i = 0; i < m; ++i) {
            string id, name;
            cin >> id >> name;
            students[id] = name;
        }
        
        vector<Record> records;
        
        for (int i = 0; i < n * m; ++i) {
            string sid, sub_id, ans;
            cin >> sid >> sub_id >> ans;
            
            string sub_name = subjects[sub_id].first;
            string std_ans = subjects[sub_id].second;
            int T = std_ans.length();
            int score = 0;
            if (T > 0) {
                int per_question = 100 / T;
                for (int j = 0; j < T; ++j) {
                    if (j < ans.length() && ans[j] != '=' && ans[j] == std_ans[j]) {
                        score += per_question;
                    }
                }
            }
            
            records.push_back({sid, students[sid], sub_id, sub_name, score});
        }
        
        sort(records.begin(), records.end(), cmp);
        
        for (const auto& r : records) {
            cout << r.student_id << "," << r.student_name << "," << r.subject_id << "," << r.subject_name << "," << r.score << "\n";
        }
    }
    
    return 0;
}
