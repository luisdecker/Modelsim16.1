#include "calendarioeventos.h"

CalendarioEventos::CalendarioEventos() {
}
//===============================================
void CalendarioEventos::IncluirEvento(Evento *evento) {
    calendario.push_back( evento );
    std::sort( calendario.begin(),calendario.end(),metodoComparacaoEventos );
}
//===============================================
bool CalendarioEventos::metodoComparacaoEventos( Evento *primeiro,Evento *segundo ) {
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





