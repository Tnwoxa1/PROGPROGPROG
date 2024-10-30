#include "pch.h"
#include "rs.h"
#include <string>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <vector>
using namespace std;
void charToBit(char c, vector<int>& bit)
{
	for (int i = 0; i < 8; i++)
		bit.push_back(c >> (7 - i) & 1);
}

char bitToChar(vector <int> a)
{
	char R = 0x00;
	for (int k = 0; k < 8; k++)
	{
		R |= a[k] << (7 - k);
	}
	return R;
}


unsigned int RSA::powmod(unsigned int base, unsigned int power, unsigned int modul)
{
	unsigned int a = 1;
	unsigned int b = base;
	while (power > 0)
	{
		if (power % 2 == 1)
			a = (a * b) % modul;
		b = (b * b) % modul;
		power = power / 2;
	}
	return a % modul;
}


bool RSA::Ferma(unsigned int a)
{
	if (a == 1 || a == 0) return false;

	for (int i = 0; i < 10; i++)
	{
		unsigned int x = rand() % (a - 1) + 1;
		if (powmod(x, a - 1, a) != 1)
		{
			return false;
		}
	}

	return true;
}

void RSA::CreatePandQ()
{
	p = 1; q = 1;

	while (p == 1 || q == 1)
	{
		//unsigned int work = (double)rand() / RAND_MAX * ((unsigned int)pow(2, 16) - 1 - (unsigned int)pow(2, 8)) + (unsigned int)pow(2, 8);
		unsigned int work = (double)rand() / RAND_MAX * ((unsigned int)pow(2, 8) - 1 - (unsigned int)pow(2, 4)) + (unsigned int)pow(2, 4);
		if (Ferma(work))
		{
			if (p == 1) p = work;
			else q = work;
		}
	}
}

void RSA::CreateNandF()
{
	n = p * q;
	f = (p - 1) * (q - 1);
}

unsigned int RSA::gcd(unsigned int a, unsigned int b)
{
	unsigned int r;
	while (true)
	{
		/*if (b == 0) return a;
		r = a % b;
		a = b; b = r;*/

		r = a % b;
		if (r == 0) return b;
		a = b; b = r;
	}
}

void RSA::CreateE()
{
	e = f;
	unsigned int work;
	while (e >= f)
	{
		work = (double)rand() / RAND_MAX * (f - 2) + 2;
		//if (!Ferma(work)) continue;
		if (gcd(f, work) == 1) e = work;
	}
}

int RSA::BigEvklid(unsigned int a, unsigned int b)
{
	unsigned int r, w;
	int l1, m1;
	vector<int> L, m;
	L.push_back(1);
	L.push_back(0);
	m.push_back(0);
	m.push_back(1);

	/*while (true)
	{
		if (b == 0) return m[0];
		r = a % b;
		a = b;
		b = r;
		if (b == 0) return m[0];

		w = a / b;

		l1 = L[1]; m1 = m[1];
		L[1] = L[0] - w * L[1];
		m[1] = m[0] - w * m[1];
		L[0] = l1; m[0] = m1;
	}*/

	while (b != 0)
	{
		w = a / b;
		r = a % b;
		l1 = L[1]; m1 = m[1];
		L[1] = L[0] - w * L[1];
		m[1] = m[0] - w * m[1];
		L[0] = l1; m[0] = m1;
		a = b;
		b = r;
	}

	return m[0];
}

void RSA::CreateKey()
{
	do
	{
		CreatePandQ();
		CreateNandF();
		CreateE();
		d = abs(BigEvklid(f, e));
	} while ((e * d) % f != 1);
}

CString RSA::Shifr(vector<char> input, vector<char>& output, bool flag)
{
	//CreateKey();
	output.clear();
	string str;
	vector<int> bit, forchar;
	unsigned int M, C;

	if (flag)
	{
		for (int i = 0; i < input.size(); i++)
		{
			charToBit(input[i], bit);
			M = twototen(bit);
			C = powmod(M, e, n); //true - coding
			//else C = powmod(M, d, n); //false - decoding

			bit.clear();
			tentotwo(C, bit, 32);
			for (int k = 0; k < 4; k++)
			{
				for (int h = 0; h < 8; h++)
				{
					forchar.push_back(bit[k * 8 + h]);
				}
				output.push_back(bitToChar(forchar));
				str += output[k];
				forchar.clear();
			}
			bit.clear();
		}
	}

	else
	{
		for (int i = 0; i < input.size() / 4; i++)
		{
			for (int k = 0; k < 4; k++)
			{
				charToBit(input[i * 4 + k], bit);
			}
			C = twototen(bit);
			M = powmod(C, d, n);
			bit.clear();
			tentotwo(M, bit, 8);
			output.push_back(bitToChar(bit));
			str += output[i];
		}
	}

	return CString(str.c_str(), str.length());
}

unsigned int RSA::twototen(vector<int> bit)
{
	unsigned int ten(0);
	for (int s = 0; s < bit.size(); s++)
	{
		ten += bit[bit.size() - 1 - s] * pow(2, s);
	}
	return ten;
}

void RSA::tentotwo(unsigned int ten, vector<int>& bit, int maxbit)
{
	while (ten >= 2)
	{
		bit.insert(bit.begin(), ten % 2);
		ten = ten / 2;
	}
	bit.insert(bit.begin(), ten);

	int num = maxbit - bit.size();
	if (bit.size() < maxbit)
	{
		for (int j = 0; j < num; j++)
		{
			bit.insert(bit.begin(), 0);
		}
	}
}

unsigned int RSA::Getn()
{
	return n;
}

unsigned int RSA::Gete()
{
	return e;
}

int RSA::Getd()
{
	return d;
}

unsigned int RSA::Getf()
{
	return f;
}

void RSA::Sete(unsigned int a)
{
	e = a;
}

void RSA::Setn(unsigned int a)
{
	n = a;
}

void RSA::Setd(int a)
{
	d = a;
}

void RSA::Setf(unsigned int a)
{
	f = a;
}