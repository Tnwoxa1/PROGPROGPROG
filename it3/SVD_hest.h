#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

// n_n - ���������� ����� ������������������ ������� (a)
// m_m - ���������� �������� ������������������ ������� (a)
// a - ������������������ �������
// u - ����� ����������� �������
// v - ������ ����������� �������
// sigma - ������������ ������� � ������������ �������
int svd(const std::vector<std::vector<float>>& a, std::vector<std::vector<float>>& u, std::vector<std::vector<float>>& v, std::vector<std::vector<float>>& sigma, int n_n, int m_m) {
    float thr = 0.000001f;
    int n = n_n; // ���������� �����
    int m = m_m; // ���������� ��������

    // ������������� v ��� ��������� ������� �������� m x m
    v = std::vector<std::vector<float>>(m, std::vector<float>(m, 0.0f));
    for (int i = 0; i < m; ++i) {
        v[i][i] = 1.0f;
    }

    // ������������� u ��� ����� a �������� n x m
    u = std::vector<std::vector<float>>(n, std::vector<float>(m, 0.0f));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            u[i][j] = a[i][j];
        }
    }

    int iter = 0;
    while (true) {
        bool lort = false;
        iter++;
        for (int l = 0; l < m - 1; ++l) {
            for (int k = l + 1; k < m; ++k) {
                float alfa = 0.0f;
                float betta = 0.0f;
                float hamma = 0.0f;
                for (int i = 0; i < n; ++i) {
                    alfa += u[i][l] * u[i][l];
                    betta += u[i][k] * u[i][k];
                    hamma += u[i][l] * u[i][k];
                }

                if (sqrt(alfa * betta) < 1.e-10) continue;
                if (fabs(hamma) / sqrt(alfa * betta) < thr) continue;

                lort = true;
                float eta = (betta - alfa) / (2.f * hamma);
                float t = (eta / fabs(eta)) / (fabs(eta) + sqrt(1.f + eta * eta));
                float cos0 = 1.f / sqrt(1.f + t * t);
                float sin0 = t * cos0;

                for (int i = 0; i < n; ++i) {
                    float buf = u[i][l] * cos0 - u[i][k] * sin0;
                    u[i][k] = u[i][l] * sin0 + u[i][k] * cos0;
                    u[i][l] = buf;
                }

                for (int i = 0; i < m; ++i) {
                    float buf = v[i][l] * cos0 - v[i][k] * sin0;
                    v[i][k] = v[i][l] * sin0 + v[i][k] * cos0;
                    v[i][l] = buf;
                }
            }
        }

        if (!lort) break;
    }

    // �������� ������� sigma �������� m x m � ���������� ������������ ���������
    sigma = std::vector<std::vector<float>>(m, std::vector<float>(m, 0.0f));
    for (int i = 0; i < std::min(n, m); ++i) {
        float s = 0.0f;
        for (int j = 0; j < n; ++j) s += u[j][i] * u[j][i];
        s = sqrt(s);
        sigma[i][i] = s;
        if (s < 1.e-10) continue;
        for (int j = 0; j < n; ++j) u[j][i] = u[j][i] / s;
    }

    // ���������� �� �������� ����������� ����� � ��������������� ������������ �������� ������ U � V
    for (int i = 0; i < std::min(n, m) - 1; ++i) {
        for (int j = i + 1; j < std::min(n, m); ++j) {
            if (sigma[i][i] < sigma[j][j]) {
                std::swap(sigma[i][i], sigma[j][j]);
                for (int k = 0; k < n; ++k) std::swap(u[k][i], u[k][j]);
                for (int k = 0; k < m; ++k) std::swap(v[k][i], v[k][j]);
            }
        }
    }

    return iter;
}