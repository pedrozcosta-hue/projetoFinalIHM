#include <Nextion.h>

#include "IniciarNextion.h"
#include "DebugManager.h"
#include "ComponentesSoltou.h"

//======================================
// DEFINIÇÕES DAS CONSTANTES E OBJETOS
// (declarados como extern no .h)
//======================================

const uint32_t BAUD_NEXTION = 9600;
const int8_t PINO_RX_NEXTION = 18;
const int8_t PINO_TX_NEXTION = 17;

// PÁGINA 0 — MENU PRINCIPAL
NexButton botaoB0(0, 1, "b0");
NexButton botaoB1(0, 3, "b1");
NexButton botaoB2(0, 4, "b2");
NexButton botaoB3(0, 2, "b3");
NexButton botaoB4(0, 5, "b4");
NexButton botaoB5(0, 6, "b5");

// PÁGINA 1 — LÂMPADA
// TODO: melhorar nome dos botões da lâmpada
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
NexDSButton botaoDualScreen(3, 5, "bt3");

// PÁGINA 4 - AR CONDICIONADO
NexDSButton botaoDualPowerAr(4, 1, "bt0");
NexButton botaoBackAr(4, 2, "b0");
NexButton botaoModoAr(4, 3, "b1");
NexButton botaoVento(4, 4, "b2");
NexButton botaoTemperaturaUp(4, 5, "b3");
NexButton botaoTemperaturaDown(4, 6, "b6");

NexText textoTemperatura(4, 1, "t0");

// PÁGINA 5 - TV
NexButton botaoDualPowerTv(5, 1, "b0");
NexButton botaoBackTv(5, 2, "b1");
NexButton botaoVolumeUpTv(5, 3, "b2");
NexButton botaoVolumeDownTv(5, 4, "b3");
NexButton botaoSelectTv(5, 5, "b4");
NexButton botaoSetaEsquerdaTv(5, 6, "b5");
NexButton botaoSetaDireitaTv(5, 7, "b6");
NexButton botaoSetaCimaTv(5, 8, "b7");
NexButton botaoSetaBaixoTv(5, 9, "b8");
NexButton botaoReturnTv(5, 10, "b9");

// PÁGINA 6 - SENSOR
NexButton botaoSensorMenu0(0, 0, "xxx");
NexDSButton botaoDualSensorEco(0, 0, "xxx");
NexButton botaoBackSensor(6, 2, "b0");

extern NexText textoSensorTemperatura(6, 1, "t0");
extern NexText textoSensorUmidade(6, 2, "t1");
extern NexText tenxtoSensorRuido(6, 3, "t2");

//======================================
// VARIÁVEIS DE ESTADO
//======================================

uint8_t paginaAtual = 0;

// Lâmpada
// TODO: melhorar nome das variáveis de estado
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
uint32_t estadoBotaoDualScreen = 0;

// Ar condicionado
uint32_t estadoBotaoDualPowerAr = 0;
uint32_t estadoBotaoModoAr = 0;
uint32_t estadoBotaoVento = 0;
uint32_t contadorTemperatura = 22;

// TODO: ESP

// TV
uint32_t estadoComandoTV = 0;

// Sensor
uint32_t valorTemperatura = 0;
uint32_t valorUmidade = 0;
uint32_t valorRuido = 0;
uint32_t comandoAr = 0;
uint32_t alertaSom = 0;
uint32_t eco = 0;

//======================================
// FUNÇÕES
//======================================

void configurarNextion()
{
  bool nextionOk = nexInit(BAUD_NEXTION, PINO_RX_NEXTION, PINO_TX_NEXTION);
  (nextionOk) ? debugInfo("Nextion inicializado") : debugErro("Aviso: Não foi possível inicializar o nextion");
}

