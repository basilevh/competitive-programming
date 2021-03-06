// by 70!

#include "stdafx.h"
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

void solve()
{
	int N, K;
	cin >> N >> K;
	priority_queue<int, vector<int>, greater<int>> Ai;

	FOR(i, 0, N - 1)
	{
		int exp;
		cin >> exp;
		Ai.push(exp);
	}

	int eat = 0;
	int day = 1;
	while (!Ai.empty())
	{
		int cur = 0;
		while (cur < K && !Ai.empty())
		{
			int exp = Ai.top();
			Ai.pop();
			if (day <= exp)
			{
				// not expired, so eat
				cur++;
			}
			// otherwise: throw away, don't count as eaten
		}
		eat += cur;

		day++;
	}

	cout << eat;
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
