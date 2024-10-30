#include"pch.h"
#include "Work.h"
typedef const int(*PSOKFPSOKF_t)[16];
PSOKFPSOKF_t PSOKFPSOKF[8] = { S__1, S__2, S__3, S__4, S__5, S__6, S__7, S__8 };

/*CString FUNC(string& buf, string& res, string& key, int& Blocknum, int& sIze)
{

	//string res="";
	for (int i = 0; i < ((Blocknum) * (sIze)); i++) {
		res.push_back(*"\0");
	}
	for (int i = 0; i < Blocknum; i++)
	{
		for (int j = 0; j < sIze; j++)
		{
			if (i * sIze + j < buf.length()) {
				res[i * sIze + j] = buf[i * sIze + j] ^ key[j];
			}
			else {
				res.push_back(*"\0"); /*counter += 1;*/
			/*}

		}
	}
	res.resize(Blocknum * sIze);

	return CString(res.c_str(), res.length());; 

}*/
////////////////////////////////////////////////////////////////////////////
void charToBit(char c, vector<int>& bit)
{
    for (int i = 0; i < 8; i++)
        bit.push_back(c >> (7 - i) & 1);
}

char bitToChar(vector <int> a)
{
    char res = 0x00;
    for (int k = 0; k < 8; k++)
    {
        res |= a[k] << (7 - k);
    }
    return res;
}

//DES::DES() {}
    // шифрование
 string DES::encode(string str, string key) {
        m_code = "";
        total_code = str;
        total_key = key;
        
        getKeys();
       
        formatSourceCode();
        int count = 0;
        int s = total_code.size();
        while (count * 8 < s) {
            string sub;
            if (s - count * 8 >= 8) {
                sub = total_code.substr(count * 8, 8);
            }
            else {
                sub = total_code.substr(count * 8);
            }
            count++;
            fill(sub);
            
            getIP0();
            
            string a = iterationT_A(1, 16);
           
            string result = getIP1(a);
            m_code += result;
            
        }
        return m_code;
       // cout << m_code << endl;///////////////////////////////////////////////////////////////////////////////////
    }
    // расшифровать
