#include <iostream>
#include <string>
using namespace std;

class Materiale {
protected:
    string codice;
    string titolo;
    int anno;

    virtual string dettaglio() const = 0;
    virtual int giorniPrestito() const = 0;
    virtual double moraGiornaliera() const = 0;

public:
    Materiale(const string& c, const string& t, int a) : codice(c), titolo(t), anno(a) {}
    virtual ~Materiale() {}

    void descrizione() const {
        cout << "[" << codice << "] " << titolo << " (" << anno << "), "
             << dettaglio() << " - prestito " << giorniPrestito() << " giorni" << endl;
    }

    double mora(int giorniRitardo) const {
        if (giorniRitardo <= 0)
            return 0;
        return giorniRitardo * moraGiornaliera();
    }
};

class Libro : public Materiale {
    int pagine;
protected:
    string dettaglio() const override { return to_string(pagine) + " pagine"; }
    int giorniPrestito() const override { return 30; }
    double moraGiornaliera() const override { return 0.10; }
public:
    Libro(const string& c, const string& t, int a, int p) : Materiale(c, t, a), pagine(p) {}
};

class Dvd : public Materiale {
    int minuti;
protected:
    string dettaglio() const override { return to_string(minuti) + " minuti"; }
    int giorniPrestito() const override { return 7; }
    double moraGiornaliera() const override { return 0.50; }
public:
    Dvd(const string& c, const string& t, int a, int m) : Materiale(c, t, a), minuti(m) {}
};

class Rivista : public Materiale {
    int numero;
protected:
    string dettaglio() const override { return "n. " + to_string(numero); }
    int giorniPrestito() const override { return 14; }
    double moraGiornaliera() const override { return 0.20; }
public:
    Rivista(const string& c, const string& t, int a, int n) : Materiale(c, t, a), numero(n) {}
};

int main() {
    Materiale* materiali[4];
    materiali[0] = new Libro("L01", "I promessi sposi", 1827, 720);
    materiali[1] = new Dvd("D01", "Il sorpasso", 1962, 105);
    materiali[2] = new Rivista("R01", "Informatica Oggi", 2026, 12);
    materiali[3] = new Libro("L02", "Il nome della rosa", 1980, 512);

    double totale = 0;
    for (int i = 0; i < 4; i++) {
        materiali[i]->descrizione();
        double m = materiali[i]->mora(10);
        cout << "   mora per 10 giorni: " << m << " euro" << endl;
        totale += m;
    }
    cout << "Mora totale: " << totale << " euro" << endl;   // * 9 euro

    for (int i = 0; i < 4; i++)
        delete materiali[i];

    return 0;
}

// descrizione e mora sono nella base e chiamano metodi virtual,
// che ogni derivata ridefinisce con la sua parte.
