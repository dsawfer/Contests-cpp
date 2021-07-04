#include <sstream>
#include <iostream>
#include <string>

using namespace std;
void workWithCommands(string* seating, int n, string* commands, int m);
void divideSeating(string* seating, int n, string* left, string* right);
bool isFree(int num, string side, int mode);							//mode = 1, read from left to right; mode = 0, read from right to left
void printSeats(string* left, string* right, int n, int row);
void replaceSeats(string &seats, int num, int mode, char symb);

int main(void)
{
	int n = 0, m = 0;
	cin >> n;
	cin.ignore(32767, '\n');
	string *seating = new string[n];
	for (int i = 0; i < n; i++)
	{
		getline(std::cin, seating[i]);
	}

	cin >> m;
	cin.ignore(32767, '\n');
	string *commands = new string[m];
	for (int i = 0; i < m; i++)
	{
		getline(std::cin, commands[i]);
	}

	workWithCommands(seating, n, commands, m);

	delete[] seating;
	delete[] commands;
	return 0;
}

void workWithCommands(string* seating, int n, string* commands, int m)
{
	string *left = new string[n];
	string *right = new string[n];
	divideSeating(seating, n, left, right);

	stringstream x;						//create a string stream variable
	string side, position;				//storage strings
	int step = 0, num = 0, checker = 0;

	while (step < m) {
		x << commands[step];			//write a string to the stream buffer
		x >> num >> side >> position;	//copy words from string in buffer x

		int selector = 0;
		if (side == "right" && position == "window") selector = 1;
		else
			if (side == "left" && position == "window") selector = 2;
			else
				if (side == "right" && position == "aisle") selector = 3;
				else
					if (side == "left" && position == "aisle") selector = 4;

		for (int i = 0; i < n; i++)
		{
			checker = 0;
			switch (selector)
			{
			case 1:						//right window
				if (right[i][right->size() - 1] == '.') {
					if (isFree(num, right[i], 1)) {
						replaceSeats(right[i], num, 1, 'X');
						printSeats(left, right, n, i);
						replaceSeats(right[i], num, 1, '#');
						checker++;
						i = n;			//stop cycle
					}
				}
				continue;
				break;
			case 2:						//left window
				if (left[i][0] == '.') {
					if (isFree(num, left[i], 0)) {
						replaceSeats(left[i], num, 0, 'X');
						printSeats(left, right, n, i);
						replaceSeats(left[i], num, 0, '#');
						checker++;
						i = n;
					}
				}
				else continue;
				break;
			case 3:						//right aisle
				if (right[i][0] == '.') {
					if (isFree(num, right[i], 0)) {
						replaceSeats(right[i], num, 0, 'X');
						printSeats(left, right, n, i);
						replaceSeats(right[i], num, 0, '#');
						checker++;
						i = n;
					}
				}
				else continue;
				break;
			case 4:						//left aisle
				if (left[i][left->size() - 1] == '.') {
					if (isFree(num, left[i], 1)) {
						replaceSeats(left[i], num, 1, 'X');
						printSeats(left, right, n, i);
						replaceSeats(left[i], num, 1, '#');
						checker++;
						i = n;
					}
				}
				else continue;
				break;
			default:					//wrong command
				break;
			}
		}
		if (checker == 0) cout << "Cannot filfull passengers requirements\n";

		x.str("");						//resetting the value of the string stream
		x.clear();						//reset error flags and return the buffer to its original position

		step++;
	}

	delete[] left;
	delete[] right;
}

void divideSeating(string* seating, int n, string* left, string* right)
{
	int step = 0;
	while (step < n) {
		left[step] = seating[step].substr(0, seating[step].find('_'));
		right[step] = seating[step].substr(seating[step].find('_') + 1);
		step++;
	}
}

bool isFree(int num, string side, int mode)
{
	int step = 0, pos;
	if (mode) pos = side.size() - 1;
	else pos = 0;
	while (step < num)
	{
		if (side[pos] == '#') return false;

		if (mode) pos--;
		else pos++;

		step++;
	}
	return true;
}

void replaceSeats(string &seats, int num, int mode, char symb)
{
	int step = 0, pos;
	if (mode) pos = seats.size() - 1;
	else pos = 0;
	while (step < num)
	{
		seats[pos] = symb;

		if (mode) pos--;
		else pos++;

		step++;
	}
}


void printSeats(string* left, string* right, int n, int row)
{
	int step = 0;
	cout << "Passengers can take seats:";
	while (left[row][step] && right[row][step]) {
		if (left[row][step] == 'X') {
			cout << ' ' << (row + 1) << (char)(step + 65);
		}
		else if (right[row][step] == 'X') {
			cout << ' ' << (row + 1) << (char)(step + 68);
		}
		step++;
	}
	cout << '\n';
	step = 0;
	while (step < n)
	{
		cout << left[step] << '_' << right[step] << '\n';
		step++;
	}
}
