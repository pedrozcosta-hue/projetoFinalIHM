#include "IniciarNextion.h"
#include "NextionConfig.h"
#include "DebugManager.h"
#include <ArduinoJson.h>
#include <Nextion.h>

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
  botaoPowerAr.attachPop(botaoPowerArSoutou);

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