#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "error.h"

using namespace std;

//=======================================================formcommandvalidation==============
class formcommandvalidation
{ // kiem tra cac kieu cua lenh co dung dinh dang ko
public:
    bool valid;
    int numofSpace;
    int numofComponent;
    string command_CO;
    string identifier_CO;
    string value_type_CO;
    bool Static_global_CO;
    formcommandvalidation()
        : valid{false}, numofSpace{0}, numofComponent{0}, Static_global_CO{false}
    {
    }

    bool checkvalid(string &inputcommand);
};

//=============================================Symbol=

class Symbol
{

public:
    string identifier;
    int levelOfblock;
    string type;
    friend class Node;

    Symbol()
    {
    }

    Symbol(string &name, int &level, string &Type)
        : identifier{name}, levelOfblock{level}, type{Type}
    {
    }
    Symbol(int i, string name, int level, string Type)
        : identifier{name}, levelOfblock{level}, type{Type} {}
};

bool operator==(const Symbol &op1, const Symbol &op2)
{
    if (op1.levelOfblock == op2.levelOfblock && op1.identifier.compare(op2.identifier) == 0)
    {
        return true;
    }
    return false;
}
bool operator!=(const Symbol &op1, const Symbol &op2)
{
    return !(op1 == op2);
}
bool operator<(const Symbol &op1, const Symbol &op2)
{
    if (op1.levelOfblock < op2.levelOfblock)
        return true;
    else if (op1.levelOfblock > op2.levelOfblock)
        return false;
    else
    {
        if (op1.identifier.compare(op2.identifier) < 0)
            return true;
        else
            return false;
    }
}
bool operator>(const Symbol &op1, const Symbol &op2)
{
    if (op1.levelOfblock > op2.levelOfblock)
        return true;
    else if (op1.levelOfblock < op2.levelOfblock)
        return false;
    else
    {
        if (op1.identifier.compare(op2.identifier) > 0)
            return true;
        else
            return false;
    }
}
bool operator>=(const Symbol &op1, const Symbol &op2)
{
    return !(op1 < op2);
}
bool operator<=(const Symbol &op1, const Symbol &op2)
{

    return !(op1 > op2);
}

//=============================================Node===============

class Node
{

public:
    Symbol data;
    Node *parent;
    Node *left;
    Node *right;

    Node(string &name, int &level, string &Type, Node *leftnode = NULL, Node *rightnode = NULL, Node *parentnode = NULL)
        : data(name, level, Type), left{leftnode}, right{rightnode}, parent{parentnode} {}
};

//=====================SymbolTable===============================
class SymbolTable
{
public:
    SymbolTable() {}
    void run(string filename);
};

class SplayList
{
public:
    Node *root;
    int numofnode;
    int numoflevel;
    SplayList()
    {
        root = NULL;
        int numofnode = 0;
        int numoflevel = 1;
    }

    void leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != NULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void splay(Node *x)
    {
        if (x == NULL)
            return;
        while (x->parent)
        {
            if (!x->parent->parent)
            {
                if (x == x->parent->left)
                {

                    rightRotate(x->parent);
                }
                else
                {

                    leftRotate(x->parent);
                }
            }
            else if (x == x->parent->left && x->parent == x->parent->parent->left)
            {

                rightRotate(x->parent->parent);
                rightRotate(x->parent);
            }
            else if (x == x->parent->right && x->parent == x->parent->parent->right)
            {

                leftRotate(x->parent->parent);
                leftRotate(x->parent);
            }
            else if (x == x->parent->right && x->parent == x->parent->parent->left)
            {

                leftRotate(x->parent);
                rightRotate(x->parent);
            }
            else
            {

                rightRotate(x->parent);
                leftRotate(x->parent);
            }
        }
    }

    void preorder()
    {
        preOrderHelper(this->root);
    }

    void inorder()
    {
        inOrderHelper(this->root);
    }

    void postorder()
    {
        postOrderHelper(this->root);
    }

