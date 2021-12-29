#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"

//================================heper function==========

int count_Char(string &str, char c = ' ');
bool identifier_Rule(string &str);
bool is_Number(string &str);
bool is_String(string &str);
class Node;
int check_Assign_Type(string str);
int check_Assign_Type(string str, int &numAg);
bool is_Functional(string str, int &Agnum);
bool is_Argument(string str);
string function_Return_Typical(string);
int count_Argument_Functional(string &);
int match_Params(string para, string argu);
string get_Argument(string parameterlis, int indexofArgument);
bool operator!=(const Node &op1, const Node &op2);
bool operator==(const Node &op1, const Node &op2);
bool operator<(const Node &op1, const Node &op2);
bool operator>(const Node &op1, const Node &op2);
bool operator<=(const Node &op1, const Node &op2);
bool operator>=(const Node &op1, const Node &op2);
void count_Sosanh(Node *node, Node *node_find, int &num_comp);
//=================================================

class Node
{
public:
    string identifier;
    int level;
    string type;
    Node *left;
    Node *right;
    Node *parent;
    Node()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
    }
    Node(string id, int level, string type)
    {
        identifier = id;
        this->level = level;
        this->type = type;
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    Node(string id, int level)
    {
        identifier = id;
        this->level = level;
        this->type = "";
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

class Splay
{
public:
    Node *root;
    Splay()
    {
        root = NULL;
    }

protected:
    void left_Rotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != NULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL)
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

    void right_Rotate(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != NULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL)
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

    void pre_Order_Helper(Node *x)
    {
        if (x != NULL)
        {
            cout << x->identifier << "-" << x->level << "  ";
            pre_Order_Helper(x->left);
            pre_Order_Helper(x->right);
        }
    }

    void in_Order_Helper(Node *x)
    {
        if (x != NULL)
        {
            in_Order_Helper(x->left);
            cout << x->identifier << "-" << x->level << "  ";
            in_Order_Helper(x->right);
        }
    }

    void post_Order_Helper(Node *x)
    {
        if (x != NULL)
        {
            post_Order_Helper(x->left);
            post_Order_Helper(x->right);
            cout << x->identifier << "-" << x->level << "  ";
        }
    }

    void splay_Action(Node *node)
    {
        if (node == NULL)
            return;
        else
        {
            while (node->parent != NULL)
            {
                if (node->parent->parent == NULL)
                { //zig or zag
                    if (node == node->parent->left)
                    { //zig
                        right_Rotate(node->parent);
                    }
                    else
                    { // zag
                        left_Rotate(node->parent);
                    }
                }
                else if (node == node->parent->left && node->parent == node->parent->parent->left)
                {
                    right_Rotate(node->parent->parent);
                    right_Rotate(node->parent);
                }
                else if (node == node->parent->right && node->parent == node->parent->parent->right)
                {
                    // zagzag
                    left_Rotate(node->parent->parent);
                    left_Rotate(node->parent);
                }
                else if (node == node->parent->right && node->parent == node->parent->parent->left)
                {
                    // zigzag
                    left_Rotate(node->parent);
                    right_Rotate(node->parent);
                }
                else
                {
                    right_Rotate(node->parent);
                    left_Rotate(node->parent);
                }
            }
        }
    }

    Node *insert_NO_Splay(Node *&node, Node *x, Node *y)
    {
        if (node == NULL)
        {
            node = x;
            node->parent = y;
            return node;
        }
        else if ((*node) <= (*x))
        {
            return insert_NO_Splay(node->right, x, node);
        }
        else
        {
            return insert_NO_Splay(node->left, x, node);
        }
    }

    Node *insert_NO_Splay_Count(Node *&node, Node *&x, Node *y, int &z)
    {
        if (node == NULL)
        {
            node = x;
            node->parent = y;
            z = z + 0;
            return node;
        }
        else if ((*node) <= (*x))
        {
            z++;
            return insert_NO_Splay_Count(node->right, x, node, z);
        }
        else
        {
            z++;
            return insert_NO_Splay_Count(node->left, x, node, z);
        }
    }

    bool search_Helper2(Node *node, Node *find)
    {
        if (node == NULL)
        {
            return false;
        }

        if (node == find)
        {
            return true;
        }
        else if ((*node) < (*find))
        {
            return search_Helper2(node->right, find);
        }
        else
        {
            return search_Helper2(node->left, find);
        }
    }

    Node *delete_All(Node *root)
    {
        if (root == NULL)
            return root;
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }
        if (root->left != NULL)
        {
            root->left = delete_All(root->left);
        }
        if (root->right != NULL)
        {
            root->right = delete_All(root->right);
        }
        delete root;
        return NULL;
    }

public:
    bool nodeis_to_assign(string id, int &lv, Node *&nodefound)
    {

        nodefound = NULL;
        while (lv >= 0)
        {
            Node *temp = new Node(id, lv);
            Node *temp2 = this->root;
            nodefound = search_Helper1(temp2, temp);
            if (nodefound != NULL)
            {

                delete temp;
                return true;
            }
            delete temp;
            lv--;
        }

        return false;
    }
    void pre_Order();
    void splaynode(Node *node)
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
                    }
                    else
                    { // zag
                        left_Rotate(node->parent);
                    }
                }
                else if (node == parentnode->left && parentnode == grandparent->left)
                {
                    right_Rotate(node->parent->parent);
                    right_Rotate(node->parent);
                }
                else if (node == parentnode->right && parentnode == grandparent->right)
                {
                    // zagzag
                    left_Rotate(node->parent->parent);
                    left_Rotate(node->parent);
                }
                else if (node == parentnode->right && parentnode == grandparent->left)
                {
                    // zigzag
                    left_Rotate(node->parent);
                    right_Rotate(node->parent);
                }
                else
                {
                    right_Rotate(node->parent);
                    left_Rotate(node->parent);
                }
            }
        }
    }
    Node *search_Helper1(Node *&node, Node *&find)
    {

        if (node == NULL)
        {
            return NULL;
        }
        if (((*node) == (*find)))
        {
            return node;
        }
        else if (((*node) > (*find)) && (node != NULL))
        {
            return search_Helper1(node->left, find);
        }
        return search_Helper1(node->right, find);
    }

    bool insert(string id, int level, string type);

    bool insert_And_Count(string id, int level, string type, int &num_com, int &num_slay);

    bool insert_And_Count(string id, int level, string type, int &num_com, int &num_slay, Node *&reff)
    {
        Node *temp = new Node(id, level, type);
        // da ton tai;
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
            reff = temp;
            return true;
        }
    }
    void Splay_Node_Count(Node *node, int &num_splay);
    void Splay_Node_noCount(Node *node);

    Node *indentifier_Tontai_Level(string id, int lv = 0)
    {
        Node *temp = new Node(id, lv);

        Node *x = search_Helper1(this->root, temp);
        delete temp;
        return x;
    }

    Node *tim_Kiem_Node(Node *goc, Node *node)
    {
        if (goc == NULL)
            return NULL;
        if (node->level == goc->level && node->identifier.compare(goc->identifier) == 0)
            return goc;
        else if ((node->level < goc->level) || (node->level == goc->level && node->identifier.compare(goc->identifier) < 0))
            return tim_Kiem_Node(goc->left, node);

        return tim_Kiem_Node(goc->right, node);
    }
    bool node_Dang_Ky(string id, int &lv, Node *&x);

    Node *identiifier_Tontai_Cay(string id, int a = 0)
    {

        for (int hello = a; hello >= 0; hello--)
        {
            Node *nodeid = indentifier_Tontai_Level(id, a);
            if (nodeid != NULL)
            {
                return nodeid;
            }
        }
        return NULL;
    }

    bool ton_Tai(Node *node);

    void delete_Tree();
    Node *maxnode(Node *node)
    {
        while (node->right != NULL)
        {
            node = node->right;
        }
        return node;
    }

    Node *minnode(Node *node)
    {
        while (node->left != NULL)
        {
            node = node->left;
        }
        return node;
    }

    void splithelper(Node *&node, Node *&l, Node *&r)
    {
        if (node == NULL)
            return;
        else
        {
            splay_Action(node);
            if (node->right != NULL)
            {
                r = node->right;
                r->parent = NULL;
            }
            else
            {
                r = NULL;
            }

            l = node;
            l->right = NULL;
            node = NULL;
        }
    }

    Node *joinhelper(Node *l, Node *r)
    {
        if (l == NULL)
        {
            return r;
        }

        if (r == NULL)
        {
            return l;
        }

        Node *maxnodeinleft = this->maxnode(l);
        this->splay_Action(maxnodeinleft);
        maxnodeinleft->right = r;
        r->parent = maxnodeinleft;
        return maxnodeinleft;
    }

    bool deletenode(Node *&node_delete)
    {
        return deletenodehelper(this->root, node_delete);
    }

    bool deletenodehelper(Node *nodetree_root, Node *&nodedelete)
    {
        // kiem tra xem node delete co ton tai hay khong
        // Node* nodefind=NULL;
        // bool isfind=this->nodeis_to_assign(nodedelete->identifier,nodedelete->level,nodefind);
        // if(isfind)
        Node *delnode = NULL;
        delnode = this->search_Helper1(nodetree_root, nodedelete);
        if (delnode == NULL)
        { // node ko ton tai
            return false;
        }
        else
        { //tim thay node;
            nodedelete = NULL;
            // slip
            Node *l;
            Node *r;
            this->splithelper(delnode, l, r);
            this->root = joinhelper(l->left, r);
            delete l;
            l = NULL;
            root->parent = NULL;
            return true;
            //join

            //delete
        }
        return true;
    }
};

class SymbolTable
{
public:
    SymbolTable() {}
    void run(string filename);
};

class line
{
public:
    int numof = 0;
    string command;
    string identifier;
    string type;
    int level;
    bool check_Input(string &input);
};

class type
{
public:
    bool is_Functional;
    string type_Trave;
    int bienSo;
    bool check_Type(string &typeinput);
};

class ltable
{
public:
    Node *blockofnode[100];
    int numofnode;
    ltable()
    {
        for (int i = 0; i < 100; i++)
        {
            blockofnode[i] = NULL;
        }
        numofnode = 0;
    }
};
class leveltable
{
public:
    Node *blockofnode[100];
    int numofnode;
    leveltable()
    {
        for (int i = 0; i < 100; i++)
        {
            blockofnode[i] = NULL;
        }
        numofnode = 0;
    }
};
#endif