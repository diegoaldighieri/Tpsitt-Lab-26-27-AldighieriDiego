#include <iostream>
#include <string>
using namespace std;

class Sensore {
protected:
    string nome;
    int grezzo;
public:
    Sensore(const string& n, int g) : nome(n), grezzo(g) {}
    virtual ~Sensore() {}

    string getNome() const { return nome; }
    virtual double valore() const { return grezzo; }   // * nessuna conversione
    virtual string unita() const = 0;
    virtual bool allarme() const { return false; }     // * mai in allarme
};

class Temperatura : public Sensore {
public:
    Temperatura(const string& n, int g) : Sensore(n, g) {}
    double valore() const override { return grezzo / 10.0; }
    string unita() const override { return "gradi C"; }
    bool allarme() const override { return valore() > 30; }
};

class Umidita : public Sensore {
public:
    Umidita(const string& n, int g) : Sensore(n, g) {}
    double valore() const override { return grezzo * 100.0 / 1023; }
    string unita() const override { return "%"; }
    bool allarme() const override { return valore() > 70; }
};

class Luce : public Sensore {
public:
    Luce(const string& n, int g) : Sensore(n, g) {}
    string unita() const override { return "lux"; }
};

class Centralina {
    Sensore* sensori[10];
    int n;
public:
    Centralina() : n(0) {}

    bool aggiungi(Sensore* s) {
        if (n >= 10)
            return false;
        sensori[n++] = s;
        return true;
    }

    int report() const {
        int allarmi = 0;
        for (int i = 0; i < n; i++) {
            cout << sensori[i]->getNome() << ": " << sensori[i]->valore()
                 << " " << sensori[i]->unita();
            if (sensori[i]->allarme()) {
                cout << " <-- ALLARME";
                allarmi++;
            }
            cout << endl;
        }
        return allarmi;
    }
};

int main() {
    Temperatura t1("Temp. aula", 215);
    Temperatura t2("Temp. server", 342);
    Umidita u("Umidita bagno", 818);
    Luce l("Luce corridoio", 350);

    Centralina c;
    c.aggiungi(&t1);
    c.aggiungi(&t2);
    c.aggiungi(&u);
    c.aggiungi(&l);

    int allarmi = c.report();
    cout << "Sensori in allarme: " << allarmi << endl;   // * 2

    return 0;
}

// Aggregazione: i sensori sono creati nel main e la centralina non li distrugge.
// Luce ridefinisce solo unita. valore e allarme della base vanno già bene.
