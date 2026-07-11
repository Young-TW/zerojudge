#include <iostream>
#include <string>
using namespace std;

int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
string monthNames[13] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
string dayNames[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

bool isLeapJulian(int year) {
    return year % 4 == 0;
}

bool isLeapGregorian(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isJulian(int month, int day, int year) {
    if (year < 1752) return true;
    if (year > 1752) return false;
    if (month < 9) return true;
    if (month > 9) return false;
    return day <= 2;
}

bool isValid(int month, int day, int year) {
    if (month < 1 || month > 12) return false;
    if (day < 1) return false;
    if (year == 1752 && month == 9 && day >= 3 && day <= 13) return false;
    
    bool julian = isJulian(month, day, year);
    bool leap = julian ? isLeapJulian(year) : isLeapGregorian(year);
    
    int maxDay = monthDays[month];
    if (month == 2 && leap) maxDay = 29;
    
    return day <= maxDay;
}

long long julianDayNumber(int month, int day, int year, bool julian) {
    long long a = (14 - month) / 12;
    long long y = (long long)year + 4800 - a;
    long long m = month + 12 * a - 3;
    
    if (julian) {
        return day + (153 * m + 2) / 5 + 365 * y + y / 4 - 32083;
    } else {
        return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    }
}

int main() {
    int month, day, year;
    while (cin >> month >> day >> year) {
        if (month == 0 && day == 0 && year == 0) break;
        
        if (!isValid(month, day, year)) {
            cout << month << "/" << day << "/" << year << " is an invalid date." << endl;
        } else {
            bool julian = isJulian(month, day, year);
            long long jdn = julianDayNumber(month, day, year, julian);
            int dow = (int)((jdn + 1) % 7);
            if (dow < 0) dow += 7;
            cout << monthNames[month] << " " << day << ", " << year << " is a " << dayNames[dow] << endl;
        }
    }
    return 0;
}
