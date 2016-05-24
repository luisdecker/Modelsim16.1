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

//===============================================
void JanelaPrincipal::atualizarValores() {
    Simulador::valoresEstatistica estatisticasNovas = simulador->obterEstatisticas();
    std::string alce;
    //
    alce ="Minimo de entidades: ";
    alce += std::to_string( estatisticasNovas.minimoFilaCarregamento );
    ui->minimoEntidadesFilaCarregamento->setText( alce.c_str() );
    //
    alce ="Minimo de entidades: ";
    alce += std::to_string( estatisticasNovas.minimoFilaPesagem );
    ui->minimoEntidadesPesagem->setText( alce.c_str() );
    //
    alce = "Maximo de entidades: ";
    alce += std::to_string( estatisticasNovas.maximoFilaCarregamento );
    ui->maximoEntidadesFilaCarregamento->setText( alce.c_str() );
    //
    alce = "Maximo de entidades: ";
    alce += std::to_string( estatisticasNovas.maximoFilaPesagem );
    ui->maximoEntidadesPesagem->setText( alce.c_str() );
    //
    alce = "Media de entidades: ";
    alce += std::to_string( estatisticasNovas.mediaFilaCarregamento );
    ui->mediaEntidadesFilaCarregamento->setText( alce.c_str() );
    //
    alce = "Media de entidades: ";
    alce += std::to_string( estatisticasNovas.mediaFilaPesagem );
    ui->mediaEntidadesPesagem->setText( alce.c_str() );
    //
    alce = "Taxa media de ocupacao(1|2): ( ";
    alce += std::to_string( ( int )( estatisticasNovas.taxaOcupacaoCarregamento1*100 )%100 );
    alce += "% | ";
    alce += std::to_string( ( int )( estatisticasNovas.taxaOcupacaoCarregamento2*100 )%100 );
    alce += "% )";
    ui->taxaOcupacaoCarregamento->setText( alce.c_str() );
    //
    alce = "Taxa media de ocupacao: ";
    alce += std::to_string( ( int )( estatisticasNovas.taxaOcupacaoPesagem*100 )%100 );
    alce += "%";
    ui->taxaOcupacaoPesagem->setText( alce.c_str() );
    //
    alce = "Tempo minimo na fila: ";
    alce += std::to_string( estatisticasNovas.tempoMinimoFilaCarregamento );
    ui->tempoMinimoFilaCarregamento->setText( alce.c_str() );
    //
    alce = "Tempo minimo na fila: ";
    alce += std::to_string( estatisticasNovas.tempoMinimoFilaPesagem );
    ui->tempoMinimoFilaPesagem->setText( alce.c_str() );
    //
    alce = "Tempo maximo na fila: ";
    alce += std::to_string( estatisticasNovas.tempoMaximoFilaCarregamento );
    ui->tempoMaximoFilaCarregamento->setText( alce.c_str() );
    //
    alce = "Tempo maximo na fila: ";
    alce += std::to_string( estatisticasNovas.tempoMaximoFilaPesagem );
    ui->tempoMaximoFilaPesagem->setText( alce.c_str() );
    //
    alce = "Tempo medio na fila: ";
    alce += std::to_string( estatisticasNovas.mediaTempoFilaCarregamento );
    ui->tempoMedioFilaCarregamento->setText( alce.c_str() );
    //
    alce = "Tempo medio na fila: ";
    alce += std::to_string( estatisticasNovas.mediaTempoFilaPesagem );
    ui->tempoMedioFilaPesagem->setText( alce.c_str() );
    //
    alce = "Total de entidades: ";
    alce += std::to_string( estatisticasNovas.numeroCaminhoes );
    ui->totalEntidades->setText( alce.c_str() );
    //
    alce = "Numero de viagens: ";
    alce += std::to_string( estatisticasNovas.numeroViagens );
    ui->numeroViagem->setText( alce.c_str() );
    //
    alce = "Tempo minimo de ciclo: ";
    alce += std::to_string( estatisticasNovas.tempoMinimoCiclo );
    ui->tempoMinimoCiclo->setText( alce.c_str() );
    //
    alce = "Tempo maximo de ciclo: ";
    alce += std::to_string( estatisticasNovas.tempoMaximoCiclo );
    ui->tempoMaximoCiclo->setText( alce.c_str() );
    //
    alce = "Tempo medio de ciclo: ";
    alce += std::to_string( estatisticasNovas.tempoMedioCiclo );
    ui->tempoMedioCiclo->setText( alce.c_str() );
    //
    alce = "Passos simulados: ";
    alce += std::to_string( passosSimulacao );
    ui->passosSimulacao->setText( alce.c_str() );
    //
    ui->relogioSimulacao->setText( estatisticasNovas.horaSimulacao.toString().c_str() );
}

