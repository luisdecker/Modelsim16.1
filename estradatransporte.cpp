#include "estradatransporte.h"


/*===============================================
                  Construtores
===============================================*/

EstradaTransporte::EstradaTransporte() {
    distTT = new RN::Constante( 1.0 );
}

EstradaTransporte::EstradaTransporte( RN::Distribuicao *distribuicaoTransporte ) {
    distTT = distribuicaoTransporte;
}

/*===============================================
                Eventos principais
===============================================*/

Evento *EstradaTransporte::transportarCarga( Caminhao *caminhao, Relogio horaAtual ) {
    int TT = distTT->gerarVariavelAleatoria();
    std::cout<<"[TT = " << TT<< "]" << std::endl;
    Relogio fimTransporte( horaAtual );
    Relogio relTT = Relogio();
    relTT.adicionaSegundos( TT );
    fimTransporte << relTT;
    return new Evento( Evento::chegadaCarga,fimTransporte,caminhao );
}

/*===============================================
           Funções auxiliares (private)
===============================================*/

void EstradaTransporte::modificarDistribuicaoTT( RN::Distribuicao *novaDist ) {
    distTT = novaDist;
}
