#include "NextionConfig.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "IniciarNextion.h"
#include "WiFiManager.h"
#include "ComponentesSoltou.h"

#include <ArduinoJson.h>
#include <Arduino.h>
#include <ezTime.h>

extern Timezone fusoLocal;

// Tópico de publicação — definido aqui, main.cpp usa o de recebimento
const char TOPICO_LAMPADA[] = "senai134/shared/projeto/lampada";
const char TOPICO_PROJETOR[] = "senai134/shared/projeto/projetor";
const char TOPICO_TELA_RETRATIL[] = "senai134/shared/projeto/telaRetratil";
const char TOPICO_AR_CONDICIONADO[] = "senai134/shared/projeto/AC";
const char TOPICO_TELEVISAO[] = "senai134/shared/projeto/TV";

//==========MONTAR==========

// LAMPADA
void montarJsonLampadaInterruptor1Sala09(JsonDocument &doc)
{
  doc["lampadaSala09"]["interruptor1"] = (estadoBotaoDualInterruptor1 == 1) ? 1 : 0;
  doc["lampadaSala09"]["timestamp"] = fusoLocal.now();
}
void montarJsonLampadaInterruptor2Sala09(JsonDocument &doc)
{
  doc["lampadaSala09"]["interruptor2"] = (estadoBotaoDualInterruptor2 == 1) ? 1 : 0;
  doc["lampadaSala09"]["timestamp"] = fusoLocal.now();
}
void montarJsonLampadaInterruptor3Sala10(JsonDocument &doc)
{
  doc["lampadaSala10"]["interruptor3"] = (estadoBotaoDualInterruptor3 == 1) ? 1 : 0;
  doc["lampadaSala10"]["timestamp"] = fusoLocal.now();
}
void montarJsonLampadaInterruptor4Sala10(JsonDocument &doc)
{
  doc["lampadaSala10"]["interruptor4"] = (estadoBotaoDualInterruptor4 == 1) ? 1 : 0;
  doc["lampadaSala10"]["timestamp"] = fusoLocal.now();
}

// PROJETOR
void montarJsonPower(JsonDocument &doc)
{
  doc["id"] = 1;
  doc["power"] = (estadoBotaoDualPower == 1) ? 1 : 0;
  doc["timestamp"] = fusoLocal.now();
}

void montarJsonFreeze(JsonDocument &doc)
{
  doc["id"] = 1;
  doc["freeze"] = (estadoBotaoDualFreeze == 1) ? 1 : 0;
  doc["timestamp"] = fusoLocal.now();
}

void montarJsonPower10(JsonDocument &doc)
{
  doc["id"] = 2;
  doc["power"] = (estadoBotaoDualPower10 == 1) ? 1 : 0;
  doc["timestamp"] = fusoLocal.now();
}

void montarJsonFreeze10(JsonDocument &doc)
{
  doc["id"] = 2;
  doc["freeze"] = (estadoBotaoDualFreeze10 == 1) ? 1 : 0;
  doc["timestamp"] = fusoLocal.now();
}

// TELA-RETRATIL
void montarJsonTelaRetratil(JsonDocument &doc)
{
  doc["telaRetratil"]["comando"] = estadoComandoTela;
  doc["telaRetratil"]["timestamp"] = fusoLocal.now();
}
void montarJsonTrocarTela(JsonDocument &doc)
{
  doc["telaRetratil"]["tela"] = (estadoBotaoDualScreen == 1) ? 1 : 0;
  doc["telaRetratil"]["timestamp"] = fusoLocal.now();
}

// AC

