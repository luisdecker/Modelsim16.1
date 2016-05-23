#include "janelaprincipal.h"
#include "janelaconfiguracao.h"
#include "rn.h"
#include <QApplication>
#include <iostream>
#include <random>

int main( int argc, char *argv[] ) {
    QApplication a( argc, argv );
    JanelaPrincipal w;
    w.show();
    return a.exec();
    return 0;
}
