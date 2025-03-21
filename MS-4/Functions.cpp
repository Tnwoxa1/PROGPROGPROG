#include "pch.h"
using namespace std;

long double pi = 3.141592653589793238;
complexld I(0., 1.);

long double Gauss(long double x, long double y, long double muX, long double sigmaX, long double muY, long double sigmaY) 
{
	return exp(-Pow2((x - muX) / (2 * sigmaX))) * exp(-Pow2((y - muY) / (2 * sigmaY)));
}

template <typename T>
int sign(T x) 
{
	if (x > 0) return 1;
	else if (x == 0) return 0;
	else return -1;
}

long double Pow2(long double x)
{
	return x * x;
}

//// функция
//long double PotentialFunction(long double x, long double y, long double k1, long double k2) 
//{
//	////return k1 * x * x / 2 + k2 * y * y / 2;
//	//return 0;
//	// Расстояния до двух центров
//	long double r1 = std::abs(x + a);
//	long double r2 = std::abs(x - a);
//
//	// Проверка на деление на ноль
//	if (r1 == 0 || r2 == 0)
//		return std::numeric_limits<long double>::infinity();
//
//	// Общий потенциал
//	long double V = -k / r1 - k / r2;
//
//	return V;
//}
// функция
long double PotentialFunction(long double x, long double y, long double k1, long double k2)
{
	long double r1 = std::sqrt((x + 0.5) * (x + 0.5) + y * y);
	long double r2 = std::sqrt((x - 0.5) * (x - 0.5) + y * y);

	// Проверка на нулевые расстояния
	if (r1 == 0 || r2 == 0)
		return std::numeric_limits<long double>::infinity();

	// Потенциал от двух центров
	return -k1 / r1 - k2 / r2;
}

vector<vector<long double>> CreateWaveFunction(long double R, long double muX, long double sigmaX, long double muY, long double sigmaY) //masZ меняется
{
	int numStep = 256;
	long double step = 2 * R / numStep;

	//х, у - порядок
	vector<vector<long double>> masPsi(numStep, vector<long double>(numStep));
	
	for (int i = 0; i < numStep; i++)
	{
		for (int j = 0; j < numStep; j++) 
		{
			long double x = - R + i * step;
			long double y = - R + j * step;
			masPsi[i][j] = Gauss(x, y, muX, sigmaX, muY, sigmaY);
		}
	}
	return masPsi;
}

