#include <math.h>
#include<string>
#include<vector>

using namespace std;

class Parser
{
    const vector<string> Operations =
    {"+", "-", "*", "/", "^", "√", "Sin", "Cos", "Tan", "Ln", "Exp", "—"};
public:
    Parser();

    //Парсинг выражения(вернет результат)
    string ParsingExpression(string Expression);

private:
    //Удаление лишних скобок в выражении
    void DelBorder(string& mainExp);

    //Поиск точки перегиба
    //(разрыв выражения на два поменьше, в месте с наименьшей по приоритету операцией)
    //Вернет два этих выражения
    string SearchInflectionPoint(string mainExp, string& exp1, string& exp2);

    //Проверка правильности выбора точки перегиба для бинарной операции
    bool RightInflectionPointBinary(unsigned indOper, const string& mainExp);

    //Вернет выражение справа и слева от точки перегиба (бинарной операции)
    void RightLeftExpression(string mainExp, unsigned indOper, string& exp1, string& exp2);

    //Вернет выражение справа от точки перегиба (унарной операции)
    void RightExpression(string mainExp, string& exp1, string& exp2);

    //Выполнение опрации в зависимости от точки перегиба
    string RunOperation(const string& oper, float exp1, float exp2);

    //Проверить если в выражении лишь одно число
    bool Digit(const string& Expression);
};
