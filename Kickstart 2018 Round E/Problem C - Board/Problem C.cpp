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
#define FOR(a, b, c) for(int a = (b); a <= (c); a++)
#define FORD(a, b, c) for(int a = (b); a >= (c); a--)
#define FORI(it, set) for(auto it = (set).begin(); it != (set).end(); it++)

typedef pair<int, int> pi;


int N;
vector<int> my_cards;
vector<int> enemy_cards;
int my_total_sum;
int enemy_total_sum;

double approach;

typedef struct {
	int a, b, c;
} fdist_even2;

class MyCmp2
{
public:
	bool operator() (fdist_even2 x, fdist_even2 y)
	{
		return abs(x.a - approach) + abs(x.b - approach) > abs(y.a - approach) + abs(y.b - approach);
	}
};

typedef struct {
	int a, b, c;
} fdist_even3;

class MyCmp3
{
public:
	bool operator() (fdist_even3 x, fdist_even3 y)
	{
		return abs(x.a - approach) + abs(x.b - approach) + abs(x.c - approach)
> abs(y.a - approach) + abs(y.b - approach) + abs(y.c - approach);
	}
};


// N elements only
void get_half_sums(set<int>& res, vector<int>& cards, int sum, int used)
{
	if (cards.empty())
	{
		if (used == N)
			res.insert(sum);
		return;
	}

	int cur = cards[0];
	cards.erase(cards.begin());
	// without
	get_half_sums(res, cards, sum, used);
	// with
	if (used < N)
		get_half_sums(res, cards, cur + sum, used + 1);
	cards.insert(cards.begin(), cur);
}

map<pi, int> count_field_dists(vector<int> cards)
{
	map<pi, int> res;
	vector<int> sel; // selector
	FOR(k, 1, 3)
		FOR(i, 0, N - 1)
		sel.push_back(k); // 1,..,1, 2,..,2, 3,..,3

// check all disjunct subsets of sizes N, N, N (= 3 fields)
	do
	{
		// determine this distribution (sums)
		int s1 = 0;
		int s2 = 0;
		FOR(i, 0, 3 * N - 1)
		{
			if (sel[i] == 1)
				s1 += cards[i];
			else if (sel[i] == 2)
				s2 += cards[i];
			// else: field 3, don't care
		}

		pi key = pi(s1, s2);

		if (res.find(key) == res.end())
			res[key] = 1;
		else
			res[key]++;

	} while (next_permutation(sel.begin(), sel.end())); // always unique!

	return res;
}

bool me_wins(int my_f1, int my_f2, int en_f1, int en_f2)
{
	int my_f3 = my_total_sum - my_f1 - my_f2;
	int en_f3 = enemy_total_sum - en_f1 - en_f2;
	int cnt = (my_f1 > en_f1 ? 1 : 0) + (my_f2 > en_f2 ? 1 : 0) + (my_f3 > en_f3 ? 1 : 0);
	return (cnt >= 2);
}

double get_prob(int my_f1, int my_f2, map<pi, int> efc)
{
	int total = 0;
	int wins = 0;
	FORI(it, efc)
	{
		int en_f1 = it->first.first;
		int en_f2 = it->first.second;
		total += it->second;
		if (me_wins(my_f1, my_f2, en_f1, en_f2))
			wins += it->second;
	}
	return (double)wins / (double)total;
}

void solve()
{
	cin >> N;
	my_cards.clear();
	enemy_cards.clear();
	my_total_sum = 0;
	enemy_total_sum = 0;

	FOR(i, 0, 3 * N - 1)
	{
		int strength;
		cin >> strength;
		my_cards.push_back(strength);
		my_total_sum += strength;
	}
	FOR(i, 0, 3 * N - 1)
	{
		int strength;
		cin >> strength;
		enemy_cards.push_back(strength);
		enemy_total_sum += strength;
	}

	// I need 2 wins
	// setup most promising distributions
	// first, put N lowest in one field (don't care)
	// distribute 2*N remaining as evenly as possible

	map<pi, int> mfc = count_field_dists(my_cards);
	map<pi, int> efc = count_field_dists(enemy_cards);

	double best_prob = -1.0;
	int best_f1, best_f2;

	approach = (double)my_total_sum / 2.0;
	priority_queue<fdist_even2, vector<fdist_even2>, MyCmp2> pool2;
	FORI(it, mfc)
	{
		fdist_even2 fd;
		fd.a = it->first.first;
		fd.b = it->first.second;
		fd.c = my_total_sum - fd.a - fd.b;
		pool2.push(fd);
	}

	// find best
	FOR(i, 1, N*N*N*N)
		if (pool2.empty())
			break;
		else
		{
			fdist_even2 top = pool2.top();
			pool2.pop();
			int my_f1 = top.a;
			int my_f2 = top.b;
			if (my_f1 > 0 && my_f2 > 0)
			{
				double cur = get_prob(my_f1, my_f2, efc);
				if (cur > best_prob)
				{
					// this strategy is optimal so far
					best_prob = cur;
					best_f1 = my_f1;
					best_f2 = my_f2;
				}
			}
		}

	// geometrical argument: all 3 fields should be as equal as possible
	approach = (double)my_total_sum / 3.0;
	priority_queue<fdist_even3, vector<fdist_even3>, MyCmp3> pool3;
	FORI(it, mfc)
	{
		fdist_even3 fd;
		fd.a = it->first.first;
		fd.b = it->first.second;
		fd.c = my_total_sum - fd.a - fd.b;
		pool3.push(fd);
	}

	// find best
	FOR(i, 1, N*N*N*N)
		if (pool3.empty())
			break;
		else
		{
			fdist_even3 top = pool3.top();
			pool3.pop();
			int my_f1 = top.a;
			int my_f2 = top.b;
			if (my_f1 > 0 && my_f2 > 0)
			{
				double cur = get_prob(my_f1, my_f2, efc);
				if (cur > best_prob)
				{
					// this strategy is optimal so far
					best_prob = cur;
					best_f1 = my_f1;
					best_f2 = my_f2;
				}
			}
		}

	cout << best_prob;

	// DEBUG:
	// cout << "\t\t" << best_f1 << "," << best_f2 << "," << (my_total_sum - best_f1 - best_f2);
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
