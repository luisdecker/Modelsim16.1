#include "estacaocarregamento.h"

/*===============================================
                  Construtores
===============================================*/

EstacaoCarregamento::EstacaoCarregamento() {
	tempoMinimoFila = Relogio();
	tempoMaximoFila = Relogio();
	minimoEntidadesNaFila = 0;
	maximoEntidadesNaFila = 0;
	distTC = RN::Constante( 1.0 );
}
//===============================================
EstacaoCarregamento::EstacaoCarregamento( RN::Distribuicao distribuicaoProbabilidadeTC ) {
	tempoMinimoFila = Relogio();
	tempoMaximoFila = Relogio();
	minimoEntidadesNaFila = 0;
	maximoEntidadesNaFila = 0;
	distTC = distribuicaoProbabilidadeTC;
}

/*===============================================
                Eventos principais
===============================================*/


Evento *EstacaoCarregamento::enfileirarCaminhao( Caminhao *caminhao, Relogio horaAtual ) {
	Evento *eventoCarga;
	if( temEstacaoLivre() ) {
		eventoCarga = new Evento( Evento::carga,horaAtual,caminhao );
		atualizaTemposFila( Relogio() );
		return eventoCarga;
	}
	eventoCarga = new Evento( Evento::carga,proximoTempoLivre,caminhao );
	Relogio tempoEmFila( proximoTempoLivre );
	tempoEmFila -= horaAtual;
	atualizaTemposFila( tempoEmFila );
	aumentaNumeroNaFila();
	return eventoCarga;
}
//===============================================
Evento *EstacaoCarregamento::carregarCaminhao( Caminhao *caminhao, Relogio horaAtual ) {
	int plataformaOcupando;
    diminuiNumeroNaFila();
	//Verifica qual plataforma está livre
	plataformaOcupando = plataformaLivre();
	livre[plataformaOcupando-1] = false;//ocupa a plataforma
	caminhaoOcupandoPlataforma[plataformaOcupando-1] = caminhao;//Seta o caminhao que está ocupando essa plataforma
	int TC = distTC();//Gera o TC
	tempoTotalOcupacaoPlataforma[plataformaOcupando-1] += TC;//Aumenta o tempo total de ocupação desta plataforma
	Relogio fimCarga( horaAtual );
	Relogio relTC = Relogio();
	relTC.adicionaSegundos( TC );
	fimCarga << relTC;
	horaLiberacaoPlataforma[plataformaOcupando-1] = fimCarga;
	if( proximoTempoLivre > fimCarga ) {
		proximoTempoLivre = fimCarga;
	}
	return new Evento( Evento::chegadaPesagem,fimCarga,caminhao );
}

//===============================================
void EstacaoCarregamento::retirarCaminhao( Caminhao *caminhao ) {
	int plataformaRetirada;
	if( *caminhaoOcupandoPlataforma[0]==*caminhao ) {
        plataformaRetirada = 1;
	} else {
		plataformaRetirada = 2;
	}
	livre[plataformaRetirada-1] = true;
}



/*===============================================
           Funções auxiliares (private)
===============================================*/

int EstacaoCarregamento::plataformaLivre() {
	if( livre[0] ) {
		return  1;
	} else {
		return 2;
	}
}
//===============================================
void EstacaoCarregamento::modificarDistribuicaoTC( RN::Distribuicao dist ) {
	this->distTC = dist;
}
//===============================================
bool EstacaoCarregamento::temEstacaoLivre() {
	return livre[0] || livre[1];
}
//===============================================
void EstacaoCarregamento::atualizaTemposFila( Relogio tempoFila ) {
	Relogio zero = Relogio();
	if ( tempoFila == zero ) {
		temposDeFila.push_back( Relogio( tempoFila ) );
		return;
	}
	//Atualiza a lista de tempos de fila
	temposDeFila.push_back( Relogio( tempoFila ) );
	//Atualiza o tempo mínimo em fila
	if( tempoFila < tempoMinimoFila ) {
		tempoMinimoFila = tempoFila;
	}
	//Atualiza o tempo máximo em fila
	if ( tempoMaximoFila < tempoFila ) {
		tempoMaximoFila = tempoFila;
	}
}
//===============================================
void EstacaoCarregamento::aumentaNumeroNaFila() {
	numeroEntidadesEnfileiradas++;
	totalEntidadesEnfileiradas++;
	somaFila.push_back( numeroEntidadesEnfileiradas );
	if( maximoEntidadesNaFila < numeroEntidadesEnfileiradas ) {
		maximoEntidadesNaFila  = numeroEntidadesEnfileiradas;
	}
}
//===============================================
void EstacaoCarregamento::diminuiNumeroNaFila() {
	numeroEntidadesEnfileiradas--;
	somaFila.push_back( numeroEntidadesEnfileiradas );
	if( minimoEntidadesNaFila > numeroEntidadesEnfileiradas ) {
		minimoEntidadesNaFila = numeroEntidadesEnfileiradas;
	}
}
//===============================================
double EstacaoCarregamento::mediaFila() {
	if( somaFila.empty() ) return 0;
	int somaTotal = 0;
	for( int numeroEmFila : somaFila ) {
		somaTotal += numeroEmFila;
	}
	return somaTotal / somaFila.size();
}
//===============================================
void EstacaoCarregamento::atualizaEstatisticasTempoFila() {
    //Organiza os tempos de fila
    tempoMinimoFila = *std::max_element(temposDeFila.begin(),temposDeFila.end());
    tempoMaximoFila = *std::min_element(temposDeFila.begin(),temposDeFila.end());
}
//===============================================
double EstacaoCarregamento::getMediaTempoFila() {
    int somaTemposFila;
    for( Relogio tempoEmFila: temposDeFila ) {
        somaTemposFila += tempoEmFila.getSegundosSimulacao();
    }
    return (double) somaTemposFila / (double) temposDeFila.size();
}
