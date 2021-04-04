#include <iostream>
#include <string>
#define N 4

using namespace std;

class Time
{
private:

	int Size;
	int *hour;
	int *minute;
	int *seconds;
	int	*difference;

public:
	Time(int p) {
		this->Size = 1;
		this->hour = new int[Size];
		this->minute = new int[Size];
		this->seconds = new int[Size];
		this->difference = new int[Size];
		for (int i = 0; i < Size; i++) {
			hour[i] = 0;
			minute[i] = 0;
			seconds[i] = 0;
			difference[i] = p;
		}
	}
	Time(int a, int b, int c) 
	{ 
		this->Size = 1;
		this->hour = new int[Size];
		this->minute = new int[Size];
		this->seconds = new int[Size];
		this->difference = new int[Size];
		for (int i = 0; i < Size; i++) {
			hour[i] = a;
			minute[i] = b;
			seconds[i] = c;
			difference[i] = (hour[i] * 3600) + (minute[i] * 60) + seconds[i];
		}
	}
	Time(const Time &obj) 
	{
		this->Size = obj.Size;
		this->hour = new int[obj.Size]; 
		this->minute = new int[obj.Size];
		this->seconds = new int[obj.Size];
		this->difference = new int[obj.Size];
		for (int i = 0; i < obj.Size; i++) 
		{
			this->hour[i] = obj.hour[i];
			this->minute[i] = obj.minute[i];
			this->seconds[i] = obj.seconds[i];
			this->difference[i] = obj.difference[i];
		}
	}
	~Time() 
 	{ 
		delete[] hour, delete[] minute, delete[] seconds, delete[] difference; 
	}

	string Get_Info()
	{
		return "Time: Hours - " + to_string(hour[0]) + " : Minutes - " + to_string(minute[0]) + " : Seconds - " + to_string(seconds[0]);
	}

	bool operator<(const Time& obj)
	{
		for (int i = 0; i < N; i++)
		{
			if (this->difference[i] < obj.difference[i]) return true;
			else if (this->difference[i] > obj.difference[i]) return false;
		}
		return false;
	}

	Time operator=(Time& obj) {
		this->Size = obj.Size;
		for (int i = 0; i < this->Size; i++) {
			this->hour[i] = obj.hour[i];
			this->minute[i] = obj.minute[i];
			this->seconds[i] = obj.seconds[i];
			this->difference[i] = obj.difference[i];
		}
		 
		return *this;
	}

	Time operator-=(Time& obj) {
		this->Size = obj.Size;
		for (int i = 0; i < this->Size; i++) {
			if (obj.difference[i] < 60) {
				if (this->seconds[i] < obj.difference[i]) {
					this->minute[i] = this->minute[i] - 1;
					this->seconds[i] = this->seconds[i] - obj.difference[i] + 60;
				}
				else {
					this->seconds[i] = this->seconds[i] - obj.difference[i];
				}
			}
			else if(obj.difference[i] == 60) {
				this->minute[i] = this->minute[i] - 1;
			}
			else if (obj.difference[i] > 60 && obj.difference[i] < 3600) {
				int a = obj.difference[i] / 60;
				int b = obj.difference[i] % 60;
				this->minute[i] = this->minute[i] - a;
				this->seconds[i] = this->seconds[i] - b;
				if (this->minute[i] < 0) {
					this->hour[i] = this->hour[i] - 1;
					this->minute[i] += 60;
				}
				if (this->seconds[i] < 0) {
					do {
						this->minute[i] = this->minute[i] - 1;
						this->seconds[i] += 60;
					} while (this->seconds[i] < 0);
				}
			}
			else if (obj.difference[i] == 3600) {
				this->hour[i] = this->hour[i] - 1;
			}
			else if (obj.difference[i] > 3600) {
				int a = obj.difference[i] / 3600;
				int b = obj.difference[i] % 3600;
				int c = b / 60;
				int k = b % 60;
				this->hour[i] = this->hour[i] - a;
				this->minute[i] = this->minute[i] - c;
				this->seconds[i] = this->seconds[i] - k;
				if (this->minute[i] < 0) {
					do {
					this->hour[i] = this->hour[i] - 1;
					this->minute[i] += 60;
					} while (this->minute[i] < 0);
				}
				if (this->seconds[i] < 0) {
					do {
						this->minute[i] = this->minute[i] - 1;
						this->seconds[i] += 60;
					} while (this->seconds[i] < 0);
				}
			}
		}
		 
		return *this;
	}
};

void Print();
void Sort();
void Swap(int a, int b);
void Decrease(Time& obj);

Time elems[N]
{
	Time(11, 34, 7),
	Time(4, 54, 12),
	Time(9, 23, 44),
	Time(17, 48, 31)
};


int main()
{
	Print();
	Sort();
	cout << endl;
	cout << "Sorted:" << endl;
	Print();
	cout << endl;
	Time decrease(1488);
	Decrease(decrease);
	cout << "Decreased:" << endl;
	Print();
}

void Print()
{
	for (int i = 0; i < N; i++)
		cout << elems[i].Get_Info() << endl;
	cout << endl;
}

void Sort() 
{
	for (int startIndex = 0; startIndex < N - 1; startIndex++)
	{
		int smallestIndex = startIndex;
		for (int currentIndex = startIndex + 1; currentIndex < N; currentIndex++) 
		{
			if (elems[currentIndex] < elems[smallestIndex])
			{
				smallestIndex = currentIndex;
			}
		}
		Swap(startIndex, smallestIndex);
	}
}

void Swap(int a, int b)
{
	Time temp(elems[a]);
	elems[a] = elems[b];
	elems[b] = temp;
}

void Decrease(Time &obj) {
	for (int i = 0; i < N; i++) {
		elems[i] -= obj;
	}
}