//волновая функция в следующий момент времени
vector<vector<complexld>> WaveInNextTime(long double R, vector<vector<complexld>> wave, long double dt, long double k1, long double k2) 
{
	vector<vector<complexld>> Psi = wave;

	vector<complexld> A(wave.size()), B(wave.size()), C(wave.size()), D(wave.size());
	vector<complexld> alpha(wave.size()), beta(wave.size());

	for (int y = 0; y < Psi.size(); y++) 
	{
		Psi[Psi.size() - 1][y] = 0;
		Psi[0][y] = 0;
	}

	for (int x = 0; x < Psi.size(); x++) 
	{
		Psi[x][Psi.size() - 1] = 0;
		Psi[x][0] = 0;
	}

	//Прогонка по Х (У - фиксируется)
	for (int y = 1; y < wave.size() - 1; y++) 
	{
		//выделим память под N-2 точек
		long double step = 2 * R / wave.size();
		complexld derivY = (long double)2*((wave[0][y + 1] - wave[0][y]) - (wave[0][y] - wave[0][y - 1])) / (step * step);
		complexld AA = -(I * dt) / (2 * step * step);

		//получаем коэффициенты A,B,C,D от 1 до N-1
		for (int x = 1; x < wave.size() - 1; x++) 
		{
			A[x] = AA;
			B[x] = AA;
			//C[x] = (long double)1 + I * dt * PotentialFunction(step * x, step * y, k1, k2) * (long double)0.5 - (long double)2. * AA;
			C[x] = (long double)1 + I * dt * PotentialFunction(step * x, step * y, k1, k2) * (long double)0.5 - (long double)2. * AA;

			complexld derivX = ((wave[x + 1][y] - wave[x][y]) - (wave[x][y] - wave[x - 1][y])) / (step * step);

			D[x] = wave[x][y] + I * dt * (long double)0.5 * (derivX + derivY - PotentialFunction(x * step, y * step, k1, k2) * wave[x][y]);
		}

		//коэффы альфа, бета
		alpha[1] = 0;
		beta[1] = 0;
		for (int y = 1; y < wave.size() - 1; y++) 
		{
			alpha[y + 1] = -B[y] / (C[y] + A[y] * alpha[y]);
			beta[y + 1] = (D[y] - A[y] * beta[y]) / (C[y] + A[y] * alpha[y]);
		}

		// волновая функция в следующий момент времени
		Psi[Psi.size() - 1][y] = 0;
		Psi[0][y] = 0;
		for (int x = Psi.size() - 2; x >= 1; x--) 
		{
			Psi[x][y] = alpha[x + 1] * Psi[x + 1][y] + beta[x];
		}
	}

	wave = Psi;

	for (int y = 0; y < Psi.size(); y++) 
	{
		Psi[Psi.size() - 1][y] = 0;
		Psi[0][y] = 0;
	}

	for (int x = 0; x < Psi.size(); x++) 
	{
		Psi[x][Psi.size() - 1] = 0;
		Psi[x][0] = 0;
	}

	//Прогонка по У (Х - фиксируется)
	for (int x = 1; x < wave.size() - 1; x++) 
	{
		//выделим память под N-2 точек
		long double step = 2 * R / wave.size();

		complexld derivX = (long double)2*((wave[x + 1][0] - wave[x][0]) - (wave[x][0] - wave[x - 1][0])) / (step * step);
		complexld AA = -(I * dt) / (2. * step * step);
		//получаем коэффициенты A,B,C,D от 1 до N-1
		for (int y = 1; y < wave.size() - 1; y++) 
		{
			A[y] = AA;
			B[y] = AA;
			C[y] = (long double)1 + I * dt * PotentialFunction(step * x, step * y, k1, k2) * (long double)0.5 - (long double)2. * AA;

			//complexld derivX = ((wave[x + 1][y] - wave[x][y]) - (wave[x][y] - wave[x - 1][y])) / (step * step);
			complexld derivY = ((wave[x][y + 1] - wave[x][y]) - (wave[x][y] - wave[x][y - 1])) / (step * step);

			D[y] = wave[x][y] + I * dt * (long double)0.5 * (derivX + derivY - PotentialFunction(x * step, y * step, k1, k2) * wave[x][y]);
		}

		//коэффы альфа, бета
		alpha[1] = 0;
		beta[1] = 0;
		for (int y = 1; y < wave.size() - 1; y++) 
		{
			alpha[y + 1] = -B[y] / (C[y] + A[y] * alpha[y]);
			beta[y + 1] = (D[y] - A[y] * beta[y]) / (C[y] + A[y] * alpha[y]);
		}

		//волновая фукнция в следующий момент времени
		Psi[x][Psi.size() - 1] = 0;
		Psi[x][0] = 0;
		for (int y = Psi.size() - 2; y >= 1; y--) 
		{
			Psi[x][y] = alpha[y + 1] * Psi[x][y + 1] + beta[y + 1];
		}
	}
	return Psi;
}

//найти максимальный элемент
long double FindMaxCmplx(vector<complexld> vec) 
{
	long double max = abs(vec[0]);
	for (int i = 0; i < vec.size(); i++) 
	{
		if (abs(vec[i]) >= max) max = abs(vec[i]);
	}
	return max;
}

long double FindMaxCmplx(vector<vector<complexld>> vec) 
{
	long double max = FindMaxCmplx(vec[0]);
	for (int i = 1; i < vec.size(); i++) 
	{
		long double temp = FindMaxCmplx(vec[i]);
		if (temp > max) max = temp;
	}
	return max;
}

