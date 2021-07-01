#include <iostream>

int checkNonDecreasing(int* tanks, int n);
void equalizeTanks(int* tanks, int n);

int main(void)
{
	int n = 0;
	std::cin >> n;
	int* tanks = new int[n];

	for (int i = 0; i < n; i++)
	{
		std::cin >> tanks[i];
	}

	if (checkNonDecreasing(tanks, n) == 1)
		equalizeTanks(tanks, n);
	else std::cout << -1;

	delete[] tanks;
	return 0;
}

int checkNonDecreasing(int* tanks, int n)
{
	int step = 0;
	while (step < (n - 1)) {
		if (tanks[step] > tanks[step + 1])
			return 0;
		step++;
	}
	return 1;
}

void equalizeTanks(int* tanks, int n)
{
	int count = 0, step = (n - 2);
	while (step >= 0) {
		if (tanks[step] < tanks[step + 1]) {
			tanks[step] += count;
			while (tanks[step] < tanks[n - 1]) {
				tanks[step]++;
				count++;
			}
		}
		step--;
	}
	std::cout << count;
}