void montarJsonArId1(JsonDocument &doc)
{
  if (estadoBotaoArId1 == 1)
  {
    doc["ar-condicionado"]["id_ar"] = 1;
    doc["ar-condicionado"]["esp"] = 1;
    doc["ar-condicionado"]["timestamp"] = fusoLocal.now();
  }
  else
    return;
}
void montarJsonArId2(JsonDocument &doc)
{
  if (estadoBotaoArId2 == 1)
  {
    doc["ar-condicionado"]["id_ar"] = 2;
    doc["ar-condicionado"]["esp"] = 1;
    doc["ar-condicionado"]["timestamp"] = fusoLocal.now();
  }
  else
    return;
}
void montarJsonArId3(JsonDocument &doc)
{
  if (estadoBotaoArId3 == 1)
  {
    doc["ar-condicionado"]["id_ar"] = 3;
    doc["ar-condicionado"]["esp"] = 2;
    doc["ar-condicionado"]["timestamp"] = fusoLocal.now();
  }
  else
    return;
}
void montarJsonArId4(JsonDocument &doc)
{
  if (estadoBotaoArId4 == 1)
  {
    doc["ar-condicionado"]["id_ar"] = 4;
    doc["ar-condicionado"]["esp"] = 2;
    doc["ar-condicionado"]["timestamp"] = fusoLocal.now();
  }
  else
    return;
}
void montarJsonOnOffAr(JsonDocument &doc)
{
  if (estadoBotaoOnOffAr == 1)
    doc["ar-condicionado"]["estado"] = 1;
  else
    doc["ar-condicionado"]["estado"] = 0;
  doc["ar-condicionado"]["timestamp"] = fusoLocal.now();
}
void montarJsonTemperatura(JsonDocument &doc)
{
  doc["ar-condicionado"]["temperatura"] = contadorTemperatura;
  doc["ar-condicionado"]["timestamp"] = fusoLocal.now();
}
void montarJsonModoAr(JsonDocument &doc)
{
  if (estadoBotaoModoAr <= 3)
    doc["ar-condicionado"]["modo"] = estadoBotaoModoAr;
  doc["ar-condicionado"]["timestamp"] = fusoLocal.now();
  // Modo
  // modo 0 = cool
  // modo 1 = dry
  // modo 2 = fan
  // modo 3 = heat
}
void montarJsonVentoAr(JsonDocument &doc)
{
  if (estadoBotaoVento <= 4)
    doc["ar-condicionado"]["vento"] = estadoBotaoVento;
  doc["ar-condicionado"]["timestamp"] = fusoLocal.now();
  // velocidade do vento 0 = auto
  // velocidade do vento 1 = quiet
  // velocidade do vento 2 = low
  // velocidade do vento 3 = med
  // velocidade do vento 4 = high
}

// TV
void montarJsonTelevisao(JsonDocument &doc)
{
  if (estadoComandoTV <= 9)
  {
    doc["comando"] = estadoComandoTV;
  }

  doc["televisao"]["timestamp"] = fusoLocal.now();
}

//==========PUBLICAR==========

// LAMPADA
void publicarJsonLampadaInterruptor1Sala09()
{
  JsonDocument doc;
  montarJsonLampadaInterruptor1Sala09(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_LAMPADA, mensagem.c_str());
}
void publicarJsonLampadaInterruptor2Sala09()
{
  JsonDocument doc;
  montarJsonLampadaInterruptor2Sala09(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_LAMPADA, mensagem.c_str());
}
void publicarJsonLampadaInterruptor3Sala10()
{
  JsonDocument doc;
  montarJsonLampadaInterruptor3Sala10(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_LAMPADA, mensagem.c_str());
}
void publicarJsonLampadaInterruptor4Sala10()
{
  JsonDocument doc;
  montarJsonLampadaInterruptor4Sala10(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_LAMPADA, mensagem.c_str());
}

// PROJETOR
void publicarJsonPower()
{
  JsonDocument doc;
  montarJsonPower(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_PROJETOR, mensagem.c_str());
}
void publicarJsonFreeze()
{
  JsonDocument doc;
  montarJsonFreeze(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_PROJETOR, mensagem.c_str());
}
void publicarJsonPower10()
{
  JsonDocument doc;
  montarJsonPower10(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_PROJETOR, mensagem.c_str());
}
void publicarJsonFreeze10()
{
  JsonDocument doc;
  montarJsonFreeze10(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_PROJETOR, mensagem.c_str());
}

// TELA-RETRATIL
void publicarJsonTelaRetratil()
{
  JsonDocument doc;
  montarJsonTelaRetratil(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_TELA_RETRATIL, mensagem.c_str());

  debugInfo("Tela Retratil: " + String(estadoComandoTela));
}
void publicarJsonTrocarTela()
{
  JsonDocument doc;
  montarJsonTrocarTela(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_TELA_RETRATIL, mensagem.c_str());

  debugInfo("Tela Retratil: " + String(estadoBotaoDualScreen));
}

