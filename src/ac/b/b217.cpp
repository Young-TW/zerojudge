#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <tuple>

using namespace std;

struct Article {
    string norm_subject;
    tuple<int, int, int, int> date; // Y, M, D, H
    int order;
    string id;
};

string normalize_subject(const string& line) {
    string content;
    size_t pos = line.find("Subject:");
    if (pos != string::npos) {
        pos += 8; // length of "Subject:"
        while (pos < line.size() && line[pos] == ' ') pos++;
        content = line.substr(pos);
    } else {
        content = line;
    }

    // trim leading spaces
    size_t start = 0;
    while (start < content.size() && content[start] == ' ') start++;
    // trim trailing spaces
    size_t end = content.size();
    while (end > start && content[end - 1] == ' ') end--;
    content = content.substr(start, end - start);

    // remove leading "Re:" or "RE:" once
    if (content.size() >= 3) {
        string prefix = content.substr(0, 3);
        if (prefix == "Re:" || prefix == "RE:") {
            content = content.substr(3);
            // trim leading spaces again
            start = 0;
            while (start < content.size() && content[start] == ' ') start++;
            content = content.substr(start);
        }
    }
    return content;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }

    vector<Article> articles;
    int order = 0;
    int i = 0;
    int n = lines.size();

    while (i < n) {
        // skip blank lines
        while (i < n && lines[i].empty()) i++;
        if (i >= n) break;
        if (i + 2 >= n) break; // incomplete article

        string subj_line = lines[i];
        string date_line = lines[i + 1];
        string id_line = lines[i + 2];

        Article art;
        art.norm_subject = normalize_subject(subj_line);

        // parse date: "Date: M D H Y"
        int M, D, H, Y;
        {
            stringstream ss(date_line);
            string tmp;
            ss >> tmp; // "Date:"
            ss >> M >> D >> H >> Y;
        }
        art.date = make_tuple(Y, M, D, H);

        // parse id: "ID: xxxxx"
        {
            size_t pos = id_line.find("ID:");
            if (pos != string::npos) {
                pos += 3;
                while (pos < id_line.size() && id_line[pos] == ' ') pos++;
                art.id = id_line.substr(pos);
                while (!art.id.empty() && art.id.back() == ' ') art.id.pop_back();
            } else {
                art.id = id_line;
            }
        }

        art.order = order++;
        articles.push_back(art);

        i += 3;
        // check for blank lines after article
        if (i < n && lines[i].empty()) {
            i++;
            if (i < n && lines[i].empty()) {
                // two consecutive blank lines -> end of data
                break;
            }
        }
    }

    // Group by normalized subject
    unordered_map<string, vector<Article>> groups;
    for (auto& art : articles) {
        groups[art.norm_subject].push_back(art);
    }

    struct Thread {
        string subject;
        vector<Article> articles;
        tuple<int, int, int, int> earliest_date;
        int earliest_order;
    };

    vector<Thread> threads;
    for (auto& kv : groups) {
        auto& vec = kv.second;
        sort(vec.begin(), vec.end(), [](const Article& a, const Article& b) {
            if (a.date != b.date) return a.date < b.date;
            return a.order < b.order;
        });
        Thread th;
        th.subject = kv.first;
        th.articles = vec;
        th.earliest_date = vec[0].date;
        th.earliest_order = vec[0].order;
        threads.push_back(th);
    }

    sort(threads.begin(), threads.end(), [](const Thread& a, const Thread& b) {
        if (a.earliest_date != b.earliest_date) return a.earliest_date < b.earliest_date;
        return a.earliest_order < b.earliest_order;
    });

    int total_threads = threads.size();
    // Output first two threads
    for (int idx = 0; idx < 2 && idx < total_threads; idx++) {
        cout << "Subject: " << threads[idx].subject << '\n';
        cout << "ID: ";
        for (int j = 0; j < threads[idx].articles.size(); j++) {
            if (j) cout << ',';
            cout << threads[idx].articles[j].id;
        }
        cout << '\n';
        if (idx == 0 && total_threads > 2) {
            cout << '\n';
        }
    }

    return 0;
}
