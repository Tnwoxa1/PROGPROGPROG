// my_puasson.cpp: файл реализации
//

#include "pch.h"
#include "Puason.h"
#include "my_puasson.h"
using namespace std;
using namespace Gdiplus;

// my_puasson

IMPLEMENT_DYNAMIC(my_puasson, CStatic)

my_puasson::my_puasson()
{
	GdiplusStartupInput input;
	Status s;
	s = GdiplusStartup(&token, &input, NULL);
	if (s != Ok)
	{
		MessageBox(L"Не удалось нарисовать", L"Ошибка", NULL);
	}
	draw = false;
	izoline = false;
	power_line = false;
}

my_puasson::~my_puasson()
{
	GdiplusShutdown(token);
}


BEGIN_MESSAGE_MAP(my_puasson, CStatic)
END_MESSAGE_MAP()



// Обработчики сообщений my_puasson



double MYsign(double x)
{
	return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

void my_puasson::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  Добавьте исходный код для отображения указанного элемента
	if (!draw) return;

	if (setka.empty()) return;

	//if (my_izoline.empty()) izoline = false;

	Graphics wnd(lpDrawItemStruct->hDC);
	Bitmap buffer(lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &wnd);
	Graphics draw_in_buffer(&buffer);
	draw_in_buffer.SetSmoothingMode(SmoothingModeAntiAlias);

	draw_in_buffer.Clear(Color::White);

	SolidBrush b_metall(Color::LightGray), b_sreda(Color::White), b_granica_vne(Color::RosyBrown), b_granica_vnut(Color::LightGoldenrodYellow);
	Pen white_pen(Color::White, 3), black_pen(Color::Black, 2);

	double cur_width = lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left;
	double cur_height = lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top;

	int fi_width = setka[0].size();
	int fi_height = setka.size();

	xScale = cur_width / fi_width;
	yScale = cur_height / fi_height;

	Matrix matr;
	matr.Scale(xScale, yScale);

	PointF pt[4];

	for (int i = 0; i < fi_height; i++)
	{
		for (int j = 0; j < fi_width; j++)
		{
			pt[0] = PointF((double)j, (double)i);
			pt[1] = PointF((double)(j + 1), (double)i);
			pt[2] = PointF((double)(j + 1), (double)(i + 1));
			pt[3] = PointF((double)j, (double)(i + 1));
			matr.TransformPoints(pt, 4);

			switch (setka[i][j].material_cell)
			{
			case sreda: draw_in_buffer.DrawRectangle(&Pen(&b_sreda), pt[0].X, pt[0].Y, pt[1].X - pt[0].X, pt[3].Y - pt[0].Y);
				draw_in_buffer.FillRectangle(&b_sreda, pt[0].X, pt[0].Y, pt[1].X - pt[0].X, pt[3].Y - pt[0].Y); break;
			case metall: draw_in_buffer.DrawRectangle(&Pen(&b_metall), pt[0].X, pt[0].Y, pt[1].X - pt[0].X, pt[3].Y - pt[0].Y);
				draw_in_buffer.FillRectangle(&b_metall, pt[0].X, pt[0].Y, pt[1].X - pt[0].X, pt[3].Y - pt[0].Y); break;
			case granica_vne: draw_in_buffer.DrawRectangle(&Pen(&b_granica_vne), pt[0].X, pt[0].Y, pt[1].X - pt[0].X, pt[3].Y - pt[0].Y);
				draw_in_buffer.FillRectangle(&b_granica_vne, pt[0].X, pt[0].Y, pt[1].X - pt[0].X, pt[3].Y - pt[0].Y); break;
			}
		}
	}

	if (izoline)
	{
		CreateIzoline(&draw_in_buffer);
		CreateElime(&draw_in_buffer);
	}
	wnd.DrawImage(&buffer, 0, 0, 0, 0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, UnitPixel);
}

void my_puasson::CreateIzoline(Gdiplus::Graphics* my_dr)
{
	int size = my_const.size();
	my_izoline = vector<vector<pair<double, double>>>(size);

	bool first = true;
	
	Pen white_pen(Color::White, 3), black_pen(Color::Blue, 2);

	Matrix matr;
	matr.Scale(xScale, yScale);

	PointF pt[4];

	for (int i = 0; i < setka.size() - 1; i++)
	{
		for (int j = 0; j < setka[i].size() - 1; j++)
		{
			for (int k = 0; k < size; k++)
			{
				if ((my_const[k] <= setka[i][j].fi && my_const[k] >= setka[i][j + 1].fi)
					|| (my_const[k] >= setka[i][j].fi && my_const[k] <= setka[i][j + 1].fi))
					my_izoline[k].push_back(pair<double, double>((double)(j + 1) - fabs(setka[i][j + 1].fi - my_const[k]) / fabs(setka[i][j].fi - setka[i][j + 1].fi), (double)i));

				if ((my_const[k] <= setka[i][j + 1].fi && my_const[k] >= setka[i + 1][j + 1].fi)
					|| (my_const[k] >= setka[i][j + 1].fi && my_const[k] <= setka[i + 1][j + 1].fi))
					my_izoline[k].push_back(pair<double, double>((double)(j + 1), (double)(i + 1) - fabs(setka[i + 1][j + 1].fi - my_const[k]) / fabs(setka[i][j + 1].fi - setka[i + 1][j + 1].fi)));

				if ((my_const[k] <= setka[i + 1][j].fi && my_const[k] >= setka[i + 1][j + 1].fi)
					|| (my_const[k] >= setka[i + 1][j].fi && my_const[k] <= setka[i + 1][j + 1].fi))
					my_izoline[k].push_back(pair<double, double>((double)(j + 1) - fabs(setka[i + 1][j + 1].fi - my_const[k]) / fabs(setka[i + 1][j].fi - setka[i + 1][j + 1].fi), (double)(i + 1)));

				if ((my_const[k] <= setka[i][j].fi && my_const[k] >= setka[i + 1][j].fi)
					|| (my_const[k] >= setka[i][j].fi && my_const[k] <= setka[i + 1][j].fi))
					my_izoline[k].push_back(pair<double, double>((double)(j), (double)(i + 1) - fabs(setka[i + 1][j].fi - my_const[k]) / fabs(setka[i][j].fi - setka[i + 1][j].fi)));

				if (my_izoline[k].size() == 2)
				{
					pt[0] = PointF(my_izoline[k][my_izoline[k].size() - 2].first, my_izoline[k][my_izoline[k].size() - 2].second);
					pt[1] = PointF(my_izoline[k][my_izoline[k].size() - 1].first, my_izoline[k][my_izoline[k].size() - 1].second);
					matr.TransformPoints(pt, 2);
				}

				my_dr->DrawLine(&black_pen, pt[0], pt[1]);
				my_izoline[k].clear();
			}
		}
	}
	write();
}

