#ifndef EVENTO_H
#define EVENTO_H
#include "relogio.h"
#include "caminhao.h"


class Evento {

public:
    enum TipoEvento {inicio,chegadaCarga,carga,chegadaPesagem,pesagem,transporte};
    Evento( TipoEvento tipo, Relogio tempoInicio, Caminhao *entidadeEvento );
    bool operator<  ( Evento outro ) {
        if( this->tempoRelogio==outro.tempoRelogio ) {
            if( ( this->tipo==carga||this->tipo==pesagem||this->tipo==transporte ) &&
                !( outro.tipo==carga||outro.tipo==pesagem||outro.tipo==transporte ) ) {
                return true;
            }
        }
        return tempoRelogio < outro.tempoRelogio;
    }
    bool operator>  ( Evento outro ) {return !( *this <= outro );}
    bool operator== ( Evento outro ) {
        if( this->tempoRelogio == outro.tempoRelogio ) {
            if( this->eventoPrioritario() && outro.eventoPrioritario() ) {
                return true;
            } else if ( ( !this->eventoPrioritario() ) && ( !outro.eventoPrioritario() ) ) {
                return true;
            }
        }
        return false;
    }
    bool operator<= ( Evento outro ) {return ( *this < outro || *this == outro );}
    bool operator>= ( Evento outro ) {return ( *this > outro ) || ( *this == outro );}
    TipoEvento tipo;
    Caminhao *entidade() {return entidadeEvento;}
    Relogio *obterTempoRelogio() {return new Relogio( tempoRelogio );}
private:
    Relogio tempoRelogio;
    Caminhao *entidadeEvento;
    bool eventoPrioritario() {
        return this->tipo==carga||this->tipo==pesagem||this->tipo==transporte ;
    }
};


#endif // EVENTO_H
