#ifndef SIMULADOR_H
#define SIMULADOR_H


#include <vector>
#include <iostream>
#include "relogio.h"
#include "caminhao.h"
#include "calendarioeventos.h"
#include "evento.h"
#include "estacaocarregamento.h"
#include "estacaopesagem.h"
#include "estradatransporte.h"
#include "rn.h"

class Simulador {
public:
    struct valoresEstatistica {
        int numeroCaminhoes;
        Relogio horaSimulacao;
        //a)
        int maximoFilaCarregamento;
        int minimoFilaCarregamento;
        double mediaFilaCarregamento;

        int maximoFilaPesagem;
        int minimoFilaPesagem;
        double mediaFilaPesagem;

        //b)
        double taxaOcupacaoCarregamento1;
        double taxaOcupacaoCarregamento2;
        double taxaOcupacaoPesagem;

        //c)
        int tempoMaximoFilaCarregamento;
        int tempoMinimoFilaCarregamento;
        double mediaTempoFilaCarregamento;

        int tempoMaximoFilaPesagem;
        int tempoMinimoFilaPesagem;
        double mediaTempoFilaPesagem;

        //d)
        int tempoMaximoCiclo;
        int tempoMinimoCiclo;
        double tempoMedioCiclo;

        //e)
        int numeroViagens;
    };

    Simulador( int numeroCaminhoes );
    void simular();

    //Enviar infos pra interface
    valoresEstatistica obterEstatisticas();

    //Trocar as distribuicoes
    void trocarDistCarregamento(RN::Distribuicao *novaDist );
    void trocarDistPesagem( RN::Distribuicao *novaDist );
    void trocarDistTransporte( RN::Distribuicao* novaDist );

private:
    //Estatísticas

    int numeroEventos=0;

    //a) Numero de entidades nas filas
    //Carregamento
    void atualizarEstatisticasFilaCarregamento();///Atualiza as estatisticas da estação de carregamento
    int maximoFilaCarregamento=0;///< Maximo de entidades na fila de carregamento
    int minimoFilaCarregamento=0;///< Minimo de entidades na fila de carregamento
    double mediaFilaCarregamento=0;///< Media de entidades na fila de carregamento
    //Pesagem
    void atualizarEstatisticasFilaPesagem();
    int maximoFilaPesagem=0; ///< Maximo de entidades na fila de pesagem
    int minimoFilaPesagem=0;///< Minimo de entidades na fila de pesagem
    double mediaFilaPesagem=0;///< media de entidades na fila de pesagem

    //b) Taxa média de ocupação dos recursos
    void atualizarOcupacaoRecursos();
    double taxaOcupacaoCarregamento1=0;///< Taxa de ocupacao da primeira estacao de carga
    double taxaOcupacaoCarregamento2=0; ///< Taxa de ocupacao da segunda estacao de carga
    double taxaOcupacaoPesagem=0; ///< Taxa de ocupacao da estacao de pesagem
    int eventosEC1Ocupado=0;///< Numero de eventos em que a primeira estacao de carga estava ocupada
    int eventosEC2Ocupado=0;///< Numero de eventos em que a segunda estação de carga estava ocupada
    int eventosEPOcupado=0;///< Numero de eventos emque a estacao de pesagem estava ocupada.

    //c)tempo de uma entidade na fila
    //Carregamento
    //Atualização de informações feitas nos respectivos atualizarEstatisticasFila(pesagem|carregamento)
    int tempoMaximoFilaCarregamento=0;///< Tempo maximo de uma entidade na fila de carregamento
    int tempoMinimoFilaCarregamento=0;///< Tempo mínimo de uma entidade na fila de carregamento
    double mediaTempoFilaCarregamento=0;///< Tempo médio de uma entidade na fila de carregamento
    //Pesagem
    int tempoMaximoFilaPesagem=0;///< Tempo maximo de uma entidade na fila de pesagem
    int tempoMinimoFilaPesagem=0;///< Tempo minimo de uma entidade na fila de pesagem
    double mediaTempoFilaPesagem=0;///< Tempo medio de uma entidade na fila de pesagem

    //d)Tempo de ciclo
    void atualizarEstatisticasCiclo();
    int tempoMaximoCiclo=0;
    int tempoMinimoCiclo=0;
    double tempoMedioCiclo=0;

    //e)Contador de numero de viagens;
    int numeroViagens = int( 0 ); ///< Numero de viagens completadas no sistema

    std::vector<int> temposDeCiclo;
    Relogio relogioDeSimulacao;///< Horário atual de simulacao
    int numeroCaminhoes=0;///< Numero de entidades no sistema
    std::vector<Caminhao *> entidades;///< Lista de entidades
    CalendarioEventos calendarioEventos;///< Calendario de eventos futuros



//	//Filas
//	std::vector<Caminhao *>filaCarregamento;
//	std::vector<Caminhao *>carregando;
//	std::vector<Caminhao *>filaPesagem;
//	Caminhao *pesando;

    //Estacoes
    EstacaoCarregamento estacaoCarregamento;///< Estacao de carregamento de caminhoes
    EstacaoPesagem estacaoPesagem;///< Estacao de pesagem de caminhoes
    EstradaTransporte estrada;///< Estrada responsável pelo transporte


//Funcoes para cada evento
    void inicioSimulacao();///< Evento de configuração inicial
    void chegadaCarga( Evento *e );///< Evento de chegada de um caminhão na estação de carga
    void carga( Evento *e );///< Evento de carregamento de um caminhao;
    void chegadaPesagem( Evento *e ); ///< Evento de chegada de um caminhao da estacao de pesagem;
    void pesagem( Evento *e ); ///< Evento de pesagem de caminhao;
    void transporte( Evento *e ); ///< Evento do tranporte da carga e retorno do caminhão a fila de carga.
};

#endif // SIMULADOR_H
