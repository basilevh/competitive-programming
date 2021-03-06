// by 70!

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

typedef struct {
	int D, A, B;
	int M, N;
} sign;

int S;
sign signs[100000]; // originally 100 -> runtime error x(

int y, z;

bool is_valid(int begin, int end)
{
	// 10^6
	FOR(i, begin, end - 1)
	{
		int m = signs[i].M;
		FOR(j, begin, end - 1)
		{
			int n = signs[j].N;
			bool ok = true;
			FOR(k, begin, end - 1)
			{
				if (signs[k].M != m && signs[k].N != n)
				{
					ok = false;
					break;
				}
			}
			if (ok)
				return true;
		}
	}
	return false;
}

void solve()
{
	priority_queue<int> seq_lens;

	int begin = 0;
	int end = 1;
	bool back = true;

	// between 10^2 and 10^4
	while (end <= S)
	{
		if (!back)
		{
			if (is_valid(begin, end))
			{
				seq_lens.push(end - begin);
				end++;
			}
			else
			{
				begin++;
				back = true;
			}
		}
		else
		{
			if (is_valid(begin, end))
			{
				seq_lens.push(end - begin);
				end++;
				back = false;
			}
			else
			{
				end--;
			}
		}
	}

	y = seq_lens.top();
	seq_lens.pop();
	z = 1;
	while (!seq_lens.empty() && seq_lens.top() == y)
	{
		seq_lens.pop();
		z++;
	}
}

int main()
{
	int T;
	cin >> T;
	FOR(t, 1, T)
	{
		cin >> S;
		FOR(i, 0, S - 1)
		{
			cin >> signs[i].D >> signs[i].A >> signs[i].B;
			signs[i].M = signs[i].D + signs[i].A;
			signs[i].N = signs[i].D - signs[i].B;
		}

		solve();

		cout << "Case #" << t << ": ";
		cout << y << " " << z;
		cout << endl;
	}
	return 0;
}