long double FindMaxDouble(vector<vector<long double>> vec) 
{
	long double max = vec[0][0];
	for (int i = 0; i < vec.size(); i++) 
	{
		long double temp = *max_element(vec[i].begin(), vec[i].end());
		if (temp > max) max = temp;
	}
	return max;
}

//комплексное в long double
vector<long double> Cmplx2LDouble(vector<complexld> vec) 
{
	vector<long double> out;
	for (int i = 0; i < vec.size(); i++) 
	{
		out.push_back(abs(vec[i]));
	}
	return out;
}

vector<vector<long double>> Cmplx2LDouble(vector<vector<complexld>> vec) 
{
	vector<vector<long double>> out;
	for (int i = 0; i < vec.size(); i++) 
	{
		out.push_back(Cmplx2LDouble(vec[i]));
	}
	return out;
}

//long double в комплексное
vector<complexld> Double2Cmplx(vector<long double> vec) 
{
	vector<complexld> out(vec.size());
	for (int i = 0; i < vec.size(); i++) 
	{
		out[i] = complexld((long double)vec[i], 0);
	}
	return out;
}

vector<vector<complexld>> Double2Cmplx(vector<vector<long double>> vec) 
{
	vector<vector<complexld>> out(vec.size());
	for (int i = 0; i < vec.size(); i++) 
	{
		out[i] = Double2Cmplx(vec[i]);
	}
	return out;
}

vector<complexld> fft(const vector<complexld>& In)
{
	int i = 0, wi = 0;
	int n = In.size();
	vector<complexld> A(n / 2), B(n / 2), Out(n);
	if (n == 1) 
	{
		return vector<complexld>(1, In[0]);
	}
	i = 0;
	copy_if(In.begin(), In.end(), A.begin(), [&i](complexld e) 
		{
			return !(i++ % 2);
		});
	copy_if(In.begin(), In.end(), B.begin(), [&i](complexld e) 
		{
			return (i++ % 2);
		});

	vector<complexld> At = fft(A);
	vector<complexld> Bt = fft(B);

	transform(At.begin(), At.end(), Bt.begin(), Out.begin(), [&wi, &n]
	(complexld& a, complexld& b) 
		{
			return  a + b * exp(complexld(0, 2 * pi * wi++ / n));
		});
	transform(At.begin(), At.end(), Bt.begin(), Out.begin() + n / 2, [&wi, &n]
	(complexld& a, complexld& b) 
		{
			return  a + b * exp(complexld(0, 2 * pi * wi++ / n));
		});
	return Out;
}

//fft для трехмерной волновой функции
vector<vector<complexld>> fft(vector< vector<complexld>>& in) 
{
	vector<vector<complexld>> out(in.size());
	for (int i = 0; i < in.size(); i++) 
	{
		out[i] = fft(in[i]);
	}
	return out;
}

// нормировка всех значений массива от 0 до 1
vector<vector<long double>> Normalizate(vector<vector<long double>> vec) 
{
	vector<vector<long double>> out = vec;
	long double max = FindMaxDouble(vec);
	for (int i = 0; i < vec.size(); i++) 
	{
		for (int j = 0; j < vec[i].size(); j++) 
		{
			out[i][j] = vec[i][j] / max;
		}
	}
	return out;
}

// получаем столбец из матрицы
vector<complexld> GetColumn(vector<vector<complexld>> matr, int col) 
{
	vector<complexld> out;
	for (int i = 0; i < matr.size(); i++) 
	{
		out.push_back(matr[i][col]);
	}
	return out;
}

// расчёт волновых функций
void CalculateWaveEvolution(vector< vector<long double>> wave0, vector< vector< vector<complexld>>>* out, long double R, int num_waves, long double dt, bool* thEvolutionDone, long double k1, long double k2) 
{
	vector<vector<complexld>> waveCmplx = Double2Cmplx(wave0);
	out->push_back(waveCmplx);

	//рассчитываем положение в следующие моменты времени
	for (int i = 0; i < num_waves - 1; i++) 
	{
		waveCmplx = WaveInNextTime(R, waveCmplx, dt, k1, k2);
		out->push_back(waveCmplx);
	}
	*thEvolutionDone = true;
}