void JanelaPrincipal::on_botaoConfigurar_clicked() {
    std::cout << "Chamou configuracao, this = " << this << std::endl;
    JanelaConfiguracao *janela = new JanelaConfiguracao( this ,this );
    janela->show();
}

void JanelaPrincipal::atualizarConfiguracoes( configs novasConfiguracoes , JanelaPrincipal *isso ) {
    std::cout << "Entrou na mae" << std::endl;
    if( novasConfiguracoes.distTC == nullptr ) {
        std::cout <<"Chegou nulo na mae" << std::endl;
    }
    std::cout << "[mae]TC= " << novasConfiguracoes.distTC << std::endl;
    std::cout << "[mae]TP= " << novasConfiguracoes.distTP<< std::endl;
    std::cout << "[mae]TT= " << novasConfiguracoes.distTT<< std::endl;
//
    if( isso==nullptr ) std::cout << "This is null jaja" << std::endl;
    isso->distTC = novasConfiguracoes.distTC;
    isso->distTP = novasConfiguracoes.distTP;
    isso->distTT = novasConfiguracoes.distTT;
    std::cout << "Atualizou as distribuicoes QT" << std::endl;
    if ( !configurado ) {
        isso->configurado= true;
        isso->numeroEntidades = novasConfiguracoes.numEntidades;
        isso->simulador = new Simulador( numeroEntidades );
        isso->ui->botaoInciarPausar->setEnabled( 1 );
        isso->ui->botaoSimularPasso->setEnabled( 1 );
    }
    isso->simulador->trocarDistCarregamento( distTC );
    isso->simulador->trocarDistPesagem( distTP );
    //std::cout << "Teste distTP " << distTP->gerarVariavelAleatoria() << std::endl;
    isso->simulador->trocarDistTransporte( distTT );
}

JanelaPrincipal::~JanelaPrincipal() {
    delete ui;
}

void JanelaPrincipal::simularPasso() {
    this->simulador->simular();
    passosSimulacao++;
    std::cout <<"===========Simulou==========" <<std::endl;
    atualizarValores();
}

void JanelaPrincipal::on_botaoSimularPasso_clicked() {
    simularPasso();
}

void JanelaPrincipal::on_botaoInciarPausar_clicked() {
    simulando = !simulando;
    if( simulando ) {
        ui->botaoInciarPausar->setText( "Pausar Simulacao" );
        threadSimulacao= std::thread( threadFunc,this,&msSleep ,&simulando );
        return;
    } else {
        threadSimulacao.join();
        ui->botaoInciarPausar->setText( "Iniciar Simulacao" );
    }
}

void JanelaPrincipal::threadFunc( JanelaPrincipal *mae, int *msSleep ,bool *rodando ) {
    while( *rodando ) {
        mae->salto();
        std::this_thread::sleep_for( std::chrono::milliseconds( *msSleep +1 ) );
    }
}

void JanelaPrincipal::salto() {simularPasso();}

void JanelaPrincipal::on_sliderVelocidade_valueChanged( int value ) {
    this->msSleep = value;
}


