#include <Nextion.h>
#include "IniciarNextion.h"
#include "DebugManager.h"
#include "ComponentesSoltou.h"

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

  // TODO: COMPONENTES DA PÁGINA 6

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
  botaoVento.attachPop(botaoVentoArSoltou);
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

  // Sensor análise - //TODO
  botaoBackSensor.attachPop(botaoBackSensorSoltou);

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

  //TODO: SENSOR
  
}