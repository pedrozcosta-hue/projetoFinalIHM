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
const char TOPICO_LAMPADA[] = "senai134/equipe/boo/lampada/estado";
const char TOPICO_PROJETOR[] = "senai134/shared/projeto/projetor09";
const char TOPICO_TELA_RETRATIL[] = "senai134/shared/projeto/telaRetratil";
const char TOPICO_AR_CONDICIONADO[] = "senai134/shared/projeto/AC";
const char TOPICO_TELEVISAO[] = "senai134/shared/projeto/yoshi";
const char TOPICO_PROJETOR10[] = "senai134/shared/projeto/projetor10";

void montarJsonLampada(JsonDocument &doc)
{
  doc["lampadaSala09"]["interruptor1"] = (estadoBotaoDualBt1 == 1) ? 1 : 0;
  doc["lampadaSala09"]["interruptor2"] = (estadoBotaoDualBt0 == 1) ? 1 : 0;
  doc["lampadaSala10"]["interruptor3"] = (estadoBotaoDualBt3 == 1) ? 1 : 0;
  doc["lampadaSala10"]["interruptor4"] = (estadoBotaoDualBt2 == 1) ? 1 : 0;

  doc["lampadaSala10"]["timestamp"] = fusoLocal.now();
  doc["lampadaSala09"]["timestamp"] = fusoLocal.now();
}

void montarJsonProjetor(JsonDocument &doc)
{
  doc["projetor"]["estadoPower"] = (estadoBotaoDualPower == 1) ? 1 : 0;
  doc["projetor"]["estadoCongelamento"] = (estadoBotaoDualFreeze == 1) ? 1 : 0;

  doc["projetor"]["timestamp"] = fusoLocal.now();
}

void montarJsonProjetor10(JsonDocument &doc)
{
  doc["projetor"]["estadoPower"] = (estadoBotaoDualPower10 == 1) ? 1 : 0;
  doc["projetor"]["estadoCongelamento"] = (estadoBotaoDualFreeze10 == 1) ? 1 : 0;

  doc["projetor"]["timestamp"] = fusoLocal.now();
}

void montarJsonTelaRetratil(JsonDocument &doc)
{
  doc["telaRetratil"]["UP"] = false;
  doc["telaRetratil"]["DOWN"] = false;
  doc["telaRetratil"]["PAUSE"] = false;

  if (estadoBotaoDualUp == 1 && estadoBotaoDualSelect == 0 && estadoBotaoDualDown == 0)
  {
    doc["telaRetratil"]["UP"] = true;
    doc["telaRetratil"]["DOWN"] = false;
    doc["telaRetratil"]["PAUSE"] = false;
  }

  else if (estadoBotaoDualDown == 1 && estadoBotaoDualSelect == 0 && estadoBotaoDualUp == 0)
  {
    doc["telaRetratil"]["UP"] = false;
    doc["telaRetratil"]["DOWN"] = true;
    doc["telaRetratil"]["PAUSE"] = false;
  }

  else if (estadoBotaoDualSelect == 1 && estadoBotaoDualUp == 0 && estadoBotaoDualDown == 0)
  {
    doc["telaRetratil"]["UP"] = false;
    doc["telaRetratil"]["DOWN"] = false;
    doc["telaRetratil"]["PAUSE"] = true;
  }

  else if (estadoBotaoDualUp == 1 && estadoBotaoDualSelect == 1 && estadoBotaoDualDown == 1)
  {
    doc["telaRetratil"]["UP"] = false;
    doc["telaRetratil"]["DOWN"] = false;
    doc["telaRetratil"]["PAUSE"] = false;
  }

  else if (estadoBotaoDualUp == 1 && estadoBotaoDualSelect == 1)
  {
    doc["telaRetratil"]["UP"] = false;
    doc["telaRetratil"]["DOWN"] = false;
    doc["telaRetratil"]["PAUSE"] = true;
  }

  else if (estadoBotaoDualDown == 1 && estadoBotaoDualSelect == 1)
  {
    doc["telaRetratil"]["UP"] = false;
    doc["telaRetratil"]["DOWN"] = false;
    doc["telaRetratil"]["PAUSE"] = true;
  }

  else if (estadoBotaoDualUp == 1 && estadoBotaoDualDown == 1 && estadoBotaoDualSelect == 0)
  {
    doc["telaRetratil"]["UP"] = false;
    doc["telaRetratil"]["DOWN"] = false;
    doc["telaRetratil"]["PAUSE"] = true;
  }
  else
  {
    doc["telaRetratil"]["UP"] = false;
    doc["telaRetratil"]["DOWN"] = false;
    doc["telaRetratil"]["PAUSE"] = false;
  }

  doc["telaRetratil"]["tela"] = (estadoBotaoDualScreen == 1) ? 1 : 0;

  doc["telaRetratil"]["timestamp"] = fusoLocal.now();
}

