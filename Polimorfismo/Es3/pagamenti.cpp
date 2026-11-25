#include <iostream>
#include <vector>
using namespace std;

class MetodoPagamento {
    public:
    virtual ~MetodoPagamento(){};
    virtual void paga(double importo) = 0;
    void pagaConCommissione(double importo, double percCommissione) {
        double commissione = importo * percCommissione / 100;
        double totale = importo + commissione;

        cout << "Commissione: " << commissione << "$" << endl;
        paga(totale);

    }
};

class CartaCredito :public MetodoPagamento {
    public:
    void paga (double importo) override{std::cout<<"Ho pagato:"<<importo<<"$ con la carta di credito"<<std::endl;};
};
class PayPal :public MetodoPagamento {
public:
    void paga (double importo) override{std::cout<<"Ho pagato:"<<importo<<"$ con PayPal"<<std::endl;};
};
class Contanti :public MetodoPagamento {
public:
    void paga (double importo) override{std::cout<<"Ho pagato:"<<importo<<"$ in contanti"<<std::endl;};
};


int main() {

    std::vector<MetodoPagamento*> pagamenti;
    pagamenti.push_back(new CartaCredito());
    pagamenti.push_back(new PayPal());
    pagamenti.push_back(new Contanti());

    int i = 0;
    for (MetodoPagamento* pagamento : pagamenti) {
        pagamento->pagaConCommissione(150 + (i + 1) * 10, 23); // qua uso (i + 1) * 10 perchè volevo passare un valore diverso ad ogni metodo di pagamento
        i++;
    }

    for (MetodoPagamento* pagamento : pagamenti) {
        delete pagamento;
    }



    return 0;
}
