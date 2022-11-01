# hw2 撲克牌作業
[hackmd](https://hackmd.io/_bUPVsDGSxaj-EsOyhY5qQ)
* 練習重點
    * class
    * 使用 template function
    * vector
    * 其餘基本語法
* 實作兩個 class 和一個 template function

~~會給對應的 python code~~
和一部分的 c++ 程式
**只能動 card.cpp 和 deck.cpp**

可以使用 example/ 裡的三個範例來確認是否正確

>(基本上應該可以不用看題目詳述XD，直接看 code 裡的註解就好了～)


### 程式邏輯
1. 一次會給 9 張牌，在 `main.cpp` 會依序將每一張牌轉換成 Card，並依照拿牌規則將符合的牌放入 Deck 的 vector<Card> 中
2. 在拿完牌組後，會建立 4 $\times$ 13 的 bool 矩陣，方便計算，e.g. cards 有一張 SA，對應的 matrix[0][0] 就會是 `True`
3. 建議先將 Card.cpp 完成，再開始寫 Deck.cpp
4. Deck.cpp 裡的 check_continous()，input 是一個 len=13 的 vector，分別代表 A~K，這是一個 template function，可以放入 Int/bool

以下是漏漏長的題目
### class 1

我們將在程式中建立名為 Card 的類別，每個 Card 物件裡面儲存該張撲克牌的花色和點數。類別的一部份如下：
``` cpp
class Card
{
    public:
        Card(string s, string r);  // init
        bool is_same_color(Card* that) ;  // 比較兩張牌是否擁有同樣花色
        bool diff_one_index(Card* that) ;  // 回傳兩張牌是否符合拿掉的規則
        tuple<int, int> get_coordinate(){return(std::make_tuple(suit, rank));}; // get suit and rank
        friend ostream& operator<<(ostream& os, const Card& card); // print
    private:
        int suit; // 花色
        int rank; // 數字
        const vector<string> color_list = {"S", "H", "D", "C"}; // 牌組花色種類
        const vector<string> num_list = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"}; // 牌組數字
};
```

### class 2

一套牌組 Deck 有五張撲克牌。你的程式應該讀取撲克牌資訊，建立五個 Card 物件，並依照以下規則計算分數：
```
規則 a：如果你打出一張 $A$，你可以獲得 $1$ 分。
規則 b：如果你打出一對，也就是有兩張相同點數的牌，每對可以獲得 $2$ 分。
規則 c：如果你打出同花，也就是五張同一花色的牌，你可以獲得 $3$ 分。
規則 d：如果你打出順子，也就是五張順連的牌，你可以獲得 $5$ 分。順連與否不考慮花色，也不因點數而中斷，比如說黑桃$Q$、梅花$K$、方塊$A$、梅花$2$、黑桃$3$ 這種組合也算順連。換言之，不考慮花色的話，共有 13 種順連的方式。
規則 e：如果你打出葫蘆，也就是三張同一點數的牌，加一對其他點數的牌，你可以獲得 $10$ 分。
規則 f：如果你打出四條，也就是四張同一點數的牌，你可以獲得 $20$ 分。
規則 g：如果你打出同花順，也就是五張同一花色且順連的牌，你可以獲得 $100$ 分。
```
在遊戲中，一張牌只能用一次。比如說當你能打出同花順，代表你一定也可以打出同花或是順子，這時候你只會獲得同花順的分數（或者說，我們假設你會選擇以分數最大化的方式出牌）；又或者是你打出了四張7、一張黑桃 A，這時你會獲得四條及一張A的分數，共21分，一對不重複計分。
 method（成員函數）
``` cpp
class Deck
{
    public:
        Deck():matrix(4, std::vector<bool>(13, false)), cards(0){} // constructor
        ~Deck(); // destructor
        void add_card(Card* card); // 新增牌組
        int cal_max_score(); // 計算牌組分數
        int count_num_without_color(int x); // 不考慮牌組花色，特定數字的出現數量
        friend ostream& operator<<(ostream& os, const Deck& deck); // print
    private:
        vector<Card*> cards;  // 牌的一維 list
        std::vector<std::vector<bool> > matrix;  // 牌的二維矩陣(4*13)
        vector<int> num_without_color_list;  // 不考慮牌組花色的數字數量陣列

        void build_cards(); // 建立牌組矩陣 cards -> matrix
        void get_num_without_color(); // matrix -> num_without_color_list
        // 分數規則
        int check_a();
        int check_b();
        bool check_c();
        bool check_d();
        bool check_e();
        bool check_f();
        bool check_g();
};
```

## main.cpp
主程式應該建立一些 Deck 物件，並在讀到新卡片的時候建立一個 Card 物件，再放到某個 Deck 物件中。
一個人拿到的牌並不會重複。但為了增加遊戲的困難度，我們新增了一個規定，每個人在開局時會依序收到九張牌，
```
1. 若新拿到一張牌，其點數為手中某張牌的點數加一，且兩張牌花色相同，那麼這兩張牌就必須被拿掉，須注意點數 10、J、Q 、 K、A   的點數加一依序為點數J、Q 、 K、A 、2 。
2. 終止條件: 一直拿到九張牌都看過了，或是拿滿五張牌了。
```
> 舉例來說，若你拿到了黑桃 2、方塊3 、黑桃5 ，新拿到一張方塊4 ，此時方塊3  和方塊4  都必須被拿掉。再新拿到一張紅心8 ，可以繼續拿牌，再新拿到一張黑桃 6，此時黑桃 5 和黑桃 6 都必須被拿掉。
> 
你可能會想幫你的類別實作一些成員函數，例如在 Deck 類別中寫一個 method，確保新增加的卡片沒有違反新規定，又或者是回傳牌組總分。

本題會若干組撲克牌，遇到`-1`則終止讀取，請計算並印出每一個人能拿到的最高分數。



### example

```
Input
SK,S8,S3,H2,C6,SA,S2,H3,S4 // 9張牌
SK,S8,S3,H2,S4,SA,S2,H3,C6 // 9張牌
-1

Output
0
0
```
