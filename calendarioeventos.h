#ifndef CALENDARIOEVENTOS_H
#define CALENDARIOEVENTOS_H

#include "evento.h"
#include <vector>
#include <algorithm>

class CalendarioEventos {
public:
    CalendarioEventos();
    void IncluirEvento (Evento * evento );
    Evento* obterProximoEvento();
    void consumirEvento();
private:
    std::vector<Evento *> calendario;
    static bool metodoComparacaoEventos( Evento *primeiro, Evento *segundo );
};

#endif // CALENDARIOEVENTOS_H
