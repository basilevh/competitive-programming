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

void solve()
{
	LL A, B, N;
	cin >> A >> B >> N;
	cerr << A << " " << B << " " << N << endl;

	// trivial binary search
	while (true)
	{
		LL mid = (A + B + 1) / 2;
		cout << mid << endl << flush;
		string s = "";
		while (s.length() == 0)
		{
			getline(cin, s);
			cerr << s << endl;
		}
		if (s.find("TOO_SMALL") != string::npos)
			A = mid;
		else if (s.find("TOO_BIG") != string::npos)
			B = mid - 1;
		else if (s.find("WRONG") != string::npos)
			exit(1);
		else if (s.find("CORRECT") != string::npos)
			break;
	}
}

int main()
{
	int T;
	cin >> T;
	FOR(t, 1, T)
	{
		// cout << "Case #" << t << ": ";
		solve();
		// cout << endl;
	}
	return 0;
}
