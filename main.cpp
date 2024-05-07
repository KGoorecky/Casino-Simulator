#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <limits>
#include <fstream>

using namespace std;

class Gracz{
private:
    string nazwa;
    int zetony;

public:
    Gracz(){
        nazwa = "";
        zetony = 0;
    }

    Gracz(string nazwa) : nazwa(nazwa), zetony(zetony) {
        nazwa = nazwa;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(500, 1000);

        int randomInt = dist(gen);

        zetony = randomInt;
    }

    string getName(){
        return Gracz::nazwa;
    }
    int getZetony(){
        return Gracz::zetony;
    }

    void setNazwa(string nazwa){
        Gracz::nazwa = nazwa;
    }
    void setZetony(int zetony){
        Gracz::zetony = zetony;
    }

    int addZetony(int ile){
        zetony += ile;
    }
    int subtractZetony(int ile){
        zetony -= ile;
        if(zetony < 0){
            zetony = 0;
        }
    }
};

void blackjack(Gracz &g, int startBet){
    cout << endl << "Witaj w BLACKJACK!" << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 13);

    int krupierPula = 0;
    int graczPula = 0;

    for(int i=0; i < 2; i++){

        int krupierLos = dist(gen);

        if(krupierLos>9){krupierLos=10;}
        else if (krupierLos==1 && krupierPula+10<=21){
            krupierLos = 10;
        }

        krupierPula += krupierLos;

        int graczLos = dist(gen);

        if(graczLos>9){graczLos=10;}
        else if (graczLos==1 && graczPula+10<=21){
            graczLos = 10;
        }

        graczPula += graczLos;
    }

    cout << endl << "Twoje dwie karty maja razem: " << graczPula << endl;

    string action = "";

    while(true){

        cout << endl << "Suma kart krupiera: " << krupierPula << endl;
        cout << "Suma kart gracza: " << graczPula << endl << endl;

        int krupierPulaAS = krupierPula + 10;

        if(krupierPula<=16){
            int krupierLos = dist(gen);

            if(krupierLos>9){krupierLos=10;}
            else if (krupierLos==1 && krupierPulaAS<=21){
                krupierLos = 10;
            }

            krupierPula += krupierLos;
        }

        if(krupierPula>21){
            break;
        }

        if(action=="stand" && krupierPula>16){
            break;
        }

        if(action=="stand") {
            continue;
        }
        do{
            cout << "Co zamierzasz zrobic? (Hit/Stand/DoubleDown): ";
            cin >> action;
            cout << endl;

            for (char& ch : action) {
                ch = std::tolower(ch);
            }
        } while(action != "hit" && action != "stand" && action != "doubledown");

        int graczPulaAS = graczPula + 10;

        if(action=="hit" || action=="doubledown"){
            int graczLos = dist(gen);

            if(graczLos>9){graczLos=10;}
            else if (graczLos==1 && graczPulaAS<=21){
                graczLos = 10;
            }

            graczPula += graczLos;
        }
            if(action=="doubledown") {
                    startBet *= 2;
            }


        if(graczPula>=21 || krupierPula>=21){
            break;
        }
    }

    if (graczPula > 21) {
        cout << "Przegrales!" << endl;
        g.subtractZetony(startBet);
    } else if (krupierPula > 21) {
        cout << "Wygrales!" << endl;
        g.addZetony(startBet);
    } else if (graczPula == krupierPula) {
        cout << "Remis!" << endl;
    } else if (graczPula > krupierPula) {
        cout << "Wygrales!" << endl;
        g.addZetony(startBet);
    } else {
        cout << "Przegrales!" << endl;
        g.subtractZetony(startBet);
    }

    cout << endl << "Ostateczna suma kart krupiera: " << krupierPula << endl;
    cout << "Ostateczna suma kart gracza: " << graczPula << endl;
}

