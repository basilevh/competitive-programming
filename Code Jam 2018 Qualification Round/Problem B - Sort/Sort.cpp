// by 70!

#include "stdafx.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define LL long long
#define FOR(a, b, c) for(int a = (b); a <= (c); a++)
#define FORD(a, b, c) for(int a = (b); a >= (c); a--)
#define FORI(it, set) for(auto it = (set).begin(); it != (set).end(); it++)

int N;
int V[100000];
int error;

void solve()
{
	// cout << endl;

	error = -1;

	priority_queue<int, vector<int>, greater<int> > a;
	priority_queue<int, vector<int>, greater<int> > b;

	for (int i = 0; i < N; i += 2)
		a.push(V[i]);
	for (int i = 1; i < N; i += 2)
		b.push(V[i]);

	/*while (!a.empty())
	{
		cout << a.top() << ' ';
		cout << endl;
		a.pop();
	}
	while (!b.empty())
	{
		cout << b.top() << ' ';
		cout << endl;
		b.pop();
	}*/

	int x = -1;
	int y = -1;

	while (true)
	{
		if (a.empty())
		{
			// OK
			error = -1;
			return;
		}

		x = a.top();
		a.pop();
		// cout << "popped from a: " << x << endl;

		if (x < y)
			// error here
			return;

		error++;

		if (b.empty())
		{
			// OK
			error = -1;
			return;
		}

		y = b.top();
		b.pop();
		// cout << "popped from b: " << y << endl;

		if (y < x)
			// error here
			return;

		error++;
	}
}

int main()
{
	int T;
	cin >> T;
	FOR(t, 1, T)
	{
		cin >> N;
		FOR(i, 0, N - 1)
			cin >> V[i];

		solve();

		cout << "Case #" << t << ": ";
		if (error >= 0)
			cout << error;
		else
			cout << "OK";
		cout << endl;
	}
	return 0;
}
