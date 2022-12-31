#pragma GCC optimize("unroll-loops", "O3")

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

ll mod = 998244353;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	ll h, g;
	cin >> h >> g;

	vector<vector<vector<ll>>> dp(h+1, vector<vector<ll>>(g+1, vector<ll>(7+1, 0)));
	// счет 0 0 в первом тайме мы можем получить единственным способом
	dp[0][0][1] = 1;

	// идем по четвертям и овертаймам
	for (int k = 1; k <= 7; ++k) {
		// итерируемся по голам хозяев
		for (int i = 0; i <= h; ++i) {
			// итерируемся по голам гостей
			for (int j = 0; j <= g; ++j) {
				if ((k > 1 && k <= 4) || (k >= 5 && i == j)) {
					dp[i][j][k] = dp[i][j][k-1] % mod;
				}

				if (i == 0 && j == 0) {
					continue;
				}

				// забиваем за хозяев
				for (int l = 1; l <= 3 && i - l >= 0; ++l) {
					dp[i][j][k] = (dp[i][j][k] + dp[i - l][j][k]) % mod;
				}

				// забиваем за гостей 
				for (int l = 1; l <= 3 && j - l >= 0; ++l) {
					dp[i][j][k] = (dp[i][j][k] + dp[i][j - l][k]) % mod;
				}
			}
		}
	}

	// считаем и выводим ответ

	ll ans = 0;

	for (int k = 4; k <= 7; ++k) {
		ans = (ans + dp[h][g][k]) % mod;
	}

	cout << ans;

	return 0;
}
