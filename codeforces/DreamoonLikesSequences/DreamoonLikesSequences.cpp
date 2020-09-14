// Source : [B. Dreamoon Likes Sequences](https://codeforces.com/contest/1329/problem/B)
// Author : shenguo
// Date   : 2020-09-14

#include <bits/stdc++.h>
using namespace std;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int d, m;
		scanf("%d %d", &d, &m);
		int now = 0;
		long long ans = 1;
		while (true) {
			int begin = (1 << now);
			int num = (1 << now);
			int ed = begin + num - 1;
			if (ed > d) {
				ed = d;
			}
			ans = ans * (ed - begin + 1 + 1) % m;
			now++;
			if (ed == d) {
				break;
			}
		}
		ans = ((ans - 1) % m + m) % m;
		printf("%lld\n", ans);
	}
	return 0;
}