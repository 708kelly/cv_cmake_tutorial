#include "card.h"
#include <vector>

using namespace std;

Card::Card(string s, string r)
{
}


bool Card::is_same_color( Card* that) 
{
    // 是否相同花色
}


ostream& operator<<(ostream& os, const Card& card)
{
    os << card.suit << ' ' << card.rank;
    return os;
}

bool Card::diff_one_index( Card* that) 
{
    /*
    回傳兩張牌是否符合拿掉的規則（點數加一）
    規則：某張牌的點數加一，且兩張牌花色相同，那麼這兩張牌就必須被拿掉，須注意點數 10、J、Q、K、A 的點數加一依序為點數J、Q、K、A、2 。
    */
}