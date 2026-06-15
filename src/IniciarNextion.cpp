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
NexButton botaoB1(0, 2, "b1");
NexButton botaoB2(0, 3, "b2");
NexButton botaoB3(0, 4, "b3");
NexButton botaoB4(0, 5, "b4");
NexButton botaoB5(0, 6, "b5");

// PÁGINA 1 — LÂMPADA
// TODO: melhorar nome dos botões da lâmpada
NexDSButton botaoDualBt0(1, 1, "bt0");
NexDSButton botaoDualBt1(1, 2, "bt1");
NexDSButton botaoDualBt2(1, 3, "bt2");
NexDSButton botaoDualBt3(1, 4, "bt3");
NexButton botaoBackLampada(1, 5, "b1");

// PÁGINA 2 — PROJETOR
NexDSButton botaoDualPower(2, 1, "bt0");
NexDSButton botaoDualFreeze(2, 2, "bt1");
NexDSButton botaoDualPower10(2, 3, "bt2");
NexDSButton botaoDualFreeze10(2, 4, "bt3");
NexButton botaoBackProjetor(2, 5, "b0");

// PÁGINA 3 — TELA RETRÁTIL
NexButton botaoDualUp(3, 2, "b0");
NexButton botaoDualDown(3, 3, "b1");
NexButton botaoDualSelect(3, 4, "b2");
NexButton botaoBackTela(3, 1, "b3");
NexDSButton botaoDualScreen(3, 5, "bt0");

// PÁGINA 4 - AR CONDICIONADO
NexButton botaoTemperaturaUp(4, 1, "b0");
NexButton botaoTemperaturaDown(4, 2, "b1");
NexButton botaoVento(4, 4, "b2");
NexButton botaoModoAr(4, 5, "b3");
NexDSButton botaoArId1(4, 6, "bt1");
NexDSButton botaoArId2(4, 7, "bt2");
NexDSButton botaoArId3(4, 8, "bt3");
NexDSButton botaoArId4(4, 9, "bt4");
NexButton botaoBackAr(4, 10, "b4");
NexButton botaoOnAr(4, 14, "b6");
NexButton botaoOffAr(4, 13, "b5");

NexText textoTemperatura(4, 3, "t0");
NexText textoVento(4, 11, "t1");
NexText textoModoAr(4, 12, "t2");

// PÁGINA 5 - TV
NexDSButton botaoDualPowerTv(5, 1, "bt0");
NexButton botaoBackTv(5, 10, "b8");
NexButton botaoVolumeUpTv(5, 8, "b6");
NexButton botaoVolumeDownTv(5, 9, "b7");
NexButton botaoSelectTv(5, 3, "b1");
NexButton botaoSetaEsquerdaTv(5, 6, "b4");
NexButton botaoSetaDireitaTv(5, 4, "b2");
NexButton botaoSetaCimaTv(5, 2, "b0");
NexButton botaoSetaBaixoTv(5, 5, "b3");
NexButton botaoReturnTv(5, 7, "b5");

// PÁGINA 6 - SENSOR
NexButton botaoBackSensor(6, 1, "b1");

NexText textoSensorTemperatura(6, 2, "t0");
NexText textoSensorUmidade(6, 4, "t2");
NexText textoSensorRuido(6, 3, "t1");

NexText textoSensorTemperatura10(6, 5, "t3");
NexText textoSensorRuido10(6, 6, "t4");
NexText textoSensorUmidade10(6, 7, "t5");

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
uint32_t estadoBotaoDualPower10 = 0;
uint32_t estadoBotaoDualFreeze10 = 0;

// Tela Retrátil
uint32_t estadoComandoTela = 5;
uint32_t estadoBotaoDualScreen = 0;

// Ar condicionado
uint32_t contadorTemperatura = 22;
uint32_t estadoBotaoModoAr = 0;
uint32_t estadoBotaoVento = 0;

uint32_t estadoBotaoDualPowerAr = 0;
uint32_t estadoBotaoArId1 = 0;
uint32_t estadoBotaoArId2 = 0;
uint32_t estadoBotaoArId3 = 0;
uint32_t estadoBotaoArId4 = 0;

// TODO: ESP

// TV
uint32_t estadoBotaoDualPowerTv = 0;
uint32_t estadoComandoTV = 0;

// Sensor
float valorTemperatura = 0;
float valorUmidade = 0;
float valorRuido = 0;
uint32_t comandoAr = 0;
uint32_t alertaSom = 0;
uint32_t eco = 0;
uint32_t timestemp = 0;

float valorTemperatura10 = 0;
float valorUmidade10 = 0;
float valorRuido10 = 0;
uint32_t comandoAr10 = 0;
uint32_t alertaSom10 = 0;
uint32_t eco10 = 0;
uint32_t timestemp10 = 0;


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
  estadoBotaoDualPower10 = 0;
  estadoBotaoDualFreeze10 = 0;

  // Tela Retrátil
  estadoComandoTela;
  estadoBotaoDualScreen = 0;

  // Ar condicionado
  estadoBotaoDualPowerAr = 0;
  estadoBotaoModoAr = 0;
  estadoBotaoVento = 0;
  contadorTemperatura = 22;

  estadoBotaoArId1 = 0;
  estadoBotaoArId2 = 0;   
  estadoBotaoArId3 = 0;
  estadoBotaoArId4 = 0;

  // TV
  estadoBotaoDualPowerTv = 0;
  estadoComandoTV = 0;

  // Sensor
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
  botaoDualPower10.setValue(estadoBotaoDualPower10);
  botaoDualFreeze10.setValue(estadoBotaoDualFreeze10);

  // Página 3 — Tela Retrátil
  sendCommand("page page3");
  paginaAtual = 3;
  delay(500);

  botaoDualScreen.setValue(estadoBotaoDualScreen);
  
  // Página 4
  sendCommand("page page4");
  paginaAtual = 4;
  delay(500);

  botaoDualPowerAr.setValue(estadoBotaoDualPowerAr);
  botaoArId1.setValue(estadoBotaoArId1);
  botaoArId2.setValue(estadoBotaoArId2);
  botaoArId3.setValue(estadoBotaoArId3);
  botaoArId4.setValue(estadoBotaoArId4);

  // Página 5
  sendCommand("page page5");
  paginaAtual = 5;
  delay(500);

  botaoDualPowerTv.setValue(estadoBotaoDualPowerTv);

  // Página 6
  sendCommand("page page6");
  paginaAtual = 6;
  delay(500);

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
  botaoBackSensor.attachPop(botaoBackSensorSoltou);

  // Projetor
  botaoDualPower.attachPop(botaoDualPowerSoltou);
  botaoDualFreeze.attachPop(botaoDualFreezeSoltou);
  botaoBackProjetor.attachPop(botaoBackProjetorSoltou);
  botaoDualPower10.attachPop(botaoDualPower10Soltou);
  botaoDualFreeze10.attachPop(botaoDualFreeze10Soltou);

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
  nexListen(botaoBackSensor);

  // projetor
  nexListen(botaoDualPower);
  nexListen(botaoDualFreeze);
  nexListen(botaoDualPower10);
  nexListen(botaoDualFreeze10);

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


}