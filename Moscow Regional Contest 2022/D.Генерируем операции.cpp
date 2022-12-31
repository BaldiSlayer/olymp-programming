#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int8_t getBit(uint32_t& num) {
    int8_t res = num & 1;
    num >>= 1;
    return res;
}

int main() {
    uint32_t a, b, c;
    cin >> a >> b >> c;
    vector<int8_t> f(4, -1);
    int32_t cnt = 0;
    while (a != 0 || b != 0 || c != 0) {
        cnt++;
        auto bitA = getBit(a);
        auto bitB = getBit(b);
        auto bitC = getBit(c);
        auto ind = (bitA << 1) | bitB;
        if (f[ind] == -1) {
            f[ind] = bitC;
            continue;
        }
        if (f[ind] != bitC) {
            cout << 0;
            return 0;
        }
    }
    if (cnt < 32) {
        auto bitA = getBit(a);
        auto bitB = getBit(b);
        auto bitC = getBit(c);
        auto ind = (bitA << 1) | bitB;
        if (f[ind] == -1) {
            f[ind] = bitC;
        }
        if (f[ind] != bitC) {
            cout << 0;
            return 0;
        }
    }
    auto free = count(f.begin(), f.end(), -1);
    cout << pow(2, free);
    return 0;
}
