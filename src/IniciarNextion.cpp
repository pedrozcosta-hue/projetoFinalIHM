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
NexButton botaoLampada(0, 1, "b0");
NexButton botaoProjetor(0, 2, "b1");
NexButton botaoTelaRetratil(0, 3, "b2");
NexButton botaoArCondicionado(0, 4, "b3");
NexButton botaoTv(0, 5, "b4");
NexButton botaoSensor(0, 6, "b5");

// PÁGINA 1 — LÂMPADA
NexDSButton botaoDualInterruptor1(1, 1, "bt0");
NexDSButton botaoDualInterruptor2(1, 2, "bt1");
NexDSButton botaoDualInterruptor3(1, 3, "bt2");
NexDSButton botaoDualInterruptor4(1, 4, "bt3");
NexButton botaoBackLampada(1, 5, "b1");

// PÁGINA 2 — PROJETOR
NexDSButton botaoDualPower(2, 1, "bt0");
NexDSButton botaoDualFreeze(2, 2, "bt1");
NexDSButton botaoDualPower10(2, 3, "bt2");
NexDSButton botaoDualFreeze10(2, 4, "bt3");
NexButton botaoBackProjetor(2, 5, "b0");

// PÁGINA 3 — TELA RETRÁTIL
NexButton botaoUp(3, 3, "b0");
NexButton botaoDown(3, 4, "b1");
NexButton botaoStop(3, 5, "b2");
NexButton botaoBackTela(3, 2, "b3");
NexDSButton botaoDualScreen(3, 1, "bt0");

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

NexText textoTemperatura(4, 3, "t30");
NexText textoVento(4, 11, "t10");
NexText textoModoAr(4, 12, "t20");

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
uint32_t estadoBotaoDualInterruptor1 = 0;
uint32_t estadoBotaoDualInterruptor2 = 0;
uint32_t estadoBotaoDualInterruptor3 = 0;
uint32_t estadoBotaoDualInterruptor4 = 0;

// Projetor
uint32_t estadoBotaoDualPower = 0;
uint32_t estadoBotaoDualFreeze = 0;
uint32_t estadoBotaoDualPower10 = 0;
uint32_t estadoBotaoDualFreeze10 = 0;

// Tela Retrátil
uint32_t estadoComandoTela = 5;
uint32_t estadoBotaoDualScreen = 0;

// Ar condicionado
uint32_t estadoBotaoOnOffAr = 0;
uint32_t estadoBotaoModoAr = 0;
uint32_t estadoBotaoVento = 0;
uint32_t contadorTemperatura = 22;

uint32_t estadoBotaoArId1 = 0;
uint32_t estadoBotaoArId2 = 0;
uint32_t estadoBotaoArId3 = 0;
uint32_t estadoBotaoArId4 = 0;

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

void configurarEventosNextion()
{
  // Menu principal
  botaoLampada.attachPop(botaoLampadaSoltou);
  botaoProjetor.attachPop(botaoProjetorSoltou);
  botaoTelaRetratil.attachPop(botaoTelaRetratilSoltou);
  botaoArCondicionado.attachPop(botaoArCondicionadoSoltou);
  botaoTv.attachPop(botaoTvSoltou);
  botaoSensor.attachPop(botaoSensorSoltou);

  // Lâmpada
  botaoDualInterruptor1.attachPop(botaoDualInterruptor1Soltou);
  botaoDualInterruptor2.attachPop(botaoDualInterruptor2Soltou);
  botaoDualInterruptor3.attachPop(botaoDualInterruptor3Soltou);
  botaoDualInterruptor4.attachPop(botaoDualInterruptor4Soltou);
  botaoBackLampada.attachPop(botaoBackLampadaSoltou);
  botaoBackSensor.attachPop(botaoBackSensorSoltou);

  // Projetor
  botaoDualPower.attachPop(botaoDualPowerSoltou);
  botaoDualFreeze.attachPop(botaoDualFreezeSoltou);
  botaoBackProjetor.attachPop(botaoBackProjetorSoltou);
  botaoDualPower10.attachPop(botaoDualPower10Soltou);
  botaoDualFreeze10.attachPop(botaoDualFreeze10Soltou);

  // Tela Retrátil
  botaoUp.attachPop(botaoDualUpSoltou);
  botaoDown.attachPop(botaoDualDownSoltou);
  botaoStop.attachPop(botaoDualStopSoltou);
  botaoDualScreen.attachPop(botaoDualScreenSoltou);
  botaoBackTela.attachPop(botaoBackTelaSoltou);

  // Ar-condicionado
  botaoArId1.attachPop(botaoArId1Soltou);
  botaoArId2.attachPop(botaoArId2Soltou);
  botaoArId3.attachPop(botaoArId3Soltou);
  botaoArId4.attachPop(botaoArId4Soltou);

  botaoOnAr.attachPop(botaoOnArSoltou);
  botaoOffAr.attachPop(botaoOffArSoltou);
  botaoModoAr.attachPop(botaoModoArSoltou);
  botaoVento.attachPop(botaoVentoArSoltou); // nome correto do callback
  botaoBackAr.attachPop(botaoBackArSoltou);
  botaoTemperaturaUp.attachPop(botaoTemperaturaUpSoltou);
  botaoTemperaturaDown.attachPop(botaoTemperaturaDownSoltou);

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
  nexListen(botaoLampada);
  nexListen(botaoProjetor);
  nexListen(botaoTelaRetratil);
  nexListen(botaoArCondicionado);
  nexListen(botaoTv);
  nexListen(botaoSensor);

  //------------BOTÕES BACK------------
  nexListen(botaoBackLampada);
  nexListen(botaoBackAr);
  nexListen(botaoBackProjetor);
  nexListen(botaoBackTela);
  nexListen(botaoBackTv);
  nexListen(botaoBackSensor);

  // lampada
  nexListen(botaoDualInterruptor1);
  nexListen(botaoDualInterruptor2);
  nexListen(botaoDualInterruptor3);
  nexListen(botaoDualInterruptor4);
  nexListen(botaoBackSensor);

  // projetor
  nexListen(botaoDualPower);
  nexListen(botaoDualFreeze);
  nexListen(botaoDualPower10);
  nexListen(botaoDualFreeze10);

  // tela retratil
  nexListen(botaoUp);
  nexListen(botaoDown);
  nexListen(botaoStop);
  nexListen(botaoDualScreen);

  // ar condicionado
  nexListen(botaoOnAr);
  nexListen(botaoOffAr);
  nexListen(botaoArId1);
  nexListen(botaoArId2);
  nexListen(botaoArId3);
  nexListen(botaoArId4);
  nexListen(botaoModoAr);
  nexListen(botaoVento);
  nexListen(botaoTemperaturaUp);
  nexListen(botaoTemperaturaDown);

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