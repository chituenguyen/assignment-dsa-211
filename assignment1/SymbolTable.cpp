#include "SymbolTable.h"
void sperate_command::sperate(string str)
{
    int times = count_Char(str, ' ');
    this->num = times + 1;
    if (times == 0)
    {
        this->command = str;
        return;
    }
    else if (times == 1)
    {
        this->command = str.substr(0, str.find(' '));
        this->identifier = str.substr(str.find(' ') + 1);
        return;
    }
    else if (times == 2)
    {
        this->command = str.substr(0, str.find(' '));
        int sSpace = str.find(' ', str.find(' ') + 1);
        this->identifier = str.substr(command.size() + 1, sSpace - command.size() - 1);
        this->type = str.substr(sSpace + 1);
    }
}

Symbol::Symbol()
{
    this->next_In_Scope = NULL;
    this->before_In_Scope = NULL;
}

Symbol::Symbol(string identifier, string type)
{
    this->next_In_Scope = NULL;
    this->before_In_Scope = NULL;
    this->identifier = identifier;
    this->type = type;
}

string Symbol::get_Symbol_Identifier()
{
    return this->identifier;
}

string Symbol::get_Symbol_Type()
{
    return this->type;
}

Scope_Of_Symbol::Scope_Of_Symbol(int level)
{
    this->level = level;
    this->num_Of_Symbol = 0;
    this->Head = NULL;
    this->Tail = NULL;
    this->next_In_Lit = NULL;
    this->before_In_Lit = NULL;
}
int Scope_Of_Symbol::get_Num_Of_Symbol()
{
    return this->num_Of_Symbol;
}

void Scope_Of_Symbol::add_Symbol_To_Scope(string identifier, string type)
{
    Symbol *new_Node = new Symbol(identifier, type);
    if (this->num_Of_Symbol == 0)
    {
        this->Head = new_Node;
        this->Tail = new_Node;
    }
    else
    {
        new_Node->before_In_Scope = this->Tail;
        this->Tail->next_In_Scope = new_Node;
        this->Tail = new_Node;
    }
    this->num_Of_Symbol++;
}

bool Scope_Of_Symbol::is_Symbol_identifier_exist_in_Scope(string identifier)
{
    if (this->num_Of_Symbol == 0)
        return false;
    Symbol *temp = new Symbol();
    temp = this->Head;
    while (temp != NULL)
    {
        if (temp->get_Symbol_Identifier() == identifier)
        {
            return true;
        }
        temp = temp->next_In_Scope;
    }
    return false;
}

string Scope_Of_Symbol::get_Type_Of_Symbol(string identifier)
{
    if (this->is_Symbol_identifier_exist_in_Scope(identifier))
    {
        Symbol *temp = new Symbol();
        temp = this->Head;
        while (temp != NULL)
        {
            if (temp->get_Symbol_Identifier() == identifier)
            {
                return temp->get_Symbol_Type();
            }
            temp = temp->next_In_Scope;
        }
    }

    return "\0";
}

void Scope_Of_Symbol::del_all_Symbol_in_Scope()
{
    if (this->num_Of_Symbol == 0)
    {
        this->Head = NULL;
        this->Tail = NULL;
    }
    else if (this->num_Of_Symbol == 1)
    {
        Symbol *temp = new Symbol();
        temp = this->Head;
        delete temp;
        this->Head = NULL;
        this->Tail = NULL;
        num_Of_Symbol = 0;
    }
    else
    {
        Symbol *temp = new Symbol();
        temp = this->Head;
        ;
        while (temp != NULL)
        {
            Symbol *j = temp;
            temp = temp->next_In_Scope;
            delete j;
        }
        this->Head = NULL;
        this->Tail = NULL;
        this->num_Of_Symbol = 0;
    }
}

bool Scope_Of_Symbol::is_Symbol_exist_in_higher_Scope(string identifier)
{
    if (this->next_In_Lit == NULL)
        return false;
    else
    {
        Scope_Of_Symbol *temp_Scope = this->next_In_Lit;
        while (temp_Scope != NULL)
        {
            if (temp_Scope->is_Symbol_identifier_exist_in_Scope(identifier))
                return true;
            temp_Scope = temp_Scope->next_In_Lit;
        }
    }
    return false;
}

int Scope_Of_Symbol::get_Level()
{
    return this->level;
}

bool Scope_Of_Symbol::is_Symbol_exist_in_lower_Scope(string identifier)
{
    if (this->before_In_Lit == NULL)
        return false;
    else
    {
        Scope_Of_Symbol *temp_Scope = this->before_In_Lit;
        for (; temp_Scope != NULL;)
        {
            if (temp_Scope->is_Symbol_identifier_exist_in_Scope(identifier))
                return true;
            temp_Scope = temp_Scope->before_In_Lit;
        }
    }
    return false;
}

