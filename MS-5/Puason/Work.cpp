#include "pch.h"
#include "Work.h"
using namespace std;

double e0 = 8.854187817e-12;

model::model()
{
}

void model::SetParametr(int my_a, int my_d, int my_l, double my_q, int my_num_const, int my_num_line)
{
	a = my_a;
	d = my_d;
	l = my_l;
	q = my_q;
	left_fi = q;
	num_fi_const = my_num_const;
	fi_const = vector<double>(num_fi_const);
	for (int i = 0; i < num_fi_const; i++) fi_const[i] = right_fi + fabs(right_fi - left_fi) / (num_fi_const + 1) * (i + 1);
	num_F_line = my_num_line;
}

bool model::Initialize(int width, int height)
{
	last_fi = vector<vector<cell>>(height, vector<cell>(width));
	int d_vne = 1;
	int width_plus = 10, height_plus = 10, dopusk = 2;
	int w_cell = (width - width_plus - 2. * d_vne) / 2.;
	int h_cell = (height - height_plus - 2. * d_vne) / 2;

	if (!E_line.empty()) E_line.clear();

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			last_fi[i][j].material_cell = sreda;
			last_fi[i][j].fi = 0;
		}
	}

	if (w_cell <= 0)
	{
		MessageBoxW(NULL, L"w_cell <= 0", L"Error!", NULL);
		return false;
	}
	if (h_cell <= 0)
	{
		MessageBoxW(NULL, L"h_cell <= 0", L"Error!", NULL);
		return false;
	}

	for (int j = 0; j < width; j++) //верхняя и нижняя внешняя стенка
	{
		last_fi[height - 1][j].material_cell = last_fi[0][j].material_cell = granica_vne;
		last_fi[height - 1][j].fi = last_fi[0][j].fi = 0.;
		E_line.push_back(pair<double, double>({ j, 1.1 }));
		E_line.push_back(pair<double, double>({ j, height - 2 }));
		E_line.push_back(pair<double, double>({ j, 1.1 }));
		E_line.push_back(pair<double, double>({ j, height - 2 }));
	}

	for (int i = 0; i < height; i++) //боковые внешние стенки
	{
		last_fi[i][0].material_cell = last_fi[i][width - 1].material_cell = granica_vne;
		last_fi[i][0].fi = last_fi[i][width - 1].fi = 0.;
		E_line.push_back(pair<double, double>({ 1.1, i }));
		E_line.push_back(pair<double, double>({ height - 2, i }));
		E_line.push_back(pair<double, double>({ 1.1, i }));
		E_line.push_back(pair<double, double>({ height - 2, i }));
	}

	int hei_to_gor = 4, wid_to_ver = 4;

	for (int i = h_cell + hei_to_gor; i <= h_cell + hei_to_gor + dopusk; i++) //горизонтальная часть плюсика
	{
		for (int j = w_cell; j <= w_cell + width_plus; j++)
		{
			last_fi[i][j].material_cell = last_fi[i][j].material_cell = metall;
			last_fi[i][j].fi = last_fi[i][j].fi = left_fi;/*
			E_line.push_back(pair<double, double>({ j, i - 0.1 }));
			E_line.push_back(pair<double, double>({ j, i + 0.1 }));
			E_line.push_back(pair<double, double>({ j + 0.1, i }));
			E_line.push_back(pair<double, double>({ j - 0.1, i }));*/
		}
	}

	for (int j = w_cell + wid_to_ver; j <= w_cell + wid_to_ver + dopusk; j++) //вертикальная часть плюсика
	{
		for (int i = h_cell; i <= h_cell + height_plus; i++)
		{
			last_fi[i][j].material_cell = last_fi[i][j].material_cell = metall;
			last_fi[i][j].fi = last_fi[i][j].fi = left_fi;/*
			E_line.push_back(pair<double, double>({ j - 0.1, i }));
			E_line.push_back(pair<double, double>({ j + 1, i }));*/
		}
	}
	cur_fi = last_fi;
	return true;
}

void model::Initialize(std::vector<std::vector<cell>> my_fi)
{
	cur_fi = last_fi = my_fi;
}

void model::Iteration()
{
	for (int i = 1; i < last_fi.size() - 1; i++)
	{
		for (int j = 1; j < last_fi[i].size() - 1; j++)
		{
			if (cur_fi[i][j].material_cell == sreda) cur_fi[i][j].fi = (last_fi[i + 1][j].fi + last_fi[i - 1][j].fi + last_fi[i][j + 1].fi + last_fi[i][j - 1].fi) / 4.;
		}
	}

}

void model::write()
{
	ofstream file;
	file.open(L"my fi.txt");
	file.precision(2);
	for (int i = 0; i < last_fi.size(); i++)
	{
		for (int j = 0; j < last_fi[i].size(); j++)
		{
			file << last_fi[i][j].fi << "\t";
		}
		file << endl;
	}
	file.close();
}

double model::error()
{
	double er = 0;
	for (int i = 1; i < last_fi.size() - 1; i++)
	{
		for (int j = 1; j < last_fi[i].size() - 1; j++) er += fabs(last_fi[i][j].fi - cur_fi[i][j].fi);
	}
	last_fi = cur_fi;
	write();
	return er;
}

std::vector<std::vector<cell>> model::GetFi()
{
	return last_fi;
}

std::vector<std::vector<std::pair<double, double>>> model::GetPowerL()
{
	//return powerL;
	return std::vector<std::vector<std::pair<double, double>>>();
}
