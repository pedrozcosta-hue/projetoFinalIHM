
#include "NextionConfig.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include <ArduinoJson.h>

// PÁGINA 0 — MENU PRINCIPAL
static NexButton botaoB0(0, 1, "b0");
static NexButton botaoB1(0, 3, "b1");
static NexButton botaoB2(0, 4, "b2");
static NexButton botaoB3(0, 2, "b3");
static NexButton botaoB4(0, 5, "b4");
static NexButton botaoB5(0, 6, "b5");


// PÁGINA 1 — LÂMPADA
static NexDSButton botaoDualBt0(1, 3, "bt0");
static NexDSButton botaoDualBt1(1, 4, "bt1");
static NexDSButton botaoDualBt2(1, 5, "bt2");
static NexDSButton botaoDualBt3(1, 6, "bt3");

static NexButton botaoBackLampada(1, 1, "b2");

// PÁGINA 2 — PROJETOR
static NexDSButton botaoDualPower(2, 1, "bt0");
static NexDSButton botaoDualFreeze(2, 2, "bt1");

static NexButton botaoBackProjetor(2, 3, "b0");

// PÁGINA 3 — TELA RETRÁTIL
static NexDSButton botaoDualUp(3, 1, "bt0");
static NexDSButton botaoDualDown(3, 2, "bt1");
static NexDSButton botaoDualSelect(3, 3, "bt2");

static NexButton botaoBackTela(3, 4, "b0");

//PÁGINA 4 - AR CONDICIONADO
static NexDSButton botaoPowerAr(4, 1, "bt0");

static NexButton botaoBackAr(4, 2, "b0");

//======================================
// VARIÁVEIS DE ESTADO
//======================================

static uint8_t paginaAtual = 0;

// Lâmpada
static uint32_t estadoBotaoDualBt0 = 0;
static uint32_t estadoBotaoDualBt1 = 0;
static uint32_t estadoBotaoDualBt2 = 0;
static uint32_t estadoBotaoDualBt3 = 0;

// Projetor
static uint32_t estadoBotaoDualPower = 0;
static uint32_t estadoBotaoDualFreeze = 0;

// Tela Retrátil
static uint32_t estadoBotaoDualUp = 0;
static uint32_t estadoBotaoDualDown = 0;
static uint32_t estadoBotaoDualSelect = 0;

// Ar condicionado
static uint32_t estadoBotaoPowerAr = 0;

//*======================================
//* TÓPICO MQTT (usado ao publicar)
//*======================================

static const char TOPICO_COMANDO[] = "senai134/freire/esp32/comando";

//TODO TOPICOS PARA CADA COMPONENTE

//*======================================
//* PUBLICAÇÃO JSON — estado completo
//*======================================

static void publicarEstado()
{
 JsonDocument doc;

 // Lâmpada
 doc["lampadaSala09"]["lampadaFrente"] = (estadoBotaoDualBt0 == 1) ? 1 : 0;
 doc["lampadaSala09"]["lampadaTras"] = (estadoBotaoDualBt1 == 1) ? 1 : 0;
 doc["lampadaSala10"]["lampadaFrente"] = (estadoBotaoDualBt2 == 1) ? 1 : 0;
 doc["lampadaSala10"]["lampadaTras"] = (estadoBotaoDualBt3 == 1) ? 1 : 0;

 // Projetor
 doc["projetor"]["estadoPower"] = (estadoBotaoDualPower == 1) ? 1 : 0;
 doc["projetor"]["estadoCongelamento"] = (estadoBotaoDualFreeze == 1) ? 1 : 0;

 // Tela Retrátil
 doc["tela"]["Up"] = (estadoBotaoDualUp == 1) ? 1 : 0;
 doc["tela"]["Down"] = (estadoBotaoDualDown == 1) ? 1 : 0;
 doc["tela"]["Select"] = (estadoBotaoDualSelect == 1) ? 1 : 0;

 //TODO: JSON AR, TV E SENSOR

 String mensagem;
 serializeJson(doc, mensagem);
 publicarMensagem(TOPICO_COMANDO, mensagem.c_str());
}

//======================================
// ATUALIZA BOTÕES DA PÁGINA ATIVA
//======================================

static void sincronizarPaginaAtual()
{
 if (paginaAtual == 1)
  {
   botaoDualBt0.setValue(estadoBotaoDualBt0);
   botaoDualBt1.setValue(estadoBotaoDualBt1);
   botaoDualBt2.setValue(estadoBotaoDualBt2);
   botaoDualBt3.setValue(estadoBotaoDualBt3);
  }
  else if (paginaAtual == 2)
  {
   botaoDualPower.setValue(estadoBotaoDualPower);
   botaoDualFreeze.setValue(estadoBotaoDualFreeze);
  }
  else if (paginaAtual == 3)
  {
   botaoDualUp.setValue(estadoBotaoDualUp);
   botaoDualDown.setValue(estadoBotaoDualDown);
   botaoDualSelect.setValue(estadoBotaoDualSelect);
  }
  else if (paginaAtual == 4)
  {
      //TODO: COMPONENTEDPAGINA 4
  }
  else
  {
     //TODO: COMPONENTED PAGINA 5 
  }
}

//=======================================
// CALLBACKS — MENU PRINCIPAL - PÁGINA 0
//=======================================

