#ifndef INICIARNEXTION_H
#define INICIARNEXTION_H
#include <Nextion.h>

//CONFIGURAÇÕES DA TELA NEXTION
// Definidas em IniciarNextion.cpp para evitar múltiplas definições
extern const uint32_t BAUD_NEXTION;
extern const int8_t PINO_RX_NEXTION;
extern const int8_t PINO_TX_NEXTION;

// OBJETOS DE INTERAÇÃO COM A TELA
// PÁGINA 0 — MENU PRINCIPAL
extern NexButton botaoB0;
extern NexButton botaoB1;
extern NexButton botaoB2;
extern NexButton botaoB3;
extern NexButton botaoB4;
extern NexButton botaoB5;

// PÁGINA 1 — LÂMPADA
// TODO: melhorar nome dos botões da lâmpada
extern NexDSButton botaoDualBt0;
extern NexDSButton botaoDualBt1;
extern NexDSButton botaoDualBt2;
extern NexDSButton botaoDualBt3;
extern NexButton botaoBackLampada;

// PÁGINA 2 — PROJETOR
extern NexDSButton botaoDualPower;
extern NexDSButton botaoDualFreeze;
extern NexButton botaoBackProjetor;

// PÁGINA 3 — TELA RETRÁTIL
extern NexDSButton botaoDualUp;
extern NexDSButton botaoDualDown;
extern NexDSButton botaoDualSelect;
extern NexButton botaoBackTela;
extern NexDSButton botaoDualScreen;

// PÁGINA 4 - AR CONDICIONADO
extern NexDSButton botaoDualPowerAr;
extern NexDSButton botaoArId1;
extern NexDSButton botaoArId2;
extern NexDSButton botaoArId3;
extern NexDSButton botaoArId4;
extern NexButton botaoBackAr;
extern NexButton botaoModoAr;
extern NexButton botaoVento;
extern NexButton botaoTemperaturaUp;
extern NexButton botaoTemperaturaDown;


// PÁGINA 5 - TV
extern NexButton botaoDualPowerTv;
extern NexButton botaoBackTv;
extern NexButton botaoVolumeUpTv;
extern NexButton botaoVolumeDownTv;
extern NexButton botaoSelectTv;
extern NexButton botaoSetaEsquerdaTv;
extern NexButton botaoSetaDireitaTv;
extern NexButton botaoSetaCimaTv;
extern NexButton botaoSetaBaixoTv;
extern NexButton botaoReturnTv;

// PÁGINA 6 - SENSOR
extern NexButton botaoSensorMenu0;
extern NexDSButton botaoDualSensorEco;
extern NexButton botaoBackSensor;

extern NexText textoUmidade;
extern NexText textoRuido;
extern NexText textoTemperatura;

//======================================
// VARIÁVEIS DE ESTADO
//======================================

extern uint8_t paginaAtual;

// Lâmpada
//TODO: melhorar nome das variáveis de estado
extern uint32_t estadoBotaoDualBt0;
extern uint32_t estadoBotaoDualBt1;
extern uint32_t estadoBotaoDualBt2;
extern uint32_t estadoBotaoDualBt3;

// Projetor
extern uint32_t estadoBotaoDualPower;
extern uint32_t estadoBotaoDualFreeze;

// Tela Retrátil
extern uint32_t estadoBotaoDualUp;
extern uint32_t estadoBotaoDualDown;
extern uint32_t estadoBotaoDualSelect;
extern uint32_t estadoBotaoDualScreen;

// Ar condicionado
extern uint32_t estadoBotaoDualPowerAr;
extern uint32_t estadoBotaoModoAr;
extern uint32_t estadoBotaoVento;
extern uint32_t contadorTemperatura;

extern uint32_t estadoBotaoArId1;
extern uint32_t estadoBotaoArId2;
extern uint32_t estadoBotaoArId3;
extern uint32_t estadoBotaoArId4;

extern NexText textoTemperatura;

//TODO: ESP

// TV
extern uint32_t estadoComandoTV;

// Sensor
extern uint32_t estadoBotaoSensorMenu0;
extern uint32_t estadoBotaoDualSensorEco;
extern uint32_t valorTemperatura;
extern uint32_t valorUmidade;
extern uint32_t valorRuido;
extern uint32_t comandoAr;
extern uint32_t alertaSom;
extern uint32_t eco;

extern NexText textoSensorTemperatura;
extern NexText textoSensorUmidade;
extern NexText tenxtoSensorRuido;

void configurarNextion();
void configurarTelaInicial();
void configurarEventosNextion();
#endif