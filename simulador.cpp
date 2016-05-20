#include "simulador.h"


/*===============================================
    Método construtor de um simulador
    Este é o metodo de inicialização de um simulador.
    Ele incializa todos os geradores de tempo, e os eventos iniciais.
===============================================*/
Simulador::Simulador( int numeroCaminhoes ):numeroCaminhoes( numeroCaminhoes ) {
    relogioDeSimulacao = Relogio();
    entidades = std::vector<Caminhao *>( numeroCaminhoes );
    calendarioEventos.IncluirEvento( new Evento( Evento::TipoEvento::inicio, relogioDeSimulacao,nullptr ) );
    estacaoCarregamento = EstacaoCarregamento();
}
/*===============================================
          Metodo de avanco no tempo
===============================================*/
void Simulador::simular() {
    Evento *proximoEvento = calendarioEventos.obterProximoEvento();
    calendarioEventos.consumirEvento();
    relogioDeSimulacao = *proximoEvento->obterTempoRelogio();
    switch ( proximoEvento->tipo ) {
        case Evento::inicio: {inicioSimulacao(  ); break;}
        case Evento::chegadaCarga: {chegadaCarga( proximoEvento ); break;}
        case Evento::chegadaPesagem: {chegadaPesagem( proximoEvento ); break;}
        case Evento::carga: {carga( proximoEvento ); break;}
        case Evento::pesagem: {pesagem( proximoEvento ); break;}
        case Evento::transporte: {transporte( proximoEvento ); break;}
    }
}
/*===============================================
             Eventos de simulação
===============================================*/
//Evento de início de simulação
void Simulador::inicioSimulacao( ) {
    for( int i = 0; i<numeroCaminhoes; i++ ) {
        entidades.push_back( new Caminhao( i+1 ) );
    }
    for( int i = 0; i<numeroCaminhoes; i++ ) {
        Relogio tempoEvento = Relogio( relogioDeSimulacao );
        if( i>=2 ) {
            tempoEvento.adicionaSegundos( 2 );//cria os dois primeiros eventos em t0 e os seguintes depois, para dar tempo de ocupar o recurso
        }
        calendarioEventos.IncluirEvento( new Evento( Evento::TipoEvento::chegadaCarga,tempoEvento,entidades[i] ) );
    }
}
//===============================================
//Evento de chegada na estação de carga
void Simulador::chegadaCarga( Evento *e ) {
    if( e->entidade()->jaViajou() ) {
        numeroViagens++;//Estatistica e (Contagem de viagens)
    }
    e->entidade()->inicioViagem( relogioDeSimulacao );
    Evento *carga = estacaoCarregamento.enfileirarCaminhao( e->entidade(),relogioDeSimulacao );
    calendarioEventos.IncluirEvento( carga );
}
//===============================================
//Evento de carga de caminhão
void Simulador::carga( Evento *e ) {
    Evento *eventoFilaPesagem = estacaoCarregamento.carregarCaminhao( e->entidade(),relogioDeSimulacao );
    calendarioEventos.IncluirEvento( eventoFilaPesagem );
}
//===============================================
//Evento de enfileiramento para pesagem
//Tem que tirar um caminhao da estacao de carga
void Simulador::chegadaPesagem( Evento *e ) {
    estacaoCarregamento.retirarCaminhao( e->entidade() );
    Evento *eventoPesagem = estacaoPesagem.enfileirarCaminhao( e->entidade(),relogioDeSimulacao );
    calendarioEventos.IncluirEvento( eventoPesagem );
}
//===============================================
//Evento de pesagem de caminhao
void Simulador::pesagem( Evento *e ) {
    Evento *eventoTransporte = estacaoPesagem.pesarCaminhao( e->entidade(),relogioDeSimulacao );
    calendarioEventos.IncluirEvento( eventoTransporte );
}
//===============================================
//Evento de transporte da carga
//Desocupar a balanca
void Simulador::transporte( Evento *e ) {
    estacaoPesagem.retirarCaminhao();
    Evento *eventoReenfileirar = estrada.transportarCarga( e->entidade(),relogioDeSimulacao );
    calendarioEventos.IncluirEvento( eventoReenfileirar );
}

/*===============================================
        Métodos de troca de Distribuicoes
===============================================*/

void Simulador::trocarDistCarregamento( RN::Distribuicao novaDist ) {
    estacaoCarregamento.modificarDistribuicaoTC( novaDist );
}
//===============================================
void Simulador::trocarDistPesagem( RN::Distribuicao novaDist ) {
    estacaoPesagem.modificarDistribuicaoTC( novaDist );
}
//===============================================
void Simulador::trocarDistTransporte( RN::Distribuicao novaDist ) {
    estrada.modificarDistribuicaoTT( novaDist );
}








