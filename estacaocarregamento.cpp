#include "estacaocarregamento.h"

/*===============================================
                  Construtores
===============================================*/

EstacaoCarregamento::EstacaoCarregamento() {
	tempoMinimoFila = Relogio();
	tempoMaximoFila = Relogio();
	minimoEntidadesNaFila = 0;
	maximoEntidadesNaFila = 0;
    distTC = new RN::Constante( 1.0 );
}
//===============================================
EstacaoCarregamento::EstacaoCarregamento( RN::Distribuicao *distribuicaoProbabilidadeTC ) {
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
    std::cout << "[Enfileirando caminhão carga]"<<std::endl;
    Evento *eventoCarga;
	if( temEstacaoLivre() ) {
		eventoCarga = new Evento( Evento::carga,horaAtual,caminhao );
		atualizaTemposFila( Relogio() );
		return eventoCarga;
	}
	eventoCarga = new Evento( Evento::carga,proximoTempoLivre,caminhao );
	Relogio tempoEmFila( proximoTempoLivre );
    std::cout <<">Carregamento ocupado " << horaAtual.getSegundosSimulacao()<< " - " << proximoTempoLivre.getSegundosSimulacao()<<std::endl;
    tempoEmFila -= horaAtual;
	atualizaTemposFila( tempoEmFila );
	aumentaNumeroNaFila();
	return eventoCarga;
}
//===============================================
Evento *EstacaoCarregamento::carregarCaminhao( Caminhao *caminhao, Relogio horaAtual ) {
    std::cout << "[Carregando caminhão]"<<std::endl;
	int plataformaOcupando;
    diminuiNumeroNaFila();
	//Verifica qual plataforma está livre
    plataformaOcupando = plataformaLivre();
	livre[plataformaOcupando-1] = false;//ocupa a plataforma
	caminhaoOcupandoPlataforma[plataformaOcupando-1] = caminhao;//Seta o caminhao que está ocupando essa plataforma
    int TC = distTC->gerarVariavelAleatoria();//Gera o TC
    std::cout<<"[TC = " << TC<< "]" << std::endl;
	tempoTotalOcupacaoPlataforma[plataformaOcupando-1] += TC;//Aumenta o tempo total de ocupação desta plataforma
	Relogio fimCarga( horaAtual );
	Relogio relTC = Relogio();
	relTC.adicionaSegundos( TC );
	fimCarga << relTC;
	horaLiberacaoPlataforma[plataformaOcupando-1] = fimCarga;
    if( horaLiberacaoPlataforma[0] < horaLiberacaoPlataforma[1] ) {
        proximoTempoLivre = horaLiberacaoPlataforma[0];
    } else {
        proximoTempoLivre = horaLiberacaoPlataforma[1];
    }
    jaUtilizada [plataformaOcupando-1] = true;
    std::cout << "[Fim da carga "<< fimCarga.getSegundosSimulacao()<< "][Proximo Livre " << proximoTempoLivre.getSegundosSimulacao()<<"]" << std::endl;
	return new Evento( Evento::chegadaPesagem,fimCarga,caminhao );
}

//===============================================
void EstacaoCarregamento::retirarCaminhao( Caminhao *caminhao ) {
    std::cout << "[Retirando caminhão carregamento]"<<std::endl;
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
bool EstacaoCarregamento::plataformasVirgens() {
    if( !jaUtilizada[0] )return true;
    if( !jaUtilizada[1] )return true;
    return false;
}

//===============================================
int EstacaoCarregamento::plataformaLivre() {
	if( livre[0] ) {
		return  1;
	} else {
		return 2;
	}
}
//===============================================
void EstacaoCarregamento::modificarDistribuicaoTC( RN::Distribuicao *dist ) {
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
    if( numeroEntidadesEnfileiradas >0 )
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
        //std::cout << "Media carregamento: somando " << numeroEmFila << std::endl;
        somaTotal += numeroEmFila;
	}
    return ( double )somaTotal / somaFila.size();
}
//===============================================
void EstacaoCarregamento::atualizaEstatisticasTempoFila() {
    //Organiza os tempos de fila
    if( temposDeFila.size()==0 ) {tempoMinimoFila = Relogio(); tempoMaximoFila=Relogio(); return;}
    tempoMinimoFila = *std::max_element( temposDeFila.begin(),temposDeFila.end() );
    tempoMaximoFila = *std::min_element( temposDeFila.begin(),temposDeFila.end() );
}
//===============================================
double EstacaoCarregamento::getMediaTempoFila() {
    if( temposDeFila.size()>0 ) {
        int somaTemposFila;
        for( Relogio tempoEmFila: temposDeFila ) {
            somaTemposFila += tempoEmFila.getSegundosSimulacao();
        }
        return ( double ) somaTemposFila / ( double ) temposDeFila.size();
    }
    return 0;
}
