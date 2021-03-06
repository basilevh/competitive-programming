// by 70!

#include "stdafx.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define LL long long
#define FOR(a, b, c) for(int a = (b); a <= (c); a++)
#define FORD(a, b, c) for(int a = (b); a >= (c); a--)
#define FORI(it, set) for(auto it = (set).begin(); it != (set).end(); it++)

int D;
string P;
int len;
char prog[30] = { 0 }; // {'C', 'S', 'C', 'S'}
int dmg[30] = { 0 }; // {1, 2, 2, 4}
int hacks;

int get_total_dmg()
{
	int res = 0;
	FOR(i, 0, len - 1)
		if (prog[i] == 'S')
			res += dmg[i];

	/*FOR(i, 0, len - 1)
		cout << prog[i];
	cout << endl;
	cout << "total dmg: " << res << endl;*/

	return res;
}

void fill_dmg()
{
	dmg[0] = 1;
	FOR(i, 1, len - 1)
		dmg[i] = dmg[i - 1] * (prog[i - 1] == 'C' ? 2 : 1);
}

void solve()
{
	len = P.length();

	FOR(i, 0, len - 1)
		prog[i] = P[i];

	fill_dmg();

	hacks = 0;

	while (true)
	{
		// Check condition
		int tot = get_total_dmg();
		if (tot <= D)
			break;

		// Check greedy first
		/*FOR(i, 1, len - 1)
		{
			if (prog[i - 1] == 'C' && prog[i] == 'S' && tot - dmg[i] / 2 <= D)
			{
				hacks++;
				return;
			}
		}*/

		bool cont = false;

		// Swap biggest if possible
		FORD(i, len - 1, 1)
		{
			if (prog[i - 1] == 'C' && prog[i] == 'S')
			{
				prog[i - 1] = 'S';
				prog[i] = 'C';
				fill_dmg();

				hacks++;
				cont = true;
				break;
			}
		}

		if (!cont)
		{
			// Impossible
			hacks = -1;
			return;
		}
	}
}

int main()
{
	int T;
	cin >> T;
	FOR(t, 1, T)
	{
		cin >> D;
		cin >> P;

		solve();

		cout << "Case #" << t << ": ";
		if (hacks >= 0)
			cout << hacks;
		else
			cout << "IMPOSSIBLE";
		cout << endl;
	}
	return 0;
}
