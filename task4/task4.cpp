#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

void getDist(vector <pair<int, int> > digits, int k);
int searchDigit(int key, vector <pair<int, int> > digits);
int processDigit(int key, vector <pair<int, int> > digits, int k);

int main(void)
{
	int n, k;
	cin >> n >> k;
	vector <pair<int, int> > digits (n);

	for (int i = 0; i < n; i++)
	{
		digits[i].first = i + 1;
		cin >> digits[i].second;
	}

	getDist(digits, k);

	return 0;
}

bool comp(pair <int, int> a, pair <int, int> b)
{
	return a.second < b.second;
}

void getDist(vector <pair<int, int> > digits, int k)
{
	sort(digits.begin(), digits.end(), comp);

	int step = 1, cur;
	while (step <= digits.size()) {
		cur = searchDigit(step, digits);
		if (cur != -1) cout << processDigit(cur, digits, k) << ' ';
		++step;
	}
}

int searchDigit(int key, vector <pair<int, int> > digits)
{
	int step = 0;
	while (step < digits.size()) {
		if (key == digits[step].first) return step;
		++step;
	}
	return -1;
}

int processDigit(int key, vector <pair<int, int> > digits, int k)
{
	int step = 0, sum = 0, left = key - 1, right = key + 1, ldist = 0, rdist = 0;

	while (step < k)
	{
		if (left >= 0) ldist = abs(digits[key].second - digits[left].second);
		else ldist = -1;
		if (right < digits.size()) rdist = abs(digits[key].second - digits[right].second);
		else rdist = -1;

		if ((ldist < rdist || rdist == -1) && ldist != -1) {
			sum += ldist;
			--left;
		}
		else {
			sum += rdist;
			++right;
		}
		++step;
	}
	return sum;
}