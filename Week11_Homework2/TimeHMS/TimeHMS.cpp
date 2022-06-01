#include <iostream>
using namespace std;

class TimeHMS
{
	int hour, min, sec;
public:
	TimeHMS(int h = 0, int m = 0, int s = 0) : hour(h), min(m), sec(s) { }
	void Scale()
	{
		int temp = 0;
		temp = hour * 3600 + min * 60 + sec;

		hour = temp / 3600;
		min = abs((temp % 3600) / 60);
		sec = abs(temp % 60);
	}

	TimeHMS operator+ (TimeHMS& t)								// 1
	{
		return TimeHMS(hour + t.hour, min + t.min, sec + t.sec);
	}
	TimeHMS operator- (TimeHMS& t)								//2
	{
		return TimeHMS(hour - t.hour, min - t.min, sec - t.sec);
	}
	bool operator== (TimeHMS& t) { return (hour * 3600 + min * 60 + sec) == (t.hour * 3600 + t.min * 60 + t.sec); }
	bool operator!= (TimeHMS& t) { return (hour * 3600 + min * 60 + sec) != (t.hour * 3600 + t.min * 60 + t.sec); }
																// 3
	TimeHMS operator++() {
		hour++;
		return *this;
	}
	TimeHMS operator--() {
		hour--;
		return *this;
	}	// 4
	TimeHMS operator++(int) {
		sec++;
		return *this;
	}
	TimeHMS operator--(int) {
		sec--;
		return *this;
	}
																// 5
	int& operator[] (int id)									// 6
	{													
		if (id == 0) return hour;
		else if (id == 1) return min;
		else if (id == 2) return sec;
		else exit(0);
	}
	operator int() { return (int)(3600 * hour + 60 * min + sec); }
																// 7
	operator double() { return (double)(3600 * hour + 60 * min + sec)/3600; }
																// 8
	friend TimeHMS operator* (int num, TimeHMS& t)								// 9
	{
		return TimeHMS(num * t.hour, num * t.min, num * t.sec);		
	}
	friend ostream& operator<<(ostream& os, const TimeHMS& t)
	{
		int temp_hour = t.hour;
		int temp_min = t.min;
		int temp_sec = t.sec;
		int temp = 0;
		temp = temp_hour * 3600 + temp_min * 60 + temp_sec;

		temp_hour = temp / 3600;
		temp_min = abs((temp % 3600) / 60);
		temp_sec = abs(temp % 60);

		if (temp_sec < 10)
			if (temp_min < 10)
				os << temp_hour << ":0" << temp_min << ":0" << temp_sec;
			else
				os << temp_hour << ":" << temp_min << ":0" << temp_sec;
		else
			if (temp_min < 10)
				os << temp_hour << ":0" << temp_min << ":" << temp_sec;
			else
				os << temp_hour << ":" << temp_min << ":" << temp_sec;
		return os;
	}
	friend istream& operator>>(istream& is, TimeHMS& t)
	{
		is >> t.sec;
		return is;
	}
};

void main()
{
	TimeHMS t1(1, 20, 30), t2(4, 35, 46), t3, t4, t5, t6;
	
	cout << "t1 \t\t= " << t1 << endl;
	cout << "t2 \t\t= " << t2 << endl;

	cout << "t3[sec]\t\t= ";
	cin >> t3;
	cout << "t3 \t\t= " << t3 << endl;

	t4 = t3 + t2;
	cout << "t4 = t3 + t2 \t= " << t4 << endl;

	t5 = t3 - t2;
	cout << "t5 = t3 - t2 \t= " << t5 << endl;

	cout << "t3 = t1\t\t: ";
	(t3 == t1) ? cout << "true" << endl : cout << "false" << endl;

	cout << "++t1\t\t= " << ++t1 << endl;
	cout << "--t1\t\t= " << --t1 << endl;

	cout << "t1++\t\t= " << t1++ << endl;
	cout << "t1--\t\t= " << t1-- << endl;

	cout << "t2[hour]\t: " << t2[0] << endl;
	cout << "t2[min]\t\t: " << t2[1] << endl;
	cout << "t2[sec]\t\t: " << t2[2] << endl;

	cout << "t1 (sec)\t= " << (int)t1 << endl;
	cout << "t2 (hour)\t= " << (double)t2 << endl;
	t6 = 2 * t1;
	cout << "t6 = 2 * t1\t= " << t6 << endl;
}