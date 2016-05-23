#include "rn.h"
//Funcoes da fachada
//=============================================================================

//=============================================================================
//Geracao de variáveis das distribuicoes
double RN::Constante::gerarVariavelAleatoria() {
    return ( double )valor;
}
//=============================================================================
double RN::Triangular::gerarVariavelAleatoria() {
    double random = ( double )( std::rand()%10000 )/10000;
    if( random <= ( ( c-a )/( b-a ) ) ) {
        return a + sqrt( random*( ( c-a )/( b-a ) ) );
    } else {
        return b - sqrt( ( 1-random )*( ( b-c )/( b-a ) ) );
    }
}
//=============================================================================
double RN::Exponencial::gerarVariavelAleatoria() {
    double random = ( double )( std::rand()%10000 )/10000;
    return ( -1 )*( media * ( log( 1-random ) ) );
}
//=============================================================================
double RN::Normal::gerarVariavelAleatoria() {
    if( proximoCalculado ) {
        proximoCalculado = false;
        return proximo;
    }
    double random1 =( double ) (  std::rand()%10000 )/10000, random2 =( double )(  std::rand()%10000 )/10000;
    double z1 = sqrt( -2 * log( random1 ) ) * cos( 2*M_PI*random2 );
    double z2 = sqrt( -2 * log( random1 ) ) * sin( 2*M_PI*random2 );
    proximo = media + ( desvio * z2 );
    proximoCalculado = true;
    return ( media + ( desvio * z1 ) );
}
//=============================================================================
double RN::Uniforme::gerarVariavelAleatoria() {
    double random = ( double )( std::rand()%10000 )/10000;
    return minimo + ( ( maximo - minimo ) * random );
}
















