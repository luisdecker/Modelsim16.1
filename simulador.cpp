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
    numeroEventos++;
    switch ( proximoEvento->tipo ) {
        case Evento::inicio: {inicioSimulacao(  ); break;}
        case Evento::chegadaCarga: {chegadaCarga( proximoEvento ); break;}
        case Evento::chegadaPesagem: {chegadaPesagem( proximoEvento ); break;}
        case Evento::carga: {carga( proximoEvento ); break;}
        case Evento::pesagem: {pesagem( proximoEvento ); break;}
        case Evento::transporte: {transporte( proximoEvento ); break;}
    }
    //Atualizar estatísticas
    atualizarEstatisticasFilaCarregamento();
    atualizarEstatisticasFilaPesagem();
    atualizarOcupacaoRecursos();
    atualizarEstatisticasCiclo();
}
/*===============================================
             Eventos de simulação
===============================================*/
//Evento de início de simulação
void Simulador::inicioSimulacao( ) {
    for( int i = 0; i<numeroCaminhoes; i++ ) {
        entidades.push_back( new Caminhao( i+1 ) );
        std::cout << "Incluiu caminhao " << entidades.back() << std::endl;
        entidades.shrink_to_fit();
    }
    for( int i = 0; i<numeroCaminhoes; i++ ) {
        Relogio tempoEvento = Relogio( relogioDeSimulacao );
        if( i>=2 ) {
            tempoEvento.adicionaSegundos( 2 );//cria os dois primeiros eventos em t0 e os seguintes depois, para dar tempo de ocupar o recurso
        }
        if( entidades.at( entidades.size()-i-1 ) == nullptr ) {
            std::cout << "Entidades " << i << " nulo!["<<entidades.size()<<"]"<< std::endl;
        }
        calendarioEventos.IncluirEvento( new Evento( Evento::TipoEvento::chegadaCarga,tempoEvento,entidades[entidades.size()-1-i] ) );
    }
}
//===============================================
//Evento de chegada na estação de carga
void Simulador::chegadaCarga( Evento *e ) {
    if( e->entidade()==nullptr ) {std::cout<<"Caminhao nulo fila carga" << std::endl;}
    if( e->entidade()->jaViajou() ) {
        numeroViagens++;//Estatistica e (Contagem de viagens)
        temposDeCiclo.push_back( e->entidade()->fimViagem( relogioDeSimulacao ).getSegundosSimulacao() );
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

void Simulador::trocarDistCarregamento( RN::Distribuicao *novaDist ) {
    estacaoCarregamento.modificarDistribuicaoTC( novaDist );
}
//===============================================
void Simulador::trocarDistPesagem( RN::Distribuicao *novaDist ) {
    std::cout << "Sim testando troca TP "<< novaDist->gerarVariavelAleatoria()<<std::endl;
    estacaoPesagem.modificarDistribuicaoTP( novaDist );
}
//===============================================
void Simulador::trocarDistTransporte( RN::Distribuicao *novaDist ) {
    estrada.modificarDistribuicaoTT( novaDist );
}

/*==============================================
            Métodos Estatísticos
===============================================*/


void Simulador::atualizarEstatisticasFilaCarregamento() {
    maximoFilaCarregamento = estacaoCarregamento.maximoFila();
    minimoFilaCarregamento = estacaoCarregamento.minimoFila();
    mediaFilaCarregamento = estacaoCarregamento.mediaFila();
    //Estatísticas para tempos em fila
    tempoMaximoFilaCarregamento = estacaoCarregamento.getTempoMaximoFila();
    tempoMinimoFilaCarregamento = estacaoCarregamento.getTempoMinimoFila();
    mediaTempoFilaCarregamento = estacaoCarregamento.getMediaTempoFila();
}
//===============================================
void Simulador::atualizarEstatisticasFilaPesagem() {
    //Estatísticas para numero de entidades em fila
    maximoFilaPesagem = estacaoPesagem.maximoFila();
    minimoFilaPesagem = estacaoPesagem.minimoFila();
    mediaFilaPesagem = estacaoPesagem.mediaFila();
    //Estatísticas para tempos em fila
    tempoMaximoFilaPesagem = estacaoPesagem.getTempoMaximoFila();
    tempoMinimoFilaPesagem = estacaoPesagem.getTempoMinimoFila();
    mediaTempoFilaPesagem = estacaoPesagem.getMediaTempoFila();
}
//===============================================
void Simulador::atualizarOcupacaoRecursos() {
    if( numeroEventos > 0 ) {
        if( !estacaoCarregamento.estacao1Livre() ) {
            eventosEC1Ocupado++;
        }
        if( !estacaoCarregamento.estacao2Livre() ) {
            eventosEC2Ocupado++;
        }
        if( !estacaoPesagem.estacaoLivre() ) {
            eventosEPOcupado++;
        }
        taxaOcupacaoCarregamento1 = ( double )eventosEC1Ocupado/( double )numeroEventos;
        taxaOcupacaoCarregamento2 = ( double ) eventosEC2Ocupado/ ( double ) numeroEventos;
        taxaOcupacaoPesagem = ( double ) eventosEPOcupado / ( double )numeroEventos;
    }
}
//===============================================
void Simulador::atualizarEstatisticasCiclo() {
    if( numeroViagens>0 ) {
        tempoMaximoCiclo = *std::max_element( temposDeCiclo.begin(),temposDeCiclo.end() );
        tempoMinimoCiclo = *std::min_element( temposDeCiclo.begin(),temposDeCiclo.end() );
        int somaTemposCiclo = 0;
        for( int tempoCiclo : temposDeCiclo ) {
            somaTemposCiclo += tempoCiclo;
        }
        tempoMedioCiclo = ( double ) somaTemposCiclo/numeroViagens;
    }
}
//===============================================
Simulador::valoresEstatistica Simulador::obterEstatisticas() {
    valoresEstatistica retorno;
    retorno.numeroCaminhoes=numeroCaminhoes;
    retorno.horaSimulacao=relogioDeSimulacao;
    //a)
    //Carregamento
    retorno.maximoFilaCarregamento=maximoFilaCarregamento;
    retorno.minimoFilaCarregamento = minimoFilaCarregamento;
    retorno.mediaFilaCarregamento = mediaFilaCarregamento;
    //Pesagem
    retorno.maximoFilaPesagem = maximoFilaPesagem;
    retorno.minimoFilaPesagem = minimoFilaPesagem;
    retorno.mediaFilaPesagem = mediaFilaPesagem;
    //b)
    retorno.taxaOcupacaoCarregamento1 = taxaOcupacaoCarregamento1;
    retorno.taxaOcupacaoCarregamento2 = taxaOcupacaoCarregamento2;
    retorno.taxaOcupacaoPesagem = taxaOcupacaoPesagem;
    //c)
    //Carregamento
    retorno.tempoMaximoFilaCarregamento = tempoMaximoFilaCarregamento;
    retorno.tempoMinimoFilaCarregamento = tempoMinimoFilaCarregamento;
    retorno.mediaTempoFilaCarregamento = mediaTempoFilaCarregamento;
    //Pesagem
    retorno.tempoMaximoFilaPesagem = tempoMaximoFilaPesagem;
    retorno.tempoMinimoFilaPesagem =tempoMinimoFilaPesagem;
    retorno.mediaTempoFilaPesagem = mediaTempoFilaPesagem;
    //d)
    retorno.tempoMaximoCiclo = tempoMaximoCiclo;
    retorno.tempoMinimoCiclo= tempoMinimoCiclo;
    retorno.tempoMedioCiclo = tempoMedioCiclo;
    //e)
    retorno.numeroViagens= numeroViagens;
    return retorno;
}
