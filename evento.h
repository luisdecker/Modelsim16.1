#ifndef EVENTO_H
#define EVENTO_H
#include "relogio.h"
#include "caminhao.h"


class Evento {

public:
    enum TipoEvento {inicio,chegadaCarga,carga,chegadaPesagem,pesagem,transporte};
    Evento( TipoEvento tipo, Relogio tempoInicio, Caminhao *entidadeEvento );
    bool operator<  ( Evento outro ) {return tempoRelogio < outro.tempoRelogio;}
    bool operator>  ( Evento outro ) {return !( *this <= outro );}
    bool operator== ( Evento outro ) {return tempoRelogio == outro.tempoRelogio;}
    bool operator<= ( Evento outro ) {return ( *this < outro || *this == outro );}
    bool operator>= ( Evento outro ) {return ( *this > outro ) || ( *this == outro );}
    TipoEvento tipo;
    Caminhao *entidade() {return entidadeEvento;}
    Relogio *obterTempoRelogio() {return new Relogio( tempoRelogio );}
private:
    Relogio tempoRelogio;
    Caminhao *entidadeEvento;
};


#endif // EVENTO_H
