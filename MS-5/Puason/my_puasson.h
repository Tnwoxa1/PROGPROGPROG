#pragma once
#include <gdiplus.h>
#include "Work.h"

// my_puasson

class my_puasson : public CStatic
{
	DECLARE_DYNAMIC(my_puasson)

public:
	my_puasson();
	virtual ~my_puasson();

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	UINT_PTR token;
	std::vector<std::vector<cell>> setka;
	double xScale, yScale;
	bool draw;
	std::vector<std::vector<std::pair<double, double>>> my_izoline, my_power_line;
	std::vector<std::pair<double, double>> my_e_line;
	std::vector<double> my_const;
	void CreateIzoline(Gdiplus::Graphics* my_dr);
	void write();
	bool izoline;
	void CreateElime(Gdiplus::Graphics* my_dr);
	double step_e_line;
	double rasstoanie(double my_x, double my_y, double xpt, double ypt);
	double A(double fi1, double fi2);
	double B(double fi1, double fi2);
	void up_down(Gdiplus::Graphics* my_dr, int i, int j, int inext, int jnext, double& x, double& y, int znak);
	bool power_line;
	void SetPower(std::vector<std::vector<std::pair<double, double>>> my);
};

