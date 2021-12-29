#include "SymbolTable.h"

int Hashing ::xoa_iden_cung_le(int &le)
{
    int rs = 0;
    char lete = le + 48;
    size_t fou = this->bang_level.find_first_of(lete, 0);
    while (fou != std::string::npos)
    {
        rs += 1;
        bang_Hash[fou].empty = true;
        bang_Hash[fou].dinh_dang.clear();
        bang_Hash[fou].le = 0;
        bang_Hash[fou].kieu = '#';
        bang_Hash[fou].soluong_thamso = 0;
        bang_Hash[fou].dangky.clear();
        bang_level[fou] = '-';
        fou = bang_level.find_first_of(lete, fou + 1);
        soluong_symbol = soluong_symbol - 1;
    }

    return rs;
}

int Hashing ::timkiem_linear(string na, int &le)
{
    for (; le > -1; le--)
    {
        khoa_so_ k = chuyen_doi_key(na, le);
        for (int j = 0; j < this->maxLoop + 1; j++)
        {
            int rs = (h1(k) + c1 * j) % succhua;
            if ((bang_Hash[rs].empty == false) && (le == bang_Hash[rs].le) && (na.compare(bang_Hash[rs].dinh_dang) == 0))
            {
                return rs;
            }
        }
    }
    return -1;
}

int Hashing ::timkiem_double(string na, int &le)
{
    for (int i = le; i > -1; i--)
    {
        le = i;
        khoa_so_ k = chuyen_doi_key(na, i);

        for (int j = this->maxLoop; j > -1; j--)
        {
            int rs = (h1(k) + c1 * j * h2(k)) % succhua;
            if ((bang_Hash[rs].empty == false) && (le == bang_Hash[rs].le) && (na.compare(bang_Hash[rs].dinh_dang) == 0))
            {
                return rs;
            }
            else
            {
                continue;
            }
        }
    }
    return -1;
}

int Hashing ::timkiem_quadratic(string na, int &le)
{
    for (int i = le; i > -1; i--)
    {
        le = i;
        khoa_so_ k = chuyen_doi_key(na, i);
        for (int j = 0; j < this->maxLoop + 1; j++)
        {
            int rs = (h1(k) + c1 * j + c2 * j * j) % succhua;
            if ((bang_Hash[rs].empty == false) && (le == bang_Hash[rs].le) && (na.compare(bang_Hash[rs].dinh_dang) == 0))
            {
                return rs;
            }
        }
    }
    return -1;
}
int Hashing ::ham_timkiem(string na, int &le)
{
    if (this->phuongphap == 'Q')
    {
        return timkiem_quadratic(na, le);
    }
    else if (this->phuongphap == 'D')
    {
        return timkiem_double(na, le);
    }
    else
    {
        return timkiem_linear(na, le);
    }
}

