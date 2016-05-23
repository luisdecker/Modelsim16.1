#ifndef JANELAPRINCIPAL_H
#define JANELAPRINCIPAL_H

#include <QMainWindow>
#include <string>
#include <thread>
#include <chrono>
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
    void simularPasso();
    static void threadFunc( JanelaPrincipal *mae,int msSleep,bool *rodando );
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
    void salto();
private slots:
    void on_botaoConfigurar_clicked();

    void on_botaoSimularPasso_clicked();

    void on_botaoInciarPausar_clicked();

private:
    RN::Distribuicao *distTC = 0;
    RN::Distribuicao *distTP = 0;
    RN::Distribuicao *distTT = 0;
    int numeroEntidades = 0;

    int passosSimulacao = 0;
    void atualizarValores();
    bool configurado = false;
    bool simulando = false;
    Ui::JanelaPrincipal *ui;
    Simulador *simulador;
    std::thread threadSimulacao;

    int msSleep = 500;
};

#endif // JANELAPRINCIPAL_H
