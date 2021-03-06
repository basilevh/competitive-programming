// by 70!

#include "stdafx.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define LL long long
#define FOR(a, b, c) for(int a = (b); a <= (c); a++)
#define FORD(a, b, c) for(int a = (b); a >= (c); a--)
#define FORI(it, set) for(auto it = (set).begin(); it != (set).end(); it++)

#define ROOT2 1.4142135623730950488
#define ROOT3 1.7320508075688772935
#define PI    3.1415926535897932384

double A;
double fx1, fy1, fz1;
double fx2, fy2, fz2;
double fx3, fy3, fz3;

void rotate_x(double angle, double x, double y, double z, double *nx, double *ny, double *nz)
{
	double tx = x;
	double ty = cos(angle) * y - sin(angle) * z;
	double tz = sin(angle) * y + cos(angle) * z;
	*nx = tx; *ny = ty; *nz = tz;
}

void rotate_z(double angle, double x, double y, double z, double *nx, double *ny, double *nz)
{
	double tx = cos(angle) * x - sin(angle) * y;
	double ty = sin(angle) * x + cos(angle) * y;
	double tz = z;
	*nx = tx; *ny = ty; *nz = tz;
}

void solve()
{
	double alpha = 0.0; // around a horizontal axis
	double beta = 0.0; // around the other horizontal axis
	double shadow = 1.0;
	double step = PI / 8.0;

	if (A <= ROOT2)
	{
		while (abs(shadow - A) > 1e-9)
		{
			if (shadow < A)
				alpha += step;
			else
				alpha -= step;
			step /= 2.0;

			shadow = cos(alpha) + sin(alpha);
		}
	}
	else
	{
		alpha = PI / 4.0;
		shadow = ROOT2;
		step = atan(1.0 / ROOT2) / 2.0; // halfway to extremum of sqrt(3)
		while (abs(shadow - A) > 1e-9)
		{
			if (shadow < A)
				beta += step;
			else
				beta -= step;
			step /= 2.0;

			shadow = sqrt(2.0) * cos(beta) + sin(beta);
		}
	}

	/*cout << "A: " << A << endl;
	cout << "alpha: " << alpha << endl;
	cout << "beta: " << beta << endl;
	cout << "shadow: " << shadow << endl;*/

	fx1 = 0.5; fy1 = 0.0; fz1 = 0.0;
	fx2 = 0.0; fy2 = 0.5; fz2 = 0.0;
	fx3 = 0.0; fy3 = 0.0; fz3 = 0.5;

	rotate_x(alpha, fx1, fy1, fz1, &fx1, &fy1, &fz1);
	rotate_x(alpha, fx2, fy2, fz2, &fx2, &fy2, &fz2);
	rotate_x(alpha, fx3, fy3, fz3, &fx3, &fy3, &fz3);
	rotate_z(beta, fx1, fy1, fz1, &fx1, &fy1, &fz1);
	rotate_z(beta, fx2, fy2, fz2, &fx2, &fy2, &fz2);
	rotate_z(beta, fx3, fy3, fz3, &fx3, &fy3, &fz3);
}

int main()
{
	cout.precision(15);
	int T;
	cin >> T;
	FOR(t, 1, T)
	{
		cin >> A;
		solve();
		cout << "Case #" << t << ':' << endl;
		cout << fx1 << ' ' << fy1 << ' ' << fz1 << endl;
		cout << fx2 << ' ' << fy2 << ' ' << fz2 << endl;
		cout << fx3 << ' ' << fy3 << ' ' << fz3 << endl;
	}
	return 0;
}
