// Source : [D. Walk on Matrix](https://codeforces.com/contest/1332/problem/D)
// Author : shenguo
// Date   : 2020-09-14

#include <bits/stdc++.h>
using namespace std;
int main() {
	int k;
	scanf("%d", &k);
	cout << 2 << ' ' << 3 << endl;
	int mx = 0;
	for (int i = 0; i < 20; i++) {
		if ((1 << i) & k) {
			mx = i;
		}
	}
	mx += 1;
	int val = 1 << mx;
	printf("%d %d %d\n", val + k, val, 0);
	printf("%d %d %d\n", k, val + k, k);
}