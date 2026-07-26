#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

struct Book {
    std::string title;
    std::string author;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<Book> books;
    std::string line;

    // ----- read book list -----
    while (std::getline(std::cin, line)) {
        if (line == "END") break;
        std::size_t p1 = line.find('"');
        std::size_t p2 = line.find('"', p1 + 1);
        std::string title = line.substr(p1 + 1, p2 - p1 - 1);
        std::size_t p3 = line.find(" by ", p2);
        std::string author = line.substr(p3 + 4);
        books.push_back({title, author});
    }

    // sort according to author, then title
    std::sort(books.begin(), books.end(),
              [](const Book& a, const Book& b) {
                  if (a.author != b.author) return a.author < b.author;
                  return a.title < b.title;
              });

    // map title -> index in sorted vector
    std::unordered_map<std::string, int> id;
    for (int i = 0; i < (int)books.size(); ++i) {
        id[books[i].title] = i;
    }

    // books currently on the shelf
    std::set<int> shelf;
    for (int i = 0; i < (int)books.size(); ++i) shelf.insert(i);

    // books that have been returned but not yet shelved
    std::set<int> returned;

    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "END") break;

        if (cmd == "SHELVE") {
            for (int idx : returned) {
                auto it = shelf.lower_bound(idx);
                if (it == shelf.begin()) {
                    std::cout << "Put \"" << books[idx].title << "\" first\n";
                } else {
                    --it;
                    std::cout << "Put \"" << books[idx].title << "\" after \""
                              << books[*it].title << "\"\n";
                }
                shelf.insert(idx);
            }
            returned.clear();
            std::cout << "END\n";
        } else {
            std::string rest;
            std::getline(std::cin, rest);          // the rest of the line
            std::size_t p1 = rest.find('"');
            std::size_t p2 = rest.find('"', p1 + 1);
            std::string title = rest.substr(p1 + 1, p2 - p1 - 1);
            int idx = id[title];
            if (cmd == "BORROW") {
                shelf.erase(idx);
            } else if (cmd == "RETURN") {
                returned.insert(idx);
            }
        }
    }
    return 0;
}
