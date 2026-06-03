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

NexText textoBt0(1, 0, "t0");
NexText textoBt1(1, 1, "t1");
NexText textoBt2(1, 2, "t2");
NexText textoBt3(1, 3, "t3");

// PÁGINA 2 — PROJETOR
NexDSButton botaoDualPower(2, 1, "bt0");
NexDSButton botaoDualFreeze(2, 2, "bt1");
NexButton botaoBackProjetor(2, 3, "b0");

NexText textoPowerProjetor(2, 1, "t0");
NexText textoFreeze(2, 2, "t1");

// PÁGINA 3 — TELA RETRÁTIL
NexDSButton botaoDualUp(3, 1, "bt0");
NexDSButton botaoDualDown(3, 2, "bt1");
NexDSButton botaoDualSelect(3, 3, "bt2");
NexButton botaoBackTela(3, 4, "b0");

NexText textoUpTela(3, 1, "t0");
NexText textoDownTela(3, 2, "t1");
NexText textoSelectTela(3, 3, "t2");

// PÁGINA 4 - AR CONDICIONADO
NexDSButton botaoDualPowerAr(4, 1, "bt0");
NexButton botaoBackAr(4, 2, "b0");
NexButton botaoModoAr(4, 3, "b1");
NexButton botaoVento(4, 4, "b2");
NexSlider sliderTemperatura(4, 5, "h0");

// PÁGINA 5 - TV
NexDSButton botaoDualPowerTv(5, 1, "bt0");
NexButton botaoBackTv(5, 2, "b0");
NexButton botaoVolumeUpTv(5, 3, "b1");
NexButton botaoVolumeDownTv(5, 4, "b2");
NexButton botaoSelectTv(5, 5, "b3");
NexButton botaoSetaEsquerdaTv(5, 6, "b4");
NexButton botaoSetaDireitaTv(5, 7, "b5");
NexButton botaoSetaCimaTv(5, 8, "b6");
NexButton botaoSetaBaixoTv(5, 9, "b7");

// PÁGINA 6 - SENSOR
NexButton botaoSensorMenu0(0, 0, "xxx");
NexDSButton botaoDualSensorEco(0, 0, "xxx");
NexButton botaoBackSensor(6, 2, "b0");

//======================================
// VARIÁVEIS DE ESTADO
//======================================

uint8_t paginaAtual = 0;

// Lâmpada
//TODO: melhorar nome das variáveis de estado
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
uint32_t estadoBotaoDualPowerAr = 0;
uint32_t estadoBotaoModoAr = 0;
uint32_t estadoBotaoVento = 0;
uint32_t valorSliderTemperatura = 0;
//TODO: ESP

// TV
uint32_t estadoBotaoDualPowerTv = 0;
uint32_t estadoBotaoSelectTv = 0;
uint32_t estadoBotaoVolumeUpTv = 0;
uint32_t estadoBotaoVolumeDownTv = 0;
uint32_t estadoBotaoSetaEsquerdaTv = 0;
uint32_t estadoBotaoSetaDireitaTv = 0;
uint32_t estadoBotaoSetaCimaTv = 0;
uint32_t estadoBotaoSetaBaixoTv = 0;

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
  //TODO: melhorar nome das variáveis de estado
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

  // Ar condicionado
  estadoBotaoDualPowerAr = 0;
  estadoBotaoModoAr = 0;
  estadoBotaoVento = 0;
  valorSliderTemperatura = 0;

  // TV
  estadoBotaoDualPowerTv = 0;
  estadoBotaoSelectTv = 0;
  estadoBotaoVolumeUpTv = 0;
  estadoBotaoVolumeDownTv = 0;
  estadoBotaoSetaEsquerdaTv = 0;
  estadoBotaoSetaDireitaTv = 0;
  estadoBotaoSetaCimaTv = 0;
  estadoBotaoSetaBaixoTv = 0;

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

  //TODO: melhorar nome dos botões da lâmpada
  botaoDualBt0.setValue(estadoBotaoDualBt0);
  botaoDualBt1.setValue(estadoBotaoDualBt1);
  botaoDualBt2.setValue(estadoBotaoDualBt2);
  botaoDualBt3.setValue(estadoBotaoDualBt3);

  textoBt0.setText("Desligado");
  textoBt1.setText("Desligado");
  textoBt2.setText("Desligado");
  textoBt3.setText("Desligado");

  // Página 2 — Projetor
  sendCommand("page page2");
  paginaAtual = 2;
  delay(500);

  botaoDualPower.setValue(estadoBotaoDualPower);
  botaoDualFreeze.setValue(estadoBotaoDualFreeze);

  textoPowerProjetor.setText("Desligado");
  textoFreeze.setText("Descongelado");

  // Página 3 — Tela Retrátil
  sendCommand("page page3");
  paginaAtual = 3;
  delay(500);

  botaoDualUp.setValue(estadoBotaoDualUp);
  botaoDualDown.setValue(estadoBotaoDualDown);
  botaoDualSelect.setValue(estadoBotaoDualSelect);

  textoDownTela.setText("Descer tela retrátil");
  textoUpTela.setText("Subir tela retrátil");
  textoSelectTela.setText("Parar tela Retrátil");

  // Página 4
  sendCommand("page page4");
  paginaAtual = 4;
  delay(500);

  botaoDualPowerAr.setValue(estadoBotaoDualPowerAr);
  sliderTemperatura.setValue(valorSliderTemperatura);

  // Página 5
  sendCommand("page page5");
  paginaAtual = 5;
  delay(500);

  botaoDualPowerTv.setValue(estadoBotaoDualPowerTv);

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
  //TODO: melhorar nome dos botões da lâmpada
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
  botaoBackTela.attachPop(botaoBackTelaSoltou);

  // Ar-condicionado
  botaoDualPowerAr.attachPop(botaoDualPowerArSoltou);
  botaoModoAr.attachPop(botaoModoArSoltou);
  botaoVento.attachPop(botaoVentoArSoltou);  // nome correto do callback
  botaoBackAr.attachPop(botaoBackArSoltou);
  sliderTemperatura.attachPop(sliderTemperaturaSoltou);
  //TODO: ESP

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

  //------------BÕTOES BACK------------
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

  // ar condicionado
  nexListen(botaoDualPowerAr);
  nexListen(botaoModoAr);
  nexListen(botaoVento);
  nexListen(sliderTemperatura);
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

  // sensor
  nexListen(botaoSensorMenu0);
  nexListen(botaoDualSensorEco);
}