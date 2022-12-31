#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;
typedef long double ld;

string s;

string gete(ll x) {
    cout << "E " << x << endl;
    cin >> s;

    return s;
}

string getm(ll x) {
    cout << "M " << x << endl;
    cin >> s;

    return s;
}

/*string gete(ll x) {
    if (1 * 1 + 2 * 2 <= x) {
        return "in";
    }
    return "out";
}

string getm(ll x) {
    if (1 + 2 <= x) {
        return "in";
    }
    return "out";
}*/

int main() {
    ll l = -1, r = 5 * 1e18;
    ll x;

    while (r - l > 1) {
        ll m = (l + r) / 2;

        s = getm(m);
        if (s == "out") {
            l = m;
        }
        else {
            r = m;
        }
    }

    ll mat = r;

    l = -1;
    r = mat * mat;
    while (r - l > 1) {
        ll m = (l + r) / 2;

        s = gete(m);
        if (s == "out") {
            l = m;
        }
        else {
            r = m;
        }
    }

    ld euclid = r;
    ld a = 2, b = -2 * mat, c = mat * mat - euclid;
    ld sqD = sqrtl(b * b - 4 * a * c);

    ld x1 = (-b + sqD) / (2 * a), x2 = (-b - sqD) / (2 * a);
    ld y1 = -x1 + mat, y2 = -x2 + mat;

    if (x1 <= y1) {
        cout << "! " << (ll)x1 << " " << (ll)y1 << endl;
    }
    else {
        cout << "! " << (ll)x2 << " " << (ll)y2 << endl;
    }

    return 0;
}
