#include "janelaprincipal.h"
#include "ui_janelaprincipal.h"

JanelaPrincipal::JanelaPrincipal( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::JanelaPrincipal ) {
    ui->setupUi( this );
    //
    ui->botaoInciarPausar->setDisabled( 1 );
    ui->botaoSimularPasso->setDisabled( 1 );
}


void JanelaPrincipal::atualizarValores(){

}

void JanelaPrincipal::on_botaoConfigurar_clicked() {
    JanelaConfiguracao *janela = new JanelaConfiguracao( this );
    janela->show();
}

void JanelaPrincipal::atualizarConfiguracoes( configs novasConfiguracoes ) {
    configuracoesAtuais.distTC =novasConfiguracoes.distTC;
    configuracoesAtuais.distTP = novasConfiguracoes.distTP;
    configuracoesAtuais.distTT = novasConfiguracoes.distTT;
    if ( !configurado ) {
        configurado= true;
        configuracoesAtuais.numEntidades = novasConfiguracoes.numEntidades;
        simulador = new Simulador( configuracoesAtuais.numEntidades );
    }
    simulador->trocarDistCarregamento( *configuracoesAtuais.distTC );
    simulador->trocarDistPesagem( *configuracoesAtuais.distTP );
    simulador->trocarDistTransporte( *configuracoesAtuais.distTT );
}

JanelaPrincipal::~JanelaPrincipal() {
    delete ui;
}
