#pragma once



#include <fstream>


#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
/*CString FUNC(string& buf, string& res, string& key, int& Blocknum, int& sIze); */





const int IP[64] = { 58,50,42,34,26,18,10,2,
                     60,52,44,36,28,20,12,4,
                     62,54,46,38,30,22,14,6,
                     64,56,48,40,32,24,16,8,
                     57,49,41,33,25,17, 9,1,
                     59,51,43,35,27,19,11,3,
                     61,53,45,37,29,21,13,5,
                     63,55,47,39,31,23,15,7 };

const int IP_1[64] = { 40,8,48,16,56,24,64,32,
                       39,7,47,15,55,23,63,31,
                       38,6,46,14,54,22,62,30,
                       37,5,45,13,53,21,61,29,
                       36,4,44,12,52,20,60,28,
                       35,3,43,11,51,19,59,27,
                       34,2,42,10,50,18,58,26,
                       33,1,41,9,49,17,57,25 };

const int E_exp[48] = { 32,1,2,3,4,5,
                        4,5,6,7,8,9,
                        8,9,10,11,12,13,
                        12,13,14,15,16,17,
                        16,17,18,19,20,21,
                        20,21,22,23,24,25,
                        24,25,26,27,28,29,
                        28,29,30,31,32,1 };

const int P_transform[32] = { 16,7,20,21,
                              29,12,28,17,
                              1,15,23,26,
                              5,18,31,10,
                              2,8,24,14,
                              32,27,3,9,
                              19,13,30,6,
                              22,11,4,25 };

const int PC_1[56] = { 57,49,41,33,25,17,9,
                       1,58,50,42,34,26,18,
                       10,2,59,51,43,35,27,
                       19,11,3,60,52,44,36,
                       63,55,47,39,31,23,15,
                       7,62,54,46,38,30,22,
                       14,6,61,53,45,37,29,
                       21,13,5,28,20,12,4 };

const int PC_2[56] = { 14,17,11,24,1,5,
                       3,28,15,6,21,10,
                       23,19,12,4,26,8,
                       16,7,27,20,13,2,
                       41,52,31,37,47,55,
                       30,40,51,45,33,48,
                       44,49,39,56,34,53,
                       46,42,50,36,29,32 };

const int S__1[4][16] = { {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
                           {0,15,7,4,15,2,13,1,10,6,12,11,9,5,3,8},
                           {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                           {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} };

const int S__2[4][16] = { {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
                           {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                           {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
                           {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9} };

const int S__3[4][16] = { {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
                           {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                           {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
                           {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12} };

const int S__4[4][16] = { {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
                           {12,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                           {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
                           {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14} };

const int S__5[4][16] = { {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
                           {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                           {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
                           {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3} };

const int S__6[4][16] = { {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
                           {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                           {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
                           {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13} };

const int S__7[4][16] = { {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
                           {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                           {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
                           {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12} };

const int S__8[4][16] = { {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
                           {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
                           {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
                           {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11} };

//typedef const int(*PSOKFPSOKF_t)[16];
//PSOKFPSOKF_t PSOKFPSOKF[8] = { S__1, S__2, S__3, S__4, S__5, S__6, S__7, S__8 };

class DES {
public:
    string total_code, total_key;//���� ���������� �������� ������:�������� ����� � ����
    string tempCode_1, tempCode_2;//
    string m_code, code;// � m_code ������������ ��������� ��������(� �����), ��� �� � �������
    string L, R, C, D;// ������ � ���� �����. � � � ����� ��� ��������� ������
    vector<string> K;//���� ������������ �����
   // DES() {}
    // ����������
    string encode(string str, string key);
    // ������������
    string decode(string str, string key);
    
    // ����� ������
    // ��������� ������
    void fill(string str);
    // ��������� ������
    void formatSourceCode();
    // ������ IP (LR)
    void getIP0();


    // ������� ������� ��������
    string Feistel(string R, string K);
    // P ������
    string getPTransform(string str);
    // Feistel SBOX
    string Feistel_SBOX(string str, int num);
    // ���������� E
    string E_expend(string str);
    // �������� XOR
    string XORoperation(string a, string b);
    // � �������� (�������������)
    string iterationT_A(int begin, int end);
    // T �������� (������������)
    string iterationT_D(int begin, int end);
    // �������� ������ IP
    string getIP1(string str);
    // ��������� �������� ����� 1
    string formatResult(string str);
    // ��������� �������� ����� 2
    string formatAndReduceResult(string str);
    // �������� � ����������
    int Two2Ten(string num);
    // ����� ����������
    // ������ ��������
    string formatKey();
    // ������ ��1
    string getPC1Key(string str);
    // �������� C, D
    void get_C_D(string str);
    
    // ������ LS
    void getKeyI();
    
    // LS ������������ (1)
    void LS_1(string& str);
    // LS ������������ (2)
    void LS_2(string& str);
    // ������ ��2
    string getPC2Key(string str);
    // �������� ����� ������� ����������
    void getKeys();
};
string  from2Tocharr(string c2de);
void stringtovector(string a, vector<int>& bit);
char bitTochar(vector<int> a);
////
string fromCharrTo2(string ciphertext);
string vectorToString(vector<int> bit);
void chartobit(char c, vector<int>& bit);
string VTS(vector<char> bit);
void STV(string a, vector<char>& bit);

//const int  N = 10;
//
//class RSA 
//{
//public: 
//    string firstFunc(RSA h);
//    void RSA_Decrypt();
//    void RSA_Encrypt(RSA h);
//    string inttotext();
//    string inttotext1(RSA h);
//    void RSA_Initialize(RSA h);
//    void Initialize();
//    int Exgcd(int m, int n, int& x);
//    int ProducePrimeNumber(int prime[]);
//    long long Modular_Exonentiation(long long a, int b, int n);
//    int BianaryTransform(int num, int bin_num[]);
//    string plain;
//    string cipher;
//    int hello[N];
//    vector<unsigned int> Plaintext; // �������� �����
//    vector<unsigned int> Ciphertext; // ������������� �����
//    unsigned int n, e, d;
//    void textToint(string hh, RSA h);
//    string RSA::secondFunc(RSA h);
//    unsigned int powmod(unsigned int base, unsigned int power, unsigned int modul);
//};

class RSA
{
    unsigned int e, n, p, q, f;
    unsigned int d;

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