#ifndef RELOGIO_H
#define RELOGIO_H
#define SEGUNDOS_DIA 86400
#define SEGUNDOS_HORA 3600
#define SEGUNDOS_MINUTO 60
#include <string>

class Relogio {
public:
	Relogio();
	Relogio( const Relogio &outro );
	void adicionaSegundos( int segundos );
	void adicionaMinutos( int minutos );
	void adicionaHoras( int horas );
	void adicionaDias( int dias );
    std::string toString();

	void operator<<( Relogio outro );
	bool operator<( Relogio outro ) {return segundosSimulados < outro.segundosSimulados;}
	bool operator> ( Relogio outro ) {return !( *this <= outro );}
	bool operator==( Relogio outro ) {return segundosSimulados == outro.segundosSimulados;}
	bool operator<= ( Relogio outro ) {return ( *this < outro || *this == outro );}
	bool operator >= ( Relogio outro ) {return ( *this > outro ) || ( *this == outro );}
	void operator-=( Relogio outro ) { segundosSimulados  -= outro.segundosSimulados;}

	void atualizaTempos();
	int getHoras() {return horas;}
	int getDias() {return dias;}
	int getMinutos() {return minutos;}
	int getSegundos() {return segundos;}
	int getSegundosSimulacao() {return segundosSimulados;}


private:
    int segundos=0, minutos=0,horas=0,dias=0,segundosSimulados=0;

};

#endif // RELOGIO_H
