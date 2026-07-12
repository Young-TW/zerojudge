#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

struct Book {
    string title;
    string author;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<Book> books;
    string line;
    while (getline(cin, line)) {
        if (line == "END") break;
        size_t p1 = line.find('"');
        size_t p2 = line.find('"', p1 + 1);
        string title = line.substr(p1 + 1, p2 - p1 - 1);
        size_t p3 = line.find(" by ", p2);
        string author = line.substr(p3 + 4);
        books.push_back({title, author});
    }

    sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        if (a.author != b.author) return a.author < b.author;
        return a.title < b.title;
    });

    map<string, int> title_to_idx;
    for (size_t i = 0; i < books.size(); ++i) {
        title_to_idx[books[i].title] = i;
    }

    set<int> shelf;
    set<int> returned;
    for (size_t i = 0; i < books.size(); ++i) {
        shelf.insert(i);
    }

    string cmd;
    while (cin >> cmd) {
        if (cmd == "END") break;
        if (cmd == "SHELVE") {
            for (int idx : returned) {
                auto it = shelf.lower_bound(idx);
                if (it == shelf.begin()) {
                    cout << "Put \"" << books[idx].title << "\" first\n";
                } else {
                    --it;
                    cout << "Put \"" << books[idx].title << "\" after \"" << books[*it].title << "\"\n";
                }
                shelf.insert(idx);
            }
            returned.clear();
        } else {
            string rest;
            getline(cin, rest);
            size_t p1 = rest.find('"');
            size_t p2 = rest.find('"', p1 + 1);
            string title = rest.substr(p1 + 1, p2 - p1 - 1);
            int idx = title_to_idx[title];
            if (cmd == "BORROW") {
                shelf.erase(idx);
            } else if (cmd == "RETURN") {
                returned.insert(idx);
            }
        }
    }

    cout << "END\n";

    return 0;
}
