#pragma once
#include <vector>

class RSA
{
	unsigned int e, n, p, q, f;
	int d;

public:

	unsigned int powmod(unsigned int base, unsigned int power, unsigned int modul);

	bool Ferma(unsigned int a);

	void CreatePandQ();

	void CreateNandF();

	unsigned int gcd(unsigned int a, unsigned int b);

	void CreateE();

	int BigEvklid(unsigned int a, unsigned int b);

	void CreateKey();

	CString Shifr(std::vector<char> input, std::vector<char>& output, bool flag);

	unsigned int twototen(std::vector<int> bit);

	void tentotwo(unsigned int ten, std::vector<int>& bit, int maxbit);

	unsigned int Getn();
	unsigned int Gete();
	int Getd();
	unsigned int Getf();

	void Sete(unsigned int a);
	void Setn(unsigned int a);
	void Setd(int a);
	void Setf(unsigned int a);
};