static void botaoB0Soltou()
{
  sendCommand("page page1");
  paginaAtual = 1;
  Serial.print("b0 solto - Página 1 (Lâmpada)");
}

static void botaoB1Soltou()
{
  sendCommand("page page2");
  paginaAtual = 2;
  Serial.print("b1 solto - Página 2 (Projetor)");
}
static void botaoB2Soltou()
{
 sendCommand("page page3");
 paginaAtual = 3;
 debugInfo("b2 solto - Página 3 (Tela Retratil)");
}
static void botaoB3Soltou()
{
 sendCommand("page page4"); 
 paginaAtual = 4;
 debugInfo("b3 solto - Página 4 (Ar-condicionado)");
}
static void botaoB4Soltou() 
{
 sendCommand("page page5");
 paginaAtual = 5;    
 debugInfo("B4 solto - Página 5 (Televisão)"); 
}
static void botaoB5Soltou() 
{
 sendCommand("page page6");
 paginaAtual = 6;    
 debugInfo("B5 solto - Página 6 (Sensor de análise)"); 
}


//======================================
// CALLBACKS — LÂMPADA (PÁGINA 1)
//======================================
static void  botaoBackLampadaSoltou()
{
  sendCommand("page page0");
  paginaAtual = 0;
  debugInfo("B0 Back - Página 0 (Menu)");
}

static void botaoDualBt0Soltou()
{
  botaoDualBt0.getValue(&estadoBotaoDualBt0);
  sincronizarPaginaAtual();
  publicarEstado();
  debugInfo("Bt0 solto. Estado = " + String(estadoBotaoDualBt0));
}

static void botaoDualBt1Soltou()
{
 botaoDualBt1.getValue(&estadoBotaoDualBt1);
 sincronizarPaginaAtual();
 publicarEstado();
 debugInfo("Bt1 solto. Estado = " + String(estadoBotaoDualBt1));
}

static void botaoDualBt2Soltou()
{
 botaoDualBt2.getValue(&estadoBotaoDualBt2);
 sincronizarPaginaAtual();
 publicarEstado();
 debugInfo("Bt2 solto. Estado = " + String(estadoBotaoDualBt2));
}

static void botaoDualBt3Soltou()
{
 botaoDualBt3.getValue(&estadoBotaoDualBt3);
 sincronizarPaginaAtual();
 publicarEstado();
 debugInfo("Bt3 solto. Estado = " + String(estadoBotaoDualBt3));
}

//======================================
// CALLBACKS — PROJETOR (PÁGINA 2)
//======================================
static void  botaoBackProjetorSoltou()
{
  sendCommand("page page0");
  paginaAtual = 0;
  debugInfo("B0 Back - Página 0 (Menu)");
}

static void botaoDualPowerSoltou()
{
 botaoDualPower.getValue(&estadoBotaoDualPower);
 sincronizarPaginaAtual();
 publicarEstado();
 debugInfo("Power solto. Estado = " + String(estadoBotaoDualPower));
}

static void botaoDualFreezeSoltou()
{
 botaoDualFreeze.getValue(&estadoBotaoDualFreeze);
 sincronizarPaginaAtual();
 publicarEstado();
 debugInfo("Freeze solto. Estado = " + String(estadoBotaoDualFreeze));
}

//======================================
// CALLBACKS — TELA RETRÁTIL (PÁGINA 3)
//======================================
static void  botaoBackTelaSoltou()
{
  sendCommand("page page0");
  paginaAtual = 0;
  debugInfo("B0 Back - Página 0 (Menu)");
}

static void botaoDualUpSoltou()
{
 botaoDualUp.getValue(&estadoBotaoDualUp);
 sincronizarPaginaAtual();
 publicarEstado();
 debugInfo("Up solto. Estado = " + String(estadoBotaoDualUp));
}

static void botaoDualDownSoltou()
{
 botaoDualDown.getValue(&estadoBotaoDualDown);
 sincronizarPaginaAtual();
 publicarEstado();
 debugInfo("Down solto. Estado = " + String(estadoBotaoDualDown));
}

static void botaoDualSelectSoltou()
{
 botaoDualSelect.getValue(&estadoBotaoDualSelect);
 sincronizarPaginaAtual();
 publicarEstado();
 debugInfo("Select solto. Estado = " + String(estadoBotaoDualSelect));
}

//======================================
// CALLBACKS — AR CONDICIONADO (PÁGINA 4)
//======================================

static void botaoBackArSoltou()
{
  sendCommand("page page0");
  paginaAtual = 0;
  debugInfo("B0 Back - Página 0 (Menu)");
}

static void botaoPowerArSoutou()
{


}






//======================================
// FUNÇÕES PÚBLICAS
//======================================

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

 //ar
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

 //TODO: PAGINA 4, 5 E 6
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

 //Ar-condicionado - //TODO
 botaoPowerAr.attachPop(botaoPowerArSoutou);

 //TV - //TODO

 //Sensor análise - //TODO

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

 //lampada
 nexListen(botaoDualBt0);
 nexListen(botaoDualBt1);
 nexListen(botaoDualBt2);
 nexListen(botaoDualBt3);

 //projetor
 nexListen(botaoDualPower);
 nexListen(botaoDualFreeze);

 //tela retratil
 nexListen(botaoDualUp);
 nexListen(botaoDualDown);
 nexListen(botaoDualSelect);

 //ar condicionado
 nexListen(botaoPowerAr);
}