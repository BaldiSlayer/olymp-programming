#include <iostream>
#include <cmath>
#include <string>

typedef long long ll;
typedef long double ld;

using namespace std;

int main() {
	ll l = -1;
	ll r = 5 * 1e18;
	string s;

	while (r - l > 1) {
		ll m = (l + r) / 2;

		cout << "M " << m << endl;
		cin >> s;
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

		cout << "E " << m << endl;
		cin >> s;
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
