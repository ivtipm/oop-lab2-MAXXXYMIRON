#include "history.h"

History::History()
{

}

//Записать выражение в историю
void History::WriteHist(const string& Str)
{
    H.push_back(Str);
}

//Считать историю
vector<string> History::GetHistory() const
{
    if(H.size() == 0) throw EmptyHistory;
    return H;
}