void jednorekiBandyta(Gracz &g, int startBet){
    cout << endl << "Witaj w JEDNOREKIM BANDYCIE!" << endl;

    const int LUCKY_NUMBER = 7;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 9);

    int fstSlot = dist(gen);
    this_thread::sleep_for(chrono::seconds(1));
    cout << fstSlot << "   ";

    int sndSlot = dist(gen);
    this_thread::sleep_for(chrono::seconds(1));
    cout << sndSlot << "   ";

    int trdSlot = dist(gen);
    this_thread::sleep_for(chrono::seconds(1));
    cout << trdSlot << "   " << endl;

    if(fstSlot == sndSlot && sndSlot == trdSlot){
        if(fstSlot==LUCKY_NUMBER && sndSlot==LUCKY_NUMBER && trdSlot==LUCKY_NUMBER){
            cout << endl << "BRAWO! Trafiles na szczesliwa 777!" << endl;
            startBet *= 15;
        }
        else{
            cout << endl << "Wygrana! Trafiles na trzy takie same liczby!" << endl;
            startBet *= 7;
        }
        g.addZetony(startBet);
    }
    else{
        g.subtractZetony(startBet);
    }

}

void ruletka(Gracz &g, int startBet){
    cout << endl << "Witaj w RULETCE!" << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 36);

    const int ROZMIAR = 18;

    string tryb;

    string kolorGracz;
    int liczbaGracz = 0;

    int kolorWin = 0;

    int poleLos = dist(gen);

    const int czarnePola[ROZMIAR] = {15, 4, 2, 17, 6, 13, 11, 8, 10,
                        24, 33, 20, 31, 22, 29, 28, 35, 26};

    const int czerwonePola[ROZMIAR] = {32, 19, 21, 25, 34, 27, 36, 30, 23,
                            5, 16, 1, 14, 9, 18, 7, 12, 3};

    while(tryb != "kolory" && tryb != "liczby"){
        cout << endl << "Na jakich zasadach gramy? (kolory/liczby): ";
        cin >> tryb;
        cout << endl;
    }

    if(tryb == "kolory"){
        while(kolorGracz != "czarny" && kolorGracz != "czerwony"){
            cout << endl << "Jaki kolor wybierasz? (czarny/czerwony): ";
            cin >> kolorGracz;
            cout << endl;
        }

        for(int i=0; i < ROZMIAR; i++){
            if(czarnePola[i] == poleLos && kolorGracz == "czarny"){
                kolorWin = 1;
            }
        }

        for(int i=0; i < ROZMIAR; i++){
            if(czerwonePola[i] == poleLos && kolorGracz == "czerwony"){
                kolorWin = 2;
            }
        }

        switch(kolorWin){
            case 0:
                cout << endl << "Niestey trafiles na pole o przeciwnym kolorze! Jego numer to: " << poleLos << endl;
                g.subtractZetony(startBet);
                break;
            case 1:
                cout << endl << "BRAWO TRAFILES NA CZARNE POLE! Jego numer to: " << poleLos << endl;
                g.addZetony(startBet);
                break;
            case 2:
                cout << endl << "BRAWO TRAFILES NA CZERWONE POLE! Jego numer to: " << poleLos << endl;
                g.addZetony(startBet);
                break;
        }
    }

    if(tryb == "liczby"){
        do{
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Niepoprawne dane. Wprowadz liczbe." << endl;
            }

            cout << endl << "Jaka liczbe wybierasz? (0-36): ";
            cin >> liczbaGracz;
            cout << endl;
        } while ((liczbaGracz < 0 || liczbaGracz > 36) || cin.fail());

        if(liczbaGracz == poleLos){
            cout << endl << "BRAWO TRAFILES NA WYBRANA LICZBE! Liczba ta to: " << poleLos << endl;
            startBet *= 35;
            g.addZetony(startBet);
        }
        else{
            cout << endl << "Niestey trafiles na inna liczbe niz wybrana! Liczba ta to: " << poleLos << endl;
            g.subtractZetony(startBet);
        }
    }
}