void configurarTelaInicial()
{
  // Zera todas as variáveis de estado
  // Lâmpada
  // TODO: melhorar nome das variáveis de estado
  estadoBotaoDualBt0 = 0;
  estadoBotaoDualBt1 = 0;
  estadoBotaoDualBt2 = 0;
  estadoBotaoDualBt3 = 0;

  // Projetor
  estadoBotaoDualPower = 0;
  estadoBotaoDualFreeze = 0;

  // Tela Retrátil
  estadoBotaoDualUp = 0;
  estadoBotaoDualDown = 0;
  estadoBotaoDualSelect = 0;
  estadoBotaoDualScreen = 0;

  // Ar condicionado
  estadoBotaoDualPowerAr = 0;
  estadoBotaoModoAr = 0;
  estadoBotaoVento = 0;
  contadorTemperatura = 22;

  // TV
  estadoComandoTV = 0;

  // Sensor
  estadoBotaoSensorMenu0 = 0;
  estadoBotaoDualSensorEco = 0;
  valorTemperatura = 0;
  valorUmidade = 0;
  valorRuido = 0;
  comandoAr = 0;
  alertaSom = 0;
  eco = 0;

  // Página 0
  sendCommand("page page0");
  paginaAtual = 0;
  delay(500);

  // Página 1 — Lâmpada
  sendCommand("page page1");
  paginaAtual = 1;
  delay(500);

  // TODO: melhorar nome dos botões da lâmpada
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
  botaoDualScreen.setValue(estadoBotaoDualScreen);

  // Página 4
  sendCommand("page page4");
  paginaAtual = 4;
  delay(500);

  botaoDualPowerAr.setValue(estadoBotaoDualPowerAr);
  textoTemperatura.setText("0");

  // Página 5
  sendCommand("page page5");
  paginaAtual = 5;
  delay(500);

  // Página 6
  sendCommand("page page6");
  paginaAtual = 6;
  delay(500);

  botaoDualSensorEco.setValue(estadoBotaoDualSensorEco);

  // Retorna ao menu principal
  sendCommand("page page0");
  paginaAtual = 0;
  delay(500);
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

  // Lâmpada
  // TODO: melhorar nome dos botões da lâmpada
  botaoDualBt0.attachPop(botaoDualBt0Soltou);
  botaoDualBt1.attachPop(botaoDualBt1Soltou);
  botaoDualBt2.attachPop(botaoDualBt2Soltou);
  botaoDualBt3.attachPop(botaoDualBt3Soltou);
  botaoBackLampada.attachPop(botaoBackLampadaSoltou);

  // Projetor
  botaoDualPower.attachPop(botaoDualPowerSoltou);
  botaoDualFreeze.attachPop(botaoDualFreezeSoltou);
  botaoBackProjetor.attachPop(botaoBackProjetorSoltou);

  // Tela Retrátil
  botaoDualUp.attachPop(botaoDualUpSoltou);
  botaoDualDown.attachPop(botaoDualDownSoltou);
  botaoDualSelect.attachPop(botaoDualSelectSoltou);
  botaoDualScreen.attachPop(botaoDualScreenSoltou);
  botaoBackTela.attachPop(botaoBackTelaSoltou);

  // Ar-condicionado
  botaoArId1.attachPop(botaoArId1Soltou);
  botaoArId2.attachPop(botaoArId2Soltou);
  botaoArId3.attachPop(botaoArId3Soltou);
  botaoArId4.attachPop(botaoArId4Soltou);

  botaoDualPowerAr.attachPop(botaoDualPowerArSoltou);
  botaoModoAr.attachPop(botaoModoArSoltou);
  botaoVento.attachPop(botaoVentoArSoltou); // nome correto do callback
  botaoBackAr.attachPop(botaoBackArSoltou);
  botaoTemperaturaUp.attachPop(botaoTemperaturaUpSoltou);
  botaoTemperaturaDown.attachPop(botaoTemperaturaDownSoltou);
  // TODO: ESP

  // TV
  botaoDualPowerTv.attachPop(botaoDualPowerTvSoltou);
  botaoBackTv.attachPop(botaoBackTvSoltou);
  botaoVolumeUpTv.attachPop(botaoVolumeUpTvSoltou);
  botaoVolumeDownTv.attachPop(botaoVolumeDownTvSoltou);
  botaoSelectTv.attachPop(botaoSelectTvSoltou);
  botaoSetaEsquerdaTv.attachPop(botaoSetaEsquerdaTvSoltou);
  botaoSetaDireitaTv.attachPop(botaoSetaDireitaTvSoltou);
  botaoSetaCimaTv.attachPop(botaoSetaCimaTvSoltou);
  botaoSetaBaixoTv.attachPop(botaoSetaBaixoTvSoltou);
  botaoReturnTv.attachPop(botaoReturnTvSoltou);

  // Sensor análise
  botaoBackSensor.attachPop(botaoBackSensorSoltou);
  botaoSensorMenu0.attachPop(botaoSensorMenu0Soltou);
  botaoDualSensorEco.attachPop(botaoDualSensorEcoSoltou);

  nexClearListenList();

  // Registra listeners
  nexListen(botaoB0);
  nexListen(botaoB1);
  nexListen(botaoB2);
  nexListen(botaoB3);
  nexListen(botaoB4);
  nexListen(botaoB5);

  //------------BOTÕES BACK------------
  nexListen(botaoBackLampada);
  nexListen(botaoBackAr);
  nexListen(botaoBackProjetor);
  nexListen(botaoBackTela);
  nexListen(botaoBackTv);
  nexListen(botaoBackSensor);

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
  nexListen(botaoDualScreen);

  // ar condicionado
  nexListen(botaoDualPowerAr);
  nexListen(botaoArId1);
  nexListen(botaoArId2);
  nexListen(botaoArId3);
  nexListen(botaoArId4);
  nexListen(botaoModoAr);
  nexListen(botaoVento);
  nexListen(botaoTemperaturaUp);
  nexListen(botaoTemperaturaDown);
  // TODO: ESP

  // TV
  nexListen(botaoDualPowerTv);
  nexListen(botaoVolumeUpTv);
  nexListen(botaoVolumeDownTv);
  nexListen(botaoSelectTv);
  nexListen(botaoSetaEsquerdaTv);
  nexListen(botaoSetaDireitaTv);
  nexListen(botaoSetaCimaTv);
  nexListen(botaoSetaBaixoTv);
  nexListen(botaoReturnTv);

  // sensor
  nexListen(botaoDualSensorEco);
}