Lit_Of_Scope::Lit_Of_Scope()
{
    this->num_Of_Scope = 0;
    this->Head = NULL;
    this->Tail = NULL;
}

void Lit_Of_Scope::add_Scope_To_Lit(int level_Scope)
{
    Scope_Of_Symbol *new_Scope = new Scope_Of_Symbol(level_Scope);
    if (this->num_Of_Scope == 0)
    {
        this->Head = new_Scope;
        this->Tail = new_Scope;
    }
    else
    {
        new_Scope->before_In_Lit = this->Tail;
        this->Tail->next_In_Lit = new_Scope;
        this->Tail = new_Scope;
    }
    this->num_Of_Scope++;
}

bool Lit_Of_Scope::delete_High_Level()
{
    if (this->num_Of_Scope == 0)
        return false;
    else if (this->num_Of_Scope == 1)
    {
        this->Head->del_all_Symbol_in_Scope();
        delete Head;
        this->Head = NULL;
        this->Tail = NULL;
        this->num_Of_Scope = 0;
        return true;
    }
    else
    {
        Scope_Of_Symbol *temp = (this->Head);
        for (; temp->next_In_Lit != (this->Tail); temp = temp->next_In_Lit)
            ;
        Tail->del_all_Symbol_in_Scope();
        delete Tail;
        temp->next_In_Lit = NULL;
        this->Tail = temp;
        num_Of_Scope -= 1;
        return true;
    }
}
bool Lit_Of_Scope::delete_All_Level()
{
    if (this->num_Of_Scope == 0)
        return true;
    else if (this->num_Of_Scope > 0)
    {
        while (this->num_Of_Scope > 0)
        {
            this->delete_High_Level();
        }

        if (num_Of_Scope != 0)
            return false;
        else
            return true;
    }
    return false;
}

int Lit_Of_Scope::get_Num_Scope()
{
    return this->num_Of_Scope;
}

bool is_String(string str)
{
    return not is_Num(str);
}

bool is_Num(string str)
{
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (str[i] < 48 || str[i] > 57)
            return false;
    }
    return true;
}

