#include "estacaopesagem.h"


/*===============================================
                 Construtores
===============================================*/

EstacaoPesagem::EstacaoPesagem() {
    tempoMaximoFila = Relogio();
    tempoMinimoFila = Relogio();
    minimoEntidadesNaFila = 0;
    maximoEntidadesNaFila = 0;
    distTP = RN::Constante( 1.0 );
}

EstacaoPesagem::EstacaoPesagem( RN::Distribuicao dist ) {
    tempoMaximoFila = Relogio();
    tempoMinimoFila = Relogio();
    minimoEntidadesNaFila = 0;
    maximoEntidadesNaFila = 0;
    distTP = dist;
}

/*===============================================
                Eventos principais
===============================================*/
Evento *EstacaoPesagem::enfileirarCaminhao( Caminhao *caminhao, Relogio horaAtual ) {
    Evento *eventoPesagem;
    if( livre ) {
        eventoPesagem = new Evento( Evento::pesagem, horaAtual,caminhao );
        atualizaTemposFila( Relogio() );
        return eventoPesagem;
    }
    eventoPesagem = new Evento ( Evento::pesagem,proximoTempoLivre,caminhao );
    Relogio tempoEmFila( proximoTempoLivre );
    tempoEmFila -=horaAtual;
    atualizaTemposFila( tempoEmFila );
    aumentaNumeroNaFila();
    return eventoPesagem;
}
//===============================================
Evento *EstacaoPesagem::pesarCaminhao( Caminhao *caminhao, Relogio horaAtual ) {
    livre = false;
    diminuiNumeroNaFila();
    caminhaoOcupandoPlataforma = caminhao;
    int TP = distTP();
    tempoTotalOcupacaoPlataforma += TP;
    Relogio fimPesagem( horaAtual );
    Relogio relTP = Relogio();
    relTP.adicionaSegundos( TP );
    fimPesagem << relTP;
    proximoTempoLivre = fimPesagem;
    return new Evento( Evento::transporte, fimPesagem,caminhao );
}
//===============================================
void EstacaoPesagem::retirarCaminhao() {
    livre = true;
}

/*===============================================
            Funções auxiliares (private)
===============================================*/
void EstacaoPesagem::modificarDistribuicaoTC( RN::Distribuicao dist ) {
    this->distTP = dist;
}
//===============================================
void EstacaoPesagem::atualizaTemposFila( Relogio tempoFila ) {
    Relogio zero = Relogio();
    if ( tempoFila == zero ) {
        temposDeFila.push_back( Relogio () );
        return;
    }
    //Atualiza a lista de tempos de fila
    temposDeFila.push_back( Relogio( tempoFila ) );
    //Atualiza o tempo mínimo em fila
    if( tempoFila < tempoMinimoFila ) {
        tempoMinimoFila = tempoFila;
    }
    //Atualiza o tempo máximo em fila
    if ( tempoMaximoFila < tempoFila ) {
        tempoMaximoFila = tempoFila;
    }
}
//===============================================

void EstacaoPesagem::aumentaNumeroNaFila() {
    numeroEntidadesEnfileiradas++;
    totalEntidadesEnfileiradas++;
    somaFila.push_back( numeroEntidadesEnfileiradas );
    if( maximoEntidadesNaFila < numeroEntidadesEnfileiradas ) {
        maximoEntidadesNaFila  = numeroEntidadesEnfileiradas;
    }
}
//===============================================

void EstacaoPesagem::diminuiNumeroNaFila() {
    numeroEntidadesEnfileiradas--;
    somaFila.push_back( numeroEntidadesEnfileiradas );
    if( minimoEntidadesNaFila > numeroEntidadesEnfileiradas ) {
        minimoEntidadesNaFila = numeroEntidadesEnfileiradas;
    }
}

//===============================================
double EstacaoPesagem::mediaFila() {
    if( somaFila.empty() ) return 0;
    int somaTotal = 0;
    for( int numeroEmFila : somaFila ) {
        somaTotal += numeroEmFila;
    }
    return somaTotal / somaFila.size();
}
//===============================================
void EstacaoPesagem::atualizaEstatisticasTempoFila() {
    tempoMaximoFila = *std::max_element( temposDeFila.begin(),temposDeFila.end() );
    tempoMinimoFila = *std::min_element( temposDeFila.begin(),temposDeFila.end() );
}
//===============================================
double EstacaoPesagem::getMediaTempoFila() {
    int somaTemposFila;
    for( Relogio tempoDeFila :temposDeFila ) {
        somaTemposFila += tempoDeFila.getSegundosSimulacao();
    }
    return ( double ) somaTemposFila / ( double ) temposDeFila.size();
}






