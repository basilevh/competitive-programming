// BVH
// Exercise in Competitive Programmer's Handbook by Antti Laaksonen

#include "stdafx.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <fstream>
#include <iostream>
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
vector<int> seq;

// O(N^2)

void solveN2()
{
	vector<int> lens(N);
	vector<int> prev_idcs(N, -1);

	FOR(i, 0, N - 1)
	{
		lens[i] = 1;
		FOR(j, 0, i - 1)
		{
			if (seq[j] < seq[i] && lens[j] + 1 > lens[i])
			{
				lens[i] = lens[j] + 1;
				prev_idcs[i] = j;
			}
		}
	}

	string res = "";
	int idx = max_element(lens.begin(), lens.end()) - lens.begin();
	while (idx != -1)
	{
		res = to_string(seq[idx]) + " " + res;
		idx = prev_idcs[idx];
	}

	cout << res;
}

// O(N log(N))

void solveNlogN()
{
	int max_len = 1;
	vector<int> best_idcs(N);
	vector<int> best_vals(N);
	vector<int> prev_idcs(N, -1);

	best_idcs[1] = 0;
	best_vals[1] = seq[0];

	FOR(i, 1, N - 1)
	{
		int cur_len = lower_bound(best_vals.begin() + 1, best_vals.begin() + 1 + max_len, seq[i]) - best_vals.begin();
		best_idcs[cur_len] = i;
		best_vals[cur_len] = seq[i];
		max_len = max(cur_len, max_len);
		if (cur_len > 1)
		{
			prev_idcs[i] = best_idcs[cur_len - 1];
		}
	}

	string res = "";
	int idx = best_idcs[max_len];
	while (idx != -1)
	{
		res = to_string(seq[idx]) + " " + res;
		idx = prev_idcs[idx];
	}

	cout << res;
}

int main()
{
	int T;
	cin >> T;
	FOR(t, 1, T)
	{
		cin >> N;
		seq.clear(); seq.resize(N);
		FOR(i, 0, N - 1)
		{
			cin >> seq[i];
		}

		cout << "Case #" << t << ": ";

		// solveN2();
		solveNlogN();

		cout << endl;
	}
	return 0;
}
