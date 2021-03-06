#ifndef ESTACAOPESAGEM_H
#define ESTACAOPESAGEM_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "relogio.h"
#include "caminhao.h"
#include "evento.h"
#include "rn.h"

class EstacaoPesagem {
public:
    EstacaoPesagem();
    EstacaoPesagem(RN::Distribuicao *distribuicaoProbabilidadeTC );

    /*Enfilera um caminhão, caso esteja ocupado
      Retorna um evento para a hora de carga do caminhao*/
    Evento *enfileirarCaminhao( Caminhao *caminhao, Relogio horaAtual );
    /*Calcula o tempo de atendimento do caminhão, e atualiza os tempos livres*/
    Evento *pesarCaminhao( Caminhao *caminhao, Relogio horaAtual );
    void modificarDistribuicaoTP(RN::Distribuicao *dist );

    void retirarCaminhao();

    //Estatisticas de numero de entidades na fila
    double mediaFila();
    int maximoFila() {return maximoEntidadesNaFila;}
    int minimoFila() {return minimoEntidadesNaFila;}

    //Esatistica de tempos de entidade na fila
    int getTempoMaximoFila() {atualizaEstatisticasTempoFila(); return tempoMaximoFila.getSegundosSimulacao();}
    int getTempoMinimoFila() {atualizaEstatisticasTempoFila(); return tempoMinimoFila.getSegundosSimulacao();}
    double getMediaTempoFila();


    bool estacaoLivre() {return livre;}
private:
    RN::Distribuicao * distTP; //Distribuicao de variaveis aleatorias;

    Relogio proximoTempoLivre;//Próximo horário em que alguma plataforma estará livre

    void aumentaNumeroNaFila();//Aumenta o número de entidades na fila;
    void diminuiNumeroNaFila();//Diminui o numero de entidades na fila;

    Relogio tempoMinimoFila = Relogio();//Menor tempo em que uma entidade ficou na fila;
    Relogio tempoMaximoFila = Relogio();//Maior tempo em que uma entidade ficou na fila;
    std::vector<Relogio > temposDeFila; //Tempos em que entidades ficaram em fila;
    void atualizaEstatisticasTempoFila ();

    std::vector<int> somaFila;
    int totalEntidadesEnfileiradas = 0;

    bool livre = true; //Disponibilidade das plataformas
    int tempoTotalOcupacaoPlataforma = 0;
    Caminhao *caminhaoOcupandoPlataforma = 0;//Caminhão que está ocupado a n plataforma.

    int numeroEntidadesEnfileiradas = 0;//Numero de entidades na fila do recurso
    int maximoEntidadesNaFila = 0, minimoEntidadesNaFila =0; //Menor e maior número de entidades que ficaram na fila

    void atualizaTemposFila( Relogio tempoFila );//Atualiza os tempos de fila




};

#endif // ESTACAOPESAGEM_H
