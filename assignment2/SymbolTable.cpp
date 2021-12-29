#include "SymbolTable.h"
int demsoluongkytu(string str, char c)
{
    int soluong = 0;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (str[i] == c)
            soluong++;
    }
    return soluong;
}

bool tenhople(string str)
{
    int chieudai = str.length();

    if (chieudai > 0)
    {
        if (str[0] < 97 || str[0] > 122)
        {
            return false;
        }

        for (int i = 1; i < chieudai; i++)
        {
            if (str[i] == '_')
            {
                continue;
            }
            else if (str[i] >= 97 && str[i] <= 122)
            {
                continue;
            }
            else if (str[i] >= 65 && str[i] <= 90)
            {
                continue;
            }
            else if (str[i] >= 48 && str[i] <= 57)
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
bool kieuso(string str)
{ // check is number;
    int chieudai = str.size();
    for (int i = 0; i < chieudai; i++)
    {
        if (str[i] < 48 || str[i] > 57)
        {
            return false;
        }
    }
    return true;
}

bool kieuchuoi(string str)
{
    int sum = 0;
    if (str[0] != '\'' || str[str.size() - 1] != '\'')
    {
        sum++;
    }
    else
    {
        for (unsigned int i = 1; i < str.size() - 1; i++)
        {
            if (!(str[i] == 32 || (str[i] >= 97 && str[i] <= 122) || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 48 && str[i] <= 57)))
            {
                sum++;
            }
        }
    }
    return sum == 0;
}
int check_Assign_Type(string str, int &x)
{
    if (kieuso(str))
    {
        return 1;
    }

    if (kieuchuoi(str))
    {
        return 2;
    }

    if (tenhople(str))
    {
        return 3;
    }

    if (is_Functional(str, x))
    {
        return 4;
    }

    return 0;
}
bool is_Functional(string str)
{

    if (str.size() < 3 || demsoluongkytu(str, '(') != 1 || demsoluongkytu(str, ')') != 1)
        return false;

    unsigned n1 = str.find('(');
    unsigned num2 = str.find(')');
    if (num2 != str.length() - 1)
        return false;
    unsigned num3 = str.find(',');
    if (n1 <= 0 || str.find(')') <= str.find('('))
        return false;
    return false;

    string funcname = str.substr(0, n1);
    if (!tenhople(funcname))
    {
        return false;
    }

    int soluong = demsoluongkytu(str, ',');
    if (soluong == 0)
    {
        if (n1 + 1 == num2)
        {
            return true;
        }
        else
        {
            string agr = str.substr(n1 + 1, num2 - n1 - 1);
            if (is_Argument(agr))
            {

                return true;
            }
            return false;
        }
    }
    else
    {
        soluong += 1;
        if (soluong == 2)
        {
            string anso = str.substr(n1 + 1, num3 - n1 - 1);
            if (!is_Argument(anso))
            {
                return false;
            }
            anso = str.substr(num3 + 1, num2 - num3 - 1);
            if (!is_Argument(anso))
            {
                return false;
            }
            return true;
        }

        int lo = str.find(',');
        int hi = str.find(',', lo + 1);
        int ope = str.find('(');
        int clos = str.find(')');
        for (int i = 0; i < soluong; i++)
        {
            string temp;
            if (i == 0)
            {
                temp = str.substr(ope + 1, lo - ope - 1);
                if (!is_Argument(temp))
                {
                    return false;
                }
                continue;
            }

            if (i == soluong - 1)
            {
                temp = str.substr(lo + 1, clos - lo - 1);
                if (!is_Argument(temp))
                {
                    return false;
                }
            }
            else
            {
                temp = str.substr(lo + 1, hi - lo - 1);
                if (!is_Argument(temp))
                {
                    return false;
                }
            }
            lo = hi;
            hi = str.find(',', hi + 1);
        }

        return true;
    }

    return true;
}
int check_Assign_Type(string str)
{
    if (kieuso(str))
    {
        return 1;
    }

    if (kieuchuoi(str))
    {
        return 2;
    }

    if (tenhople(str))
    {
        return 3;
    }

    if (is_Functional(str))
    {
        return 4;
    }

    return 0;
}
bool is_Functional(string str, int &x)
{
    x = 0;
    if (str.size() < 3 || demsoluongkytu(str, '(') != 1 || demsoluongkytu(str, ')') != 1)
        return false;
    int n1 = str.find('(');
    int num2 = str.find(')');
    if (n1 <= 0)
        return false;
    if (str.find(')') <= str.find('('))
        return false;

    string function_Name = str.substr(0, n1);
    if (!tenhople(function_Name))
    {
        return false;
    }

    int soluong = demsoluongkytu(str, ',');
    if (soluong == 0)
    {
        if (n1 + 1 == num2)
        {
            x = 0;
            return true;
        }
        else
        {
            string agr = str.substr(n1 + 1, num2 - n1 - 1);
            if (is_Argument(agr))
            {
                x = 1;
                return true;
            }
            return false;
        }
    }
    else
    {
        int num3 = str.find(',');
        soluong += 1;
        if (soluong == 2)
        {
            string anso = str.substr(n1 + 1, num3 - n1 - 1);
            if (!is_Argument(anso))
            {
                return false;
            }
            anso = str.substr(num3 + 1, num2 - num3 - 1);
            if (!is_Argument(anso))
            {
                return false;
            }
            x = 2;
            return true;
        }

        int lo = str.find(',');
        int hi = str.find(',', lo + 1);
        int ope = str.find('(');
        int clos = str.find(')');
        for (int i = 0; i < soluong; i++)
        {
            string temp;
            if (i == 0)
            {
                temp = str.substr(ope + 1, lo - ope - 1);
                if (!is_Argument(temp))
                {
                    return false;
                }
                continue;
            }

            if (i == soluong - 1)
            {
                temp = str.substr(lo + 1, clos - lo - 1);
                if (!is_Argument(temp))
                {
                    return false;
                }
            }
            else
            {
                temp = str.substr(lo + 1, hi - lo - 1);
                if (!is_Argument(temp))
                {
                    return false;
                }
            }
            lo = hi;
            hi = str.find(',', hi + 1);
        }
        x = soluong;
        return true;
    }
    x = soluong;
    return true;
}

bool is_Argument(string str)
{
    if (kieuso(str) || kieuchuoi(str) || tenhople(str))
        return true;

    return false;
}
string function_Return_Typical(string str)
{
    int num = str.find('>');
    string type;
    type.assign(str, num + 1);
    return type;
}
int count_Argument_Functional(string &str)
{
    int n1 = str.find('(');
    int num2 = str.find(')');
    if (n1 + 1 == num2)
    {
        return 0;
    }
    int num3 = demsoluongkytu(str, ',');
    if (num3 == 0)
    {
        return 1;
    }
    return num3 + 1;
}
int match_Params(string x, string y)
{

    if (x == "number" && kieuso(y))
    {
        return 1;
    }

    if (x == "string" && kieuchuoi(y))
    {
        return 2;
    }

    if ((!kieuso(y)) && (!kieuchuoi(y)))
    {
        if (tenhople(y))
        {
            return 3;
        }
        else
        {
            return 0;
        }
    }

    return -1;
}
string get_Argument(string x, int y)
{
    int soluong = count_Argument_Functional(x);
    if (soluong == 0 || y == 0 || soluong < y)
    {
        return "";
    }
    if (soluong == 1)
    {
        int n1 = x.find('(');
        int num2 = x.find(')');
        return x.substr(n1 + 1, num2 - n1 - 1);
    }

    if (soluong > 1 && y == 1)
    {
        int n1 = x.find('(');
        int num2 = x.find(',');
        return x.substr(n1 + 1, num2 - n1 - 1);
    }
    if (soluong == 2 && y == 2)
    {
        int num2 = x.find(',');
        int num3 = x.find(')');
        return x.substr(num2 + 1, num3 - num2 - 1);
    }

    int num2 = x.find(',');
    int num3 = x.find(')');
    int num4 = 0;
    if (soluong > 2 && y == soluong)
    {
        for (int i = 2; i < y; i++)
        {
            num4 = x.find(',', num2 + 1);
            if (i < y - 1)
            {
                num2 = num4;
            }
        }
        return x.substr(num4 + 1, num3 - num4 - 1);
    }

    if (soluong > 2 && y < soluong)
    {
        int n1 = x.find(',');
        int n2 = x.find(',', n1 + 1);
        for (int i = 3; i <= y; i++)
        {
            n1 = n2;
            n2 = x.find(',', n1 + 1);
        }
        return x.substr(n1 + 1, n2 - n1 - 1);
    }

    return "";
}
bool operator!=(const Node &op1, const Node &op2)
{
    return !(op1 == op2);
}

bool operator==(const Node &op1, const Node &op2)
{
    if (op1.level == op2.level && op1.identifier == op2.identifier)
    {
        return true;
    }
    return false;
}

bool operator<(const Node &op1, const Node &op2)
{
    if (op1.level < op2.level)
        return true;
    else if (op1.level > op2.level)
        return false;
    else
    {
        if (op1.identifier.compare(op2.identifier) < 0)
            return true;
        else
            return false;
    }
}
bool operator>(const Node &op1, const Node &op2)
{
    if (op1.level > op2.level)
        return true;
    else if (op1.level < op2.level)
        return false;
    else
    {
        if (op1.identifier.compare(op2.identifier) > 0)
            return true;
        else
            return false;
    }
}
bool operator<=(const Node &op1, const Node &op2)
{
    return !(op1 > op2);
}
void Splay::pre_Order()
{
    pre_Order_Helper(this->root);
}
bool Splay::insert(string id, int level, string type)
{
    Node *temp = new Node(id, level, type);
    if (ton_Tai(temp))
    {
        delete temp;
        return false;
    }
    else
    {
        Node *temp2 = NULL;
        temp = insert_NO_Splay(root, temp, temp2);
        splay_Action(temp);
        root = temp;
        return true;
    }
}
bool Splay::insert_And_Count(string id, int level, string type, int &num_com, int &num_slay)
{
    Node *temp = new Node(id, level, type);
    if (ton_Tai(temp))
    {
        delete temp;
        return false;
    }
    else
    {
        Node *temp2 = NULL;
        temp = insert_NO_Splay_Count(root, temp, temp2, num_com);
        Splay_Node_Count(temp, num_slay);
        return true;
    }
}
void Splay::Splay_Node_Count(Node *node, int &solansplay)
{
    if (node == NULL)
        return;
    else
    {
        while (node->parent != NULL)
        {
            Node *parentnode = node->parent;
            Node *grandparent = node->parent->parent;
            if (grandparent == NULL)
            { //zig or zag
                if (node == parentnode->left)
                { //zig
                    right_Rotate(node->parent);
                    solansplay += 1;
                }
                else
                { // zag
                    solansplay += 1;
                    left_Rotate(node->parent);
                }
            }
            else if (node == parentnode->left && parentnode == grandparent->left)
            {
                right_Rotate(node->parent->parent);
                right_Rotate(node->parent);
                solansplay += 1;
            }
            else if (node == parentnode->right && parentnode == grandparent->right)
            {
                // zagzag
                left_Rotate(node->parent->parent);
                left_Rotate(node->parent);
                solansplay += 1;
            }
            else if (node == parentnode->right && parentnode == grandparent->left)
            {
                // zigzag
                left_Rotate(node->parent);
                right_Rotate(node->parent);
                solansplay += 1;
            }
            else
            {
                right_Rotate(node->parent);
                left_Rotate(node->parent);
                solansplay += 1;
            }
        }
    }
}

bool Splay::node_Dang_Ky(string id, int &lvel, Node *&x)
{

    x = NULL;
    while (lvel >= 0)
    {
        Node *temp = new Node(id, lvel);
        Node *temp2 = this->root;
        x = search_Helper1(temp2, temp);
        if (x != NULL)
        {

            delete temp;
            return true;
        }
        delete temp;
        lvel--;
    }

    return false;
}

bool Splay::ton_Tai(Node *node)
{
    if (root == NULL)
        return false;
    else
    {
        Node *temp = root;
        while (temp != NULL)
        {
            if ((*temp) == (*node))
                return true;
            else if ((*temp) > (*node))
                temp = temp->left;
            else
                temp = temp->right;
        }

        return false;
    }
}
void Splay::delete_Tree()
{
    root = delete_All(this->root);
}
void count_Sosanh(Node *node, Node *node_find, int &solansosanh)
{
    if (node == NULL)
    {
        solansosanh = 0;
        return;
    }

    if ((*node) == (*node_find))
    {
        solansosanh += 1;
        return;
    }
    else if ((*node_find) < (*node))
    {
        count_Sosanh(node->left, node_find, solansosanh);
        solansosanh += 1;
    }
    else
    {
        count_Sosanh(node->right, node_find, solansosanh);
        solansosanh += 1;
    }
}
bool line::check_Input(string &x)
{
    int leng = x.size();
    if (leng < 3)
    {
        return false;
    }

    if (x[0] == ' ' || x[leng - 1] == ' ')
    {
        return false;
    }
    int y = demsoluongkytu(x, ' ');
    if (y == 0)
    {
        if (x == "BEGIN" || x == "END" || x == "PRINT")
        {
            numof = 1;
            command = x;
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (y == 1)
    {
        string temp = x.substr(0, 6);
        if (temp == "LOOKUP")
        {
            identifier.assign(x, 7);
            if (tenhople(identifier))
            {
                numof = 2;
                return true;
            }
            return false;
        }
        return false;
    }
    else if (y == 2)
    {
        int s1 = x.find(' ');
        this->command = x.substr(0, s1);
        if (command != "ASSIGN")
        {

            return false;
        }
        int s2 = x.find(' ', s1 + 1);
        this->identifier = x.substr(s1 + 1, s2 - s1 - 1);
        if (!tenhople(identifier))
        {

            return false;
        }
        this->type.assign(x, s2 + 1);

        this->numof = 3;
        return true;
    }
    else if (y == 3)
    {
        int s1 = x.find(' ');
        this->command = x.substr(0, s1);
        if (command != "INSERT")
        {

            return false;
        }
        int s2 = x.find(' ', s1 + 1);
        this->identifier = x.substr(s1 + 1, s2 - s1 - 1);
        if (!tenhople(identifier))
        {
            return false;
        }

        int s3 = x.find(' ', s2 + 1);
        this->type = x.substr(s2 + 1, s3 - s2 - 1);
        string static_temp;
        static_temp.assign(x, s3 + 1);
        if (static_temp == "true")
        {
            level = 0;
            this->numof = 4;
            return true;
        }
        else if (static_temp == "false")
        {
            level = -1;
            this->numof = 4;
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
bool type::check_Type(string &typeinput)
{
    this->is_Functional = false;
    if (typeinput == "number" || typeinput == "string")
    {
        return true;
    }
    // mabe function
    if (typeinput.size() < 10)
    {
        return false;
    }
    int n1 = typeinput.find('(');
    int num2 = typeinput.find(')');
    int num3 = typeinput.find('-');
    int num4 = typeinput.find('>');
    if (!(n1 == 0 && (n1 + 1 <= num2) && (num2 + 1 == num3) && (num3 + 1 == num4)))
    {
        return false;
    }

    type_Trave = typeinput.substr(num4 + 1);
    if (type_Trave != "string" && type_Trave != "number")
    {
        return false;
    }

    bienSo = demsoluongkytu(typeinput, ',');
    if (bienSo == 0)
    {

        is_Functional = true;
        return true;
    }
    else
    {
        bienSo += 1;
        int j = 1;
        string str;
        for (int i = 0; i < bienSo; i++)
        {
            str = typeinput.substr(j, 6);
            j += 7;
            if (str != "number" && str != "string")
            {
                return false;
            }
        }
        is_Functional = true;
        return true;
    }
}
void SymbolTable::run(string filename)
{
    fstream myfile;

    myfile.open(filename, ios::in);
    if (!myfile.is_open())
    {
        cout << "file is not exist" << endl;
        return;
    }

    string input;
    int levelHientai = 0;
    line line;
    Splay tree;
    type typecheck;
    leveltable table[100];
    table[0].numofnode = 0;
    while (getline(myfile, input))
    {
        if (line.check_Input(input))
        {
            if (line.command == "INSERT")
            {
                if (line.level == -1)
                {
                    line.level = levelHientai;
                }
                else
                {
                    line.level = 0;
                }

                if (!typecheck.check_Type(line.type))
                {

                    tree.delete_Tree();
                    InvalidInstruction errorne(input);
                    throw InvalidInstruction(input);
                    cout << endl;
                }

                if (typecheck.is_Functional)
                {
                    if (line.level != 0)
                    {
                        tree.delete_Tree();
                        InvalidDeclaration errorne(input);
                        throw InvalidDeclaration(input);
                        cout << endl;
                    }
                }

                int solansosanh = 0;
                int solansplay = 0;
                Node *ref = NULL;
                bool insertthanhcong = tree.insert_And_Count(line.identifier, line.level, line.type, solansosanh, solansplay, ref);
                if (insertthanhcong)
                {
                    cout << solansosanh << " " << solansplay << endl;
                    table[ref->level].numofnode += 1;
                    int index = table[ref->level].numofnode;
                    table[ref->level].blockofnode[index - 1] = ref;
                }
                else
                {
                    tree.delete_Tree();
                    Redeclared errorne(input);
                    throw Redeclared(input);
                    cout << endl;
                }
            }
            else if (line.command == "ASSIGN")
            {
                int soluongthamso = 0;
                int kieutrave = check_Assign_Type(line.type, soluongthamso);
                if (kieutrave == 1)
                {
                    int levelFInd = levelHientai;
                    Node *nodedatim = NULL;
                    bool timchua = tree.node_Dang_Ky(line.identifier, levelFInd, nodedatim);
                    if (timchua)
                    {
                        if (nodedatim->type == "number")
                        {
                            int solansosanh = 0;
                            count_Sosanh(tree.root, nodedatim, solansosanh);
                            int solansplay = 0;
                            tree.Splay_Node_Count(nodedatim, solansplay);
                            cout << solansosanh << " " << solansplay << endl;
                        }
                        else
                        {
                            tree.delete_Tree();
                            TypeMismatch errorne(input);
                            throw TypeMismatch(input);
                            cout << endl;
                        }
                    }
                    else
                    {
                        tree.delete_Tree();
                        Undeclared errorne(input);
                        throw Undeclared(input);
                        cout << endl;
                    }
                }

                else if (kieutrave == 2)
                {
                    int levelFInd = levelHientai;
                    Node *nodedatim = NULL;
                    bool timchua = tree.node_Dang_Ky(line.identifier, levelFInd, nodedatim);
                    if (timchua)
                    {
                        if (nodedatim->type == "string")
                        {
                            int solansosanh = 0;
                            count_Sosanh(tree.root, nodedatim, solansosanh);
                            int solansplay = 0;
                            tree.Splay_Node_Count(nodedatim, solansplay);
                            cout << solansosanh << " " << solansplay << endl;
                        }
                        else
                        {
                            tree.delete_Tree();
                            TypeMismatch errorne(input);
                            throw TypeMismatch(input);
                            cout << endl;
                        }
                    }
                    else
                    {
                        tree.delete_Tree();
                        Undeclared errorne(input);
                        throw Undeclared(input);
                        cout << endl;
                    }
                }

                else if (kieutrave == 3)
                {

                    int solansosanh = 0;
                    int solansosplay = 0;
                    int levelFInd = levelHientai;
                    Node *bienSo = NULL;
                    bool timchua = tree.node_Dang_Ky(line.type, levelFInd, bienSo);
                    if (timchua)
                    {
                        count_Sosanh(tree.root, bienSo, solansosanh);

                        tree.Splay_Node_Count(bienSo, solansosplay);
                    }
                    else
                    {
                        tree.delete_Tree();
                        Undeclared errorne(input);
                        throw Undeclared(input);
                        cout << endl;
                    }

                    Node *bienSoThemVao = NULL;
                    timchua = false;
                    levelFInd = levelHientai;
                    int solansosanhgangiatri = 0;
                    int solansplaygangiatri = 0;
                    //=> kiem tra id ton tai
                    timchua = tree.node_Dang_Ky(line.identifier, levelFInd, bienSoThemVao);
                    if (timchua)
                    {
                        count_Sosanh(tree.root, bienSoThemVao, solansosanhgangiatri);

                        tree.Splay_Node_Count(bienSoThemVao, solansplaygangiatri);
                    }
                    else
                    {
                        tree.delete_Tree();
                        Undeclared errorne(input);
                        throw Undeclared(input);
                        cout << endl;
                    }

                    if (bienSoThemVao->type == bienSo->type)
                    {
                        cout << solansosanh + solansosanhgangiatri << " " << solansosplay + solansplaygangiatri << endl;
                    }
                    else
                    {
                        tree.delete_Tree();
                        TypeMismatch errorne(input);
                        throw TypeMismatch(input);
                        cout << endl;
                    }
                }
                else if (kieutrave == 4)
                {
                    int n1 = line.type.find('(');
                    string funcname = line.type.substr(0, n1);
                    int lvel = 0;
                    Node *nodeFunctional = NULL;
                    bool timchua = tree.node_Dang_Ky(funcname, lvel, nodeFunctional);
                    if (timchua)
                    {
                        if (soluongthamso == 0)
                        {

                            if (count_Argument_Functional(nodeFunctional->type) != soluongthamso)
                            {
                                tree.delete_Tree();
                                TypeMismatch errorne(input);
                                throw TypeMismatch(input);
                                cout << endl;
                            }

                            Node *nodedatim = NULL;
                            lvel = levelHientai;
                            timchua = tree.node_Dang_Ky(line.identifier, lvel, nodedatim);
                            if (timchua)
                            {
                                string kieuham = function_Return_Typical(nodeFunctional->type);
                                string nodetype = nodedatim->type;
                                if (kieuham == nodetype)
                                {
                                    int soluongssfunc = 0;
                                    int soluongssnode = 0;
                                    int soluongsplayfunc = 0;
                                    int soluongsplaynode = 0;
                                    count_Sosanh(tree.root, nodeFunctional, soluongssfunc);
                                    tree.Splay_Node_Count(nodeFunctional, soluongsplayfunc);
                                    count_Sosanh(tree.root, nodedatim, soluongssnode);
                                    tree.Splay_Node_Count(nodedatim, soluongsplaynode);
                                    cout << soluongssfunc + soluongssnode << " " << soluongsplaynode + soluongsplayfunc << endl;
                                }
                                else
                                {
                                    tree.delete_Tree();
                                    TypeMismatch errorne(input);
                                    throw TypeMismatch(input);
                                    cout << endl;
                                }
                            }
                            else
                            {
                                tree.delete_Tree();
                                Undeclared errorne(input);
                                throw Undeclared(input);
                                cout << endl;
                            }
                        }
                        else if (soluongthamso >= 1)
                        {
                            int tongsplay = 0;
                            int tongsosanh = 0;
                            count_Sosanh(tree.root, nodeFunctional, tongsosanh);
                            tree.Splay_Node_Count(nodeFunctional, tongsplay);
                            if (count_Argument_Functional(nodeFunctional->type) != soluongthamso)
                            {
                                tree.delete_Tree();
                                TypeMismatch errorne(input);
                                throw TypeMismatch(input);
                                cout << endl;
                            }

                            for (int i = 1; i <= soluongthamso; i++)
                            {
                                string anso = get_Argument(line.type, i);
                                string params = get_Argument(nodeFunctional->type, i);
                                int check_match = match_Params(params, anso);
                                if (check_match == 1 || check_match == 2)
                                {
                                    continue;
                                }
                                else if (check_match == 0)
                                {
                                    tree.delete_Tree();
                                    InvalidInstruction errmessage(input);
                                    throw InvalidInstruction(input);
                                    cout << endl;
                                }
                                else if (check_match == -1)
                                {
                                    tree.delete_Tree();
                                    TypeMismatch errorne(input);
                                    throw TypeMismatch(input);
                                    cout << endl;
                                }
                                else if (check_match == 3)
                                {
                                    Node *nodecuabien = NULL;
                                    int levelbien = levelHientai;
                                    bool danhdau = tree.node_Dang_Ky(anso, levelbien, nodecuabien);
                                    if (danhdau)
                                    {
                                        count_Sosanh(tree.root, nodecuabien, tongsosanh);
                                        tree.Splay_Node_Count(nodecuabien, tongsplay);
                                        if (nodecuabien->type.compare(params) != 0)
                                        {
                                            tree.delete_Tree();
                                            TypeMismatch errorne(input);
                                            throw TypeMismatch(input);
                                            cout << endl;
                                        }
                                    }
                                    else
                                    {
                                        tree.delete_Tree();
                                        Undeclared errorne(input);
                                        throw Undeclared(input);
                                        cout << endl;
                                    }
                                }
                            }

                            Node *nodethemvao = NULL;
                            int levelcuanode = levelHientai;
                            bool timchua = tree.node_Dang_Ky(line.identifier, levelcuanode, nodethemvao);
                            if (timchua)
                            {
                                string kieuham = function_Return_Typical(nodeFunctional->type);
                                string nodetype = nodethemvao->type;
                                if (kieuham == nodetype)
                                {
                                    count_Sosanh(tree.root, nodethemvao, tongsosanh);
                                    tree.Splay_Node_Count(nodethemvao, tongsplay);
                                    cout << tongsosanh << " " << tongsplay << endl;
                                }
                                else
                                {
                                    tree.delete_Tree();
                                    TypeMismatch errorne(input);
                                    throw TypeMismatch(input);
                                    cout << endl;
                                }
                            }
                            else
                            {
                                tree.delete_Tree();
                                Undeclared errorne(input);
                                throw Undeclared(input);
                                cout << endl;
                            }
                        }
                    }
                    else
                    {
                        tree.delete_Tree();
                        Undeclared errorne(input);
                        throw Undeclared(input);
                        cout << endl;
                    }
                }
                else if (kieutrave == 0)
                {
                    tree.delete_Tree();
                    InvalidInstruction errorne(input);
                    throw InvalidInstruction(input);
                    cout << endl;
                }
            }
            else if (line.command == "BEGIN")
            { // lenh mo ngoac
                levelHientai += 1;
                table[levelHientai].numofnode = 0;
            }
            else if (line.command == "END")
            { //lenh dong ngoac
                if (levelHientai <= 0)
                {
                    tree.delete_Tree();
                    UnknownBlock unknowblockmessage;
                    throw UnknownBlock();
                }
                else
                {
                    int numnodeinlv = table[levelHientai].numofnode;
                    for (int i = 0; i < numnodeinlv; i++)
                    {
                        tree.deletenode(table[levelHientai].blockofnode[i]);
                    }

                    table[levelHientai].numofnode = 0;
                    levelHientai -= 1;
                }
            }
            else if (line.command == "LOOKUP")
            { // lenhd tim kiem
                int lvfound = levelHientai;
                Node *temp = NULL;
                bool lookupfound = tree.nodeis_to_assign(line.identifier, lvfound, temp);
                if (lookupfound)
                {
                    cout << lvfound << endl;
                    tree.splaynode(temp);
                }
                else
                {
                    tree.delete_Tree();
                    Undeclared undeclaredmessage(input);
                    throw Undeclared(input);
                }
            }
            else if (line.command == "PRINT")
            { // leng in
                tree.pre_Order();
            }
        }
        else
        {

            tree.delete_Tree();
            InvalidInstruction errorne(input);
            throw InvalidInstruction(input);
            cout << endl;
        }
    }
    if (levelHientai > 0)
    {
        // kết thúc mà hcua7 đóng khối

        tree.delete_Tree();
        UnclosedBlock uncloseblockmessage(levelHientai);
        throw UnclosedBlock(levelHientai);
    }
    else
    {
        // kết thuc chuong trinh giai phong vung nhớ
        tree.delete_Tree();
    }

    myfile.close();
}