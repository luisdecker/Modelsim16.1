#include "calendarioeventos.h"

CalendarioEventos::CalendarioEventos() {
}
//===============================================
bool tipoPrimario( Evento *e ) {
    return  ( e->tipo==Evento::carga||e->tipo==Evento::pesagem||e->tipo==Evento::transporte );
}
//===============================================
void CalendarioEventos::IncluirEvento( Evento *evento ) {
    calendario.push_back( evento );
    std::sort( calendario.begin(),calendario.end(),metodoComparacaoEventos );
}
//===============================================
bool CalendarioEventos::metodoComparacaoEventos( Evento *primeiro,Evento *segundo ) {
    if ( primeiro->obterTempoRelogio()==segundo->obterTempoRelogio() ) {
        if( tipoPrimario( primeiro ) && !tipoPrimario( segundo ) ) {
            return true;
        } else {
            return false;
        }
    }
    return *primeiro < *segundo;
}
//===============================================
Evento *CalendarioEventos::obterProximoEvento() {
    return calendario.front();
}
//===============================================
void CalendarioEventos::consumirEvento() {
    if( calendario.size()>0 )
        calendario.erase( calendario.begin() );
}





