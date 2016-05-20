#ifndef ESTACAOPESAGEM_H
#define ESTACAOPESAGEM_H
#include "relogio.h"
#include <list>
#include "caminhao.h"
#include "evento.h"
#include "rn.h"

class EstacaoPesagem {
public:
    EstacaoPesagem();
    EstacaoPesagem( RN::Distribuicao distribuicaoProbabilidadeTC );

    /*Enfilera um caminhão, caso esteja ocupado
      Retorna um evento para a hora de carga do caminhao*/
    Evento *enfileirarCaminhao( Caminhao *caminhao, Relogio horaAtual );
    /*Calcula o tempo de atendimento do caminhão, e atualiza os tempos livres*/
    Evento *pesarCaminhao( Caminhao *caminhao, Relogio horaAtual );
    void modificarDistribuicaoTC( RN::Distribuicao dist );
    double mediaFila();
    void retirarCaminhao();
private:
    RN::Distribuicao distTP; //Distribuicao de variaveis aleatorias;

    Relogio proximoTempoLivre;//Próximo horário em que alguma plataforma estará livre

    void aumentaNumeroNaFila();//Aumenta o número de entidades na fila;
    void diminuiNumeroNaFila();//Diminui o numero de entidades na fila;
    Relogio tempoMinimoFila;//Menor tempo em que uma entidade ficou na fila;
    Relogio tempoMaximoFila;//Maior tempo em que uma entidade ficou na fila;
    std::list<Relogio *> temposDeFila; //Tempos em que entidades ficaram em fila;
    std::vector<int> somaFila;
    int totalEntidadesEnfileiradas;

    bool livre = true; //Disponibilidade das plataformas
    int tempoTotalOcupacaoPlataforma = 0;
    Caminhao *caminhaoOcupandoPlataforma;//Caminhão que está ocupado a n plataforma.

    int numeroEntidadesEnfileiradas;//Numero de entidades na fila do recurso
    int maximoEntidadesNaFila, minimoEntidadesNaFila; //Menor e maior número de entidades que ficaram na fila

    void atualizaTemposFila( Relogio tempoFila );//Atualiza os tempos de fila




};

#endif // ESTACAOPESAGEM_H
