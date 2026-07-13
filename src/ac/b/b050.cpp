#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cctype>
using namespace std;

class Set {
private:
    set<char> elements;

public:
    Set() {}
    Set(const string& s) {
        for (char c : s) {
            elements.insert(c);
        }
    }

    void print() const {
        cout << "{";
        bool first = true;
        for (char c : elements) {
            if (!first) cout << "";
            cout << c;
            first = false;
        }
        cout << "}";
    }

    Set operator+(const Set& other) const {
        Set result;
        set_union(elements.begin(), elements.end(),
                  other.elements.begin(), other.elements.end(),
                  inserter(result.elements, result.elements.begin()));
        return result;
    }

    Set operator*(const Set& other) const {
        Set result;
        set_intersection(elements.begin(), elements.end(),
                         other.elements.begin(), other.elements.end(),
                         inserter(result.elements, result.elements.begin()));
        return result;
    }

    Set operator-(const Set& other) const {
        Set result;
        set_difference(elements.begin(), elements.end(),
                       other.elements.begin(), other.elements.end(),
                       inserter(result.elements, result.elements.begin()));
        return result;
    }

    bool operator>=(const Set& other) const {
        return includes(elements.begin(), elements.end(),
                        other.elements.begin(), other.elements.end());
    }
};

int main() {
    int n;
    int testCase = 1;
    while (cin >> n && n != 0) {
        vector<Set> sets;
        string s;
        for (int i = 0; i < n; ++i) {
            cin >> s;
            sets.emplace_back(s);
        }

        cout << "Test Case " << testCase++ << ":" << endl;
        for (int i = 0; i < n; ++i) {
            cout << char('A' + i) << ": ";
            sets[i].print();
            cout << endl;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                cout << char('A' + i) << "+" << char('A' + j) << ": ";
                (sets[i] + sets[j]).print();
                cout << endl;

                cout << char('A' + i) << "*" << char('A' + j) << ": ";
                (sets[i] * sets[j]).print();
                cout << endl;

                cout << char('A' + i) << "-" << char('A' + j) << ": ";
                (sets[i] - sets[j]).print();
                cout << endl;

                cout << char('A' + j) << "-" << char('A' + i) << ": ";
                (sets[j] - sets[i]).print();
                cout << endl;

                if (sets[i] >= sets[j]) {
                    cout << char('A' + i) << " contains " << char('A' + j) << endl;
                } else {
                    cout << char('A' + i) << " does not contain " << char('A' + j) << endl;
                }

                if (sets[j] >= sets[i]) {
                    cout << char('A' + j) << " contains " << char('A' + i) << endl;
                } else {
                    cout << char('A' + j) << " does not contain " << char('A' + i) << endl;
                }
            }
        }
    }
    return 0;
}