int count_Char(string str, char c)
{
    int s = 0;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (str[i] == c)
            s += 1;
    }
    return s;
}
void SymbolTable::run(string filename)
{
    ifstream ifs(filename);
    int Block_Of_Scope = 0;
    Lit_Of_Scope group_Scope;
    group_Scope.add_Scope_To_Lit(Block_Of_Scope);
    bool is_true = true;

    while (!ifs.eof())
    {
        string str;
        getline(ifs, str);
        sperate_command sperate;
        sperate.sperate(str);
        if (count_Char(str) >= 3)
        {
            InvalidInstruction invalid_Instruction(str);
            throw InvalidInstruction(str);
            break;
        }
        else if (sperate.command == "INSERT")
        {
            if (count_Char(str) == 2)
            {
                if (sperate.type == "string" || sperate.type == "number")
                {
                    bool is_Check_exist = false;
                    if (group_Scope.Tail->get_Num_Of_Symbol() == 0)
                    {
                        is_Check_exist = false;
                    }
                    Symbol *temp = new Symbol();
                    temp = group_Scope.Tail->Head;
                    while (temp != NULL)
                    {
                        if (temp->get_Symbol_Identifier() == sperate.identifier)
                        {
                            is_Check_exist = true;
                        }
                        temp = temp->next_In_Scope;
                    }
                    if (is_Check_exist == false)
                    {
                        group_Scope.Tail->add_Symbol_To_Scope(sperate.identifier, sperate.type);
                        cout
                            << "success" << endl;
                    }
                    else
                    {
                        Redeclared redeclared_Mess(str);
                        throw Redeclared(str);
                        is_true = false;
                        break;
                    }
                }
            }
            else
            {
                InvalidInstruction invalid_Instruction(str);
                throw InvalidInstruction(str);
                break;
            }
        }

        else if (sperate.command == "BEGIN")
        {
            if (count_Char(str) == 0)
            {
                Block_Of_Scope++;
                if (Block_Of_Scope == group_Scope.get_Num_Scope())
                {
                    group_Scope.add_Scope_To_Lit(Block_Of_Scope);
                }
            }
            else
            {
                InvalidInstruction invalid_Instruction(str);
                throw InvalidInstruction(str);
                break;
            }
        }
        else if (sperate.command == "END")
        {
            if (count_Char(str) == 0)
            {
                if (Block_Of_Scope <= 0)
                {
                    UnknownBlock unknownblockmessage;
                    throw UnknownBlock();
                    is_true = false;
                    break;
                }
                else
                {
                    group_Scope.delete_High_Level();
                    Block_Of_Scope--;
                }
            }
            else
            {
                InvalidInstruction invalid_Instruction(str);
                throw InvalidInstruction(str);
                break;
            }
        }
        else if (sperate.command == "ASSIGN")
        {
            if (count_Char(str) == 2)
            {
                bool is_Check_exist = false;
                if (group_Scope.Tail->get_Num_Of_Symbol() == 0)
                {
                    is_Check_exist = false;
                }
                Symbol *temp = new Symbol();
                temp = group_Scope.Tail->Head;
                while (temp != NULL)
                {
                    if (temp->get_Symbol_Identifier() == sperate.identifier)
                    {
                        is_Check_exist = true;
                    }
                    temp = temp->next_In_Scope;
                }
                if (is_Check_exist == true)
                {

                    string type_Of_Var = group_Scope.Tail->get_Type_Of_Symbol(sperate.identifier);
                    if (type_Of_Var == "string")
                    {
                        if (is_String(sperate.type))
                        {
                            cout << "success " << endl;
                        }
                        else
                        {
                            TypeMismatch typemismatchmessage(str);
                            throw TypeMismatch(str);
                            is_true = false;
                            break;
                        }
                    }
                    else if (type_Of_Var == "number")
                    {
                        if (is_Num(sperate.type))
                        {
                            cout << "success" << endl;
                        }
                        else
                        {
                            TypeMismatch typemismatchmessage(str);
                            throw TypeMismatch(str);
                            is_true = false;
                            break;
                        }
                    }
                }
                else
                {
                    Undeclared undeclearedmessage(str);
                    throw Undeclared(str);
                    is_true = false;
                    break;
                }
            }
            else
            {
                InvalidInstruction invalid_Instruction(str);
                throw InvalidInstruction(str);
                break;
            }
        }
        else if (sperate.command == "LOOKUP")
        {

            if (count_Char(str) == 1)
            {
                bool check_Lookup = false;
                Scope_Of_Symbol *temp;
                temp = group_Scope.Tail;
                while (temp != NULL)
                {
                    if (temp->is_Symbol_identifier_exist_in_Scope(sperate.identifier))
                    {
                        cout << temp->get_Level() << endl;
                        check_Lookup = true;
                        break;
                    }
                    temp = temp->before_In_Lit;
                }
                if (check_Lookup == false)
                {
                    Undeclared undeclaredmessage(str);
                    throw Undeclared(str);
                    break;
                }
            }
            else
            {
                InvalidInstruction invalidinstructionmessage(str);
                throw InvalidInstruction(str);
                break;
            }
        }
        else if (sperate.command == "PRINT")
        {
            bool check_Endl = false;
            if (count_Char(str) == 0)
            {
                for (Scope_Of_Symbol *temp = group_Scope.Head; temp != NULL; temp = temp->next_In_Lit)
                {
                    for (Symbol *tam = temp->Head; tam != NULL; tam = tam->next_In_Scope)
                    {
                        string variable = tam->get_Symbol_Identifier();
                        if (temp->is_Symbol_exist_in_higher_Scope(variable) == false)
                        {
                            check_Endl = true;
                            cout << tam->get_Symbol_Identifier() << "//" << temp->get_Level() << ' ';
                        }
                    }
                }
                if (check_Endl)
                {
                    cout << endl;
                }
            }
            else
            {
                InvalidInstruction invalidinstructionmessage(str);
                throw InvalidInstruction(str);
                break;
            }
        }
        else if (sperate.command == "RPRINT")
        {
            bool check_Endl = false;

            if (count_Char(str) == 0)
            {

                for (Scope_Of_Symbol *temp = group_Scope.Tail; temp != NULL; temp = temp->before_In_Lit)
                {
                    for (Symbol *tam = temp->Tail; tam != NULL; tam = tam->before_In_Scope)
                    {
                        string varible = tam->get_Symbol_Identifier();
                        if (temp->is_Symbol_exist_in_higher_Scope(varible) == false)
                        {
                            check_Endl = true;
                            cout << tam->get_Symbol_Identifier() << "//" << temp->get_Level() << ' ';
                        }
                    }
                }
                if (check_Endl)
                {
                    cout << endl;
                }
            }
            else
            {
                InvalidInstruction invalidinstructionmessage(str);
                throw InvalidInstruction(str);
                break;
            }
        }
        else
        {
            InvalidInstruction invalidinstructionmessage(str);
            throw InvalidInstruction(str);
            break;
        }
    }
    if (Block_Of_Scope > 0 && is_true == true)
    {
        UnclosedBlock unclosemessage(Block_Of_Scope);
        throw UnclosedBlock(Block_Of_Scope);
    }
    group_Scope.delete_All_Level();
    ifs.close();
}