    void insert(Symbol key)
    {
        // normal BST insert
        Node *node = new Node(key.identifier, key.levelOfblock, key.type);
        Node *y = NULL;
        Node *x = this->root;

        while (x != NULL)
        {
            y = x;
            if (node->data < x->data)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        // y is parent of x
        node->parent = y;
        if (y == NULL)
        {
            root = node;
        }
        else if (node->data < y->data)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }

        // splay the node
        this->splay(node);
        this->numofnode++;
    }

private:
    void preOrderHelper(Node *node)
    {
        if (node != NULL)
        {
            cout << node->data.identifier << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(Node *node)
    {
        if (node != NULL)
        {
            inOrderHelper(node->left);
            cout << node->data.identifier << " ";
            inOrderHelper(node->right);
        }
    }

    void postOrderHelper(Node *node)
    {
        if (node != NULL)
        {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->data.identifier << " ";
        }
    }
};

int main()
{
    string s1 = "1";
    string s2 = "2";
    string s3 = "3";
    string s4 = "4";
    string s5 = "5";
    string s6 = "6";
    string s7 = "7";
    string s8 = "8";
    string s9 = "9";
    string s10 = "8";

    int i1 = 4, i2 = 10;
    //string s3="num";
    Symbol a1(s1, i1, s3);
    Symbol a2(s2, i2, s3);
    Symbol a3(s3, i2, s3);
    Symbol a4(s4, i2, s3);
    Symbol a5(s5, i2, s3);
    Symbol a6(s6, i2, s3);
    Symbol a7(s7, i2, s3);
    Symbol a8(s8, i2, s3);
    Symbol a9(s9, i2, s3);
    SplayList table;
    if (table.root == NULL)
    {
        cout << '1' << endl;
    }
    else
    {
        cout << 2 << endl;
    }
    table.insert(a5);
    table.insert(a7);
    table.insert(a3);
    table.insert(a8);

    //table.insertToSlaytree(a9);
    if (table.root == NULL)
    {
        cout << '1' << endl;
    }
    else
    {
        cout << 2 << endl;
    }
    table.inorder();
    cout << endl;
    table.preorder();
    cout << endl;
    table.postorder();
}

//======================================================================
bool formcommandvalidation::checkvalid(string &inputcommand)
{

    int lengthofinputcommand = inputcommand.size(); //count character in inputcommand
    if (lengthofinputcommand <= 1)
    {
        valid = false;
        return false;
    }
    if (inputcommand[0] == ' ' || inputcommand[lengthofinputcommand - 1] == ' ')
    {
        valid = false;
        return valid;
    }
    this->numofSpace = count_Char(inputcommand, ' ');
    if (numofSpace == 0)
    {
        if (inputcommand.compare("BEGIN") == 0 || inputcommand.compare("END") == 0 || inputcommand.compare("PRINT") == 0)
        {
            this->command_CO = inputcommand;
            numofComponent = 1;
            this->valid = true;
            return true;
        }
        valid = false;
        return valid;
    }
    else if (numofSpace == 1)
    {
        int spaceposition = inputcommand.find(' ');
        this->command_CO = inputcommand.substr(0, spaceposition);
        if (command_CO.compare("LOOKUP") != 0)
        {
            valid = false;
            return valid;
        }
        identifier_CO.assign(inputcommand, spaceposition + 1);
        if (!identifierrule(identifier_CO))
        {
            valid = false;
            return valid;
        }
        valid = true;
        this->numofComponent = 2;
        return true;
    }
    else if (numofSpace == 2)
    {
        int spaceposition1 = inputcommand.find(' ');
        this->command_CO = inputcommand.substr(0, spaceposition1);
        if (command_CO.compare("ASSIGN") != 0)
        {
            valid = false;
            return false;
        }
        int spaceposition2 = inputcommand.find(' ', spaceposition1 + 1);
        this->identifier_CO = inputcommand.substr(spaceposition1 + 1, spaceposition2 - spaceposition1 - 1);
        if (!identifierrule(identifier_CO))
        {
            valid = false;
            return valid;
        }
        this->value_type_CO.assign(inputcommand, spaceposition2 + 1);
        valid = true;
        this->numofComponent = 3;
        return true;
    }
    else if (numofSpace == 3)
    {
        int spaceposition1 = inputcommand.find(' ');
        this->command_CO = inputcommand.substr(0, spaceposition1);
        if (command_CO.compare("INSERT") != 0)
        {
            valid = false;
            return false;
        }

        int spaceposition2 = inputcommand.find(' ', spaceposition1 + 1);
        this->identifier_CO = inputcommand.substr(spaceposition1 + 1, spaceposition2 - spaceposition1 - 1);
        if (!identifierrule(identifier_CO))
        {
            valid = false;
            return valid;
        }

        int spaceposition3 = inputcommand.find(' ', spaceposition2 + 1);
        this->value_type_CO = inputcommand.substr(spaceposition2 + 1, spaceposition3 - spaceposition2 - 1);

        string static_temp;
        static_temp.assign(inputcommand, spaceposition3 + 1);
        if (static_temp.compare("true") == 0)
        {
            this->Static_global_CO = true;
            valid = true;
            this->numofComponent = 4;
            return valid;
        }
        else if (static_temp.compare("false") == 0)
        {
            this->Static_global_CO = false;
            valid = true;
            this->numofComponent = 4;
            return valid;
        }
        else
        {
            valid = false;
            return valid;
        }
    }
    else
    {
        valid = false;
        return valid;
    }
}

int count_Char(string &str, char c = ' ')
{ // this fucntion return the time a charecter appear in the string
    int s = 0;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (str[i] == c)
            s += 1;
    }
    return s;
}
bool identifierrule(string &str)
{
    int lengthofstring = str.length();

    if (lengthofstring > 0)
    {
        if (str[0] < 97 || str[0] > 122)
        {
            return false;
        }

        for (int i = 1; i < lengthofstring; i++)
        {
            if (str[i] >= 97 && str[i] <= 122)
            {
                continue;
            }
            else if (str[i] >= 65 && str[i] <= 90)
            {
                continue;
            }
            else if (str[i] == '_')
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

bool is_Num(string &str)
{
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (str[i] < 48 || str[i] > 57)
            return false;
    }
    return true;
}

bool isstring(string &str)
{
    int lengthofstring = str.size();
    if (lengthofstring <= 1)
    {
        return false;
    }

    if (str[0] != '\'' || str[lengthofstring - 1] != str[0])
    {
        return false;
    }
    for (int i = 1; i < lengthofstring - 1; i++)
    {
        if (str[i] == ' ')
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
