#include "caminhao.h"

Caminhao::Caminhao( int id ):id( id ) {
}
//===============================================
void Caminhao::inicioViagem( Relogio tempoInicio ) {
    tempoInicioViagem = tempoInicio;
    primeiraViagem = false;
}
//===============================================
Relogio Caminhao::fimViagem( Relogio tempoFim ) {
    Relogio tempoViagem = Relogio( tempoFim );
    tempoViagem -= tempoInicioViagem;
    return tempoViagem;
}
//===============================================
bool Caminhao::operator ==( Caminhao outro ) {
    return this->id == outro.id;
}

