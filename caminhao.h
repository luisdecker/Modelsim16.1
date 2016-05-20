#ifndef CAMINHAO_H
#define CAMINHAO_H

#include "relogio.h"

class Caminhao {
public:
    Caminhao(int id);
    void inicioViagem(Relogio tempoInicio);
    Relogio fimViagem(Relogio tempoFim);
    bool jaViajou(){return !primeiraViagem;}
    bool operator== (Caminhao outro);
private:
    Relogio tempoInicioViagem;
    bool primeiraViagem = true;
    int id;


};

#endif // CAMINHAO_H