void montarJsonArCondicionado(JsonDocument &doc)
{
  if (estadoBotaoArId1 == 1)
  {
    doc["ar-condicionado"]["id_ar"] = 1;
    doc["ar-condicionado"]["esp"] = 1;
  }

  if (estadoBotaoArId2 == 1)
  {
    doc["ar-condicionado"]["id_ar"] = 2;
    doc["ar-condicionado"]["esp"] = 1;
  }

  if (estadoBotaoArId3 == 1)
  {
    doc["ar-condicionado"]["id_ar"] = 3;
    doc["ar-condicionado"]["esp"] = 2;
  }

  if (estadoBotaoArId4 == 1)
  {
    doc["ar-condicionado"]["id_ar"] = 4;
    doc["ar-condicionado"]["esp"] = 2;
  }

  if (estadoBotaoDualPowerAr == 1)
    doc["ar-condicionado"]["estado"] = 1;
  else
    doc["ar-condicionado"]["estado"] = 0;

  // estado

  // Temperatura
  doc["ar-condicionado"]["temperatura"] = contadorTemperatura;

  // Modo
  if (estadoBotaoModoAr <= 3)
    doc["ar-condicionado"]["modo"] = estadoBotaoModoAr;
  // modo 0 = cool
  // modo 1 = dry
  // modo 2 = fan
  // modo 3 = heat

  // Ar-Condicionado - Estado do Vento
  if (estadoBotaoVento <= 4)
    doc["ar-condicionado"]["vento"] = estadoBotaoVento;
  // velocidade do vento 0 = auto
  // velocidade do vento 1 = quiet
  // velocidade do vento 2 = low
  // velocidade do vento 3 = med
  // velocidade do vento 4 = high

  doc["ar-condicionado"]["timestamp"] = fusoLocal.now();
}
void montarJsonTelevisao(JsonDocument &doc)
{
  if (estadoComandoTV <= 9)
  {
    doc["televisao"]["comando"] = estadoComandoTV;
  }

  doc["televisao"]["timestamp"] = fusoLocal.now();
}

void publicarJsonLampada()
{
  JsonDocument doc;
  montarJsonLampada(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_LAMPADA, mensagem.c_str());

  debugInfo("Interruptor 1: " + String(estadoBotaoDualBt1));
  debugInfo("Interruptor 2: " + String(estadoBotaoDualBt0));
  debugInfo("Interruptor 3: " + String(estadoBotaoDualBt3));
  debugInfo("Interruptor 4: " + String(estadoBotaoDualBt2));
}

void publicarJsonProjetor()
{
  JsonDocument doc;
  montarJsonProjetor(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_PROJETOR, mensagem.c_str());

  debugInfo("Estado Power: " + String(estadoBotaoDualPower));
  debugInfo("Estado Congelamento: " + String(estadoBotaoDualFreeze));
}
void publicarJsonProjetor10()
{
  JsonDocument doc;
  montarJsonProjetor10(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_PROJETOR10, mensagem.c_str());

  debugInfo("Estado Power: " + String(estadoBotaoDualPower10));
  debugInfo("Estado Congelamento: " + String(estadoBotaoDualFreeze10));
}