string DES::decode(string str, string key) {
        int count = 0;
        code = "";
      
        total_key = key;
        getKeys();
        while (count * 64 < str.size()) {
            tempCode_1 = str.substr(count * 64, 64);
            total_key = key;
            count++;
            
            getIP0();
            
            string a = iterationT_D(16, 1);
            
            string result = getIP1(a);
            if (count * 64 == str.size()) {
                code += formatAndReduceResult(result);
            }
            else {
                code += formatResult(result);
            }
        }
        return code;
       // cout << code << endl;/////////////////////////////////////////////////////////////////////////
    }
    // часть пароля
    // заполняем строку
 void DES::fill(string str) {
        tempCode_1 = "";
        for (int i = 0; i < 8; i++) {
            string s;
            int a = i < str.size() ? (int)str[i] : 8 - str.size();
            while (a > 0) {
                s = (char)(a % 2 + 48) + s;
                a /= 2;
            }
            while (s.size() < 8) {
                s = "0" + s;
            }
            tempCode_1 += s;
        }
       
    }
    // заполняем строку
 void DES::formatSourceCode() {
        if (total_code.size() % 8 == 0) {
            total_code += "\b\b\b\b\b\b\b\b";
        }
    }
    // Замена IP (LR)
 void DES::getIP0() {
        tempCode_2 = tempCode_1;
        L = "";
        R = "";
        for (int i = 0; i < 64; i++) {
            tempCode_2[i] = tempCode_1[IP[i] - 1];
        }
        for (int i = 0; i < 64; i++) {
            if (i < 32) {
                L += tempCode_2[i];
            }
            else {
                R += tempCode_2[i];
            }
        }

       
    }
    // Круглая функция Фейстеля
 string DES::Feistel(string R, string K) {
        string res = "", rec = "";
        // E-расширение строки Ri-1 до 32 бит
        string ER = E_expend(R);
        // E (Ri-1) и подключ Ki длиной 48 бит подвергаются операции XOR
        for (int i = 0; i < 48; i++) {
            res += (char)(((ER[i] - 48) ^ (K[i] - 48)) + 48);
        }
        // Равномерно разделить на 8 групп и пройти через 8 разных S-блоков для преобразования 6-4
        for (int i = 0; i < 8; i++) {
            string sub = res.substr(i * 6, 6);
            string sub_m = Feistel_SBOX(sub, i);
            // Подключаемся последовательно, чтобы получить строку длиной 32 бита
            rec += sub_m;
        }
        
        // P- перестановка
        return getPTransform(rec);
    }
    // P замена
 string DES::getPTransform(string str) {
        string res = "";
        for (int i = 0; i < 32; i++) {
            res += str[P_transform[i] - 1];
        }
        return res;
    }
    // Feistel SBOX
 string DES::Feistel_SBOX(string str, int num) {
        int n = (str[0] - 48) * 2 + (str[5] - 48);
        int m = (str[1] - 48) * 8 + (str[2] - 48) * 4 + (str[3] - 48) * 2 + (str[4] - 48);
        int number = PSOKFPSOKF[num][n][m];
        string res = "";
        while (number > 0) {
            res = (char)(number % 2 + 48) + res;
            number /= 2;
        }
        while (res.size() < 4) {
            res = "0" + res;
        }
       
        return res;
    }
    // Расширение E
 string DES::E_expend(string str) {
        string res = "";
        for (int i = 0; i < 48; i++) {
            res += str[E_exp[i] - 1];
        }
       
        return res;
    }
    // операция XOR
 string DES::XORoperation(string a, string b) {
        string res = "";
        for (int i = 0; i < 32; i++) {
            res += (char)(((a[i] - 48) ^ (b[i] - 48)) + 48);
        }
        return res;
    }
    // Т итерация (зашифрованная)
 string DES::iterationT_A(int begin, int end) {
        string L_temp, R_temp;
        for (int i = begin - 1; i <= end - 1; i++) {
            L_temp = R;
            R_temp = XORoperation(L, Feistel(R, K[i]));
            L = L_temp;
            R = R_temp;
        }
        return R + L;
    }
    // T итерация (расшифрована)
 string DES::iterationT_D(int begin, int end) {
        string L_temp, R_temp;
        for (int i = begin - 1; i >= end - 1; i--) {
            L_temp = R;
            R_temp = XORoperation(L, Feistel(R, K[i]));
            L = L_temp;
            R = R_temp;
        }
        return R + L;
    }
    // Обратная замена IP
 string DES::getIP1(string str) {
        string res = "";
        for (int i = 0; i < 64; i++) {
            res += str[IP_1[i] - 1];
        }
        return res;
    }
    // сортируем открытый текст 1
 string DES::formatResult(string str) {
        int count = 0;
        string res = "";
        while (count * 8 < str.size()) {
            string a = str.substr(count * 8, 8);
            res += (char)(Two2Ten(a));
            count++;
        }
        return res;
    }
    // сортируем открытый текст 2
 string DES::formatAndReduceResult(string str) {
        int count = 0;
        string res = "";
        string a = str.substr(str.size() - 8, 8);
        int n = (int)(Two2Ten(a));
        
        while (count < 8 - n) {
            a = str.substr(count * 8, 8);
            res += (char)(Two2Ten(a));
            count++;
        }
        return res;
    }
    // Двоичное в десятичное
 int DES::Two2Ten(string num) {
        int base = 1;
        int res = 0;
        for (int i = num.size() - 1; i >= 0; i--) {
            res += (int)(num[i] - 48) * base;
            base *= 2;
        }
        return res;
    }
    // часть подраздела
    // Формат подключа
 string DES::formatKey() {
        string res = "", rec = "";
        for (int i = 0; i < 8; i++) {
            int num = (int)total_key[i];
            res = "";
            while (num > 0) {
                res = (char)(num % 2 + 48) + res;
                num /= 2;
            }
            while (res.size() < 8) {
                res = "0" + res;
            }
            rec += res;
        }
        
        return rec;
    }
    // Замена ПК1
 string DES::getPC1Key(string str) {
        string res = str;
        for (int i = 0; i < 56; i++) {
            res[i] = str[PC_1[i] - 1];
        }
        
        return res;
    }
    // Получаем C, D
