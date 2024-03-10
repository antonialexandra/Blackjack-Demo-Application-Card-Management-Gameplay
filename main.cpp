#include <iostream>
#include <string>
#include <vector>
//1

using namespace std;

class LcgGenerator {
private:
    uint16_t mA=0, mC=0, mCurrentX=0, mM=0;
public:
    LcgGenerator(uint16_t x, uint16_t y, uint16_t z, uint16_t a) {
        mA = x;
        mC = y;
        mCurrentX = z;
        mM = a;
    }

    uint16_t next() {
        //Xn+1 = (a * Xn + c) mod m.
        this->mCurrentX = (mA * mCurrentX + mC) % mM;
        return this->mCurrentX;
    }

};

class Card {
    //Un câmp de tip std::string numit mSuite și unul de tip uint16_t numit mValue, ambele private.
private:
    std::string mSuite;
    uint16_t mValue=0;
public:
    //Un constructor care să ia ca argumente un obiect de tip std::string (ca referință constantă) și o valoare de tip uint16_t, și care să inițializeze câmpurile de mai sus.
    //Operatorul ==, const qualified, care să ia ca argument un alt obiect de tip Card (dat ca referință constantă) întoarcă true doar dacă argumentul are aceleași valori cu obiectul curent pentru ambele câmpuri.
    Card(const string& x, uint16_t y) {
        mSuite = x;
        mValue = y;
    }

    //Operatorul ==, const qualified, care să ia ca argument un alt obiect de tip Card (dat ca referință constantă) întoarcă true doar dacă argumentul are aceleași valori cu obiectul curent pentru ambele câmpuri.
    bool operator==(const Card &carte) const {
        if (this->mSuite == carte.mSuite && this->mValue == carte.mValue) {
            return true;
        }
        return false;
    }

    //O metodă toString, fără argumente, const-qualified, care să întoarcă un std::string format din concatenarea valorii (mValue) și culorii cărții (mSuite), cu virgulă între ele.
    string toString() const {
        return to_string(this->mValue) + ',' + this->mSuite;
    }

    //O metodă isFake, fără argumente, const-qualified, care să întoarcă true dacă cartea este falsă (nu are o culoare validă sau are un număr invalid - în afara intervalului [2:14]).
    bool isFake() const {
        if ((this->mSuite != "trefla" && this->mSuite != "romb" && this->mSuite != "rosu" && this->mSuite != "negru") ||
            this->mValue < 2 || this->mValue > 14) {

            return true;
        }
        return false;
    }

    //O metodă getBlackjackValue, fără argumente, const-qualified, care să întoarcă numărul de puncte pe care l-ar obține un jucător de Blackjack pentru cartea respectivă, ca valoare de tip uint16_t.
    uint16_t getBlackjackValue() const {
        if (this->mValue <= 10) {
            return mValue;
        }
        return 10;
    }
};

class CardPack {
    //Un câmp de tip std::vector<Card> numit mCards și un câmp mCurrentIndex de tip uint16_t, ambele private.
    //Un constructor cu un argument de tip bool numit empty, cu valoare implicită true. Dacă argumentul este true, constructorul va lăsa vectorul mCards gol.
    // Dacă în schimb este false, va popula vectorul cu cele 48 de cărți necesare pentru jocul de Blackjack (vezi punctul 3 de mai jos). În ambele situații va inițializa și câmpul mCurrentIndex cu 0.
    //O metodă numită goodForBackjack, fără argumente, const-qualified, care să întoarcă true doar dacă pachetul de cărți este bun pentru Blackjack (vezi punctul 1 de mai jos).
private:
    std::vector<Card> mCards;
    uint16_t mCurrentIndex;
public:
    CardPack(bool empty) {

        if (empty) {
            mCurrentIndex = 0;
            mCards.clear();
        } else {
            mCurrentIndex = 0;
            for (int i = 0; i < 4; i++) {
                for (int j = 2; j <= 14; j++) {
                    if (i == 0 && j != 11) {
                        mCards.push_back(Card("rosu", j));
                    }
                    if (i == 1 && j != 11) {
                        mCards.push_back(Card("negru", j));
                    }
                    if (i == 2 && j != 11) {
                        mCards.push_back(Card("romb", j));
                    }
                    if (i == 3 && j != 11) {
                        mCards.push_back(Card("trefla", j));
                    }
                }
            }
            /* for (int i = 0; i < mCards.size(); i++){
                 cout<<mCards[i].getBlackjackValue()<<" ";
             }*/
        }
    }

    bool goodForBackjack() const {
        for (int i = 0; i < mCards.size(); i++) {

            if (mCards[i].isFake())
                return false;
        }
        return true;
    }

    bool ok() const {
        int ok1 = 1, ok2 = 1, ok3 = 0;
        for (int i = 0; i < mCards.size(); i++) {
            if (mCards[i].isFake()) {
                ok1 = 0;
                break;
            }
        }
        for (int i = 0; i < 52- 1; i++) {

            for (int j = i + 1; j < 52; j++) {
                if (mCards[i].operator==(mCards[j])) {
                    ok2 = 0;
                    break;
                }
            }
            if(ok2==0) break;

        }
        if (mCards.size() == 52) {
            ok3 = 1;
        }
        if (ok1 == 1 && ok2 == 1 && ok3 == 1) {
            return true;
        } else return false;
    }

