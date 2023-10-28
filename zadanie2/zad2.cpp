#include<iostream>
#include<fstream>
using namespace std;

struct punkt{  //struktura do której wrzucane będą wszytkie punkty
    float x;
    float y;
};

bool czy_dobry(punkt a, punkt b, punkt c){                      //algorytm który oblicza pole równoległoboku
    float pole = ((b.y-a.y)*(c.x-b.x) - (b.x-a.x)*(c.y-b.y));   //stworzonego przez wektory AB BC oraz ich odbicia
    if(pole>0)
        return true;
    else
        return false;

}
void figura(punkt punkty[], int il)
{
    if(il<3) {                              //gdy podane są tylko 2 punkty otoczka wypukła nie może być zrobiona
        cout << "za malo punktow";
        return;
    }
    bool dobre[il];                         //inicjowana tablica która posłuży do znajdowania 'dobrych punków'
    for (int i=0;i<il;i++)
        dobre[i]= false;//na początku nadaje wszytkim elemntom tablicy wartość false

    int lewy = 0;

    /*inicjowanie zmiennej lewy która będzie przechowywała indeks w strukturze na którym znajduje sie najbardzej
    'oddalony na lewo' punkt czyli mający najmiejsza wartość x*/
    for(int i=0; i<il;i++)
        /*wyszukanie punktu o najmniejszej wartości na osi x,
        i odpowiada za indeks w stukturze sprawdzanego punktu
        gdy wartość x punktu jest mniejsza niż wartość poprzedniego 'podejrzanego'
        wartość lewy przyjmuje indeks punktu sprawdzanego*/
            if(punkty[i].x<punkty[lewy].x)
            lewy = i;

    int pun = lewy, pot;
    /*inicjowanie zmiennej pun która przyjmuje wartość lewy pun będzie przechowywał
     indeks punktu który należy do otoczki wypukłej a od którego szukamy następnego*/

    while(true) {
        pot = (pun+1)%il;               //indeks punkt od którego zaczynamy sprawdzanie
        for (int i = 0; i < il; i++)
            if(czy_dobry(punkty[pun],punkty[i],punkty[pot]))
                /*jeżeli pole jest dodatnie to znaczy że zwrot wektora
                jest przeciwny do ruchu wskazówek zegara zamieniamy potencjalny indeks
                na indeks tego punktu*/
                pot = i;

        dobre[pun]=true; //po wyjściu z pentli mamy punkt kóry należy do otoczi czyli jego indeks przyjmuje wartosć true
        pun = pot;       // nasz potencjalny punkt staje sie punktem dla którego będziemy szukać kolejnego
        if(pun == lewy)         /* jeżeli punkt ma taki sam indeks jak ten od którego zaczynaliśmy znaczy to
            że otoczka zrobiona i można  zakończyć pętle*/
            break;
    }
    int i;
    for (i=0;i<il;i++){
        if(dobre[i])        // jeżeli indeks ma wartość true, wypisywane są koordynaty dobrych punktów
            cout<<punkty[i].x<<", "<<punkty[i].y<<endl;
    }
}

int main() {
    ifstream odczyt("przyklad.txt");
    int il;
    odczyt>>il;
    float a,b;
    punkt punkty[il];
    int i=0;
    while(odczyt>>a>>b) //odczytywanie punktów
    {

        punkty[i].x = a; //zapisywanie punktów do struktury
        punkty[i].y = b;
        i++;
    }
    figura(punkty,il);
}