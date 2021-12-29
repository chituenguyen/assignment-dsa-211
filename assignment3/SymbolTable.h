#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"

typedef long long int khoa_;
typedef unsigned long long int khoa_so_;

bool luat_dinh_dang(string &st)
{

    if (st.length() > 0)
    {
        if (st[0] <= 96 || st[0] >= 123)
        {
            return false;
        }

        for (unsigned i = 1; i <= st.length() - 1; i++)
        {
            if (st[i] == '_')
            {
                continue;
            }
            else if (st[i] > 96 && st[i] < 123)
            {
                continue;
            }
            else if (st[i] > 64 && st[i] < 91)
            {
                continue;
            }
            else if (st[i] > 47 && st[i] < 58)
            {
                continue;
            }
            else
            {
                return false;
            }
        }

        return true;
    }

    return false;
}
int dem_khoang_trang(string &st, char d)
{
    int rs = 0;
    for (unsigned int i = 0; i <= st.length() - 1; i++)
    {
        if (st[i] == d)
            rs += 1;
    }
    return rs;
}

bool la_so(string st)
{
    return st.find_first_not_of("0123456789") == string::npos;
}
bool la_so_R(string &st)
{
    return st.find_first_not_of("0123456789") == string::npos;
}
int chuyen_doi_so_R(string &st)
{
    int rs = 0;
    for (unsigned i = 0; i <= st.size() - 1; i++)
    {
        int te = st[i] - 48;
        rs = rs * 10 + te;
    }
    return rs;
}
khoa_so_ chuyen_doi_key(string na, int le)
{
    if (le >= 0)
    {
        khoa_so_ rs = le;
        for (unsigned i = 0; i <= na.length() - 1; i++)
        {
            int ins_ = ((int)na[i]) - 48;
            int te = to_string(ins_).length();
            for (int i = 1; i < te + 1; i++)
            {
                rs = rs * 10;
            }
            rs = rs + ins_;
        }
        return rs;
    }
    else
    {
        return 0;
    }
}

