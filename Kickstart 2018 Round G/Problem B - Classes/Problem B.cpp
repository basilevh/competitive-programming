// by 70!
// TODO: off by one error somewhere?

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
#define FOR(a, b, c) for(LL a = (b); a <= (c); a++)
#define FORD(a, b, c) for(LL a = (b); a >= (c); a--)
#define FORI(it, set) for(auto it = (set).begin(); it != (set).end(); it++)

typedef struct {
	LL left, right;
} my_range;

class LeftCmp
{
public:
	bool operator() (my_range x, my_range y)
	{
		// we want top = smallest so use >
		return (x.left > y.left);
	}
};

class RightCmp
{
public:
	bool operator() (my_range x, my_range y)
	{
		// we want top = smallest so use >
		return (x.right > y.right);
	}
};

typedef struct {
	LL position, q;
} pos_q;

class RankCmp
{
public:
	bool operator() (pos_q x, pos_q y)
	{
		// we want top = smallest a so use >
		return (x.position > y.position);
	}
};

LL L[400001];
LL R[400001];
LL K[100001];
LL N, Q;

LL X[400001];
LL Y[400001];
LL Z[400001];
LL A[3];
LL B[3];
LL C[3];
LL M[3];
LL S;

map<LL, LL> score_counts;

void solve()
{

	priority_queue<my_range, vector<my_range>, LeftCmp> leftq;
	priority_queue<my_range, vector<my_range>, RightCmp> rightq;
	FOR(i, 0, N - 1)
	{
		my_range sr;
		sr.left = L[i];
		sr.right = R[i];
		leftq.push(sr);
	}

	// construct score -> count map, only noting changes (= no subsequent repetitions)
	score_counts[0] = 0;
	LL cur_count = 0;
	LL max_score = 0;
	while (!leftq.empty() || !rightq.empty())
	{
		bool add = false;
		if (rightq.empty())
			add = true;
		else if (!leftq.empty() && leftq.top().left <= rightq.top().right)
			add = true;

		if (add)
		{
			// add new
			my_range sr1 = leftq.top();
			leftq.pop();
			rightq.push(sr1);
			cur_count++;
			score_counts[sr1.left] = cur_count;
		}
		else
		{
			my_range sr2 = rightq.top();
			if (!leftq.empty() && sr2.right == leftq.top().left - 1)
			{
				// coincides
				my_range sr1 = leftq.top();
				rightq.pop();
				leftq.pop();
				rightq.push(sr1);
			}
			else
			{
				// remove old
				rightq.pop();
				cur_count--;
				score_counts[sr2.right + 1] = cur_count;
				max_score = max(sr2.right + 1, max_score);
			}
		}
	}

	// sort ranks from bad to good (-> positions)
	priority_queue<pos_q, vector<pos_q>, RankCmp> rankqs;
	FOR(q, 0, Q - 1)
	{
		if (1 <= K[q] && K[q] <= S)
		{
			// 0 = worst
			// S-1 = best
			pos_q pq;
			pq.position = S - K[q];
			pq.q = q + 1;
			rankqs.push(pq);
		}
	}

	// iterate and get scores
	LL sum = 0;
	LL lastPos = -1; // [0, S]
	LL score = 0; // [1, inf)
	LL count = -1; // [0, N]
	LL rem = -1; // [1, S]; remaining climbs before score change; happens on same iteration if 0

	while (!rankqs.empty())
	{
		pos_q pq = rankqs.top();
		rankqs.pop();
		LL pos = pq.position;
		LL q = pq.q;
		LL climb = pos - lastPos;

		while (climb != 0)
		{
			if (climb < rem)
			{
				// sufficient remaining; no score change
				rem -= climb;
				climb = 0;
			}
			else
			{
				// score will change
				if (rem == -1)
				{
					// first
					climb--;
					score++;
				}
				else if (rem != count)
				{
					// unaligned; make aligned
					climb -= rem;
					score++;
				}
				else
				{
					// aligned; score will change
					LL next_score = score_counts.lower_bound(score + 1)->first;
					LL diff = next_score - score;
					if (count != 0)
						diff = min(diff, climb / count);

					// jump as far as practical
					if (diff > 0)
					{
						// diff = 1; // DEBUG
						climb -= diff * count;
						score += diff;
					}
					else
					{
						// climb < count
					}
				}

				// update count & rem
				if (score_counts.find(score) != score_counts.end())
					count = score_counts[score];
				rem = count;
			}
		}

		sum += score * q;
		lastPos = pos;
	}

	cout << sum;
}

int main()
{
	int T;
	cin >> T;
	FOR(t, 1, T)
	{
		cout << "Case #" << t << ": ";

		// reset
		score_counts.clear();

		// input
		cin >> N >> Q;
		cin >> X[0] >> X[1] >> A[0] >> B[0] >> C[0] >> M[0];
		cin >> Y[0] >> Y[1] >> A[1] >> B[1] >> C[1] >> M[1];
		cin >> Z[0] >> Z[1] >> A[2] >> B[2] >> C[2] >> M[2];
		FOR(i, 2, N - 1)
		{
			X[i] = (A[0] * X[i - 1] + B[0] * X[i - 2] + C[0]) % M[0];
			Y[i] = (A[1] * Y[i - 1] + B[1] * Y[i - 2] + C[1]) % M[1];
		}
		FOR(i, 2, Q - 1)
		{
			Z[i] = (A[2] * Z[i - 1] + B[2] * Z[i - 2] + C[2]) % M[2];
		}
		S = 0;
		FOR(i, 0, N - 1)
		{
			L[i] = min(X[i], Y[i]) + 1;
			R[i] = max(X[i], Y[i]) + 1;
			S += R[i] - L[i] + 1;
		}
		FOR(i, 0, Q - 1)
		{
			K[i] = Z[i] + 1;
		}

		// solve
		solve();

		cout << endl;
	}
	return 0;
}
