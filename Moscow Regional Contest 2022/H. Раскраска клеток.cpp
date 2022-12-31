#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int32_t, int32_t>> g;
vector<char> used;

optional<int32_t> get(int32_t x, int32_t y) {
    auto it = lower_bound(g.begin(), g.end(), pair{x, y});
    if (it == g.end() || *it != pair{x, y}) {
        return {};
    }
    return it - g.begin();
}

void dfs(int32_t i) {
    used[i] = 1;
    auto cur = g[i];
    vector<pair<int32_t, int32_t>> go = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (auto& todo : go) {
        auto [x, y] = pair{cur.first + todo.first, cur.second + todo.second};
        auto next = get(x, y);
        if (next && !used[*next]) {
            dfs(*next);
        }
    }
}

int main() {
    int32_t k;
    cin >> k;
    g.resize(k);
    used.resize(k);
    for (auto& [x, y] : g) {
        cin >> x >> y;
    }
    sort(g.begin(), g.end());
    int32_t MOD = 998244353;
    int64_t ans = 1;
    for (int32_t i = 0; i < k; ++i) {
        if (!used[i]) {
            ans <<= 1;
            ans %= MOD;
            dfs(i);
        }
    }
    cout << ans;
    return 0;
}
