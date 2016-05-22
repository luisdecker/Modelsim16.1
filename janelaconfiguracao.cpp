#include "janelaconfiguracao.h"
#include "ui_janelaconfiguracao.h"


JanelaConfiguracao::JanelaConfiguracao( QWidget *parent, JanelaPrincipal *mae ) :
    QMainWindow( parent ),
    ui( new Ui::JanelaConfiguracao ) {
    ui->setupUi( this );
    this->mae = mae;
    //Adiciona os items dos combobox
    adicionarDistribuicoes( ui->selecaoDistTC );
    adicionarDistribuicoes( ui->selecaoDistTP );
    adicionarDistribuicoes( ui->selecaoDistTT );
    //Adiciona os validadores das caixas de texto;
    adicionaValidadoresDists();
}
//===============================================
//TipoDist {constante, triangular, exponencial, normal, uniforme};
void JanelaConfiguracao::adicionarDistribuicoes( QComboBox *box ) {
    box->addItem( "Constante",QVariant( 0 ) );
    box->addItem( "Triangular",QVariant( 1 ) );
    box->addItem( "Exponencial",QVariant( 2 ) );
    box->addItem( "Normal",QVariant( 3 ) );
    box->addItem( "Uniforme",QVariant( 4 ) );
}
//===============================================
RN::Distribuicao *JanelaConfiguracao::obterDistribuicaoSelecionadaTC() {
    switch( distribuicaoTC ) {
        case RN::constante: {
            double parametro1 = ui->parametro1TC->text().toDouble();
            return new RN::Constante( parametro1 );
            break;
        }
        case RN::triangular: {
            double parametro1 = ui->parametro1TC->text().toDouble();
            double parametro2 = ui->parametro2TC->text().toDouble();
            double parametro3 = ui->parametro3TC->text().toDouble();
            return new RN::Triangular( parametro1,parametro2,parametro3 );
            break;
        }
        case RN::exponencial: {
            double parametro1 = ui->parametro1TC->text().toDouble();
            return new RN::Exponencial( parametro1 );
            break;
        }
        case RN::normal: {
            double parametro1 = ui->parametro1TC->text().toDouble();
            double parametro2 = ui->parametro2TC->text().toDouble();
            return new RN::Normal( parametro1,parametro2 );
            break;
        }
        case RN::uniforme: {
            double parametro1 = ui->parametro1TC->text().toDouble();
            double parametro2 = ui->parametro2TC->text().toDouble();
            return new RN::Uniforme( parametro1,parametro2 );
            break;
        }
    }
    return new RN::Constante( 0 );
}
//===============================================
RN::Distribuicao *JanelaConfiguracao::obterDistribuicaoSelecionadaTP() {
    switch( distribuicaoTP ) {
        case RN::constante: {
            double parametro1 = ui->parametro1TP->text().toDouble();
            return new RN::Constante( parametro1 );
            break;
        }
        case RN::triangular: {
            double parametro1 = ui->parametro1TP->text().toDouble();
            double parametro2 = ui->parametro2TP->text().toDouble();
            double parametro3 = ui->parametro3TP->text().toDouble();
            return new RN::Triangular( parametro1,parametro2,parametro3 );
            break;
        }
        case RN::exponencial: {
            double parametro1 = ui->parametro1TP->text().toDouble();
            return new RN::Exponencial( parametro1 );
            break;
        }
        case RN::normal: {
            double parametro1 = ui->parametro1TP->text().toDouble();
            double parametro2 = ui->parametro2TP->text().toDouble();
            return new RN::Normal( parametro1,parametro2 );
            break;
        }
        case RN::uniforme: {
            double parametro1 = ui->parametro1TP->text().toDouble();
            double parametro2 = ui->parametro2TP->text().toDouble();
            return new RN::Uniforme( parametro1,parametro2 );
            break;
        }
    }
    return new RN::Constante( 0 );
}

