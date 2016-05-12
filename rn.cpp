#include "rn.h"
//Funcoes da fachada
//=============================================================================
double RN::VarAletoria::obterVariavelAleatoria( TipoDist distribuicao,... ) {
    va_list ap;
    int numeroArgumentos = obterNumeroArgumentos( distribuicao );
    va_start( ap,numeroArgumentos );
    std::vector <double> args;
    for( int i = 1; i <= numeroArgumentos; i++ ) {
        args.push_back( va_arg( ap,double ) );
    }
    va_end( ap );
    switch ( distribuicao ) {
        case constante: {
            RN::Constante distConstante( args[0] );
            return distConstante();
            break;
        }
        case triangular: {
            RN::Triangular distTriangular( args[0],args[1],args[2] );
            return distTriangular();
            break;
        }
        case exponencial: {
            RN::Exponencial distExponencial( args[0] );
            return distExponencial();
            break;
        }
        case normal: {
            RN::Normal distNormal( args[0],args[1] );
            return distNormal();
            break;
        }
        case uniforme: {
            RN::Uniforme distUniforme( args[0],args[1] );
            return distUniforme();
            break;
        }
    }
}
//=============================================================================
int RN::VarAletoria::obterNumeroArgumentos( TipoDist distribuicao ) {
    int numeroArgumentos = 0;
    switch ( distribuicao ) {
        case constante: {numeroArgumentos = 1; break;}
        case triangular: {numeroArgumentos = 3; break;}
        case exponencial: {numeroArgumentos = 1; break;}
        case normal: {numeroArgumentos = 2; break;}
        case uniforme: {numeroArgumentos = 2; break;}
    }
    return numeroArgumentos;
}
//=============================================================================
//Geracao de variáveis das distribuicoes
double RN::Constante::gerarVariavelAleatoria() {
    return ( double )valor;
}
//=============================================================================
double RN::Triangular::gerarVariavelAleatoria() {
    double random = ( std::rand()%10000 )/10000;
    if( random <= ( ( c-a )/( b-a ) ) ) {
        return a + sqrt( random*( ( c-a )/( b-a ) ) );
    } else {
        return b - sqrt( ( 1-random )*( ( b-c )/( b-a ) ) );
    }
}
//=============================================================================
double RN::Exponencial::gerarVariavelAleatoria() {
    double random = ( std::rand()%10000 )/10000;
    return ( -1 )*( media * ( log( 1-random ) ) );
}
//=============================================================================
double RN::Normal::gerarVariavelAleatoria() {
    if( proximoCalculado ) {
        proximoCalculado = false;
        return proximo;
    }
    double random1 = ( std::rand()%10000 )/10000, random2 = ( std::rand()%10000 )/10000;
    double z1 = sqrt( -2 * log( random1 ) ) * cos( 2*M_PI*random2 );
    double z2 = sqrt( -2 * log( random1 ) ) * sin( 2*M_PI*random2 );
    proximo = media + ( desvio * z2 );
    proximoCalculado = true;
    return ( media + ( desvio * z1 ) );
}
//=============================================================================
double RN::Uniforme::gerarVariavelAleatoria() {
    double random = ( std::rand()%10000 )/10000;
    return minimo + ( ( maximo - minimo ) * random );
}
