    void addCard(const Card &carte) {
        mCards.push_back(carte);
    }

    void shuffle(uint16_t a1, uint16_t c1, uint16_t x1, uint16_t a2, uint16_t c2, uint16_t x2) {
        LcgGenerator a(a1, c1, x1, mCards.size());
        LcgGenerator b(a2, c2, x2, mCards.size());
        uint16_t x, y;
        mCurrentIndex=0;

        for(int i=0;i<50;i++){
            x=a.next();
            y=b.next();
            swap(mCards[x], mCards[y]);
        }
    }

    void printPack() const {
        for (int i = 0; i < mCards.size(); i++) {
            cout << mCards[i].toString();
            cout << endl;
        }
    }

    Card nextCard() {
        mCurrentIndex++;
        Card x = mCards[mCurrentIndex-1];

        return x;
    }
};

class Player {
public:
    string mName;
    uint16_t mMoney = 0;
    uint16_t mPoints = 0;

    Player(string x, uint16_t y) {
        mName = x;
        mMoney = y;
        mPoints = 0;
    }

    string toString() const {
        return this->mName + ": " + to_string(this->mMoney);
    }

    void pick(const Card &x) {
        mPoints += x.getBlackjackValue();
    }

    void play(CardPack &x) {
        while (mPoints < 17) {
            pick(x.nextCard());
        }
    }

    void newRound() {
        mPoints = 0;
    }

    bool lostRound() const {
        if (mPoints > 21) {
            return true;
        }
        return false;
    }

    uint16_t getPoints() const {
        return mPoints;
    }

    void operator--() {
        mMoney -= 10;
    }

    void operator++() {
        mMoney += 10;
    }

    bool lostGame() const {
        if (mMoney < 10) {
            return true;
        }
        return false;
    }

};

int main() {
    string comanda;
    uint16_t numar_carte=0, a1, c1, x1, a2, c2, x2, n;
    string stema_carte, nume;
    uint16_t suma_bani=0;
    vector<Player> jucatori;
    // CardPack carti(true);
    CardPack pachet1(true);
    cin >> comanda;
    if (comanda == "check_cards") {

        while(cin >> numar_carte) {
            getchar();
            cin>>stema_carte;
            Card test(stema_carte,numar_carte);
            pachet1.addCard(test);
        }

    }
    //cout<<pachet.size();
    if (comanda == "shuffle_cards") {

        cin >> a1 >> c1 >> x1 >> a2 >> c2 >> x2;
        while (cin >> numar_carte) {
            getchar();
            cin>>stema_carte;
            Card test(stema_carte,numar_carte);
            pachet1.addCard(test);
        }


    }
    Player dealer("dealer",2127);
    if(comanda=="play_game")
    {
        int numarjucatori;
        CardPack pachet(false);
        cin>>numarjucatori;
        for(int32_t i=0;i<numarjucatori;i++)
        {
            cin>>nume;
            cin>>suma_bani;
            Player jucator(nume,suma_bani);
            jucatori.push_back(jucator);

        }
        uint16_t a1,c1,x1,a2,c2,x2;
        while(cin>>a1>>c1>>x1>>a2>>c2>>x2)
        {
            pachet.shuffle(a1,c1,x1,a2,c2,x2);

            for(int32_t i=0;i<jucatori.size();i++){
                jucatori[i].pick(pachet.nextCard());
                jucatori[i].pick(pachet.nextCard());
            }

            dealer.pick(pachet.nextCard());
            dealer.pick(pachet.nextCard());

            for(int32_t i=0;i<jucatori.size();i++){
                jucatori[i].play(pachet);
            }

            dealer.play(pachet);

            for(int i=0;i<jucatori.size();i++)
            {


                if(!jucatori[i].lostRound() && (dealer.getPoints()<jucatori[i].getPoints() || dealer.lostRound()))
                {
                    jucatori[i].operator++();
                }
                if((!dealer.lostRound() && dealer.getPoints()>jucatori[i].getPoints()) || jucatori[i].lostRound() )
                {
                    jucatori[i].operator--();
                }
                if(!jucatori[i].lostGame())
                {
                    jucatori[i].newRound();

                }
                else
                {
                    vector<Player>::iterator it = jucatori.begin()+i;
                    jucatori.erase(it);
                    i--;
                }
            }

            dealer.newRound();
        }


        for(int i=0;i<jucatori.size();i++){
            cout<<jucatori[i].toString()<<endl;
        }

    }
    if(comanda=="check_cards") {
        int ok1 = 1, ok2 = 0;
        if (pachet1.goodForBackjack()) ok1 = 0;
        // cout<<pachet.size();
        if (pachet1.ok()) ok2 = 1;
        if (ok1 == 1) {
            cout << "Pachet masluit\n";
        }
        if (ok1 == 0 && ok2 == 0) {
            cout << "Pregatit pentru Blackjack\n";
        }
        if (ok1 == 0 && ok2 == 1) {
            cout << "Pachet OK\n";
        }
    }
    if (comanda=="shuffle_cards"){
        pachet1.shuffle(a1,c1,x1,a2,c2,x2);
        pachet1.printPack();

    }



    return 0;
}