//===============================================
RN::Distribuicao *JanelaConfiguracao::obterDistribuicaoSelecionadaTT() {
    switch( distribuicaoTT ) {
        case RN::constante: {
            double parametro1 = ui->parametro1TT->text().toDouble();
            return new RN::Constante( parametro1 );
            break;
        }
        case RN::triangular: {
            double parametro1 = ui->parametro1TT->text().toDouble();
            double parametro2 = ui->parametro2TT->text().toDouble();
            double parametro3 = ui->parametro3TT->text().toDouble();
            return new RN::Triangular( parametro1,parametro2,parametro3 );
            break;
        }
        case RN::exponencial: {
            double parametro1 = ui->parametro1TT->text().toDouble();
            return new RN::Exponencial( parametro1 );
            break;
        }
        case RN::normal: {
            double parametro1 = ui->parametro1TT->text().toDouble();
            double parametro2 = ui->parametro2TT->text().toDouble();
            return new RN::Normal( parametro1,parametro2 );
            break;
        }
        case RN::uniforme: {
            double parametro1 = ui->parametro1TT->text().toDouble();
            double parametro2 = ui->parametro2TT->text().toDouble();
            return new RN::Uniforme( parametro1,parametro2 );
            break;
        }
    }
    return new RN::Constante( 0 );
}
//===============================================
void JanelaConfiguracao::adicionaValidadoresDists() {
    ui->parametro1TC->setValidator( new QDoubleValidator( ui->parametro1TC ) );
    ui->parametro2TC->setValidator( new QDoubleValidator( ui->parametro2TC ) );
    ui->parametro3TC->setValidator( new QDoubleValidator( ui->parametro3TC ) );
    ui->parametro1TP->setValidator( new QDoubleValidator( ui->parametro1TP ) );
    ui->parametro2TP->setValidator( new QDoubleValidator( ui->parametro2TP ) );
    ui->parametro3TP->setValidator( new QDoubleValidator( ui->parametro3TP ) );
    ui->parametro1TT->setValidator( new QDoubleValidator( ui->parametro1TT ) );
    ui->parametro2TT->setValidator( new QDoubleValidator( ui->parametro2TT ) );
    ui->parametro3TT->setValidator( new QDoubleValidator( ui->parametro3TT ) );
}
//===============================================
void JanelaConfiguracao::adicionaValidadorNumeroEntidades() {
    ui->numeroEntidades->setValidator( new QIntValidator( ui->numeroEntidades ) );
}

//===============================================
void JanelaConfiguracao::atualizaInputTC( RN::TipoDist distSelecionada ) {
    switch ( distSelecionada ) {
        case RN::constante: {
            ui->parametro2TC->setEnabled( 0 );
            ui->parametro3TC->setEnabled( 0 );
            break;
        }
        case RN::triangular: {
            ui->parametro2TC->setEnabled( 1 );
            ui->parametro3TC->setEnabled( 1 );
            break;
        }
        case RN::exponencial: {
            ui->parametro2TC->setEnabled( 0 );
            ui->parametro3TC->setEnabled( 0 );
            break;
        }
        case RN::normal: {
            ui->parametro2TC->setEnabled( 1 );
            ui->parametro3TC->setEnabled( 0 );
            break;
        }
        case RN::uniforme: {
            ui->parametro2TC->setEnabled( 1 );
            ui->parametro3TC->setEnabled( 0 );
            break;
        }
    };
}
//===============================================
void JanelaConfiguracao::atualizaInputTP( RN::TipoDist distSelecionada ) {
    switch ( distSelecionada ) {
        case RN::constante: {
            ui->parametro2TP->setEnabled( 0 );
            ui->parametro3TP->setEnabled( 0 );
            break;
        }
        case RN::triangular: {
            ui->parametro2TP->setEnabled( 1 );
            ui->parametro3TP->setEnabled( 1 );
            break;
        }
        case RN::exponencial: {
            ui->parametro2TP->setEnabled( 0 );
            ui->parametro3TP->setEnabled( 0 );
            break;
        }
        case RN::normal: {
            ui->parametro2TP->setEnabled( 1 );
            ui->parametro3TP->setEnabled( 0 );
            break;
        }
        case RN::uniforme: {
            ui->parametro2TP->setEnabled( 1 );
            ui->parametro3TP->setEnabled( 0 );
            break;
        }
    };
}
//===============================================
void JanelaConfiguracao::atualizaInputTT( RN::TipoDist distSelecionada ) {
    switch ( distSelecionada ) {
        case RN::constante: {
            ui->parametro2TT->setEnabled( 0 );
            ui->parametro3TT->setEnabled( 0 );
            break;
        }
        case RN::triangular: {
            ui->parametro2TT->setEnabled( 1 );
            ui->parametro3TT->setEnabled( 1 );
            break;
        }
        case RN::exponencial: {
            ui->parametro2TT->setEnabled( 0 );
            ui->parametro3TT->setEnabled( 0 );
            break;
        }
        case RN::normal: {
            ui->parametro2TT->setEnabled( 1 );
            ui->parametro3TT->setEnabled( 0 );
            break;
        }
        case RN::uniforme: {
            ui->parametro2TT->setEnabled( 1 );
            ui->parametro3TT->setEnabled( 0 );
            break;
        }
    };
}

