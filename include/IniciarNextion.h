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
extern NexDSButton botaoDualPower10;
extern NexDSButton botaoDualFreeze10;
extern NexButton botaoBackProjetor;


// PÁGINA 3 — TELA RETRÁTIL
extern NexButton botaoDualUp;
extern NexButton botaoDualDown;
extern NexButton botaoDualSelect;
extern NexButton botaoBackTela;
extern NexDSButton botaoDualScreen;

// PÁGINA 4 - AR CONDICIONADO
extern NexButton botaoOnAr;
extern NexButton botaoOffAr;
extern NexDSButton botaoArId1;
extern NexDSButton botaoArId2;
extern NexDSButton botaoArId3;
extern NexDSButton botaoArId4;
extern NexButton botaoBackAr;
extern NexButton botaoModoAr;
extern NexButton botaoVento;
extern NexButton botaoTemperaturaUp;
extern NexButton botaoTemperaturaDown;

extern NexText textoTemperatura;
extern NexText textoVento;
extern NexText textoModoAr;

// PÁGINA 5 - TV
extern NexDSButton botaoDualPowerTv;
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
extern NexButton botaoBackSensor;

extern NexText textoSensorTemperatura;
extern NexText textoSensorUmidade;
extern NexText textoSensorRuido;

extern NexText textoSensorTemperatura10;
extern NexText textoSensorUmidade10;
extern NexText textoSensorRuido10;





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
extern uint32_t estadoBotaoDualPower10;
extern uint32_t estadoBotaoDualFreeze10;

// Tela Retrátil
extern uint32_t estadoComandoTela;
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


//TODO: ESP

// TV
extern uint32_t estadoBotaoDualPowerTv;
extern uint32_t estadoComandoTV;

// Sensor
extern float valorTemperatura;
extern float valorUmidade;
extern float valorRuido;
extern uint32_t comandoAr;
extern uint32_t alertaSom;
extern uint32_t eco;
extern uint32_t timestemp;

extern float valorTemperatura10;
extern float valorUmidade10;
extern float valorRuido10;
extern uint32_t comandoAr10;
extern uint32_t alertaSom10;
extern uint32_t eco10;
extern uint32_t timestemp10;

void configurarNextion();
void configurarTelaInicial();
void configurarEventosNextion();
#endif