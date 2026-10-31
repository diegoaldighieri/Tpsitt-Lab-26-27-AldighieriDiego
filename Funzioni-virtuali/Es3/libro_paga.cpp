#include <iostream>
#include <string>
using namespace std;

class Dipendente {
protected:
    string nome;
public:
    Dipendente(const string& n) : nome(n) {}
    virtual ~Dipendente() {}
    virtual double stipendio() const { return 1200.0; }
    void scheda() const {
        cout << nome << ": " << stipendio() << " euro" << endl;
    }
};

class Programmatore : public Dipendente {
    int progetti;
public:
    Programmatore(const string& n, int p) : Dipendente(n), progetti(p) {}
    double stipendio() const override { return 1500.0 + 100.0 * progetti; }
};

class Responsabile : public Dipendente {
    int collaboratori;
public:
    Responsabile(const string& n, int c) : Dipendente(n), collaboratori(c) {}
    double stipendio() const override { return 2000.0 + 50.0 * collaboratori; }
};

int main() {
    // Punto 1
    Dipendente* staff[4];
    staff[0] = new Dipendente("Rossi");
    staff[1] = new Programmatore("Bianchi", 3);
    staff[2] = new Responsabile("Verdi", 6);
    staff[3] = new Programmatore("Neri", 1);

    double totale = 0;
    for (int i = 0; i < 4; i++) {
        staff[i]->scheda();                         // * 1200, 1800, 2300, 1600
        totale += staff[i]->stipendio();
    }
    cout << "Totale: " << totale << " euro" << endl; // * 6900

    for (int i = 0; i < 4; i++)
        delete staff[i];

    // Punto 2
    Dipendente copie[2] = { Programmatore("Bianchi", 3), Responsabile("Verdi", 6) };
    for (int i = 0; i < 2; i++)
        copie[i].scheda();                          // * 1200 per tutti e due

    return 0;
}

// Punto 2: slicing, nell'array ci sono solo Dipendente, quindi 1200 a tutti.
// Punto 3: errore "marked override, but does not override". Tolgo override nelle derivate
// e il punto 1 stampa 1200 per tutti (totale 4800).
// Punto 4: scheda chiama stipendio, che è virtual.
// Punto 5: così delete chiama anche il distruttore della derivata (come nell'Es2).
