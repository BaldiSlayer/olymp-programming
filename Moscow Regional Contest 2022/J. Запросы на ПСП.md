# Разбор задачи J. Запросы на ПСП с Moscow Regional Contest Qualification 2022 год

## Условие

Дана правильная скобочная подпоследовательность P = p<sub>1</sub>p<sub>2</sub>...p<sub>n</sub> длины `n` и `q` запросов. Каждый запрос содержит по два целых числа a<sub>i</sub> и b<sub>i</sub> от 1 до n. Для каждого запроса требуется ответить, будет ли последовательность правильной после обмена скобок p<sub>a<sub>i</sub></sub> и p<sub>b<sub>i</sub></sub>. Изменения **не накапливаются** - то есть каждый запрос применяется **к исходной** последовательности.

## Формат ввода

Первая строка входных данных содержит два целых числа `n` и `q` (2 ≤ n ≤ 10<sup>5</sup>, 1 ≤ q ≤ 10<sup>5</sup>). Вторая строка содержит `n` символов p<sub>1</sub>p<sub>2</sub>...p<sub>n</sub>. Каждый символ является или открывающей скобкой (‘(’), или закрывающей скобкой (‘)’). Гарантируется, что скобки образуют правильную скобочную последовательность. `i`-я из последующих `q` строк содержит два целых числа a<sub>i</sub> и b<sub>i</sub> (1 ≤ a<sub>i</sub>, b<sub>i</sub> ≤ n, a<sub>i</sub> ≠ b<sub>i</sub>)

## Формат вывода

Для каждого запроса выведите `Yes`, если последовательность остаётся правильной, и `No` в противном случае.

# Разбор

Давайте представим `(` как 1, а `)` как -1. Заметим, что так как исходная строка `S` по условию ПСП, то сумма после такой замены будет равна 0. Давайте для подсчета таких сумм на префиксах заведем массив balance длины n (такой же длины, как и данная нам строка) и для каждого индекса `i` будем хранить в `balance[i]` сумму на префиксе `[0;i]`. Назовем такую сумму баланс.

```cpp
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
```

Если в какой-то момент баланс меньше 0, то это значит, что строка не является ПСП (потому что значит тогда есть закрывающая скобка без пары).

Значит нам нужно отвечать на запросы о нахождении отрицательных чисел на отрезке, при перестановки двух скобок.

Теперь рассмотрим, как мы будем отвечать на запрос. Для удобства сделаем так, чтобы `a` было меньше `b`
```cpp
if (a > b) {
    swap(a, b);
}
```

Если мы меняем одинаковые скобки, то очевидно, что ничего не поменяется (строка останется такой же).

Пусть `s[a] == ')'`, а `s[b] == '('`. Тогда на `[a; b)` значение `balanse[i]` увеличится на 2 (так как мы раньше при подсчете `balanse[a]` вычитали единицу, а теперь прибавляем 1). Значения `balance[i]` начиная с `i = b` не изменятся. А так как мы лишь увеличили некоторые ячейки на 2, то отрицательные числа мы не получим.

Рассмотрим последний вариант `s[a] == '('`, `s[b] == ')'`. Тогда мы получим, что на `[a; b)` значение `balanse[i]` будет уменьшено на 2 (при подсчете `balanse[i]` `+ 1` заменяется на `- 1`). Значит отрицательные числа мы получить можем, когда хотя бы одно из значений `balanse[i]` на `[a; b)` будет меньше 2. Докажем, что в `balanse[b]` мы не можем получить отрицательное число. Пусть `k = balanse[b-1]` до перестановки скобок. Рассмотрим, что будет после перестановки скобок. При перестановке скобок `k` уменьшится на 2, следовательно теперь `balanse[b-1] = k - 2`. Значит `balanse[b] = balanse[b] + 1 = k - 2 + 1 = k - 1`. Отрицательным оно может быть только если `k = 0`, но `k` не может быть равно 0, так как иначе исходная строка не была бы ПСП (потому что это значило бы, что исходная строка - не ПСП, так как есть еще закрывающася скобка под номером `b`).

Значит нам надо решить задачу, содержится ли на полуинтервале `[a; b)` хотя бы одно число меньше 2. Такую задачу мы можем решить например с помощью дерева отрезков или Sparse Table. Приведу код: 

