#include "parser.h"
#pragma once

Parser::Parser()
{
}

//Парсинг выражения(вернет результат)
string Parser::ParsingExpression(string Expression)
{
    DelBorder(Expression);

    if (Digit(Expression)) return Expression;

    string exp1 = "", exp2 = "",
    operation = SearchInflectionPoint(Expression, exp1, exp2);

    exp1 = ParsingExpression(exp1);
    exp2 = ParsingExpression(exp2);

    return RunOperation(operation, stof(exp1), stof(exp2));
}


//Проверить если в выражении лишь одно число
bool Parser::Digit(const string& Expression)
{
    string digit = "0123456789.";
    for(unsigned i = 0; i < Expression.size(); i++)
        if(digit.find(Expression[i]) == string::npos) return false;

    return true;
}


//Удаление лишних скобок в выражении
void Parser::DelBorder(string& mainExp)
{
    unsigned NumberOpenBorder = 0,
    NumberCloseBorder = 0,
    StartIndex = 0,
    StopIndex = 0;

    for(unsigned i = 0; i < mainExp.size(); i++)
        if(mainExp[i] == '(') NumberOpenBorder++;
        else
        {
            StartIndex = i;
            break;
        }
    if(NumberOpenBorder == 0) return;

    for(unsigned i = mainExp.size() - 1; i >= 0; i--)
        if(mainExp[i] == ')') NumberCloseBorder++;
        else
        {
            StopIndex = i;
            break;
        }
    if(NumberCloseBorder == 0) return;

    unsigned OpenBorderInside = 0;
    for(unsigned i = StartIndex; i < StopIndex; i++)
    {
        if(mainExp[i] == '(') OpenBorderInside++;
        else if(mainExp[i] == ')')
        {
            if(OpenBorderInside != 0) OpenBorderInside--;
            else NumberOpenBorder--;
        }
        if (NumberOpenBorder == 0) return;
    }

    NumberCloseBorder -= OpenBorderInside;

    mainExp.erase(0, NumberOpenBorder);
    mainExp.erase(mainExp.size() - NumberCloseBorder, NumberCloseBorder);
}


//Поиск точки перегиба
//(разрыв выражения на два поменьше, в месте с наименьшей по приоритету операцией)
//Вернет два этих выражения
string Parser::SearchInflectionPoint(string mainExp, string& exp1, string& exp2)
{
    for(unsigned i = 0; i < 5; i++)
        for(unsigned j = 0; j < mainExp.size(); j++)
            if(Operations[i].find(mainExp[j]) != string::npos)
                if(RightInflectionPointBinary(j, mainExp))
                {
                    RightLeftExpression(mainExp, j, exp1, exp2);
                    return Operations[i];
                }

    for(unsigned i = 5; i < Operations.size(); i++)
        if(Operations[i].find(mainExp[1]) != string::npos)
        {
            RightExpression(mainExp, exp1, exp2);
            return Operations[i];
        }
}


//Проверка правильности выбора точки перегиба для бинарной операции
bool Parser::RightInflectionPointBinary(unsigned indOper, const string& mainExp)
{
    unsigned OpenBord = 0,
            CloseBord = 0;
    for(unsigned i = indOper; i < mainExp.size(); i++)
    {
        if(mainExp[i] == '(') OpenBord++;
        else if(mainExp[i] == ')') CloseBord++;
    }

    return (OpenBord == CloseBord) ? true : false;
}


//Вернет выражение справа и слева от точки перегиба (бинарной операции)
void Parser::RightLeftExpression(string mainExp, unsigned indOper, string& exp1, string& exp2)
{
    for(unsigned i = indOper + 1; i < mainExp.size(); i++)
        exp2 += mainExp[i];

    for(unsigned i = 0; i < indOper; i++)
        exp1 += mainExp[i];
}


//Вернет выражение справа от точки перегиба (унарной операции)
void Parser::RightExpression(string mainExp, string& exp1, string& exp2)
{
    for(unsigned i = (mainExp[1] == 'n') ? 2 : 3; i < mainExp.size(); i++)
        exp2 += mainExp[i];
    exp1 = "0";
}


//Выполнение опрации в зависимости от точки перегиба
string Parser::RunOperation(const string& oper, float exp1, float exp2)
{
    if(oper == "+") return to_string(exp1 + exp2);
    else if (oper == "-") return to_string(exp1 - exp2);
    else if (oper == "*") return to_string(exp1 * exp2);
    else if (oper == "/") return (exp2 == 0) ? "0" : to_string(exp1 / exp2);
    else if (oper == "^") return to_string(pow(exp1, exp2));
    else if (oper == "√") return (exp1 + exp2 < 0) ? "0" : to_string(sqrt(exp1+exp2));
    else if (oper == "Sin") return to_string(sin(exp1+exp2));
    else if (oper == "Cos") return to_string(cos(exp1+exp2));
    else if (oper == "Tan") return to_string(tan(exp1+exp2));
    else if (oper == "Ln") return to_string(log(exp1+exp2));
    else if (oper == "—") return to_string(-(exp1+exp2));
    else return to_string(exp(exp1+exp2));
}
