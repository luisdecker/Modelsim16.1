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
    struct valoresEstatistica {
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



    //Trocar as distribuicoes
    void trocarDistCarregamento( RN::Distribuicao novaDist );
    void trocarDistPesagem( RN::Distribuicao novaDist );
    void trocarDistTransporte( RN::Distribuicao novaDist );

private:
    //Estatísticas

    int numeroEventos;

    //a) Numero de entidades nas filas
    //Carregamento
    void atualizarEstatisticasFilaCarregamento();///Atualiza as estatisticas da estação de carregamento
    int maximoFilaCarregamento;///< Maximo de entidades na fila de carregamento
    int minimoFilaCarregamento;///< Minimo de entidades na fila de carregamento
    double mediaFilaCarregamento;///< Media de entidades na fila de carregamento
    //Pesagem
    void atualizarEstatisticasFilaPesagem();
    int maximoFilaPesagem; ///< Maximo de entidades na fila de pesagem
    int minimoFilaPesagem;///< Minimo de entidades na fila de pesagem
    double mediaFilaPesagem;///< media de entidades na fila de pesagem

    //b) Taxa média de ocupação dos recursos
    void atualizarOcupacaoRecursos();
    double taxaOcupacaoCarregamento1;///< Taxa de ocupacao da primeira estacao de carga
    double taxaOcupacaoCarregamento2; ///< Taxa de ocupacao da segunda estacao de carga
    double taxaOcupacaoPesagem; ///< Taxa de ocupacao da estacao de pesagem
    int eventosEC1Ocupado;///< Numero de eventos em que a primeira estacao de carga estava ocupada
    int eventosEC2Ocupado;///< Numero de eventos em que a segunda estação de carga estava ocupada
    int eventosEPOcupado;///< Numero de eventos emque a estacao de pesagem estava ocupada.

    //c)tempo de uma entidade na fila
    //Carregamento
    //Atualização de informações feitas nos respectivos atualizarEstatisticasFila(pesagem|carregamento)
    int tempoMaximoFilaCarregamento;///< Tempo maximo de uma entidade na fila de carregamento
    int tempoMinimoFilaCarregamento;///< Tempo mínimo de uma entidade na fila de carregamento
    double mediaTempoFilaCarregamento;///< Tempo médio de uma entidade na fila de carregamento
    //Pesagem
    int tempoMaximoFilaPesagem;///< Tempo maximo de uma entidade na fila de pesagem
    int tempoMinimoFilaPesagem;///< Tempo minimo de uma entidade na fila de pesagem
    double mediaTempoFilaPesagem;///< Tempo medio de uma entidade na fila de pesagem

    //d)Tempo de ciclo
    void atualizarEstatisticasCiclo();
    int tempoMaximoCiclo;
    int tempoMinimoCiclo;
    double tempoMedioCiclo;

    //e)Contador de numero de viagens;
    int numeroViagens = int( 0 ); ///< Numero de viagens completadas no sistema

    std::vector<int> temposDeCiclo;
    Relogio relogioDeSimulacao;///< Horário atual de simulacao
    int numeroCaminhoes;///< Numero de entidades no sistema
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
