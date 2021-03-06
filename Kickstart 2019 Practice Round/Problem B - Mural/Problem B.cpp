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


int N;
int beauties[5000001];


void solve()
{
	cin >> N;
	int i = 0;
	while (i < N)
	{
		char c = getchar();
		if ('0' <= c && c <= '9')
		{
			beauties[i] = c - '0';
			i++;
		}
	}

	// check sliding window of size floor((N+1)/2) => these sections will be painted, all others destroyed
	// solution = max along all window offsets
	LL paint_count = (N + 1) / 2;
	LL cur = 0;
	LL sol = 0;
	FOR(i, 0, paint_count - 1)
	{
		cur += beauties[i];
	}
	sol = cur;
	FOR(i, 0, N - paint_count - 1)
	{
		// current window = [i + 1, i + paint_count]
		cur -= beauties[i];
		cur += beauties[i + paint_count];
		if (cur > sol)
		{
			sol = cur;
		}
	}
	cout << sol;
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
	cout << endl;
	return 0;
}
