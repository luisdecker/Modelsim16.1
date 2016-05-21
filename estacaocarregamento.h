#ifndef ESTACAOCARREGAMENTO_H
#define ESTACAOCARREGAMENTO_H
#include "relogio.h"
#include <list>
#include <vector>
#include "caminhao.h"
#include "evento.h"
#include "rn.h"

class EstacaoCarregamento {
public:
    EstacaoCarregamento();
    EstacaoCarregamento( RN::Distribuicao distribuicaoProbabilidadeTC );

    /*Enfilera um caminhão, caso esteja ocupado
      Retorna um evento para a hora de carga do caminhao*/
    Evento *enfileirarCaminhao( Caminhao *caminhao, Relogio horaAtual );

    /*Calcula o tempo de atendimento do caminhão, e atualiza os tempos livres*/
    Evento *carregarCaminhao( Caminhao *caminhao, Relogio horaAtual );

    void modificarDistribuicaoTC( RN::Distribuicao dist );
    void retirarCaminhao( Caminhao *caminhao );

    double mediaFila();
    int maximoFila() {return maximoEntidadesNaFila;}
    int minimoFila() {return minimoEntidadesNaFila;}

    bool estacao1Livre() {return livre[0];}
    bool estacao2Livre() {return livre[1];}
private:
    RN::Distribuicao distTC; //Distribuicao de variaveis aleatorias;


    bool temEstacaoLivre();
    Relogio proximoTempoLivre;//Próximo horário em que alguma plataforma estará livre
    Relogio horaLiberacaoPlataforma[2];//Próximo horário em que a plataforma n estará livre


    Relogio tempoMinimoFila;//Menor tempo em que uma entidade ficou na fila;
    Relogio tempoMaximoFila;//Maior tempo em que uma entidade ficou na fila;
    std::vector<Relogio *> temposDeFila; //Tempos em que entidades ficaram em fila;

    int tempoTotalOcupacaoPlataforma[2] = {0,0};

    Caminhao *caminhaoOcupandoPlataforma[2];//Caminhão que está ocupado a n plataforma.

    int totalEntidadesEnfileiradas;
    std::vector<int> somaFila;
    int numeroEntidadesEnfileiradas;//Numero de entidades na fila do recurso
    int maximoEntidadesNaFila, minimoEntidadesNaFila; //Menor e maior número de entidades que ficaram na fila

    void atualizaTemposFila( Relogio tempoFila );//Atualiza os tempos de fila
    bool livre[2] = {true,true}; //Disponibilidade das plataformas
    int plataformaLivre();
    void aumentaNumeroNaFila();//Aumenta o número de entidades na fila;
    void diminuiNumeroNaFila();//Diminui o numero de entidades na fila;
};

#endif // ESTACAOCARREGAMENTO_H
