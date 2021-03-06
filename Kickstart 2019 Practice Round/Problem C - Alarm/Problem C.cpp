// by 70!

#include "pch.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

#define LL long long
#define FOR(a, b, c) for(int a = (b); a <= (c); a++)
#define FORD(a, b, c) for(int a = (b); a >= (c); a--)
#define FORI(it, set) for(auto it = (set).begin(); it != (set).end(); it++)

#define P 1000000007

// returns (a+b) % P
LL addmod(LL a, LL b)
{
	return ((a % P) + (b % P)) % P;
}

// returns (ab) % P
LL multmod(LL a, LL b) {
	return ((a % P) * (b % P)) % P;
}

// returns a^b % P
LL powmod(LL a, LL b) {
	if (b == 0)
		return 1;
	if (b == 1)
		return a;
	if (a == 0)
		return 0;
	if (a == 1)
		return 1;

	// a^b = (a^(b/2))^2
	LL h = b / 2;
	LL tmp = powmod(a, h);
	LL res = multmod(tmp, tmp);
	if (b % 2)
		res = multmod(res, a);
	return res;
}

// returns (n^1 + n^2 + ... + n^k) % P
LL powsummod(LL n, LL k)
{
	if (k == 1)
		return n;
	else
	{
		LL tmp = powsummod(n, k / 2);
		LL left = tmp;
		LL right = multmod(tmp, powmod(n, k / 2));
		LL res = addmod(left, right);
		if (k % 2)
			res = addmod(res, powmod(n, k));
		return res;
	}
}


LL N, K, C, D, E1, E2, F;
LL x[1000001];
LL y[1000001];
LL A[1000001];


void solve()
{
	cin >> N >> K >> x[1] >> y[1] >> C >> D >> E1 >> E2 >> F;
	A[1] = (x[1] + y[1]) % F;
	FOR(i, 2, N)
	{
		x[i] = (C * x[i - 1] + D * y[i - 1] + E1) % F;
		y[i] = (D * x[i - 1] + C * y[i - 1] + E2) % F;
		A[i] = (x[i] + y[i]) % F;
	}
	LL res = 0;
	LL sum = 0;
	FOR(i, 1, N)
	{
		LL fact1 = addmod(sum, powsummod(i, K));
		LL fact2 = multmod(A[i], N - i + 1);
		LL cur_term = multmod(fact1, fact2);
		res = addmod(res, cur_term);
		sum = fact1;
	}
	cout << res;
}

int main()
{
	int T;
	cin >> T;
	FOR(t, 1, T)
	{
		cout << "Case #" << t << ": ";
		solve();
		cout << endl;
	}
	return 0;
}
