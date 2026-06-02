#ifndef INICIARNEXTION_H
#define INICIARNEXTION_H
#include <Nextion.h>

//CONFIGURAÇÕES DA TELA NEXTION
extern const uint32_t BAUD_NEXTION = 9600;
extern const int8_t PINO_RX_NEXTION = 18;
extern const int8_t PINO_TX_NEXTION = 17;

// OBJETOS DE INTERAÇÃO COM A TELA
// PÁGINA 0 — MENU PRINCIPAL
extern NexButton botaoB0(0, 1, "b0");
extern NexButton botaoB1(0, 3, "b1");
extern NexButton botaoB2(0, 4, "b2");
extern NexButton botaoB3(0, 2, "b3");
extern NexButton botaoB4(0, 5, "b4");
extern NexButton botaoB5(0, 6, "b5");

// PÁGINA 1 — LÂMPADA
// TODO: melhorar nome dos botões da lâmpada
extern NexDSButton botaoDualBt0(1, 3, "bt0");
extern NexDSButton botaoDualBt1(1, 4, "bt1");
extern NexDSButton botaoDualBt2(1, 5, "bt2");
extern NexDSButton botaoDualBt3(1, 6, "bt3");
extern NexButton botaoBackLampada(1, 1, "b2");

// PÁGINA 2 — PROJETOR
extern NexDSButton botaoDualPower(2, 1, "bt0");
extern NexDSButton botaoDualFreeze(2, 2, "bt1");
extern NexButton botaoBackProjetor(2, 3, "b0");

// PÁGINA 3 — TELA RETRÁTIL
extern NexDSButton botaoDualUp(3, 1, "bt0");
extern NexDSButton botaoDualDown(3, 2, "bt1");
extern NexDSButton botaoDualSelect(3, 3, "bt2");
extern NexButton botaoBackTela(3, 4, "b0");

// PÁGINA 4 - AR CONDICIONADO
extern NexDSButton botaoDualPowerAr(4, 1, "bt0");
extern NexButton botaoBackAr(4, 2, "b0");
extern NexButton botaoModoAr(4, 3, "b1");
extern NexButton botaoVento(4, 4, "b2");
extern NexSlider sliderTemperatura(4, 5, "h0");

// PÁGINA 5 - TV
extern NexDSButton botaoDualPowerTv(5, 1, "bt0");
extern NexButton botaoBackTv(5, 2, "b0");
extern NexButton botaoVolumeUpTv(5, 3, "b1");
extern NexButton botaoVolumeDownTv(5, 4, "b2");
extern NexButton botaoSelectTv(5, 5, "b3");
extern NexButton botaoSetaEsquerdaTv(5, 6, "b4");
extern NexButton botaoSetaDireitaTv(5, 7, "b5");
extern NexButton botaoSetaCimaTv(5, 8, "b6");
extern NexButton botaoSetaBaixoTv(5, 9, "b7");

// PÁGINA 6 - SENSOR
// TODO: COMPONENTES DA PÁGINA 6
extern NexButton botaoBackSensor(6, 2, "b0");

//======================================
// VARIÁVEIS DE ESTADO
//======================================

extern uint8_t paginaAtual = 0;

// Lâmpada
//TODO: melhorar nome das variáveis de estado
extern uint32_t estadoBotaoDualBt0 = 0;
extern uint32_t estadoBotaoDualBt1 = 0;
extern uint32_t estadoBotaoDualBt2 = 0;
extern uint32_t estadoBotaoDualBt3 = 0;

// Projetor
extern uint32_t estadoBotaoDualPower = 0;
extern uint32_t estadoBotaoDualFreeze = 0;

// Tela Retrátil
extern uint32_t estadoBotaoDualUp = 0;
extern uint32_t estadoBotaoDualDown = 0;
extern uint32_t estadoBotaoDualSelect = 0;

// Ar condicionado
extern uint32_t estadoBotaoDualPowerAr = 0;
extern uint32_t estadoBotaoModoAr = 0;
extern uint32_t estadoBotaoVento = 0;
extern uint32_t valorSliderTemperatura = 0;
//TODO: ESP

// TV
extern uint32_t estadoBotaoDualPowerTv = 0;
extern uint32_t estadoBotaoSelectTv = 0;
extern uint32_t estadoBotaoVolumeUpTv = 0;
extern uint32_t estadoBotaoVolumeDownTv = 0;
extern uint32_t estadoBotaoSetaEsquerdaTv = 0;
extern uint32_t estadoBotaoSetaDireitaTv = 0;
extern uint32_t estadoBotaoSetaCimaTv = 0;
extern uint32_t estadoBotaoSetaBaixoTv = 0;

// Sensor
extern uint32_t valorTemperatura = 0;
extern uint32_t valorUmidade = 0;
extern uint32_t valorRuido = 0;
extern uint32_t comandoAr = 0;
extern uint32_t alertaSom = 0;
extern uint32_t eco = 0;

void configurarNextion();
void configurarTelaInicial();
void configurarEventosNextion();
#endif