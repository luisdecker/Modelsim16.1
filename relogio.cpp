#include "relogio.h"
//===============================================
Relogio::Relogio() {
    this->segundosSimulados = 0;
    atualizaTempos();
}
//===============================================
Relogio::Relogio( const Relogio &outro ) {
    this->segundosSimulados = outro.segundosSimulados;
    atualizaTempos();
}
//===============================================
void Relogio::operator <<( Relogio outro ) {
    this->segundosSimulados += outro.segundosSimulados;
    atualizaTempos();
}
//===============================================
void Relogio::atualizaTempos() {
    this->dias = ( int ) segundosSimulados/SEGUNDOS_DIA;
    this->horas = ( int ) ( segundosSimulados%SEGUNDOS_DIA )/SEGUNDOS_HORA;
    this->minutos = ( int ) ( ( segundosSimulados%SEGUNDOS_DIA )%SEGUNDOS_HORA )/SEGUNDOS_MINUTO;
    this->segundos = ( int ) ( ( ( segundosSimulados%SEGUNDOS_DIA )%SEGUNDOS_HORA )%SEGUNDOS_MINUTO );
}
//===============================================
void Relogio::adicionaSegundos( int segundos ) {
    this->segundosSimulados += segundos;
    atualizaTempos();
}
//===============================================
void Relogio::adicionaMinutos( int minutos ) {
    adicionaSegundos( minutos*SEGUNDOS_MINUTO );
}
//===============================================
void Relogio::adicionaHoras( int horas ) {
    adicionaSegundos( horas*SEGUNDOS_HORA );
}

//===============================================
void Relogio::adicionaDias( int dias ) {
    adicionaSegundos( dias*SEGUNDOS_DIA );
}

//===============================================
std::string Relogio::toString() {
    atualizaTempos();
    std::string retorno = "";
    retorno += std::to_string( getDias() );
    retorno += ":";
    retorno += std::to_string( getHoras() );
    retorno += ":";
    retorno += std::to_string( ( getMinutos() ) );
    retorno += ":";
    retorno += std::to_string( getSegundos() );
    return retorno;
}
