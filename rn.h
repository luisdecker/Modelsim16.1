#ifndef RN_H
#define RN_H
#include <stdarg.h>
#include <vector>
#include <cstdlib>
#include <math.h>

namespace RN {
    enum TipoDist {constante, triangular, exponencial, normal, uniforme};
    class VarAletoria {
    public:
        static double obterVariavelAleatoria( TipoDist Distribuicao,... );
    private:
        static int obterNumeroArgumentos( TipoDist Distribuicao );
    };

    class Distribuicao {
    public:

        virtual double gerarVariavelAleatoria() = 0;
        virtual double operator() () = 0;
    };

    class Constante : public Distribuicao {
    public:
        Constante ( double valor ): valor( valor ) {}
        double gerarVariavelAleatoria();
        double operator() () {return gerarVariavelAleatoria();}
    private:
        double valor;

    };
    class Triangular : public Distribuicao {
    public:
        Triangular( double a, double b, double c ):a( a ), b( b ),c( c ) {}
        double gerarVariavelAleatoria();
        double operator()() {return gerarVariavelAleatoria();}
    private:
        double a,b,c;
    };
    class Exponencial : public Distribuicao {
    public :
        Exponencial( double media ):media( media ) {}
        double gerarVariavelAleatoria();
        double operator()() {return gerarVariavelAleatoria();}

    private:
        double media;
    };
    class Normal : public Distribuicao {
    public:
        Normal( double media, double desvio ):media( media ),desvio( desvio ) {proximoCalculado = false;}
        double gerarVariavelAleatoria();
        double operator()() {return gerarVariavelAleatoria();}
    private:
        double media,desvio,proximo;
        bool proximoCalculado;
    };

    class Uniforme: public Distribuicao {
    public:
        Uniforme( double minimo, double maximo ):minimo( minimo ), maximo( maximo ) {}
        double gerarVariavelAleatoria();
        double operator()() {return gerarVariavelAleatoria();}
    private:
        double minimo,maximo;
    };
}
#endif // RN_H