//===============================================
bool JanelaConfiguracao::validarEntradas() {
    bool retorno = true;
    if( ui->parametro1TC->isEnabled() && ui->parametro1TC->text().isEmpty() ) retorno = false;
    if( ui->parametro2TC->isEnabled() && ui->parametro2TC->text().isEmpty() ) retorno = false;
    if( ui->parametro3TC->isEnabled() && ui->parametro3TC->text().isEmpty() ) retorno = false;
    if( ui->parametro1TP->isEnabled() && ui->parametro1TP->text().isEmpty() ) retorno = false;
    if( ui->parametro2TP->isEnabled() && ui->parametro2TP->text().isEmpty() ) retorno = false;
    if( ui->parametro3TP->isEnabled() && ui->parametro3TP->text().isEmpty() ) retorno = false;
    if( ui->parametro1TT->isEnabled() && ui->parametro1TT->text().isEmpty() ) retorno = false;
    if( ui->parametro2TT->isEnabled() && ui->parametro2TT->text().isEmpty() ) retorno = false;
    if( ui->parametro3TT->isEnabled() && ui->parametro3TT->text().isEmpty() ) retorno = false;
    if( ui->numeroEntidades->text().isEmpty() ) retorno =false;
    return retorno;
}

//===============================================
JanelaConfiguracao::~JanelaConfiguracao() {
    delete ui;
}
//===============================================
void JanelaConfiguracao::on_selecaoDistTC_currentIndexChanged( int index ) {
    std::cout <<"Indice do TC ["<<index <<"] "<<std::endl;
    atualizaInputTC( ( RN::TipoDist )index );
    distribuicaoTC = ( RN::TipoDist )index;
}
//===============================================
void JanelaConfiguracao::on_selecaoDistTP_currentIndexChanged( int index ) {
    std::cout <<"Indice do TP ["<<index <<"] "<<std::endl;
    atualizaInputTP( ( RN::TipoDist )index );
    distribuicaoTP = ( RN::TipoDist )index;
}
//===============================================
void JanelaConfiguracao::on_selecaoDistTT_currentIndexChanged( int index ) {
    std::cout <<"Indice do TT ["<<index <<"] "<<std::endl;
    atualizaInputTT( ( RN::TipoDist )index );
    distribuicaoTT = ( RN::TipoDist )index;
}
//===============================================
void JanelaConfiguracao::on_botaoOK_clicked() {
    std::cout<<( validarEntradas()?"Entradas Validas!":"Entradas Invalidas!" ) << std::endl;
    if( validarEntradas() ) {
        JanelaPrincipal::configs configuracoes;
        configuracoes.distTC=obterDistribuicaoSelecionadaTC();
        configuracoes.distTP= obterDistribuicaoSelecionadaTP();
        configuracoes.distTT=obterDistribuicaoSelecionadaTT();
        configuracoes.numEntidades = ui->numeroEntidades->text().toInt();
        mae->atualizarConfiguracoes( configuracoes );
    }
}
//===============================================


