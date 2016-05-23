#ifndef JANELACONFIGURACAO_H
#define JANELACONFIGURACAO_H

#include <QMainWindow>
#include <QComboBox>
#include <rn.h>
#include <iostream>
#include "janelaprincipal.h"

namespace Ui {
    class JanelaConfiguracao;
}
class JanelaPrincipal;
class JanelaConfiguracao : public QMainWindow {
    Q_OBJECT

public:
    explicit JanelaConfiguracao( QWidget *parent = 0, JanelaPrincipal *mae = 0 );
    ~JanelaConfiguracao();
private slots:
    RN::Distribuicao *obterDistribuicaoSelecionadaTC(  );
    RN::Distribuicao *obterDistribuicaoSelecionadaTP(  );
    RN::Distribuicao *obterDistribuicaoSelecionadaTT(  );


    void atualizaInputTC( RN::TipoDist distSelecionada );
    void atualizaInputTP( RN::TipoDist distSelecionada );
    void atualizaInputTT( RN::TipoDist distSelecionada );

    void on_selecaoDistTC_currentIndexChanged( int index );

    void on_selecaoDistTP_currentIndexChanged( int index );

    void on_selecaoDistTT_currentIndexChanged( int index );



    void on_botaoOK_clicked();

    void on_botaoCancelar_clicked();

private:
    JanelaPrincipal *mae;
    bool validarEntradas();
    Ui::JanelaConfiguracao *ui;

    void adicionarDistribuicoes( QComboBox *box );
    RN::TipoDist distribuicaoTC ;
    RN::TipoDist distribuicaoTP ;
    RN::TipoDist distribuicaoTT ;

    void adicionaValidadoresDists();
    void adicionaValidadorNumeroEntidades();
};

#endif // JANELACONFIGURACAO_H