bool kiemtra_cauhinh(string &sosanh, int (&sosan)[4])
{
    if (sosanh[0] == ' ' || sosanh[sosanh.length() - 1] == ' ')
    {
        return false;
    }

    int ns = dem_khoang_trang(sosanh, ' ');

    if (ns != 2 && ns != 3)
    {

        return false;
    }

    int temp1 = sosanh.find_first_of(' ');
    int temp2 = sosanh.find_first_of(' ', temp1 + 1 - 1 + 1);

    if ((temp1 + 1) == temp2)
    {

        return false;
    }

    if (ns == 3)
    {
        int temp3 = sosanh.find_first_of(' ', temp2 + 1 - 1 + 1);
        if ((temp2 + 1 - 1 + 1) == temp3)
        {

            return false;
        }
        else
        {
            if (sosanh.compare(0, temp1, "QUADRATIC") == 0)
            {
                string cmmm = sosanh.substr(0, temp1);
                string m = sosanh.substr(temp1 + 1, temp2 - temp1 - 1);
                string c1 = sosanh.substr(temp2 + 1, temp3 - temp2 - 1);
                string c2 = sosanh.substr(temp3 + 1);
                bool vs = false;
                if (cmmm.compare("QUADRATIC") == 0)
                {
                    vs = true;
                }
                vs = vs && la_so(m) && la_so(c1) && la_so(c2) && (m.length() <= 6) && (c1.length() <= 6) && (c2.length() <= 6);
                if (!vs)
                {
                    return false;
                }
                char temp_c = 'Q';
                sosan[0] = (int)temp_c;
                sosan[1] = chuyen_doi_so_R(m);
                sosan[2] = chuyen_doi_so_R(c1);
                sosan[3] = chuyen_doi_so_R(c2);
            }
        }
    }

    if (ns == 2)
    {
        string cmmm = sosanh.substr(0, temp1);
        bool vs = false;
        if (cmmm.compare("LINEAR") == 0 || cmmm.compare("DOUBLE") == 0)
        {

            vs = true;
        }
        string m = sosanh.substr(temp1 + 1, temp2 - temp1 - 1);
        string c = sosanh.substr(temp2 + 1);
        vs = vs && la_so(m) && la_so(c) && (c.length() <= 6) && (m.length() <= 6);
        if (!vs)
        {
            return false;
        }

        char temp_c = (cmmm[0] == 'L') ? 'L' : 'D';
        sosan[0] = (int)temp_c;
        sosan[1] = chuyen_doi_so_R(m);
        sosan[2] = chuyen_doi_so_R(c);
    }

    return true;
}
bool kiemtra_yeucau(string caulenh, string (&tphan)[3], int &soluong_thanhphan)
{

    if (dem_khoang_trang(caulenh, ' ') != 0)
    {
        string cmd(caulenh, 0, caulenh.find(' '));
        if (cmd.compare("ASSIGN") == 0)
        {
            string id(caulenh, caulenh.find(' ') + 1, caulenh.find(' ', caulenh.find(' ') + 1) - caulenh.find(' ') - 1);
            if (luat_dinh_dang(id))
            {
                string value(caulenh, caulenh.find(' ', caulenh.find(' ') + 1) + 1);
                tphan[0] = cmd;
                tphan[1] = id;
                tphan[2] = value;
                soluong_thanhphan = 3;
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (cmd.compare("CALL") == 0)
        {
            tphan[0] = cmd;
            if (caulenh.find_first_of('(') <= caulenh.find(' ') + 1)
            {
                return false;
            }
            string id = caulenh.substr(caulenh.find(' ') + 1, caulenh.find_first_of('(') - caulenh.find(' ') - 1);
            if (luat_dinh_dang(id))
            {
                tphan[1] = caulenh.substr(caulenh.find(' ') + 1);
                soluong_thanhphan = 2;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    if (dem_khoang_trang(caulenh, ' ') >= 3)
    {
        return false;
    }
    if (dem_khoang_trang(caulenh, ' ') == 0)
    {
        if (caulenh.compare("BEGIN") == 0)
        {
            tphan[0] = caulenh;
            soluong_thanhphan = 1;
            return true;
        }
        else if (caulenh.compare("END") == 0)
        {
            tphan[0] = caulenh;
            soluong_thanhphan = 1;
            return true;
        }
        else if (caulenh.compare("PRINT") == 0)
        {
            tphan[0] = caulenh;
            soluong_thanhphan = 1;
            return true;
        }
        else
        {
            return false;
        }
    }
    if (caulenh[0] == ' ' || caulenh[caulenh.length() - 1] == ' ')
    {
        return false;
    }

    if (dem_khoang_trang(caulenh, ' ') == 1)
    {
        string cmd_temp = caulenh.substr(0, caulenh.find_first_of(' '));
        if ((cmd_temp.compare("INSERT") == 0) || (cmd_temp.compare("LOOKUP") == 0))
        {
            string iden_temp = caulenh.substr(caulenh.find_first_of(' ') + 1);
            if (luat_dinh_dang(iden_temp))
            {
                tphan[0] = cmd_temp;
                tphan[1] = caulenh.substr(caulenh.find_first_of(' ') + 1);
                soluong_thanhphan = 2;
                return true;
            }

            return false;
        }
        else
        {
            return false;
        }
    }
    else if (dem_khoang_trang(caulenh, ' ') == 2)
    {
        string cmd_temp = caulenh.substr(0, caulenh.find_first_of(' '));
        if (cmd_temp.compare("INSERT") == 0)
        {
            string iden_temp = caulenh.substr(caulenh.find_first_of(' ') + 1, caulenh.find_last_of(' ') - caulenh.find_first_of(' ') - 1);
            if (luat_dinh_dang(iden_temp))
            {
                string value = caulenh.substr(caulenh.find_last_of(' ') + 1);
                if (la_so_R(value))
                {
                    tphan[0] = cmd_temp;
                    tphan[1] = iden_temp;
                    tphan[2] = value;
                    soluong_thanhphan = 3;
                    return true;
                }
                return false;
            }
            return false;
        }
        return false;
    }
    return false;
}
int so_luong_arg(string st)
{
    int rs = 0;
    int tmp = dem_khoang_trang(st, ',');

    if (st.find('(') + 1 != st.find_last_of(')'))
    {
        rs = tmp + 1;
    }

    return rs;
}
string chuky_bandau(int pr)
{
    if (pr == 0)
    {
        return "#()";
    }
    else if (pr == 1)
    {
        return "#(#)";
    }
    else if (pr == 2)
    {
        return "#(#,#)";
    }
    else if (pr >= 3)
    {
        string tmp = "#(#";
        for (int i = 1; i <= pr - 1; i++)
        {
            tmp.append(",#");
        }
        tmp.push_back(')');
        return tmp;
    }
    return "";
}
void SymbolTable::run(string filename)
{
    fstream myFile;
    myFile.open(filename, ios::in);
    string dong;
    bool bien_bandau = true;
    int level_dautien = 0;
    Hashing hashing;
    while (getline(myFile, dong))
    {
        if (bien_bandau)
        {
            bien_bandau = false;
            int cauhinh[4];
            if (!kiemtra_cauhinh(dong, cauhinh))
            {
                InvalidInstruction loicuphap(dong);
                throw InvalidInstruction(dong);
            }
            if (cauhinh[0] == 'Q')
            {

                hashing.phuongphap = cauhinh[0];
                hashing.succhua = cauhinh[1];
                hashing.bang_level.assign(hashing.succhua, '-');
                hashing.c1 = cauhinh[2];
                hashing.c2 = cauhinh[3];
                hashing.bang_Hash = new Nut[hashing.succhua];
            }
            else
            {
                hashing.phuongphap = cauhinh[0];
                hashing.succhua = cauhinh[1];
                hashing.bang_level.assign(hashing.succhua, '-');
                hashing.c1 = cauhinh[2];
                hashing.bang_Hash = new Nut[hashing.succhua];
            }
        }
        else
        {
            string thanh_phan[3];
            int soluong_thanhphan = 0;

            if (kiemtra_yeucau(dong, thanh_phan, soluong_thanhphan))
            {

                if (thanh_phan[0].compare("LOOKUP") == 0)
                {
                    int loop = 0;
                    int slot_find = hashing.ham_timkiem(thanh_phan[1], level_dautien, loop);
                    if (slot_find == -1)
                    {
                        myFile.close();
                        hashing.giaiphong_bonho();
                    }
                    else
                    {
                        cout << slot_find << endl;
                    }
                }
                else if (thanh_phan[0].compare("INSERT") == 0)
                {
                    if (soluong_thanhphan == 2)
                    {
                        string dinhdangcuanut(thanh_phan[1]);
                        int muc_cua_nut = level_dautien;
                        khoa_so_ key_cua_nut = chuyen_doi_key(dinhdangcuanut, muc_cua_nut);
                        int loop = 0;
                        int ref = 0;
                        int kiemTra = hashing.themvao_hash(key_cua_nut, muc_cua_nut, loop, ref, thanh_phan[1]);
                        if (kiemTra >= 0)
                        {
                            hashing.bang_Hash[kiemTra].dinh_dang = thanh_phan[1];
                            hashing.bang_Hash[kiemTra].le = level_dautien;
                            hashing.bang_Hash[kiemTra].kieu = '#';
                            hashing.bang_Hash[kiemTra].soluong_thamso = 0;
                            hashing.bang_level[kiemTra] = ((char)(level_dautien + 48));
                            cout << loop << endl;
                            hashing.soluong_symbol += 1;
                        }
                        else if (kiemTra == -1)
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();

                            Redeclared loi_khaibaolai(thanh_phan[1]);
                            throw Redeclared(thanh_phan[1]);
                        }
                    }
                    else
                    {
                        if (level_dautien != 0)
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();
                        }
                        string dinhdangcuanut(thanh_phan[1]);
                        khoa_so_ key_cua_nut = chuyen_doi_key(dinhdangcuanut, level_dautien);
                        int loop = 0;
                        int ref = 0;
                        int kiemTra = hashing.themvao_hash(key_cua_nut, level_dautien, loop, ref, thanh_phan[1]);
                        if (kiemTra >= 0)
                        {
                            hashing.bang_Hash[kiemTra].dinh_dang = thanh_phan[1];
                            hashing.bang_Hash[kiemTra].le = level_dautien;
                            hashing.bang_Hash[kiemTra].kieu = 'F';
                            hashing.bang_Hash[kiemTra].soluong_thamso = chuyen_doi_so_R(thanh_phan[2]);
                            hashing.bang_Hash[kiemTra].dangky = chuky_bandau(hashing.bang_Hash[kiemTra].soluong_thamso);
                            hashing.bang_level[kiemTra] = ((char)(level_dautien + 48));
                            cout << loop << endl;
                            hashing.soluong_symbol += 1;
                        }
                        else if (kiemTra == -1)
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();
                            Redeclared loi_khaibaolai(thanh_phan[1]);
                            throw Redeclared(thanh_phan[1]);
                        }
                    }
                }

                else if (thanh_phan[0].compare("CALL") == 0)
                {

                    if (kiemtra_giatri(thanh_phan[1]) == 4)
                    {
                        int chieudai_name = thanh_phan[1].find('(');
                        string ten_ham(thanh_phan[1], 0, chieudai_name);
                        int muc_cua_ham = level_dautien;
                        int lap_ham = 0;
                        int tong_lap = 0;
                        int chotrong_cuaham = hashing.ham_timkiem(ten_ham, muc_cua_ham, lap_ham);
                        if (chotrong_cuaham == -1)
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();

                            Undeclared loi_da_khaibao(ten_ham);
                            throw Undeclared(ten_ham);
                        }

                        if (hashing.bang_Hash[chotrong_cuaham].kieu != 'F')
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();
                            TypeMismatch loi_khonghople(dong);
                            throw TypeMismatch(dong);
                        }

                        int soluong_thamso = hashing.bang_Hash[chotrong_cuaham].soluong_thamso;
                        int soluong_thamso_R = so_luong_arg(thanh_phan[1]);

                        if (soluong_thamso_R != soluong_thamso)
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();
                            TypeMismatch loi_khonghople(dong);
                            throw TypeMismatch(dong);
                        }
                        else if (hashing.bang_Hash[chotrong_cuaham].soluong_thamso == 1)
                        {
                            int thamso_dautien = thanh_phan[1].find('(');
                            int thamso_cuoicung = thanh_phan[1].find(')');
                            string argument(thanh_phan[1], thamso_dautien + 1, thamso_cuoicung - thamso_dautien - 1);

                            if (kiemtra_giatri(argument) == 1 || kiemtra_giatri(argument) == 2)
                            {
                                if (hashing.bang_Hash[chotrong_cuaham].dangky[2] == '#')
                                {
                                    hashing.bang_Hash[chotrong_cuaham].dangky[2] = (kiemtra_giatri(argument) == 1) ? 'N' : 'S';
                                }

                                else
                                {
                                    myFile.close();
                                    hashing.giaiphong_bonho();
                                    TypeMismatch loi_khonghople(dong);
                                    throw TypeMismatch(dong);
                                }
                            }

                            else if (kiemtra_giatri(argument) == 3)
                            {
                                // int le_dinhdang = level_dautien;
                                int loop_arg = 0;
                                int chotrongdatim = hashing.ham_timkiem(argument, level_dautien, loop_arg);
                                if (hashing.ham_timkiem(argument, level_dautien, loop_arg) == -1)
                                {
                                    myFile.close();
                                    hashing.giaiphong_bonho();

                                    Undeclared loi_da_khaibao(argument);
                                    throw Undeclared(argument);
                                }

                                if (hashing.bang_Hash[chotrongdatim].kieu == 'F')
                                {
                                    myFile.close();
                                    hashing.giaiphong_bonho();
                                    TypeMismatch loi_khonghople(dong);
                                    throw TypeMismatch(dong);
                                }

                                // char kieuthamso = hashing.bang_Hash[chotrongdatim].kieu;
                                if (hashing.bang_Hash[chotrongdatim].kieu == 'N' || hashing.bang_Hash[chotrongdatim].kieu == 'S')
                                {
                                    if (hashing.bang_Hash[chotrong_cuaham].dangky[2] == '#')
                                    {
                                        hashing.bang_Hash[chotrong_cuaham].dangky[2] = (hashing.bang_Hash[chotrongdatim].kieu == 'N') ? 'N' : 'S';
                                    }

                                    else
                                    {
                                        myFile.close();
                                        hashing.giaiphong_bonho();

                                        TypeMismatch loi_khonghople(dong);
                                        throw TypeMismatch(dong);
                                    }
                                }
                                else if (hashing.bang_Hash[chotrongdatim].kieu == '#')
                                {
                                    if (hashing.bang_Hash[chotrong_cuaham].dangky[2] == '#')
                                    {
                                        myFile.close();
                                        hashing.giaiphong_bonho();
                                        TypeCannotBeInferred loi_type(dong);
                                        throw TypeCannotBeInferred(dong);
                                    }
                                    else
                                    {
                                        hashing.bang_Hash[chotrongdatim].kieu = hashing.bang_Hash[chotrong_cuaham].dangky[2];
                                    }
                                }
                                tong_lap += loop_arg;
                            }
                        }

                        else if (hashing.bang_Hash[chotrong_cuaham].soluong_thamso >= 2)
                        {
                            // int thamso_dautien = thanh_phan[1].find('(');
                            int yeucau_1 = thanh_phan[1].find(',');
                            int yeucau_2 = yeucau_1;
                            int thamso_cuoicung = thanh_phan[1].find(')');
                            string *mang_doi_so = new string[soluong_thamso_R];
                            for (int i = 0; i < soluong_thamso_R; i++)
                            {
                                if (i == 0)
                                {
                                    mang_doi_so[i] = thanh_phan[1].substr(thanh_phan[1].find('(') + 1, yeucau_2 - thanh_phan[1].find('(') - 1);
                                    continue;
                                }
                                else if (i == soluong_thamso_R - 1)
                                {
                                    mang_doi_so[i] = thanh_phan[1].substr(yeucau_2 + 1, thamso_cuoicung - yeucau_2 - 1);
                                    continue;
                                }
                                yeucau_1 = yeucau_2;
                                yeucau_2 = thanh_phan[1].find(',', yeucau_2 + 1);
                                mang_doi_so[i] = thanh_phan[1].substr(yeucau_1 + 1, yeucau_2 - yeucau_1 - 1);
                            }

                            for (int i = 0; i < soluong_thamso_R; i++)
                            {
                                if (kiemtra_giatri(mang_doi_so[i]) == 1 || kiemtra_giatri(mang_doi_so[i]) == 2)
                                {
                                    if (hashing.bang_Hash[chotrong_cuaham].dangky[2 * i + 2] == '#')
                                    {
                                        hashing.bang_Hash[chotrong_cuaham].dangky[2 * i + 2] = (kiemtra_giatri(mang_doi_so[i]) == 1) ? 'N' : 'S';
                                    }

                                    else
                                    {
                                        myFile.close();
                                        delete[] mang_doi_so;
                                        hashing.giaiphong_bonho();

                                        TypeMismatch loi_khonghople(dong);
                                        throw TypeMismatch(dong);
                                    }
                                }

                                else if (kiemtra_giatri(mang_doi_so[i]) == 3)
                                {
                                    int muc_thamso_datim = level_dautien;
                                    int lap_thamso_i = 0;
                                    int chotrong_thamso_datim = hashing.ham_timkiem(mang_doi_so[i], muc_thamso_datim, lap_thamso_i);
                                    if (chotrong_thamso_datim == -1)
                                    {
                                        myFile.close();
                                        hashing.giaiphong_bonho();

                                        string mang_tam = mang_doi_so[i];
                                        delete[] mang_doi_so;
                                        Undeclared loi_da_khaibao(mang_tam);
                                        throw Undeclared(mang_tam);
                                    }
                                    if (hashing.bang_Hash[chotrong_thamso_datim].kieu == 'F')
                                    {
                                        myFile.close();
                                        delete[] mang_doi_so;
                                        hashing.giaiphong_bonho();

                                        TypeMismatch loi_khonghople(dong);
                                        throw TypeMismatch(dong);
                                    }

                                    // char kieuthamso_ = hashing.bang_Hash[chotrong_thamso_datim].kieu;
                                    if (hashing.bang_Hash[chotrong_thamso_datim].kieu == 'N' || hashing.bang_Hash[chotrong_thamso_datim].kieu == 'S')
                                    {
                                        if (hashing.bang_Hash[chotrong_cuaham].dangky[2 * i + 2] == '#')
                                        {
                                            hashing.bang_Hash[chotrong_cuaham].dangky[2 * i + 2] = (hashing.bang_Hash[chotrong_thamso_datim].kieu == 'N') ? 'N' : 'S';
                                        }

                                        else
                                        {
                                            myFile.close();
                                            hashing.giaiphong_bonho();

                                            delete[] mang_doi_so;
                                            TypeMismatch loi_khonghople(dong);
                                            throw TypeMismatch(dong);
                                        }
                                    }

                                    else if (hashing.bang_Hash[chotrong_thamso_datim].kieu == '#')
                                    {
                                        if (hashing.bang_Hash[chotrong_cuaham].dangky[2 * i + 2] == '#')
                                        {
                                            myFile.close();
                                            hashing.giaiphong_bonho();

                                            delete[] mang_doi_so;
                                            TypeCannotBeInferred loi_type(dong);
                                            throw TypeCannotBeInferred(dong);
                                        }
                                        else
                                        {
                                            hashing.bang_Hash[chotrong_thamso_datim].kieu = hashing.bang_Hash[chotrong_cuaham].dangky[2 * i + 2];
                                        }
                                    }
                                    tong_lap += lap_thamso_i;
                                }
                            }
                        }

                        if (hashing.bang_Hash[chotrong_cuaham].dangky[0] == '#')
                        {
                            hashing.bang_Hash[chotrong_cuaham].dangky[0] = 'V';
                        }
                        else
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();
                            TypeMismatch loi_khonghople(dong);
                            throw TypeMismatch(dong);
                        }
                        tong_lap += lap_ham;
                        cout << tong_lap << endl;
                    }
                    else
                    {
                        myFile.close();
                        hashing.giaiphong_bonho();

                        InvalidInstruction loicuphap(dong);
                        throw InvalidInstruction(dong);
                    }
                }
                else if (thanh_phan[0].compare("ASSIGN") == 0)
                {
                    int tong_lap = 0;
                    int rs = 0;
                    if (la_so(thanh_phan[2]))
                    {
                        rs = 1;
                    }
                    else if (la_chu_R(thanh_phan[2]))
                    {
                        rs = 2;
                    }
                    else if (luat_dinh_dang(thanh_phan[2]))
                    {
                        rs = 3;
                    }
                    else if (dung_ham(thanh_phan[2]))
                    {
                        rs = 4;
                    }
                    else
                    {
                        rs = 0;
                    }
                    int kieu_value = rs;

                    if (kieu_value == 1 || kieu_value == 2)
                    {
                        int level_da_timkiem = level_dautien;
                        int loop = 0;
                        int chotrongdatim = hashing.ham_timkiem(thanh_phan[1], level_da_timkiem, loop);
                        tong_lap = loop;

                        if (hashing.ham_timkiem(thanh_phan[1], level_da_timkiem, loop) == -1)
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();
                            Undeclared loi_da_khaibao(thanh_phan[1]);
                            throw Undeclared(thanh_phan[1]);
                        }

                        if (hashing.bang_Hash[chotrongdatim].kieu == '#')
                        {
                            hashing.bang_Hash[chotrongdatim].kieu = (kieu_value == 1) ? 'N' : 'S';
                        }

                        cout << tong_lap << endl;
                    }

                    else if (kieu_value == 4)
                    {
                        int chieudai_name = thanh_phan[2].find('(');
                        string ten_ham(thanh_phan[2], 0, chieudai_name);
                        int lap_ham = 0;
                        int chotrong_cuaham = hashing.ham_timkiem(ten_ham, level_dautien, lap_ham);

                        if (chotrong_cuaham == -1)
                        {
                            myFile.close();

                            hashing.giaiphong_bonho();
                            Undeclared loi_da_khaibao(ten_ham);
                            throw Undeclared(ten_ham);
                        }
                        if (hashing.bang_Hash[chotrong_cuaham].kieu != 'F')
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();
                            TypeMismatch loi_khonghople(dong);
                            throw TypeMismatch(dong);
                        }
                        int soluong_thamso_R = so_luong_arg(thanh_phan[2]);
                        if (soluong_thamso_R != hashing.bang_Hash[chotrong_cuaham].soluong_thamso)
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();
                            TypeMismatch loi_khonghople(dong);
                            throw TypeMismatch(dong);
                        }

                        else if (hashing.bang_Hash[chotrong_cuaham].soluong_thamso == 1)
                        {
                            int thamso_dautien = thanh_phan[2].find('(');
                            int thamso_cuoicung = thanh_phan[2].find(')');
                            string argument(thanh_phan[2], thamso_dautien + 1, thamso_cuoicung - thamso_dautien - 1);

                            int kieuthamso = kiemtra_giatri(argument);
                            if (kieuthamso == 1 || kieuthamso == 2)
                            {
                                if (hashing.bang_Hash[chotrong_cuaham].dangky[2] == '#')
                                {
                                    hashing.bang_Hash[chotrong_cuaham].dangky[2] = (kieuthamso == 1) ? 'N' : 'S';
                                }
                            }

                            else if (kieuthamso == 3)
                            {
                                int le_dinhdang = level_dautien;
                                int loop_arg = 0;
                                int chotrongdatim = hashing.ham_timkiem(argument, le_dinhdang, loop_arg);
                                if (chotrongdatim == -1)
                                {
                                    myFile.close();
                                    hashing.giaiphong_bonho();

                                    Undeclared loi_da_khaibao(argument);
                                    throw Undeclared(argument);
                                }

                                if (hashing.bang_Hash[chotrongdatim].kieu == 'F')
                                {
                                    myFile.close();
                                    hashing.giaiphong_bonho();

                                    TypeMismatch loi_khonghople(dong);
                                    throw TypeMismatch(dong);
                                }

                                char kieuthamso = hashing.bang_Hash[chotrongdatim].kieu;
                                if (kieuthamso == 'N' || kieuthamso == 'S')
                                {
                                    if (hashing.bang_Hash[chotrong_cuaham].dangky[2] == '#')
                                    {
                                        hashing.bang_Hash[chotrong_cuaham].dangky[2] = (kieuthamso == 'N') ? 'N' : 'S';
                                    }

                                    else
                                    {
                                        myFile.close();
                                        hashing.giaiphong_bonho();
                                    }
                                }
                                else if (kieuthamso == '#')
                                {
                                    if (hashing.bang_Hash[chotrong_cuaham].dangky[2] == '#')
                                    {
                                        myFile.close();
                                        hashing.giaiphong_bonho();
                                        TypeCannotBeInferred loi_type(dong);
                                        throw TypeCannotBeInferred(dong);
                                    }
                                    else
                                    {
                                        hashing.bang_Hash[chotrongdatim].kieu = hashing.bang_Hash[chotrong_cuaham].dangky[2];
                                    }
                                }

                                tong_lap += loop_arg;
                            }

                            else if (kieuthamso == 4)
                            {
                                myFile.close();
                                hashing.giaiphong_bonho();
                                InvalidInstruction loicuphap(dong);
                                throw InvalidInstruction(dong);
                            }
                        }

                        else if (hashing.bang_Hash[chotrong_cuaham].soluong_thamso >= 2)
                        {
                            int thamso_dautien = thanh_phan[2].find('(');
                            int yeucau_1 = thanh_phan[2].find(',');
                            int yeucau_2 = yeucau_1;
                            int thamso_cuoicung = thanh_phan[2].find(')');
                            string *mang_doi_so = new string[soluong_thamso_R];
                            for (int i = 0; i < soluong_thamso_R; i++)
                            {
                                if (i == 0)
                                {
                                    mang_doi_so[i] = thanh_phan[2].substr(thamso_dautien + 1, yeucau_2 - thamso_dautien - 1);
                                    continue;
                                }
                                else if (i == soluong_thamso_R - 1)
                                {
                                    mang_doi_so[i] = thanh_phan[2].substr(yeucau_2 + 1, thamso_cuoicung - yeucau_2 - 1);
                                    continue;
                                }
                                yeucau_1 = yeucau_2;
                                yeucau_2 = thanh_phan[2].find(',', yeucau_2 + 1);
                                mang_doi_so[i] = thanh_phan[2].substr(yeucau_1 + 1, yeucau_2 - yeucau_1 - 1);
                            }

                            for (int i = 0; i < soluong_thamso_R; i++)
                            {
                                int kieuthamso = kiemtra_giatri(mang_doi_so[i]);

                                if (kieuthamso == 1 || kieuthamso == 2)
                                {
                                    if (hashing.bang_Hash[chotrong_cuaham].dangky[2 * i + 2] == '#')
                                    {
                                        hashing.bang_Hash[chotrong_cuaham].dangky[2 * i + 2] = (kieuthamso == 1) ? 'N' : 'S';
                                    }

                                    else
                                    {
                                        myFile.close();
                                        hashing.giaiphong_bonho();
                                        delete[] mang_doi_so;
                                        TypeMismatch loi_khonghople(dong);
                                        throw TypeMismatch(dong);
                                    }
                                }

                                else if (kieuthamso == 3)
                                {
                                    int muc_thamso_datim = level_dautien;
                                    int lap_thamso_i = 0;
                                    int chotrong_thamso_datim = hashing.ham_timkiem(mang_doi_so[i], muc_thamso_datim, lap_thamso_i);
                                    if (chotrong_thamso_datim == -1)
                                    {
                                        myFile.close();
                                        hashing.giaiphong_bonho();

                                        string mang_tam = mang_doi_so[i];
                                        delete[] mang_doi_so;
                                        Undeclared loi_da_khaibao(mang_tam);
                                        throw Undeclared(mang_tam);
                                    }
                                    if (hashing.bang_Hash[chotrong_thamso_datim].kieu == 'F')
                                    {
                                        myFile.close();
                                        delete[] mang_doi_so;
                                        hashing.giaiphong_bonho();

                                        TypeMismatch loi_khonghople(dong);
                                        throw TypeMismatch(dong);
                                    }

                                    char kieuthamso_ = hashing.bang_Hash[chotrong_thamso_datim].kieu;
                                    if (kieuthamso_ == 'N' || kieuthamso_ == 'S')
                                    {
                                        if (hashing.bang_Hash[chotrong_cuaham].dangky[2 * i + 2] == '#')
                                        {
                                            hashing.bang_Hash[chotrong_cuaham].dangky[2 * i + 2] = (kieuthamso_ == 'N') ? 'N' : 'S';
                                        }

                                        else
                                        {
                                            myFile.close();
                                            hashing.giaiphong_bonho();
                                            delete[] mang_doi_so;
                                            TypeMismatch loi_khonghople(dong);
                                            throw TypeMismatch(dong);
                                        }
                                    }

                                    else if (kieuthamso_ == '#')
                                    {
                                        if (hashing.bang_Hash[chotrong_cuaham].dangky[2 * i + 2] == '#')
                                        {
                                            myFile.close();
                                            hashing.giaiphong_bonho();
                                            delete[] mang_doi_so;
                                            TypeCannotBeInferred loi_type(dong);
                                            throw TypeCannotBeInferred(dong);
                                        }
                                        else
                                        {
                                            hashing.bang_Hash[chotrong_thamso_datim].kieu = hashing.bang_Hash[chotrong_cuaham].dangky[2 * i + 2];
                                        }
                                    }
                                    tong_lap += lap_thamso_i;
                                }
                                else if (kieuthamso == 4)
                                {
                                    myFile.close();
                                    hashing.giaiphong_bonho();
                                    delete[] mang_doi_so;
                                    InvalidInstruction loicuphap(dong);
                                    throw InvalidInstruction(dong);
                                }
                            }
                        }

                        int le_dinhdang = level_dautien;
                        int loop_id = 0;
                        int chotrongdatim = hashing.ham_timkiem(thanh_phan[1], le_dinhdang, loop_id);
                        if (chotrongdatim == -1)
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();

                            Undeclared loi_da_khaibao(thanh_phan[1]);
                            throw Undeclared(thanh_phan[1]);
                        }

                        if (hashing.bang_Hash[chotrongdatim].kieu == 'F')
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();

                            TypeMismatch loi_khonghople(dong);
                            throw TypeMismatch(dong);
                        }

                        char ham_kieu_dangky = hashing.bang_Hash[chotrong_cuaham].dangky[0];
                        char dinhdang_kieu_dangky = hashing.bang_Hash[chotrongdatim].kieu;
                        if (ham_kieu_dangky == dinhdang_kieu_dangky && dinhdang_kieu_dangky == '#')
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();
                            TypeCannotBeInferred loi_type(dong);
                            throw TypeCannotBeInferred(dong);
                        }

                        else if (dinhdang_kieu_dangky == '#' && ham_kieu_dangky != '#' && ham_kieu_dangky != 'V')
                        {
                            hashing.bang_Hash[chotrongdatim].kieu = hashing.bang_Hash[chotrong_cuaham].dangky[0];
                        }
                        else if (ham_kieu_dangky == '#' && dinhdang_kieu_dangky != '#' && dinhdang_kieu_dangky != 'F')
                        {
                            hashing.bang_Hash[chotrong_cuaham].dangky[0] = hashing.bang_Hash[chotrongdatim].kieu;
                        }
                        else
                        {
                            myFile.close();
                            hashing.giaiphong_bonho();
                            TypeMismatch loi_khonghople(dong);
                            throw TypeMismatch(dong);
                        }
                        tong_lap += loop_id;
                        tong_lap += lap_ham;
                        cout << tong_lap << endl;
                    }

                    else
                    {
                        myFile.close();
                        hashing.giaiphong_bonho();
                        InvalidInstruction loicuphap(dong);
                        throw InvalidInstruction(dong);
                    }
                }

                else if (thanh_phan[0].compare("END") == 0)
                {
                    if (level_dautien == 0)
                    {
                        myFile.close();
                        hashing.giaiphong_bonho();
                        UnknownBlock UnknownBlockmessage();
                        throw UnknownBlock();
                    }
                    if (level_dautien != 0)
                    {
                        hashing.xoa_iden_cung_le(level_dautien);
                        level_dautien -= 1;
                    }
                }
                else if (thanh_phan[0].compare("BEGIN") == 0)
                {
                    level_dautien += 1;
                }
            }
            else
            {
                myFile.close();
                hashing.giaiphong_bonho();

                InvalidInstruction loicuphap(dong);
                throw InvalidInstruction(dong);
            }
        }
    }

    if (level_dautien > 0)
    {
        myFile.close();
        hashing.giaiphong_bonho();

        UnclosedBlock loi_block(level_dautien);
        throw UnclosedBlock(level_dautien);
    }
    hashing.giaiphong_bonho();

    myFile.close();
}