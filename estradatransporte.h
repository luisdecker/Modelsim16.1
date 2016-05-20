#ifndef ESTRADATRANSPORTE_H
#define ESTRADATRANSPORTE_H
#include "relogio.h"
#include <list>
#include "caminhao.h"
#include "evento.h"
#include "rn.h"


class EstradaTransporte {
public:
    EstradaTransporte();
    EstradaTransporte( RN::Distribuicao distribuicaoTransporte );

    Evento *transportarCarga( Caminhao *caminhao, Relogio horaAtual );
    void modificarDistribuicaoTT(RN::Distribuicao novaDist);
private:
    RN::Distribuicao distTT;
};

#endif // ESTRADATRANSPORTE_H
