#ifndef JANELAPRINCIPAL_H
#define JANELAPRINCIPAL_H

#include <QMainWindow>
#include <string>
#include "ui_janelaprincipal.h"
#include "simulador.h"
#include "janelaconfiguracao.h"
#include "rn.h"
namespace Ui {
    class JanelaPrincipal;
}

class JanelaPrincipal : public QMainWindow {
    Q_OBJECT

public:
    explicit JanelaPrincipal( QWidget *parent = 0 );
    ~JanelaPrincipal();
    struct configs {
        RN::Distribuicao *distTC;
        RN::Distribuicao *distTP;
        RN::Distribuicao *distTT;
        int numEntidades;
    };
    void atualizarConfiguracoes( configs novasConfiguracoes , JanelaPrincipal *isso );
    bool foiConfigurado() {return configurado;}
private slots:
    void on_botaoConfigurar_clicked();

    void on_botaoSimularPasso_clicked();

private:
    RN::Distribuicao *distTC = 0;
    RN::Distribuicao *distTP = 0;
    RN::Distribuicao *distTT = 0;
    int numeroEntidades = 0;

    int passosSimulacao = 0;
    void atualizarValores();
    bool configurado = false;
    Ui::JanelaPrincipal *ui;
    Simulador *simulador;

};

#endif // JANELAPRINCIPAL_H
