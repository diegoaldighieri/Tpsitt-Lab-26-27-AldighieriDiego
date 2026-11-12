//
// Created by 14529850 on 12/11/2026.
//

#ifndef TPSITT_LAB_26_27_ALDIGHIERIDIEGO_PERSONA_H
#define TPSITT_LAB_26_27_ALDIGHIERIDIEGO_PERSONA_H


class Persona {
    int id;
    std::string nome;
public:
    Persona(const int i = 0, std::string n = "ugone") : id (i), nome (std::move(n)) {
        std::cout << "Persona" << id << "creata" << std::endl;
    }
};


#endif //TPSITT_LAB_26_27_ALDIGHIERIDIEGO_PERSONA_H
