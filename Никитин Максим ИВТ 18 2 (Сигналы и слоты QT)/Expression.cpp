#include "Expression.h"

Expression::Expression()
{
    exp = "0";
}

void Expression::SetExpression(string expres)
{
    if(expres[0] == '-')
    {
        exp = "—";
        expres.erase(0, 1);
        exp += expres;
    }
    else exp = expres;
}

//Гетер выражения
string Expression::GetExpression() const
{
    return exp;
}

//Добавить цифру в выражение
void Expression::   AddDigit(char digit)
{
    if(exp == "0")
    {
        exp = digit;
        return;
    }
    if(exp[exp.size() - 1] != ')')
    {
        exp.push_back(digit);
    }
}

//Добавить в выражение операцию, типа Sin, Cos, √ и т.д.
void Expression::AddInFrontOperation(const string& operation)
{
    if(exp == "0")
    {
        exp = operation;
        return;
    }
    if(Operations.find(exp[exp.size() - 1]) != string::npos
    || Functions.find(exp[exp.size() - 1]) != string::npos
    || exp[exp.size() - 1] == '(')
    {
        exp += operation;
    }
}

//Добавить в выражение операцию, типа +, -, *, ^
void Expression::AddBehindOperations(char operation)
{
    if(exp == "0" && operation == '-')
    {
        exp = "—";
        return;
    }
    if(exp == "—") return;
    if(Functions.find(exp[exp.size() - 1]) != string::npos || exp[exp.size() - 1] == '(')
    {
        exp += "—";
    }

    if(Operations.find(exp[exp.size() - 1]) != string::npos)
    {
        exp[exp.size() - 1] = operation;
        return;
    }
    if(Digits.find(exp[exp.size() - 1]) != string::npos
    || exp[exp.size() - 1] == ')')
    {
        exp += operation;
    }
}

//Дабавть скобку
void Expression::AddBracket(char bracket)
{
    if(bracket == '(')
    {
        if(exp == "0")
        {
            exp = bracket;
            return;
        }
        if(Operations.find(exp[exp.size() - 1]) != string::npos
        || Functions.find(exp[exp.size() - 1]) != string::npos
        || exp[exp.size() - 1] == bracket)
        {
            exp.push_back(bracket);
        }
    }
    else if(bracket == ')')
    {
        if(!CheckCloseBracket()) return;
        if(Digits.find(exp[exp.size() - 1]) != string::npos
        || exp[exp.size() - 1] == bracket)
        {
            exp.push_back(bracket);
        }
    }
}

//Проверка возможности поставить закрываюшую скобку
bool Expression::CheckCloseBracket() const
{
    unsigned open = 0, close = 0;
    for(unsigned i = 0; i < exp.size(); i++)
    {
        if(exp[i] == '(') open++;
        else if (exp[i] == ')') close++;
    }
    return (open > close) ? true : false;
}

//Добавить точку
void Expression::AddPoint()
{
    if(Digits.find(exp[exp.size() - 1]) != string::npos)
    {
        if (!SecondPoint())
            exp.push_back('.');
    }
}

//Проверка чтобы не поставить вторую точку в числе
bool Expression::SecondPoint() const
{
    for(int i = exp.size() - 1; i >= 0; i--)
    {
        if (exp[i] == '.') return true;
        if (Digits.find(exp[i]) == string::npos) break;
    }
    return false;
}

//Стереть последнюю цифру, операцию, функцию или разделитель
 void Expression::Backspace()
 {
     unsigned index = exp.size() - 1;
     if(Functions.find(exp[exp.size() - 1]) != string::npos)
     {
        if(exp.substr(index - 1) == "Ln")
        {
            exp.erase(index - 1, 2);
        }
        else if(exp.substr(index - 2) == "Sin"
        || exp.substr(index - 2) == "Cos"
        || exp.substr(index - 2) == "Tan"
        || exp.substr(index - 2) == "Exp"
        || exp.substr(index - 2) == "√"
        || exp.substr(index - 2) == "—")
        {
            exp.erase(index - 2, 3);
        }
     }
     else
     {
         exp.erase(index, 1);
     }


     if(exp == "") exp = "0";
 }

 //Проверить провильно ли введено выражение, чтобы для поиска результата
 bool Expression::RightExpression() const
 {
     if(CheckCloseBracket()) return false;
     return (Digits.find(exp[exp.size() - 1]) != string::npos || exp[exp.size() - 1] == ')')
     ?  true
     :  false;
 }

//Очистить выражение
void Expression::Drop()
{
    exp = "0";
}
