#include <iostream>
#include <algorithm>
#include <vector>

typedef long double ll;

using namespace std;

int ok(ll a, ll b, ll c1, ll c2) {
	vector<ll> s = {a, b, c1 + c2};

	sort(s.begin(), s.end());

	if ((s[0] + s[1] > s[2]) && (a / b == c1 / c2)) {
		return 1;
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	vector<ll> a(4);

	for (auto& i : a) {
		cin >> i;
	}

	sort(a.begin(), a.end());

	do {
		if (ok(a[0], a[1], a[2], a[3])) {
			cout << 1;
			return 0;
		}

	} while (std::next_permutation(a.begin(), a.end()));

	cout << 0;

	return 0;
}