void kasyno(Gracz &g){
    cout << "Witaj w KASYNIE!" << endl;
    cout << g.getName() << ", twoja liczba zetonow to: " << g.getZetony() << endl << endl;

    int gra=0;
    int startBet=10;
    string kontynuacjaZabawy = "tak";
    string kontynuacjaGry = "tak";


    do{
        cout << endl << "W co chcialbys zagrac? (Blackjack - 1 / JednorekiBandyta - 2 / Ruletka - 3): ";
        cin >> gra;
        cout << endl;

        while((gra < 1 || gra > 3) || cin.fail()){
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Niepoprawne dane. Wprowadz liczbe." << endl;
            }
            cout << endl << "Wyberz jedna z trzech podanych gier! (Blackjack - 1 / JednorekiBandyta - 2 / Ruletka - 3): ";
            cin >> gra;
            cout << endl;
        }

        cout << endl << "Ile zetonow stawiasz? (min. 10): ";
        cin >> startBet;
        cout << endl;

        while((startBet < 10 || startBet > g.getZetony()) || cin.fail()){
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Niepoprawne dane. Wprowadz liczbe." << endl;
            }

            cout << endl << "Wprowadz stawke nie mniejsza niz 10 zetownow i nie wieksza niz twoja aktualna suma zetonow: ";
            cin >> startBet;
            cout << endl;
        }

        do{
            switch(gra){
                case 1:
                    blackjack(g, startBet);
                    break;
                case 2:
                    jednorekiBandyta(g, startBet);
                    break;
                case 3:
                    ruletka(g, startBet);
                    break;
            }

            cout << endl << "Aktualna liczba zetonow to: " << g.getZetony() << endl;

            if(startBet > g.getZetony()){
                startBet = g.getZetony();
            }

            if(g.getZetony() < 10){
                break;
            }

            cout << endl << "Czy chcesz kontynuowac ta gre na takiej stawce? (tak/nie): ";
            cin >> kontynuacjaGry;
            cout << endl;

            for (char& ch : kontynuacjaGry) {
                ch = std::tolower(ch);
            }

        } while(kontynuacjaGry == "tak" || kontynuacjaGry == "t");

        if(g.getZetony() < 10){
            cout << endl << "Posiadasz niewystarczajaca liczbe zetonow by kontynuowac dalsza gre! DZIEKUJEMY ZA GRE!" << endl;
            break;
        }

        cout << endl << "Czy chcesz kontynuowac zabawe w kasynie? (tak/nie): ";
        cin >> kontynuacjaZabawy;
        cout << endl;

        for (char& ch : kontynuacjaZabawy) {
            ch = std::tolower(ch);
        }
        if(kontynuacjaZabawy != "tak" && kontynuacjaZabawy != "t"){
            cout << endl << "DZIEKUJEMY ZA GRE!" << endl;
        }

    } while(kontynuacjaZabawy == "tak" || kontynuacjaZabawy == "t");

}

int main()
{
    Gracz g("Human");

    kasyno(g);

    ofstream outputFile("top_lista.txt", ios::app);

    if (outputFile.is_open()) {
        outputFile << g.getName() << "\t" << g.getZetony() << endl;

        outputFile.close();
    } else {
        cout << "Nie mo¿na otworzyæ pliku." << endl;
    }

    ifstream inputFile("top_lista.txt");

    if (inputFile.is_open()) {
        string line;

        cout << endl << "--| Lista TOP Graczy |--" << endl;
        cout << "NAZWA" << "\t" << "ZETONY" << endl;

        while (getline(inputFile, line)) {
            cout << line << endl;
        }

        inputFile.close();
    } else {
        cout << "Nie mo¿na otworzyæ pliku." << endl;
    }


    return EXIT_SUCCESS;
}
