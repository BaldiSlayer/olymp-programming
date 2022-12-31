#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;
    int64_t sum = 0;
    int32_t count6 = 0;
    int32_t count9 = 0;
    for (auto& el : s) {
        int32_t digit = el - '0';
        sum += digit;
        if (digit == 6)
            count6++;
        if (digit == 9)
            count9++;
    }
    if (sum % 9 == 0) {
        cout << 0 << '\n';
        return 0;
    }
    if (sum % 9 == 3 && count9 >= 1) {
        cout << 1 << '\n';
        return 0;
    }
    if (sum % 9 == 3 && count6 >= 2) {
        cout << 2 << '\n';
        return 0;
    }
    if (sum % 9 == 6 && count6 >= 1) {
        cout << 1 << '\n';
        return 0;
    }
    if (sum % 9 == 6 && count9 >= 2) {
        cout << 2 << '\n';
        return 0;
    }    
    cout << -1 << '\n';
}
