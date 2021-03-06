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
#define FOR(a, b, c) for(LL a = (b); a <= (c); a++)
#define FORD(a, b, c) for(LL a = (b); a >= (c); a--)
#define FORI(it, set) for(auto it = (set).begin(); it != (set).end(); it++)

LL N, M, P;
string pref[101];
string forb[101];

LL hamm_dist(string a, string b)
{
	LL res = 0;
	FOR(p, 0, P - 1)
		if (a[p] != b[p])
			res++;
	return res;
}

LL get_comps(string a)
{
	LL res = 0;
	FOR(i, 0, N - 1)
		res += hamm_dist(a, pref[i]);
	return res;
}

void get_cands(vector<string>& res, char test[], LL rev, LL start)
{
	if (rev <= 0)
	{
		string cand = string(test);
		FOR(i, 0, M - 1)
		{
			if (hamm_dist(cand, forb[i]) == 0)
			{
				// forbidden, don't add
				return;
			}
		}
		res.push_back(cand);
		return;
	}

	FOR(p, start, P - 1)
	{
		test[p] = (test[p] == '1' ? '0' : '1');
		get_cands(res, test, rev - 1, p + 1);
		test[p] = (test[p] == '1' ? '0' : '1');
	}
}

void solve()
{
	cin >> N >> M >> P;
	FOR(i, 0, N - 1)
	{
		cin >> pref[i];
	}
	FOR(i, 0, M - 1)
	{
		cin >> forb[i];
	}

	char closest[101] = { 0 };
	LL best = -1;
	string btype;

	LL sol_exists_cnt = 0;

	FOR(rev, 0, P)
	{
		FOR(p, 0, P - 1)
		{
			LL s0 = 0;
			LL s1 = 0;
			FOR(i, 0, N - 1)
			{
				if (pref[i][p] == '1')
					s1++;
				else
					s0++;
			}

			closest[p] = (s1 > s0 ? '1' : '0');
		}

		// test with current amount of reversions
		vector<string> cands;
		get_cands(cands, closest, rev, 0);
		FORI(it, cands)
		{
			LL cur = get_comps(*it);
			if (best == -1 || cur < best)
			{
				best = cur;
				btype = *it;
				sol_exists_cnt = 0; // reset exit counter
			}
		}

		if (best != -1 && P >= 25)
			break;

		if (best != -1)
		{
			sol_exists_cnt++;
			if (sol_exists_cnt >= 7)
				// this is probably optimal
				break;
		}

		if (rev == P)
			break;
	}

	cout << best;
	/*cout << " ";
	cout << btype;*/
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
