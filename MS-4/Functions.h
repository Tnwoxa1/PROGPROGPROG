#pragma once
#include <vector>
#include <ccomplex>
#include <cmath>
#include <algorithm>
//ось для GetMatrix
enum Axis {
	T,
	X,
	Y
};

//комплексное число
typedef std::complex<long double> complexld;
extern long  double pi;
//переменные для волновых функций
//extern int NN, last_k_max;
//extern long double UU, ppit_width, wwidth_between;

//переменные для эволюции - максимальное время и шаг времени
extern long double tt_max, ddt;
//мнимая единица
extern complexld I;

template <typename T>
int sign(T x);

long double Pow2(long double x);
long double PotentialFunction(long double x, long double y, long double k1, long double k2);
//long double PotentialFunction(long double x, long double y, long double a, long double k);

std::vector < std::vector< long double>> CreateWaveFunction(long double R, long double muX, long double sigmaX, long double muY, long double sigmaY); 

std::vector<std::vector<complexld>> WaveInNextTime(long double R, std::vector<std::vector<complexld>> wave, long double dt, long double k1, long double k2);

long double FindMaxCmplx(std::vector<complexld> vec);
long double FindMaxCmplx(std::vector<std::vector<complexld>> vec);

long double FindMaxDouble(std::vector<std::vector<long double>> vec);

std::vector<long double> Cmplx2LDouble(std::vector<complexld> vec);
std::vector<std::vector<long double>> Cmplx2LDouble(std::vector<std::vector<complexld>> vec);


std::vector<complexld> fft(const std::vector<complexld>& In);

std::vector<std::vector<complexld>> fft(std::vector< std::vector<complexld>>& In);


//получить вектор-столбец
std::vector<complexld> GetColumn(std::vector<std::vector<complexld>> matr, int col);

//long double в комплексное
std::vector<complexld> Double2Cmplx(std::vector<long double> vec);
std::vector<std::vector<complexld>> Double2Cmplx(std::vector<std::vector<long double>> vec);

std::vector<std::vector<long double>> Normalizate(std::vector<std::vector<long double>> vec);


void CalculateWaveEvolution(std::vector< std::vector<long double>> wave0, std::vector< std::vector< std::vector<complexld>>>* out, long double R, int num_waves, long double dt, bool* thEvolutionDone, long double k1, long double k2);

