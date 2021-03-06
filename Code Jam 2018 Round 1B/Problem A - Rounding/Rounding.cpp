// by 70!

#include "stdafx.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

using namespace std;

#define LL long long
#define FOR(a, b, c) for(int a = (b); a <= (c); a++)
#define FORD(a, b, c) for(int a = (b); a >= (c); a--)
#define FORI(it, set) for(auto it = (set).begin(); it != (set).end(); it++)

int N; // people
int L; // languages
int C[100000];
int chosen;

class MyCmp
{
public:
	bool operator() (double a, double b)
	{
		// returns whether b is better than a

		// (x + add) % 1.0 must be minimal and >= 0.5
		// if not found, then (x + add) % 1.0 must be maximal and < 0.5 (to encourage build-up)

		double add = 100.0 / N;

		double x = fmod(a + 0.5, 1.0);
		double y = fmod(b + 0.5, 1.0);
		return x < y;


		/*double c = fmod(a + add, 1.0);
		double d = fmod(b + add, 1.0);

		bool a_jump = (a < 0.5 && c >= 0.5);
		bool b_jump = (b < 0.5 && d >= 0.5);

		if (a_jump && !b_jump)
			return false;

		if (!a_jump && b_jump)
			return true;

		// sum closest to 0.5 = best
		if (a_jump && b_jump)
			return a < b;
		else
		{
			if (a < 0.5 && b >= 0.5)
				return false;
			if (a >= 0.5 && b < 0.5)
				return true;
			if (a < 0.5)
				return a > b;
			else
				return a < b;
		}*/
		
		/*if (c >= 0.5 && d < 0.5)
			// c = 0.7, d = 0.3
			return false;

		if (c < 0.5 && d >= 0.5)
			// c = 0.3, d = 0.7
			return true;

		if (c < 0.5)
			// c = 0.3, d = 0.4 = bad
			// c = 0.4, d = 0.3 = good
			return c < d;
		else
			// c = 0.7, d = 0.6 = bad
			// c = 0.6, d = 0.7 = good
			return c > d;*/
	}
};

priority_queue<double, vector<double>, MyCmp> pct;

int remain;

int max_pct;

void solve()
{
	remain = N - chosen;

	/*FOR(i, 0, L - 1)
	{
		cout << pct[i] << ' ';
	}
	cout << endl;*/

	while (remain > 0)
	{
		pct.push(0.0);

		// find next best element

		/*priority_queue<double, vector<double>, MyCmp> a = pct;
		cout << "contents: ";
		while (!a.empty())
		{
			cout << a.top() << ' ';
			a.pop();
		}
		cout << endl;*/

		double x = pct.top();
		pct.pop();

		x += 100.0 / N;

		pct.push(x);

		remain--;

		/*FOR(i, 0, L - 1)
		{
			cout << pct[i] << ' ';
		}
		cout << endl;*/
	}

	max_pct = 0;
	while (!pct.empty())
	{
		max_pct += (int)(pct.top() + 0.5);
		pct.pop();
	}
}

int main()
{
	int T;
	cin >> T;
	FOR(t, 1, T)
	{
		cin >> N >> L;
		chosen = 0;
		FOR(i, 0, L - 1)
		{
			cin >> C[i];
			chosen += C[i];
			pct.push(100.0 * C[i] / N);
		}

		solve();

		cout << "Case #" << t << ": ";
		cout << max_pct;
		cout << endl;
	}
	return 0;
}