// AC
void publicarJsonVentoAr()
{
  JsonDocument doc;
  montarJsonVentoAr(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_AR_CONDICIONADO, mensagem.c_str());
}
void publicarJsonModoAr()
{
  JsonDocument doc;
  montarJsonModoAr(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_AR_CONDICIONADO, mensagem.c_str());
}
void publicarJsonTemperatura()
{
  JsonDocument doc;
  montarJsonTemperatura(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_AR_CONDICIONADO, mensagem.c_str());
}
void publicarJsonOnOffAr()
{
  JsonDocument doc;
  montarJsonOnOffAr(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_AR_CONDICIONADO, mensagem.c_str());
}
void publicarJsonArId4()
{
  JsonDocument doc;
  montarJsonArId4(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_AR_CONDICIONADO, mensagem.c_str());
}
void publicarJsonArId3()
{
  JsonDocument doc;
  montarJsonArId3(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_AR_CONDICIONADO, mensagem.c_str());
}
void publicarJsonArId2()
{
  JsonDocument doc;
  montarJsonArId2(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_AR_CONDICIONADO, mensagem.c_str());
}
void publicarJsonArId1()
{
  JsonDocument doc;
  montarJsonArId1(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_AR_CONDICIONADO, mensagem.c_str());
}

// TV
void publicarJsonTV()
{
  JsonDocument doc;
  montarJsonTelevisao(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_TELEVISAO, mensagem.c_str());

  debugInfo("Comando TV: " + String(estadoComandoTV));
}

//======================================
// ATUALIZA BOTÕES DA PÁGINA ATIVA
//======================================

void sincronizarPaginaAtual()
{
  // Lâmpada
  if (paginaAtual == 1)
  {
    // TODO: MELHORAR O NOME DAS VARIÁVEIS
    botaoDualInterruptor1.setValue(estadoBotaoDualInterruptor1);
    botaoDualInterruptor2.setValue(estadoBotaoDualInterruptor2);
    botaoDualInterruptor3.setValue(estadoBotaoDualInterruptor3);
    botaoDualInterruptor4.setValue(estadoBotaoDualInterruptor4);
  }

  // Projetor
  else if (paginaAtual == 2)
  {
    botaoDualPower.setValue(estadoBotaoDualPower);
    botaoDualFreeze.setValue(estadoBotaoDualFreeze);
    botaoDualPower10.setValue(estadoBotaoDualPower10);
    botaoDualFreeze10.setValue(estadoBotaoDualFreeze10);
  }

  // Tela Retrátil
  else if (paginaAtual == 3)
    botaoDualScreen.setValue(estadoBotaoDualScreen);

  // Ar-condicionado
  else if (paginaAtual == 4)
  {
    botaoArId1.setValue(estadoBotaoArId1);
    botaoArId2.setValue(estadoBotaoArId2);
    botaoArId3.setValue(estadoBotaoArId3);
    botaoArId4.setValue(estadoBotaoArId4);
  }

  // Televisão
  else if (paginaAtual == 5)
    botaoDualPowerTv.setValue(estadoBotaoDualPowerTv);
}

void atualizarTextoTemperaturaArCondicionado()
{
  char temperatura[10];
  snprintf(temperatura, sizeof(temperatura), "%lu", contadorTemperatura);
  textoTemperatura.setText(temperatura);
}
void atualizarTextoModoAr()
{
  char modoAr[10];
  sniprintf(modoAr, sizeof(modoAr), "%lu", estadoBotaoModoAr);
  textoModoAr.setText(modoAr);
}
void atualizarTextoVento()
{
  char vento[10];
  sniprintf(vento, sizeof(vento), "%lu", estadoBotaoVento);
  textoVento.setText(vento);
}

void atualizarTextoSensor()
{
  char temperaturaAmbiente[10];
  char umidadeAmbiente[10];
  char ruidoAmbiente[10];

  snprintf(temperaturaAmbiente, sizeof(temperaturaAmbiente), "%.1f °C", valorTemperatura);
  textoSensorTemperatura.setText(temperaturaAmbiente);

  snprintf(umidadeAmbiente, sizeof(umidadeAmbiente), "%.1f %%", valorUmidade);
  textoSensorUmidade.setText(umidadeAmbiente);

  snprintf(ruidoAmbiente, sizeof(ruidoAmbiente), "%.1f db", valorRuido);
  textoSensorRuido.setText(ruidoAmbiente);
}
void atualizarTextoSensor10()
{
  char temperaturaAmbiente10[10];
  char umidadeAmbiente10[10];
  char ruidoAmbiente10[10];

  snprintf(temperaturaAmbiente10, sizeof(temperaturaAmbiente10), "%.1f °C", valorTemperatura10);
  textoSensorTemperatura10.setText(temperaturaAmbiente10);

  snprintf(umidadeAmbiente10, sizeof(umidadeAmbiente10), "%.1f %%", valorUmidade10);
  textoSensorUmidade10.setText(umidadeAmbiente10);

  snprintf(ruidoAmbiente10, sizeof(ruidoAmbiente10), "%.1f db", valorRuido10);
  textoSensorRuido10.setText(ruidoAmbiente10);
}