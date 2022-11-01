#include <iostream> 
#include <string>
#include "card.h"
#include "deck.h"

using namespace std;

int main() {
    // init
    vector<int> score_list;
    string s;
    string delimiter = ",";
    string token;
    while(getline(cin,s)){
        if(s=="-1"){break;}
        Deck deck;
        size_t pos = 0;
        // parse input
        while ((pos = s.find(delimiter)) != string::npos) 
        {
            token = s.substr(0, pos);
            deck.add_card(new Card(token.substr(0,1), token.substr(1,token.size()-1)));
            s.erase(0, pos + delimiter.length());
        }
        deck.add_card(new Card(s.substr(0,1), s.substr(1,s.size()-1)));
        score_list.push_back(deck.cal_max_score());
    }
    for(int score:score_list){cout << score << endl;}
    return 0;
}
