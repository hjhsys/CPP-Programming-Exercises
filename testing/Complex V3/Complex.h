#pragma once
#include <cstdio>
struct Complex
{
	double real;
	double imag;

public:
	void set (double r, double i)
	{
		real = r;
		imag = i;
	}
	void read(const char* msg = "���Ҽ� =");
	void print(const char* msg = "���Ҽ� = ");
	void add(Complex a, Complex b);
};