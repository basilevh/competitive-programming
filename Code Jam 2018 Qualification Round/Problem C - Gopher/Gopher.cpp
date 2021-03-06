// by 70!

#include "stdafx.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define LL long long
#define FOR(a, b, c) for(int a = (b); a <= (c); a++)
#define FORD(a, b, c) for(int a = (b); a >= (c); a--)
#define FORI(it, set) for(auto it = (set).begin(); it != (set).end(); it++)

int A;
int cur;
bool orchard[1002][1002] = { 0 };

void solve()
{
	int x1 = 100;
	int y1 = 100;
	int x2, y2, xran, yran;
	int gaps;
	int tries = 0;
	int rands = 0;

	if (A <= 20)
	{
		x2 = x1 + 4;
		y2 = y1 + 3;
		/*x2 = x1 + 6;
		y2 = y1 + 2;*/
	}
	else
	{
		// 15 * 14 = 210 >= 200
		/*x2 = x1 + 14;
		y2 = y1 + 13;*/
		x2 = x1 + 19;
		y2 = y1 + 9;
	}
	xran = x2 - x1 - 1;
	yran = y2 - y1 - 1;
	gaps = (x2 - x1 + 1) * (y2 - y1 + 1);
	cerr << "Aiming for: " << gaps << endl;

	int i, j, k, l;
	i = j = 101;
	cout << i << ' ' << j << endl << flush;

	while (true)
	{
		cin >> k >> l;
		if (k <= 0 && l <= 0)
			break;

		if (!orchard[k][l])
		{
			orchard[k][l] = true;
			gaps--;
		}

		/*if (A / gaps < 12) // this constant is an educated guess
		{
			// There are enough gaps for a random position to be probably good
			bool test = false;
			while (!test)
			{
				test = false;
				i = x1 + 1 + rand() % xran;
				j = y1 + 1 + rand() % yran;
				rands += 2;
				FOR(x, i - 1, i + 1) FOR(y, j - 1, j + 1)
					if (!orchard[x][y])
						// At least one gap present
						test = true;
			}
		}
		else
		{
			// Now look for the few gaps that are left
			i = j = 0;
			FOR(x, x1, x2) FOR(y, y1, y2)
				if (i == 0 && !orchard[x][y])
				{
					i = x;
					j = y;
				}
			i = min(max(i, x1 + 1), x2 - 1);
			j = min(max(j, y1 + 1), y2 - 1);
		}*/

		int best = 0; // gaps
		FOR(x, x1 + 1, x2 - 1) FOR(y, y1 + 1, y2 - 1)
		{
			int cur = 0; // gaps
			FOR(p, x - 1, x + 1) FOR(q, y - 1, y + 1)
			{
				if (!orchard[p][q])
					cur++;
			}
			if (cur > best)
			{
				i = x;
				j = y;
				best = cur; // doh, forgot this
			}
		}

		// cerr << i << ' ' << j << " -> gaps: " << gaps << endl;

		cout << i << ' ' << j << endl << flush;
		tries++;

		if (tries >= 1000)
			exit(1);
	}

	cerr << "Tries: " << tries << endl;
	cerr << "Rands: " << rands << endl;
}

void reset()
{
	FOR(i, 0, 1001) FOR(j, 0, 1001)
		orchard[i][j] = false;
}

int main()
{
	int T;
	cin >> T;
	FOR(t, 1, T)
	{
		cin >> A;

		reset();

		cerr << "Test case: " << t << endl;
		cerr << "A: " << A << endl;

		solve();
	}
	return 0;
}