void my_puasson::write()
{
	ofstream file;
	file.open(L"izoline.txt");
	file.precision(2);
	for (int i = 0; i < my_izoline.size(); i++)
	{
		file << i + 1 << endl;
		for (int j = 0; j < my_izoline[i].size(); j++)
		{
			file << my_izoline[i][j].first << "\t" << my_izoline[i][j].second << endl;
		}
		//file << endl;
	}
	file.close();
}

void my_puasson::CreateElime(Gdiplus::Graphics* my_dr)
{
	PointF pt[2];
	Matrix matr;
	matr.Scale(xScale, yScale);
	Pen red_pen(Color::Red, 2);
	double x = 1.5, y = 1.5, xlast, ylast, cury = y, curx = x;
	int i = 0, j = 0;
	double znak = -1;
	for (int o = 0; o < my_e_line.size(); o += step_e_line)
	{
		x = my_e_line[o].first;
		y = my_e_line[o].second;
		do
		{
			xlast = x;
			ylast = y;
			i = (int)y;
			j = (int)x;
			if (i >= setka.size() - 1 || j >= setka[0].size() - 1) break;
			up_down(my_dr, i, j, i + 1, j + 1, x, y, znak);
		} while (x - xlast != 0 || y - ylast != 0);
	
	}
}

double my_puasson::rasstoanie(double my_x, double my_y, double xpt, double ypt)
{
	return (xpt - my_x) * (xpt - my_x) + (ypt - my_y) * (ypt - my_y);
}

double my_puasson::A(double fi1, double fi2)
{
	return fi1 - fi2;
}

double my_puasson::B(double fi1, double fi3)
{
	return -(fi3 - fi1);
}

void my_puasson::up_down(Gdiplus::Graphics* my_dr, int i, int j, int inext, int jnext, double& x, double& y, int znak)
{
	PointF pt[2];
	Matrix matr;
	matr.Scale(xScale, yScale);
	Pen red_pen(Color::Green, 2);
	double sign = znak;
	double ugol, step = 0.3, mya, myb;
	double xnext = x - 1, ynext = y - 1;
	xnext = x;
	ynext = y;
	i = (int)y;
	j = (int)x;
	inext = (int)y + 1;
	jnext = (int)x + 1;
	double ab;
	if (rasstoanie(x, y, j, i) <= rasstoanie(x, y, jnext, inext))
	{
		x = xnext;
		y = ynext;
		pt[0] = PointF(x, y);
		mya = A(setka[i][j].fi, setka[i][j + 1].fi);
		myb = B(setka[i][j].fi, setka[i + 1][j].fi);
		if (mya == 0 || myb == 0) return;
		ab = sqrt(mya * mya + myb * myb);
		mya /= ab;
		myb /= ab;
		xnext = sign * mya * step + x;
		ynext = sign * myb * step + y;
		pt[1] = PointF(xnext, ynext);
		matr.TransformPoints(pt, 2);
		my_dr->DrawLine(&red_pen, pt[0], pt[1]);
	}
	if (rasstoanie(x, y, j, i) > rasstoanie(x, y, jnext, inext))
	{
		x = xnext;
		y = ynext;
		pt[0] = PointF(x, y);
		mya = A(setka[i][j].fi, setka[i][j + 1].fi);
		myb = B(setka[i][j].fi, setka[i + 1][j].fi);
		if (mya == 0 || myb == 0) return;
		ab = sqrt(mya * mya + myb * myb);
		mya /= ab;
		myb /= ab;
		xnext = sign * mya * step + x;
		ynext = sign * myb * step + y;
		pt[1] = PointF(xnext, ynext);
		matr.TransformPoints(pt, 2);
		my_dr->DrawLine(&red_pen, pt[0], pt[1]);
	}
	x = xnext;
	y = ynext;
}
void my_puasson::SetPower(std::vector<std::vector<std::pair<double, double>>> my)
{
	my_power_line = my;
}
