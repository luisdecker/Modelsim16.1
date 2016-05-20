#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "relogio.h"
#include <vector>
#include "caminhao.h"
#include "calendarioeventos.h"
#include "evento.h"
#include "estacaocarregamento.h"
#include "estacaopesagem.h"
#include "estradatransporte.h"
#include "rn.h"

class Simulador {
public:
    Simulador( int numeroCaminhoes );
    void simular();

    //Trocar as distribuicoes
    void trocarDistCarregamento( RN::Distribuicao novaDist );
    void trocarDistPesagem( RN::Distribuicao novaDist );
    void trocarDistTransporte(RN::Distribuicao novaDist);

private:
    //Estatísticas



    Relogio relogioDeSimulacao;
    int numeroCaminhoes;
    std::vector<Caminhao *> entidades;
    CalendarioEventos calendarioEventos;
    int numeroViagens = 0;

    //Filas
    std::vector<Caminhao *>filaCarregamento;
    std::vector<Caminhao *>carregando;
    std::vector<Caminhao *>filaPesagem;
    Caminhao *pesando;

    //Estacoes
    EstacaoCarregamento estacaoCarregamento;
    EstacaoPesagem estacaoPesagem;
    EstradaTransporte estrada;


//Funcoes para cada evento
    void inicioSimulacao();//Evento de configuração inicial
    void chegadaCarga( Evento *e );//Evento de chegada de um caminhão na estação de carga
    void carga( Evento *e );//Evento de carregamento de um caminhao;
    void chegadaPesagem( Evento *e ); //Evento de chegada de um caminhao da estacao de pesagem;
    void pesagem( Evento *e ); //Evento de pesagem de caminhao;
    void transporte( Evento *e ); //Evento do tranporte da carga e retorno do caminhão a fila de carga.
};

#endif // SIMULADOR_H
