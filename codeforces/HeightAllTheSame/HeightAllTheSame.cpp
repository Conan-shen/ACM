// Source : [E. Height All the Same](https://codeforces.com/contest/1332/problem/E)
// Author : shenguo
// Date   : 2020-09-14
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
long long pw(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b % 2) {
			res = res * a % mod;
		}
		a = a * a % mod;
		b /= 2;
	}
	return res;
}
int main() {
	long long n, m, L, R;
	scanf("%lld %lld %lld %lld", &n, &m, &L, &R);
	if (1LL * n * m % 2) {
		printf("%lld\n", pw(R - L + 1, n * m));
		return 0;
	} else {
		int x = (R - L + 1) / 2;
		int y = (R - L + 1) - x;
		if (x == y) {
			printf("%lld\n", pw(x + y, n * m) * pw(2, mod - 2) % mod);
		} else {
			// puts("dddd");
			printf("%lld\n", (pw(x + y, n * m) + 1) % mod * pw(2, mod - 2) % mod);
		}
	}
	return 0;
}