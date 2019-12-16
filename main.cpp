#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Dokument {
    public:
        virtual void czytaj() { } // zwykla metoda wirtualna
        virtual void drukuj() = 0; // metoda czysto wirtualna
        virtual ~Dokument() { }
};

class Dok : public Dokument {
    public:
        void drukuj() {
            cout << buf << endl;
        }
    protected:
        string buf;
};

class DokStd : public Dok {
    public:
        void czytaj() {
            getline(cin, buf);
        }
};

class DokPlik : public Dok {
    public:
        void czytaj() {
            ifstream plik("test.txt");
            if (!plik) {
                cerr << "Nie ma takiego pliku" << endl;
                exit(1);
            }
            string tmp;
            while (!plik.eof()) {
                getline(plik,tmp);
                buf += tmp + '\n';
            }
        }
};

class Dekorator : public Dokument {
    public:
        Dekorator(Dokument *p) : ptr{p} { }
        ~Dekorator() { delete ptr; }
        void drukuj() {
            ptr->drukuj();
        }
    private:
        Dokument *ptr { nullptr };
};

class Naglowek : public Dekorator {
    public:
        Naglowek(Dokument *p) : Dekorator(p), nr{++licznik} { }
        void drukuj();
    private:
        void drukujNaglowek();
        static unsigned licznik;
        const unsigned nr;
};

unsigned Naglowek::licznik { 0 };

void Naglowek::drukujNaglowek() {
    cout << string(10,'.') << " N A G L O W E K " << nr << " " << string(10,'.') << endl;
}

void Naglowek::drukuj() {
    drukujNaglowek();
    Dekorator::drukuj();
}

class Stopka : public Dekorator {
    public:
        Stopka(Dokument *p) : Dekorator(p), nr{++licznik} { }
        void drukuj();
    private:
        void drukujStopka();
        static unsigned licznik;
        const unsigned nr;
};

unsigned Stopka::licznik { 0 };

void Stopka::drukujStopka() {
    cout << string(10,'-') << " S T O P K A " << nr << " " << string(10,'-') << endl;
}

void Stopka::drukuj() {
    Dekorator::drukuj();
    drukujStopka();
}


int main() {
    //Dokument *p = new DokStd;
    Dokument *p = new DokPlik;
    p->czytaj();
    p->drukuj();
    cout << "------------------------------" << endl;
    p = new Stopka(new Naglowek(new Stopka(p)));
    p->drukuj();
    cout << "------------------------------" << endl;
    p = new Stopka(new Naglowek(new Stopka(new Stopka(new Naglowek(new Naglowek(new Stopka(p)))))));
    p->drukuj();
    delete p;
}