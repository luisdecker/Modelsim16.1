#include "evento.h"


//===============================================
Evento::Evento( TipoEvento tipo, Relogio tempoInicio, Caminhao *entidadeEvento ) {
    this->tipo = tipo;
    this->tempoRelogio = tempoInicio;
    this->entidadeEvento = entidadeEvento;
}