void DES::get_C_D(string str) {
        C = "";
        D = "";
        str.erase(63, 1);
        str.erase(55, 1);
        str.erase(47, 1);
        str.erase(39, 1);
        str.erase(31, 1);
        str.erase(23, 1);
        str.erase(15, 1);
        str.erase(7, 1);
        for (int i = 0; i < str.size(); i++) {
            if (i < 28) {
                C += str[i];
            }
            else {
                D += str[i];
            }
        }
        
    }
    // Замена LS
 void DES::getKeyI() {
        //string C_temp = C, D_temp = D;
        for (int i = 1; i <= 16; i++) {
            if (i == 1 || i == 2 || i == 9 || i == 16) {
                LS_1(C);
                LS_1(D);
            }
            else {
                LS_2(C);
                LS_2(D);
            }
            string t = C + D;
            t = getPC2Key(t);
            K.push_back(t);
        }
    }
    // LS перестановка (1)
 void DES::LS_1(string& str) {
        char a = str[0];
        for (int i = 0; i < str.size() - 1; i++) {
            str[i] = str[i + 1];
        }
        str[str.size() - 1] = a;
    }
    // LS перестановка (2)
 void DES::LS_2(string& str) {
        char a = str[0], b = str[1];
        for (int i = 0; i < str.size() - 2; i++) {
            str[i] = str[i + 2];
        }
        str[str.size() - 2] = a;
        str[str.size() - 1] = b;
    }
    // Замена ПК2
 string DES::getPC2Key(string str) {
        string res = str;
        for (int i = 0; i < 48; i++) {
            res[i] = str[PC_2[i] - 1];
        }
        res.erase(53, 1);
        res.erase(42, 1);
        res.erase(37, 1);
        res.erase(34, 1);
        res.erase(24, 1);
        res.erase(21, 1);
        res.erase(17, 1);
        res.erase(8, 1);
        return res;
    }
    // Получаем общую функцию подраздела
 void DES::getKeys() {
        vector<string> t;
        K = t;
        string a = formatKey();
        a = getPC1Key(a);
        get_C_D(a);
        getKeyI();
    }
 /////////////////////////////////////////////////////////////////////////////////////
 void stringtovector(string a, vector<int>& bit)
 {

     for (int i = 0; i < a.size(); i++) {
         if (a[i] == '0') {
             bit.push_back(0);
         }
         if (a[i] == '1') {
             bit.push_back(1);
         }

     }
 }
 char bitTochar(vector<int> a) {
     char res = 0x00;
     for (int k = 0; k < 8; k++)
     {
         res |= a[k] << (7 - k);

     }

     return res;
 }
 string  from2Tocharr(string c2de)
 {
     vector<int> bit;
     string h;//сюда мы запишем шифрованный текст
     stringtovector(c2de, bit);
     for (int i = 8; i < bit.size() + 1; i += 8) {
         char m;
         vector<int> b(bit.begin() + i - 8, bit.begin() + i);
         m = bitTochar(b);
         h.push_back(m);

     }
     return h;
     // c2de - это строка с символами 0 1, хотим получить вектор с 0,1
     
 }
 ///////////////////////////////////////////////////////////
 string vectorToString(vector<int> bit)
 {
     string a;
     for (int i = 0; i < bit.size(); i++)
     {
         if (bit[i] == 0) {
             a.push_back('0');
         }
         if (bit[i] == 1) {
             a.push_back('1');
         }
     }
     return a;

 }
 void chartobit(char c, vector<int>& bit) {

     for (int i = 0; i < 8; i++)

     {
         bit.push_back(c >> (7 - i) & 1);
     }

 }

 string fromCharrTo2(string ciphertext) 
 {
     //cipherText = это шифрованная строка из окна
     
     //res - это строка из окна, только в двоичном коде
     string res;
     vector <int> bit;
     //функцией превращаем hello в двоичный код. Записываем в вектор
     for (int i = 0; i < ciphertext.size(); i++)
     {
         chartobit(ciphertext[i], bit);
     }
     res = vectorToString(bit);

     return res;
 }////////////////////////////////////////////////
 void STV(string a, vector<char>& bit)
 {

     for (int i = 0; i < a.size(); i++) {

         bit.push_back(a[i]);
        
     }
 }
 string VTS(vector<char> bit)
 {
     string a;

     for (int i = 0; i < bit.size(); i++) {
         a.push_back(bit[i]);
     }
     return a;

 }







 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //void RSA::textToint(string hh,RSA h) {
 //    //hh = "Hello!!!";
 //    for (int i = 0; i < N; i++)
 //    {
 //        h.hello[i] = (int)hh[i];
 //    }
 //}
 //string RSA::inttotext()
 //{
 //    string g;
 //    for (int i = 0; i < N; i++)
 //    {
 //        g.push_back((char)Ciphertext[i]);
 //    }
 //    return g;

 //}
 //string RSA::inttotext1(RSA hh)
 //{
 //    string h;
 //    for (int i = 0; i < N; i++)
 //    {
 //        h.push_back((char)hh.Ciphertext[i]);
 //    }
 //   
 //    return h;

 //}

 //// Двоичное преобразование
 //int RSA::BianaryTransform(int num, int bin_num[])
 //{

 //    int i = 0, mod = 0;

 //    // Преобразуется в двоичный, обратный временно сохраняется в массиве temp []
 //    while (num != 0)
 //    {
 //        mod = num % 2;
 //        bin_num[i] = mod;
 //        num = num / 2;
 //        i++;
 //    }

 //    // Возвращает количество цифр в двоичных числах
 //    return i;
 //}

 //// Повторное возведение в квадрат в степень
 //long long RSA::Modular_Exonentiation(long long a, int b, int n)
 //{
 //    int c = 0, bin_num[1000];
 //    long long d = 1;
 //    int k = BianaryTransform(b, bin_num) - 1;

 //    for (int i = k; i >= 0; i--)
 //    {
 //        c = 2 * c;
 //        d = (d * d) % n;
 //        if (bin_num[i] == 1)
 //        {
 //            c = c + 1;
 //            d = (d * a) % n;
 //        }
 //    }
 //    return d;
 //}

 //int RSA::ProducePrimeNumber(int prime[])
 //{
 //    int c = 0, vis[1001];
 //    memset(vis, 0, sizeof(vis));
 //    for (int i = 2; i <= 1000; i++)if (!vis[i])
 //    {
 //        prime[c++] = i;
 //        for (int j = i * i; j <= 1000; j += i)
 //            vis[j] = 1;
 //    }

 //    return c;
 //}


 //// Расширенный алгоритм Евклида
 //int RSA::Exgcd(int m, int n, int& x)
 //{
 //    int x1, y1, x0, y0, y;
 //    x0 = 1; y0 = 0;
 //    x1 = 0; y1 = 1;
 //    x = 0; y = 1;
 //    int r = m % n;
 //    int q = (m - r) / n;
 //    while (r)
 //    {
 //        x = x0 - q * x1; y = y0 - q * y1;
 //        x0 = x1; y0 = y1;
 //        x1 = x; y1 = y;
 //        m = n; n = r; r = m % n;
 //        q = (m - r) / n;
 //    }
 //    return n;
 //}





 ////// Инициализация алгоритма
 ////void RSA::Initialize()
 ////{
 ////    //N = 10;
 ////    int i;
 ////    srand((unsigned)time(NULL));
 ////    for (i = 0; i < N; i++)
 ////    {
 ////        Plaintext[i] = 48 + rand() % 10;
 ////    }

 ////    /*cout << "Generate 100 random numbers:" << '\n';
 ////    for (i = 0; i < N; i++)
 ////        cout << Plaintext[i] << " ";
 ////    cout << '\n' << '\n';*/
 ////}
 // unsigned int RSA::powmod(unsigned int base, unsigned int power, unsigned int modul){
 //        unsigned int a = 1;
 //       unsigned  int b = base;
 //        while (power > 0)
 //        {
 //            if (power % 2 == 1)
 //                a = (a * b) % modul;
 //            b = (b * b) % modul;
 //            power = power / 2;
 //        }
 //        return a % modul; }
 //
 // string RSA::firstFunc(RSA h)
 // {
 //     if (h.plain.size() < N) { for (int i = 0; i < N; i++) h.plain.push_back('\0'); }


 //     for (int i = 0; i < N; i++)
 //     {
 //         // Plaintext[i]=hello[i];
 //         h.Plaintext.push_back((unsigned int)h.plain[i]);
 //     }
 //     /* while (!e)
 //          RSA_Initialize(h);*/
 //  /*   n = 228719;
 //     e = 5327;
 //     d = 48143;*/
 //     for (int i = 0; i < N; i++){
 //         int q;
 //         q = (powmod(h.Plaintext[i], e, n));
 //     h.Ciphertext.push_back(q);
 //      }
 //   // RSA_Encrypt(h);
 //   // inttotext1(h);
 //    string L;
 //    for (int i = 0; i < N; i++)
 //    {
 //        L.push_back((char)h.Ciphertext[i]);
 //    }

 //    return L;
 //  
 //}
 //string RSA::secondFunc(RSA h)
 //{
 //    h.Ciphertext.clear();
 //    h.Plaintext.clear();
 //  /*  n = 228719;
 //    e = 5327;
 //    d = 48143;*/
 //    if (h.cipher.size() < N) { for (int i = 0; i < N; i++) h.cipher.push_back('\0'); }
 //    for (int i = 0; i < N; i++)
 //    {
 //        h.Ciphertext.push_back((unsigned int)h.cipher[i]);
 //    }
 //    //for (int i = 0; i < N; i++)
 //    //{
 //    //    // Plaintext[i]=hello[i];
 //    //    h.Ciphertext[i] = h.hello[i];
 //    //}
 //   // RSA_Decrypt();
 //    for (int i = 0; i < N; i++)
 //        
 //        h.Plaintext.push_back(powmod(h.Ciphertext[i], d, n));

 //    string L;
 //    for (int i = 0; i < N; i++)
 //    {
 //        L.push_back((char)h.Plaintext[i]);
 //    }

 //    return L;
 //}

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

//проверяем на 100 случайных числах
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
            /*charToBit(input[i], bit);*/
            M = (unsigned int)(input[i]);
            C = powmod(M, e, n); //true - coding
            //else C = powmod(M, d, n); //false - decoding
            output.push_back((char)C);
            str.push_back(output[i]);
            //bit.clear();
            //tentotwo(C, bit, 32);
            //for (int k = 0; k < 4; k++)
            //{
            //    for (int h = 0; h < 8; h++)
            //    {
            //        forchar.push_back(bit[k * 8 + h]);
            //    }
            //    output.push_back(bitToChar(forchar));
            //    str.push_back(output[k]);
            //    forchar.clear();
            //}
            //bit.clear();
        }
    }

    else
    {
        for (int i = 0; i < input.size() ; i++)
        {
          /*  for (int k = 0; k < 4; k++)
            {
                charToBit(input[i * 4 + k], bit);
            }*/
          /*  C = twototen(bit);*/
            C = (unsigned int)input[i];
            M = powmod(C, d, n);
            bit.clear();
        /*    tentotwo(M, bit, 8);*/
            output.push_back((char)M);
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