void publicarJsonTelaRetratil()
{
  JsonDocument doc;
  montarJsonTelaRetratil(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_TELA_RETRATIL, mensagem.c_str());

  debugInfo("Botão Up: " + String(estadoBotaoDualUp));
  debugInfo("Botão Down: " + String(estadoBotaoDualDown));
  debugInfo("Botão Select: " + String(estadoBotaoDualSelect));
}
void publicarJsonArCondicionado()
{
  JsonDocument doc;
  montarJsonArCondicionado(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_AR_CONDICIONADO, mensagem.c_str());
}
void publicarJsonTV()
{
  JsonDocument doc;
  montarJsonTelevisao(doc);

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_TELEVISAO, mensagem.c_str());

  debugInfo("Comando TV: " + String(estadoComandoTV));
}

// TODO: JSON AR, TV E SENSOR

//======================================
// ATUALIZA BOTÕES DA PÁGINA ATIVA
//======================================

void sincronizarPaginaAtual()
{
  // Lâmpada
  if (paginaAtual == 1)
  {
    // TODO: MELHORAR O NOME DAS VARIÁVEIS
    botaoDualBt0.setValue(estadoBotaoDualBt0);
    botaoDualBt1.setValue(estadoBotaoDualBt1);
    botaoDualBt2.setValue(estadoBotaoDualBt2);
    botaoDualBt3.setValue(estadoBotaoDualBt3);
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
  {
    botaoDualUp.setValue(estadoBotaoDualUp);
    botaoDualDown.setValue(estadoBotaoDualDown);
    botaoDualSelect.setValue(estadoBotaoDualSelect);
    botaoDualScreen.setValue(estadoBotaoDualScreen);
  }

  // Ar-condicionado
  else if (paginaAtual == 4)
  {
    botaoDualPowerAr.setValue(estadoBotaoDualPowerAr);
    botaoArId1.setValue(estadoBotaoArId1);
    botaoArId2.setValue(estadoBotaoArId2);
    botaoArId3.setValue(estadoBotaoArId3);
    botaoArId4.setValue(estadoBotaoArId4);
  }

  // Televisão
  else if (paginaAtual == 5)
    botaoDualPowerTv.setValue(estadoBotaoDualPowerTv);
  // Sensor
}

void atualizarTextoArCondicionado()
{
  char temperatura[10];
  snprintf(temperatura, sizeof(temperatura), "%lu", contadorTemperatura);

  textoTemperatura.setText(temperatura);
}

void atualizarTextoSensor()
{
  char temperaturaAmbiente[10];
  char umidadeAmbiente[10];
  char ruidoAmbiente[10];

  if (valorTemperatura != 0)
  {
    snprintf(temperaturaAmbiente, sizeof(temperaturaAmbiente), "%.1f °C", valorTemperatura);
    textoSensorTemperatura.setText(temperaturaAmbiente);
  }

  if (valorUmidade != 0)
  {
    snprintf(umidadeAmbiente, sizeof(umidadeAmbiente), "%.1f %%", valorUmidade);
    textoSensorUmidade.setText(umidadeAmbiente);
  }

  if (valorRuido != 0)
  {
    snprintf(ruidoAmbiente, sizeof(ruidoAmbiente), "%.1f db", valorRuido);
    textoSensorRuido.setText(ruidoAmbiente);
  }
}
void atualizarTextoSensor10()
{
  char temperaturaAmbiente10[10];
  char umidadeAmbiente10[10];
  char ruidoAmbiente10[10];

  if (valorTemperatura10 != 0)
  {
    snprintf(temperaturaAmbiente10, sizeof(temperaturaAmbiente10), "%.1f °C", valorTemperatura10);
    textoSensorTemperatura10.setText(temperaturaAmbiente10);
  }

  if (valorUmidade10 != 0)
  {
    snprintf(umidadeAmbiente10, sizeof(umidadeAmbiente10), "%.1f %%", valorUmidade10);
    textoSensorUmidade10.setText(umidadeAmbiente10);
  }

  if (valorRuido10 != 0)
  {
    snprintf(ruidoAmbiente10, sizeof(ruidoAmbiente10), "%.1f db", valorRuido10);
    textoSensorRuido10.setText(ruidoAmbiente10);
  }
}