Дерево отрезков (построение сверху)

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct SegmentTree {
	vector<int> t;

	SegmentTree(vector<int>& a) {
		t.resize(4 * a.size());
		build(a, 0, 0, a.size());
	}

	void build(vector<int>& a, int x, int xl, int xr) {
		if (xl == xr - 1) {
			t[x] = (a[xl] < 2);
			return;
		}

		int xm = xr - (xr - xl) / 2;
		build(a, 2 * x + 1, xl, xm);
		build(a, 2 * x + 2, xm, xr);
		t[x] = (t[2 * x + 1] || t[2 * x + 2]);
	}

	int get(int x, int xl, int xr, int l, int r) {
		// [l r] [xl xr] [l r]
		if (r <= xl || xr <= l) {
			return 0;
		}

		// [l [xl xr] r]
		if (l <= xl && xr <= r) {
			return t[x];
		}

		int xm = xr - (xr - xl) / 2;
		return (get(2 * x + 1, xl, xm, l, r) || get(2 * x + 2, xm, xr, l, r));
	}
};

int main() {
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

	int a, b;
	SegmentTree st(balanse);

	for (; q--;) {
		cin >> a >> b;

		if (a > b) {
			swap(a, b);
		}

		--a; --b;
		if (s[a] == '(' && s[b] == ')') {
			if (!st.get(0, 0, n, a, b)) {
				cout << "Yes\n";
			}
			else {
				cout << "No\n";
			}
		}
		else {
			cout << "Yes\n";
		}
	}

	return 0;
}

```

Sparse Table

```cpp
#include <iostream>

using namespace std;

const int32_t maxn = 1e5+2;
const int32_t logn = 17;

int a[maxn];
bool mn[logn][maxn];

bool hasNumbersLessThan2(int l, int r) {
    int t = __lg(r - l);
    return mn[t][l] || mn[t][r - (1 << t)];
}

int main() {
    int32_t n, q;
    cin >> n >> q;
    string p;
    cin >> p;

    a[0] = 0;
    for (int i = 1; i <= n; ++i) {
        a[i] = a[i-1];
        if (p[i-1] == '(') {
            a[i]++;
        } else {
            a[i]--;
        }
    }

    for (int i = 0; i < n; ++i) {
        mn[0][i] = (a[i] < 2);
    }

    for (int l = 0; l < logn - 1; l++)
        for (int i = 0; i + (2 << l) <= n+1; i++)
            mn[l+1][i] = mn[l][i] || mn[l][i + (1 << l)];


    for (int32_t i = 0; i < q; ++i) {
        int32_t a, b;
        cin >> a >> b;
        if (a > b) {
            swap(a, b);
        }
        if (p[a-1] == '(' && p[b-1] == ')') {
            if (!hasNumbersLessThan2(a, b)) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        } else {
            cout << "Yes\n";
        }
    }
    return 0;
}


```


Решение 2 (чуть усовершенствованное)

Заметим, что мы можем определять есть ли хоть одно число меньше 2 на отрезке, составив массив, хранящий количество таких чисел на префиксе `[0; i]` (массив префиксных сумм). Если баланс меньше 2, мы добавляем единицу, иначе 0. Мы должны лишь проверить, больше ли сумма на [a; b), чем 0, или нет. Следовательно мы можем воспользоваться
префиксными суммами, или деревом Фенвика.

Дерево Фенвика

```cpp
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
```

Префиксные суммы

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int n, q;
	cin >> n >> q;

	string s;
	cin >> s;

	int balanse = 0;
	vector<int> pref(n + 1);
	pref[0] = 0;

	for (int i = 1; i <= n; i++) {
		if (s[i - 1] == '(') {
			++balanse;
		}
		else {
			--balanse;
		}

		pref[i] = pref[i - 1] + (balanse < 2);
	}

	int a, b;
	for (; q--;) {
		cin >> a >> b;
		if (a > b) {
			swap(a, b);
		}

		--a; --b;
		if (s[a] == '(' && s[b] == ')') {
			if (pref[b] - pref[a] > 0) {
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
```

На этом всё. Разбор подготовила команда Star NOT Geo (Александр Старовойтов, Алексей Лисов, Егор Домаскин, Анна Карапетян)

Ссылка на задачу [тык](https://official.contest.yandex.com/mrc2022/contest/41407/problems/J/)
