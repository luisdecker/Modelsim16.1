#-------------------------------------------------
#
# Project created by QtCreator 2016-05-07T12:21:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += static

TARGET = Simulador
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp\
        janelaprincipal.cpp \
    rn.cpp \
    caminhao.cpp \
    calendarioeventos.cpp \
    evento.cpp \
    relogio.cpp \
    simulador.cpp \
    estacaocarregamento.cpp \
    estacaopesagem.cpp \
    estradatransporte.cpp \
    janelaconfiguracao.cpp

HEADERS  += janelaprincipal.h \
    rn.h \
    caminhao.h \
    calendarioeventos.h \
    evento.h \
    relogio.h \
    simulador.h \
    estacaocarregamento.h \
    estacaopesagem.h \
    estradatransporte.h \
    janelaconfiguracao.h

FORMS    += janelaprincipal.ui \
    janelaconfiguracao.ui

DISTFILES += \
    TODO
