#ifndef HISTORY_H
#define HISTORY_H
#include<iostream>
#include<string>
#include<vector>

using namespace std;

class History
{
    vector<string> H;
public:
    History();

    //Записать выражение в историю
    void WriteHist(const string& Str);
    //Считать историю
    vector<string> GetHistory() const;

    enum ERRORS
    {
        EmptyHistory //У ВАС НЕТ ИСТОРИИ
    };
};

#endif // HISTORY_H
