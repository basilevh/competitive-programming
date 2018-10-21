// by 70!
// naive solution

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
#define FOR(a, b, c) for(LL a = (b); a <= (c); a++)
#define FORD(a, b, c) for(LL a = (b); a >= (c); a--)
#define FORI(it, set) for(auto it = (set).begin(); it != (set).end(); it++)

LL N;
LL A[7000];

void solve()
{
	cin >> N;
	FOR(i, 0, N - 1)
		cin >> A[i];

	LL cnt = 0;
	FOR(x, 0, N - 1) FOR(y, x + 1, N - 1) FOR(z, y + 1, N - 1)
	{
		if (A[x] == A[y] * A[z] || A[z] == A[x] * A[y] || A[y] == A[z] * A[x])
		{
			cnt++;
		}
	}
	cout << cnt;
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
