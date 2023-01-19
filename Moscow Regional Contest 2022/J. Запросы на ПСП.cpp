#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef int ll;

struct FenwickTree {
	vector<ll> t;
	ll n;

	FenwickTree(ll n_) : n(n_) {
		t.resize(n + 1, 0);
	}

	ll sum(ll r) {
		ll res = 0;
		for (ll i = r; i > 0; i -= (i & -i)) {
			res += t[i];
		}
		return res;
	}

	ll sum(ll l, ll r) {
		return sum(r) - sum(l);
	}

	void inc(ll ind, ll val) {
		for (ll i = ind; i <= n; i += (i & -i)) {
			t[i] += val;
		}
	}
};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int n, q;
	cin >> n >> q;

	string s;
	cin >> s;

	vector<int> balanse(n);
	balanse[0] = ((s[0] == '(') ? 1 : -1);
	for (int i = 1; i < n; i++) {
		balanse[i] = balanse[i - 1];
		if (s[i] == '(') {
			++balanse[i];
		}
		else {
			--balanse[i];
		}
	}

	FenwickTree fenwick(n);

	for (int i = 0; i < n; i++) {
		fenwick.inc(i + 1, (balanse[i] < 2));
	}

	int a, b;
	for (; q--;) {
		cin >> a >> b;
		if (a > b) {
			swap(a, b);
		}

		--a; --b;
		if (s[a] == '(' && s[b] == ')') {
			if (fenwick.sum(a, b) > 0) {
				cout << "No\n";
			}
			else {
				cout << "Yes\n";
			}
		}
		else {
			cout << "Yes\n";
		}
	}

	return 0;
}
