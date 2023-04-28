#include<iostream>
#include<string.h>

using namespace std;

class Punkt{
    private:
        double x;
        double y;
        double z;
    
    public:
        string npunktu;
        Punkt(string,double,double,double);
        double getx()const{
            return x;
        }
         double gety()const{
            return y;
        }
         double getz()const{
            return z;
        }
        
        bool podobnyPunkt(const Punkt &);
         bool takiSamPunkt(const Punkt &);
          void dodajPunkt(const Punkt &);
           void odejmijPunkt(const Punkt &);
};
    bool Punkt::podobnyPunkt(const Punkt &spr){
        if(this->x == spr.x and this->y == spr.y and this->z == spr.z)return true;
        return false;
}
    bool Punkt::takiSamPunkt(const Punkt &spr){
            if(this->npunktu != spr.npunktu)return false;
            return this->podobnyPunkt(spr);
}
    void Punkt::odejmijPunkt(const Punkt &odejmij){
        this->x -= odejmij.x;
        this->y -= odejmij.y;
        this->z -= odejmij.z;
}
    void Punkt::dodajPunkt(const Punkt &dodaj){
        this->x += dodaj.x;
        this->y += dodaj.y;
        this->z += dodaj.z;
}
    Punkt::Punkt(string nazwa="",double x = 0, double y = 0, double z = 0){
        this->npunktu = nazwa;
        this->x = x;
        this->y = y;
        this->z = z;
}

class Uklad{
    private:
        int licznik;
    public:
        static const int rozmiar = 10;
        Punkt tPunktow[rozmiar];
        string nukladu;
        Uklad(string nazwa=""){
            licznik = 0;
            nukladu = nazwa;
        };
        void operator+= (const Uklad &);
        void operator-= (const Uklad &);
        void wstawPunkt(Punkt);
        void usunPunkt(string);
            
        int getlicznik()const{
            return licznik;
        }
};
void Uklad::wstawPunkt(Punkt nowyPunkt){
    if(licznik>=rozmiar)return;
    tPunktow[licznik++] = nowyPunkt;
}

void Uklad::usunPunkt(string nazwaUsuwanego){
    for(int  i = 0; i < licznik; i++){
    if(tPunktow[i].npunktu == nazwaUsuwanego){
        tPunktow[i] = tPunktow[--licznik];
        }
    }
}

void Uklad::operator+=(const Uklad &drugiUklad){
    bool okDoDodania = true;
    for(int i = 0; i < drugiUklad.licznik; i++){
        okDoDodania = true;
        for(int k = 0; k < this->licznik; k++){
            if(this->tPunktow[k].takiSamPunkt(drugiUklad.tPunktow[i])){
                okDoDodania = false;
                break;
            }
        }
        if(okDoDodania) this->wstawPunkt(drugiUklad.tPunktow[i]);
    }
}

void Uklad::operator-=(const Uklad &drugiUklad){
    for(int i = 0; i < drugiUklad.licznik; i++){
        for(int k = 0; k < this->licznik; k++){
            if(this->tPunktow[k].podobnyPunkt(drugiUklad.tPunktow[i])){
                this->tPunktow[k] = this->tPunktow[--this->licznik];
            }
        }
    }
}

ostream & operator<< (ostream & p, const Punkt &punktDowyswietlenia){
       return p <<  punktDowyswietlenia.npunktu <<" "<<punktDowyswietlenia.getx()<<" "<<punktDowyswietlenia.gety()<<" "<<punktDowyswietlenia.getz();
    }
    
ostream & operator<< (ostream & p,const Uklad &ukladDowyswietlenia){
    for(int i = 0; i < ukladDowyswietlenia.getlicznik(); i++){
        if(i == ukladDowyswietlenia.getlicznik()-1) p<<ukladDowyswietlenia.tPunktow[i];
        else p <<ukladDowyswietlenia.tPunktow[i]<<"; ";
    }
    return p;
}

Uklad operator+( const Uklad &a,const Uklad &b){
    Uklad nowyUklad (a.nukladu+"+"+b.nukladu);
    for(int i = 0; i < a.getlicznik(); i++){
        nowyUklad.wstawPunkt(a.tPunktow[i]);
    }
    for(int i = 0; i < b.getlicznik(); i++){
        nowyUklad.wstawPunkt(b.tPunktow[i]);
    }
    return nowyUklad;
}

Uklad operator-( const Uklad &a,const Uklad &b){
    Uklad nowyUklad = a;
    nowyUklad.nukladu+="-"+b.nukladu;
    for(int i = 0 ; i <b.getlicznik(); i++){
        nowyUklad.usunPunkt(a.tPunktow[i].npunktu);
    }
    return nowyUklad;
}

Punkt operator+ (const Punkt &a,const Punkt &b){
    Punkt nowyPunkt;
    if(a.npunktu == "") nowyPunkt.npunktu=b.npunktu;
    else nowyPunkt.npunktu=a.npunktu+"+"+b.npunktu;
    nowyPunkt.dodajPunkt(a);
    nowyPunkt.dodajPunkt(b);
    return nowyPunkt;
}

Punkt operator- (const Punkt &a,const Punkt &b){
    Punkt nowyPunkt = a;
    if(nowyPunkt.npunktu == "") nowyPunkt.npunktu=b.npunktu;
    else nowyPunkt.npunktu=a.npunktu+"-"+b.npunktu;
    nowyPunkt.odejmijPunkt(b);
    return nowyPunkt;
}

bool czyDouble(string value){
    int i = 0;
    if(value[0] == '-'){
        if(value[1] == '.')return false;
        i++;
    }
    bool jedKrop = false;
    for(i; i < value.size(); i++){
        if(value[i] =='.'){
            if(jedKrop)return false;
            jedKrop = true;
            continue;
        }
        if('0' > value[i] or '9' < value[i])return false;
    }
    return true;
}

void dodajPunktDoUkladu(int z, Uklad &uklad){
    string nazwa;
    string xyz[3];
    for(int i = 0; i < z; i++){
        cin>>nazwa;
        for(int i = 0; i < 3; i++){
            do{
                cin>>xyz[i];
            }while(!czyDouble(xyz[i]));
        }
        Punkt a(nazwa, stod(xyz[0]), stod(xyz[1]), stod(xyz[2]));
        uklad.wstawPunkt(a);
    }
}

int main()
{
    string nazwa;
    cin>>nazwa;
    Uklad ukladjeden(nazwa);
    cin>>nazwa;
    Uklad ukladdwa(nazwa);
    
    dodajPunktDoUkladu(4, ukladjeden);
    dodajPunktDoUkladu(3, ukladdwa);
    
    cin>>nazwa;
    Uklad ukladtrzy(nazwa);
    ukladtrzy+=ukladjeden;
    ukladtrzy-=ukladdwa;
    
    
    Punkt plus;
    for(int i = 0; i < ukladjeden.getlicznik(); i++){
    plus=plus+ukladjeden.tPunktow[i];
    }
    
    Punkt minus;
    minus = minus + ukladtrzy.tPunktow[0];
    for(int i = 1; i <ukladtrzy.getlicznik(); i++){
    minus=minus-ukladtrzy.tPunktow[i];
    }
    if(ukladdwa.getlicznik() > 8){
        ukladdwa.tPunktow[8] = plus;
        ukladdwa.tPunktow[9] = minus;
    }
    else{
        ukladdwa.wstawPunkt(plus);
        ukladdwa.wstawPunkt(minus);
    }
    
    cout<<ukladjeden<<" ";
    cout<<ukladdwa<<" ";
    cout<<ukladtrzy;
    
    return 0;
}