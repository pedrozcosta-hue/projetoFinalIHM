#ifndef INICIARNEXTION_H
#define INICIARNEXTION_H
#include <Nextion.h>

// PÁGINA 0 — MENU PRINCIPAL
extern NexButton botaoB0;
extern NexButton botaoB1;
extern NexButton botaoB2;
extern NexButton botaoB3;
extern NexButton botaoB4;
extern NexButton botaoB5;

// PÁGINA 1 — LÂMPADA
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

// PÁGINA 4 - AR CONDICIONADO
extern NexDSButton botaoPowerAr;
extern NexButton botaoBackAr;

//======================================
// VARIÁVEIS DE ESTADO
//======================================

extern uint8_t paginaAtual;

// Lâmpada
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

// Ar condicionado
extern uint32_t estadoBotaoPowerAr;

void configurarNextion();
void configurarTelaInicial();
void configurarEventosNextion();
#endif