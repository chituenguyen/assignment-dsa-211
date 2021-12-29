#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"

class sperate_command
{
public:
    string command;
    string identifier;
    string type;
    int num;

    void sperate(string str);
    sperate_command()
    {
        num = 0;
    }
};
class Symbol
{
private:
    string identifier;
    string type;

public:
    Symbol *next_In_Scope;
    Symbol *before_In_Scope;

    Symbol();
    Symbol(string identifier, string type);
    string get_Symbol_Identifier();
    string get_Symbol_Type();
};

class Scope_Of_Symbol
{
private:
    int level;
    int num_Of_Symbol;

public:
    Symbol *Head;
    Symbol *Tail;
    Scope_Of_Symbol *next_In_Lit;
    Scope_Of_Symbol *before_In_Lit;
    Scope_Of_Symbol(int level);
    int get_Num_Of_Symbol();
    void add_Symbol_To_Scope(string identifier, string type);
    bool is_Symbol_identifier_exist_in_Scope(string);
    string get_Type_Of_Symbol(string);
    void del_all_Symbol_in_Scope();
    bool is_Symbol_exist_in_higher_Scope(string);
    int get_Level();
    bool is_Symbol_exist_in_lower_Scope(string);
};

class Lit_Of_Scope
{
private:
    int num_Of_Scope;

public:
    Scope_Of_Symbol *Head;
    Scope_Of_Symbol *Tail;
    Lit_Of_Scope();
    void add_Scope_To_Lit(int level_Scope);
    bool delete_High_Level();
    bool delete_All_Level();
    int get_Num_Scope();
};

class SymbolTable
{
public:
    SymbolTable() {}
    void run(string filename);
};

bool is_String(string str);
bool is_Num(string str);
int count_Char(string str, char c = ' ');

#endif