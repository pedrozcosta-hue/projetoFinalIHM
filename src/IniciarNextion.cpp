#include "IniciarNextion.h"
#include "NextionConfig.h"
#include "DebugManager.h"
#include <ArduinoJson.h>
#include <Nextion.h>
#include "ComponentesSoltou.h"

// PÁGINA 0 — MENU PRINCIPAL
NexButton botaoB0(0, 1, "b0");
NexButton botaoB1(0, 3, "b1");
NexButton botaoB2(0, 4, "b2");
NexButton botaoB3(0, 2, "b3");
NexButton botaoB4(0, 5, "b4");
NexButton botaoB5(0, 6, "b5");

// PÁGINA 1 — LÂMPADA
NexDSButton botaoDualBt0(1, 3, "bt0");
NexDSButton botaoDualBt1(1, 4, "bt1");
NexDSButton botaoDualBt2(1, 5, "bt2");
NexDSButton botaoDualBt3(1, 6, "bt3");
NexButton botaoBackLampada(1, 1, "b2");


// PÁGINA 2 — PROJETOR
NexDSButton botaoDualPower(2, 1, "bt0");
NexDSButton botaoDualFreeze(2, 2, "bt1");
NexButton botaoBackProjetor(2, 3, "b0");


// PÁGINA 3 — TELA RETRÁTIL
NexDSButton botaoDualUp(3, 1, "bt0");
NexDSButton botaoDualDown(3, 2, "bt1");
NexDSButton botaoDualSelect(3, 3, "bt2");
NexButton botaoBackTela(3, 4, "b0");


// PÁGINA 4 - AR CONDICIONADO
NexDSButton botaoPowerAr(4, 1, "bt0");
NexButton botaoBackAr(4, 2, "b0");


//======================================
// VARIÁVEIS DE ESTADO
//======================================

uint8_t paginaAtual = 0;

// Lâmpada
uint32_t estadoBotaoDualBt0 = 0;
uint32_t estadoBotaoDualBt1 = 0;
uint32_t estadoBotaoDualBt2 = 0;
uint32_t estadoBotaoDualBt3 = 0;

// Projetor
uint32_t estadoBotaoDualPower = 0;
uint32_t estadoBotaoDualFreeze = 0;

// Tela Retrátil
uint32_t estadoBotaoDualUp = 0;
uint32_t estadoBotaoDualDown = 0;
uint32_t estadoBotaoDualSelect = 0;

// Ar condicionado
uint32_t estadoBotaoPowerAr = 0;

void configurarNextion()
{
  bool nextionOk = nexInit(BAUD_NEXTION, PINO_RX_NEXTION, PINO_TX_NEXTION);
  (nextionOk) ? debugInfo("Nextion inicializado") : debugErro("Aviso: Não foi possível inicializar o nextion");
}

void configurarTelaInicial()
{
  // Zera todas as variáveis de estado
  estadoBotaoDualBt0 = 0;
  estadoBotaoDualBt1 = 0;
  estadoBotaoDualBt2 = 0;
  estadoBotaoDualBt3 = 0;

  estadoBotaoDualPower = 0;
  estadoBotaoDualFreeze = 0;

  estadoBotaoDualUp = 0;
  estadoBotaoDualDown = 0;
  estadoBotaoDualSelect = 0;

  // ar
  estadoBotaoPowerAr = 0;

  // Página 0
  sendCommand("page page0");
  paginaAtual = 0;
  delay(500);

  // Página 1 — Lâmpada
  sendCommand("page page1");
  paginaAtual = 1;
  delay(500);

  botaoDualBt0.setValue(estadoBotaoDualBt0);
  botaoDualBt1.setValue(estadoBotaoDualBt1);
  botaoDualBt2.setValue(estadoBotaoDualBt2);
  botaoDualBt3.setValue(estadoBotaoDualBt3);

  // Página 2 — Projetor
  sendCommand("page page2");
  paginaAtual = 2;
  delay(500);

  botaoDualPower.setValue(estadoBotaoDualPower);
  botaoDualFreeze.setValue(estadoBotaoDualFreeze);

  // Página 3 — Tela Retrátil
  sendCommand("page page3");
  paginaAtual = 3;
  delay(500);

  botaoDualUp.setValue(estadoBotaoDualUp);
  botaoDualDown.setValue(estadoBotaoDualDown);
  botaoDualSelect.setValue(estadoBotaoDualSelect);

  // Página 4
  sendCommand("page page4");
  paginaAtual = 4;
  delay(500);

  botaoPowerAr.setValue(estadoBotaoPowerAr);

  // Retorna ao menu principal
  sendCommand("page page0");
  paginaAtual = 0;
  delay(500);

  // TODO: PAGINA 4, 5 E 6
}

void configurarEventosNextion()
{
  // Menu principal
  botaoB0.attachPop(botaoB0Soltou);
  botaoB1.attachPop(botaoB1Soltou);
  botaoB2.attachPop(botaoB2Soltou);
  botaoB3.attachPop(botaoB3Soltou);
  botaoB4.attachPop(botaoB4Soltou);
  botaoB5.attachPop(botaoB5Soltou);

  botaoBackLampada.attachPop(botaoBackLampadaSoltou);
  botaoBackAr.attachPop(botaoBackArSoltou);
  botaoBackProjetor.attachPop(botaoBackProjetorSoltou);
  botaoBackTela.attachPop(botaoBackTelaSoltou);

  // Lâmpada
  botaoDualBt0.attachPop(botaoDualBt0Soltou);
  botaoDualBt1.attachPop(botaoDualBt1Soltou);
  botaoDualBt2.attachPop(botaoDualBt2Soltou);
  botaoDualBt3.attachPop(botaoDualBt3Soltou);

  // Projetor
  botaoDualPower.attachPop(botaoDualPowerSoltou);
  botaoDualFreeze.attachPop(botaoDualFreezeSoltou);

  // Tela Retrátil
  botaoDualUp.attachPop(botaoDualUpSoltou);
  botaoDualDown.attachPop(botaoDualDownSoltou);
  botaoDualSelect.attachPop(botaoDualSelectSoltou);

  // Ar-condicionado - //TODO
  botaoPowerAr.attachPop(botaoPowerArSoltou);

  // TV - //TODO

  // Sensor análise - //TODO

  // Registra listeners

  nexListen(botaoB0);
  nexListen(botaoB1);
  nexListen(botaoB2);
  nexListen(botaoB3);
  nexListen(botaoB4);
  nexListen(botaoB5);

  //------------BÕTOES BACK------------
  nexListen(botaoBackLampada);
  nexListen(botaoBackAr);
  nexListen(botaoBackProjetor);
  nexListen(botaoBackTela);

  // lampada
  nexListen(botaoDualBt0);
  nexListen(botaoDualBt1);
  nexListen(botaoDualBt2);
  nexListen(botaoDualBt3);

  // projetor
  nexListen(botaoDualPower);
  nexListen(botaoDualFreeze);

  // tela retratil
  nexListen(botaoDualUp);
  nexListen(botaoDualDown);
  nexListen(botaoDualSelect);

  // ar condicionado
  nexListen(botaoPowerAr);
}