bool dung_ham(string val)
{
    if (val.length() <= 2)
    {
        return false;
    }
    if ((val.find('(') == std::string::npos) || (val.find(')') == std::string::npos) || (val[val.length() - 1] != ')') || (dem_khoang_trang(val, '(') != 1) || (dem_khoang_trang(val, ')') != 1))
    {
        return false;
    }
    int nt = dem_khoang_trang(val, ',');
    int n1 = val.find('(');
    int n2 = val.find(')');
    if (nt != 0)
    {

        if (val[n1 + 1] == ',' || val[n2 - 1] == ',')
        {
            return false;
        }

        if (nt > 1)
        {
            for (int i = n1 + 1; i < n2; i++)
            {
                if (val[i] == ',' && val[i + 1] == ',')
                {
                    return false;
                }
            }
        }
    }

    int tmp = val.find('(');
    string id(val, 0, tmp);
    return luat_dinh_dang(id);
}
bool la_chu_R(string &st)
{
    if (st.length() < 2)
        return false;
    else if (st[0] != '\'' || st[st.length() - 1] != st[0])
        return false;

    for (unsigned i = 1; i < st.length() - 1; i++)
    {
        if (st[i] == ' ')
        {
            continue;
        }
        else if (st[i] > 47 && st[i] < 58)
        {
            continue;
        }
        else if (st[i] > 64 && st[i] <= 90)
        {
            continue;
        }
        else if (st[i] > 96 && st[i] <= 122)
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    return true;
}
int kiemtra_giatri(string val)
{

    if (la_so(val))
    {
        return 1;
    }
    else if (la_chu_R(val))
    {
        return 2;
    }
    else if (luat_dinh_dang(val))
    {
        return 3;
    }
    else if (dung_ham(val))
    {
        return 4;
    }
    else
    {
        return 0;
    }
}

class Nut
{
public:
    bool empty;
    string dinh_dang;
    int le;
    char kieu;
    int soluong_thamso;
    string dangky;
    Nut()
    {
        empty = true;
        dinh_dang.clear();
        le = 0;
        kieu = '#';
        soluong_thamso = 0;
        dangky.clear();
    }
};

class Hashing
{
public:
    Nut *bang_Hash;
    char phuongphap;
    int succhua;
    int soluong_symbol;
    int maxLoop;
    string bang_level;
    int c1;
    int c2;
    Hashing()
    {
        bang_Hash = NULL;
        phuongphap = '-';
        succhua = 0;
        soluong_symbol = 0;
        maxLoop = 0;
        bang_level.clear();
        c1 = 0;
        c2 = 0;
    }

    Hashing(char _probing, int _capacity, int _numofSymbol, int _c1 = 0, int _c2 = 0) : phuongphap(_probing), succhua(_capacity), soluong_symbol(_numofSymbol), maxLoop(0), bang_level(_numofSymbol, '-'), c1(_c1), c2(_c2) {}

    bool giaiphong_bonho()
    {
        if (bang_Hash == NULL)
        {
            return true;
        }
        else
        {
            delete[] bang_Hash;
            bang_Hash = NULL;
            this->bang_level.clear();

            return false;
        }
    }

protected:
    int h1(khoa_so_ key = 0)
    {
        return (int)(key % succhua);
    }

    int h2(khoa_so_ key = 0)
    {
        return 1 + (int)(key % (succhua - 2));
    }

public:
    int themvao_hash(khoa_so_ key, int &le, int &lo, string name = "")
    {
        if (phuongphap == 'D')
        {
            for (int i = 0; i <= succhua - 1; i++)
            {
                lo = i;
                if (bang_Hash[(h1(key) + c1 * i * h2(key)) % succhua].empty)
                {
                    bang_Hash[(h1(key) + c1 * i * h2(key)) % succhua].empty = false;
                    if (this->maxLoop <= lo - 1)
                    {

                        maxLoop = lo;
                    }
                    return (h1(key) + c1 * i * h2(key)) % succhua;
                }
                else if ((name.compare(bang_Hash[(h1(key) + c1 * i * h2(key)) % succhua].dinh_dang) == 0) && (le == bang_Hash[(h1(key) + c1 * i * h2(key)) % succhua].le))
                {
                    return -1;
                }
                else
                {
                    continue;
                }
            }
            return -2;
        }

        else if (this->phuongphap == 'L')
        {
            for (int i = 0; i <= succhua - 1; i++)
            {
                lo = i;
                if (bang_Hash[(h1(key) + c1 * i) % succhua].empty)
                {
                    bang_Hash[(h1(key) + c1 * i) % succhua].empty = false;
                    if (this->maxLoop <= lo - 1)
                    {

                        maxLoop = lo;
                    }

                    return (h1(key) + c1 * i) % succhua;
                }
                else if ((name.compare(bang_Hash[(h1(key) + c1 * i) % succhua].dinh_dang) == 0) && (le == bang_Hash[(h1(key) + c1 * i) % succhua].le))
                {
                    return -1;
                }
                else
                {
                    continue;
                }
            }
            return -2;
        }

        else
        {

            for (int i = 0; i < succhua; i++)
            {

                lo = i;
                if (bang_Hash[(h1(key) + c1 * i + c2 * i * i) % succhua].empty)
                {
                    bang_Hash[(h1(key) + c1 * i + c2 * i * i) % succhua].empty = !true;
                    if (this->maxLoop <= lo - 1)
                    {
                        maxLoop = i;
                    }
                    return (h1(key) + c1 * i + c2 * i * i) % succhua;
                }
                else if ((name.compare(bang_Hash[(h1(key) + c1 * i + c2 * i * i) % succhua].dinh_dang) == 0) && (le == bang_Hash[(h1(key) + c1 * i + c2 * i * i) % succhua].le))
                {
                    return -1;
                }
                else
                {
                    continue;
                }
            }

            return -2;
        }
    }

    int themvao_hash(khoa_so_ key, int &le, int &lo, int &at, string name = "")
    {
        if (this->phuongphap == 'D')
        {
            for (int i = 0; i < succhua; i++)
            {

                lo = i;

                if (bang_Hash[(h1(key) + c1 * i * h2(key)) % succhua].empty)
                {
                    bang_Hash[(h1(key) + c1 * i * h2(key)) % succhua].empty = false;
                    if (this->maxLoop <= lo - 1)
                    {
                        maxLoop = lo;
                    }
                    at = (h1(key) + c1 * i * h2(key)) % succhua;
                    return (h1(key) + c1 * i * h2(key)) % succhua;
                }
                else if ((name.compare(bang_Hash[(h1(key) + c1 * i * h2(key)) % succhua].dinh_dang) == 0) && (le == bang_Hash[(h1(key) + c1 * i * h2(key)) % succhua].le))
                {
                    at = (h1(key) + c1 * i * h2(key)) % succhua;
                    return -1;
                }
                else
                {
                    continue;
                }
            }
            return -2;
        }

        else if (this->phuongphap == 'L')
        {
            for (int i = 0; i < succhua; i++)
            {
                lo = i;
                if (bang_Hash[(h1(key) + c1 * i) % succhua].empty)
                {
                    bang_Hash[(h1(key) + c1 * i) % succhua].empty = false;
                    if (this->maxLoop <= lo - 1)
                    {
                        maxLoop = lo;
                    }
                    at = (h1(key) + c1 * i) % succhua;
                    return (h1(key) + c1 * i) % succhua;
                }
                else if ((name.compare(bang_Hash[(h1(key) + c1 * i) % succhua].dinh_dang) == 0) && (le == bang_Hash[(h1(key) + c1 * i) % succhua].le))
                {
                    at = (h1(key) + c1 * i) % succhua;
                    return -1;
                }
                else
                {
                    continue;
                }
            }
            return -2;
        }

        else
        {

            for (int i = 0; i < succhua; i++)
            {
                lo = i;
                if (bang_Hash[(h1(key) + c1 * i + c2 * i * i) % succhua].empty)
                {
                    bang_Hash[(h1(key) + c1 * i + c2 * i * i) % succhua].empty = false;
                    if (this->maxLoop < lo)
                    {

                        maxLoop = lo;
                    }
                    at = (h1(key) + c1 * i + c2 * i * i) % succhua;
                    return (h1(key) + c1 * i + c2 * i * i) % succhua;
                }
                else if ((name.compare(bang_Hash[(h1(key) + c1 * i + c2 * i * i) % succhua].dinh_dang) == 0) && (le == bang_Hash[(h1(key) + c1 * i + c2 * i * i) % succhua].le))
                {
                    at = (h1(key) + c1 * i + c2 * i * i) % succhua;
                    return -1;
                }
                else
                {
                    continue;
                }
            }

            return -2;
        }
    }

    int xoa_iden_cung_le(int &le);

    int timkiem_linear(string na, int &le);

    int timkiem_double(string na, int &le);

    int timkiem_quadratic(string na, int &le);

    int ham_timkiem(string na, int &le);
    int timkiem_linear(string name, int &le, int &lo)
    {
        int rs = this->maxLoop;
        int save = le;
        for (; le >= 0; le--)
        {

            khoa_so_ key = chuyen_doi_key(name, le);
            int h_k = h1(key);
            for (int j = 0; j < rs + 1; j++)
            {
                lo = j;
                int h_p = (h_k + c1 * j) % succhua;
                if ((bang_Hash[h_p].empty == false) && (le == bang_Hash[h_p].le) && (name.compare(bang_Hash[h_p].dinh_dang) == 0))
                {
                    le = save;
                    return h_p;
                }
            }
        }

        return -1;
    }
    int timkiem_double(string name, int &le, int &lo)
    {
        int muc_tam = le;
        int mxloop = this->maxLoop;
        int save = le;
        for (int i = muc_tam; i > -1; i--)
        {
            le = i;
            khoa_so_ key = chuyen_doi_key(name, i);

            for (unsigned j = mxloop; j >= 0; j--)
            {
                lo = j;
                if ((bang_Hash[(h1(key) + c1 * j * h2(key)) % succhua].empty == false) && (le == bang_Hash[(h1(key) + c1 * j * h2(key)) % succhua].le) && (name.compare(bang_Hash[(h1(key) + c1 * j * h2(key)) % succhua].dinh_dang) == 0))
                {
                    le = save;
                    return (h1(key) + c1 * j * h2(key)) % succhua;
                }
                else
                {
                    continue;
                }
            }
        }
        return -1;
    }
    int timkiem_quadratic(string name, int &le, int &lo)
    {
        int muc_tam = le;
        int mxloop = this->maxLoop;
        int save = le;
        for (unsigned i = muc_tam; i >= 0; i--)
        {
            le = i;
            khoa_so_ key = chuyen_doi_key(name, i);
            for (int j = 0; j <= mxloop; j++)
            {
                lo = j;
                if ((bang_Hash[(h1(key) + c1 * j + c2 * j * j) % succhua].empty == false) && (le == bang_Hash[(h1(key) + c1 * j + c2 * j * j) % succhua].le) && (name.compare(bang_Hash[(h1(key) + c1 * j + c2 * j * j) % succhua].dinh_dang) == 0))
                {
                    le = save;
                    return (h1(key) + c1 * j + c2 * j * j) % succhua;
                }
            }
        }
        return -1;
    }
    int ham_timkiem(string name, int &le, int &lo)
    {
        if (this->phuongphap == 'Q')
        {
            return timkiem_quadratic(name, le, lo);
        }
        else if (this->phuongphap == 'D')
        {
            return timkiem_double(name, le, lo);
        }
        else
        {
            return timkiem_linear(name, le, lo);
        }
    }
};

class SymbolTable
{
public:
    SymbolTable() {}
    void run(string filename);
};

#endif
