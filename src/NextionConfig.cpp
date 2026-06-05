#include "NextionConfig.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "IniciarNextion.h"
#include "WiFiManager.h"

#include <ArduinoJson.h>
#include <Arduino.h>
#include <ezTime.h>

extern Timezone fusoLocal;

// Tópico de publicação — definido aqui, main.cpp usa o de recebimento
const char TOPICO_LAMPADA[] = "senai134/equipe/boo/lampada/estado";
const char TOPICO_PROJETOR[] = "senai134/equipe/boo/projetor/estado";
const char TOPICO_TELA_RETRATIL[] = "senai134/equipe/boo/telaretratil/estado";
const char TOPICO_AR_CONDICIONADO[] = "senai134/equipe/boo/arcondicionado/estado";
const char TOPICO_TELEVISAO[] = "senai134/equipe/boo/televisao/estado";

void montarJsonLampada(JsonDocument &doc)
{
  doc["lampadaSala09"]["interruptor1"] = (estadoBotaoDualBt1 == 1) ? 1 : 0;
  doc["lampadaSala09"]["interruptor2"] = (estadoBotaoDualBt0 == 1) ? 1 : 0;
  doc["lampadaSala10"]["interruptor3"] = (estadoBotaoDualBt3 == 1) ? 1 : 0;
  doc["lampadaSala10"]["interruptor4"] = (estadoBotaoDualBt2 == 1) ? 1 : 0;
  doc["timestamp"] = fusoLocal.now();
}

void montarJsonProjetor(JsonDocument &doc)
{
  doc["projetor"]["estadoPower"] = (estadoBotaoDualPower == 1) ? 1 : 0;
  doc["projetor"]["estadoCongelamento"] = (estadoBotaoDualFreeze == 1) ? 1 : 0;
  doc["timestamp"] = fusoLocal.now();
}

void montarJsonTelaRetratil(JsonDocument &doc)
{
  if(estadoBotaoDualUp == 1)
  {
   doc["telaRetratil"]["UP"] = 1;
   doc["telaRetratil"]["DOWN"] = 0;
   doc["telaRetratil"]["PAUSE"] = 0;
  }  

  if(estadoBotaoDualDown == 1)
  {
    doc["telaRetratil"]["UP"] = 0;
    doc["telaRetratil"]["DOWN"] = 1;
    doc["telaRetratil"]["PAUSE"] = 0;
  }

  if(estadoBotaoDualSelect == 1)
  {
    doc["telaRetratil"]["UP"] = 0;
    doc["telaRetratil"]["DOWN"] = 0;
    doc["telaRetratil"]["PAUSE"] = 1;
  }

  doc["telaRetratil"]["tela"] = (estadoBotaoDualScreen == 1) ? 1 : 0;
  doc["timestamp"] = fusoLocal.now();
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

  // estado
  if (estadoBotaoDualPowerAr == 1)
    doc["ar-condicionado"]["estado"] = 1;
  else
    doc["ar-condicionado"]["estado"] = 0;

  // Temperatura
  if (estadoBotaoDualPowerAr == 1)
    doc["ar-condicionado"]["temperatura"] = contadorTemperatura;

  // Modo
  if (estadoBotaoModoAr == 0) // modo 0 = cool
    doc["ar-condicionado"]["modo"] = estadoBotaoModoAr;
  else if (estadoBotaoModoAr == 1) // modo 1 = dry
    doc["ar-condicionado"]["modo"] = estadoBotaoModoAr;
  else if (estadoBotaoModoAr == 2) // modo 2 = fan
    doc["ar-condicionado"]["modo"] = estadoBotaoModoAr;
  else if (estadoBotaoModoAr == 3) // modo 3 = heat
    doc["ar-condicionado"]["modo"] = estadoBotaoModoAr;

  // Ar-Condicionado - Estado do Vento
  if (estadoBotaoVento == 0) // velocidade do vento 0 = auto
    doc["ar-condicionado"]["vento"] = estadoBotaoVento;
  else if (estadoBotaoVento == 1) // velocidade do vento 1 = quiet
    doc["ar-condicionado"]["vento"] = estadoBotaoVento;
  else if (estadoBotaoVento == 2) // velocidade do vento 2 = low
    doc["ar-condicionado"]["vento"] = estadoBotaoVento;
  else if (estadoBotaoVento == 3) // velocidade do vento 3 = med
    doc["ar-condicionado"]["vento"] = estadoBotaoVento;
  else if (estadoBotaoVento == 4) // velocidade do vento 4 = high
    doc["ar-condicionado"]["vento"] = estadoBotaoVento;

  doc["timestamp"] = fusoLocal.now();
}
void montarJsonTelevisao(JsonDocument &doc)
{
  if (estadoComandoTV == 1)
    doc["televisao"]["comando"] = estadoComandoTV;
  else if (estadoComandoTV == 2)
    doc["televisao"]["comando"] = estadoComandoTV;
  else if (estadoComandoTV == 3)
    doc["televisao"]["comando"] = estadoComandoTV;
  else if (estadoComandoTV == 4)
    doc["televisao"]["comando"] = estadoComandoTV;
  else if (estadoComandoTV == 5)
    doc["televisao"]["comando"] = estadoComandoTV;
  else if (estadoComandoTV == 5)
    doc["televisao"]["comando"] = estadoComandoTV;
  else if (estadoComandoTV == 6)
    doc["televisao"]["comando"] = estadoComandoTV;
  else if (estadoComandoTV == 7)
    doc["televisao"]["comando"] = estadoComandoTV;
  else if (estadoComandoTV == 8)
    doc["televisao"]["comando"] = estadoComandoTV;
  else if (estadoComandoTV == 9)
    doc["televisao"]["comando"] = estadoComandoTV;

  doc["timestamp"] = fusoLocal.now();
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

  debugInfo("Botao power solto. Comando: " + String(estadoBotaoDualBt1));
  debugInfo("Interruptor 2: " + String(estadoBotaoDualBt0));
  debugInfo("Interruptor 3: " + String(estadoBotaoDualBt3));
  debugInfo("Interruptor 4: " + String(estadoBotaoDualBt2));
  debugInfo("Interruptor 1: " + String(estadoBotaoDualBt1));
  debugInfo("Interruptor 2: " + String(estadoBotaoDualBt0));
  debugInfo("Interruptor 3: " + String(estadoBotaoDualBt3));
  debugInfo("Interruptor 4: " + String(estadoBotaoDualBt2));
  debugInfo("Interruptor 4: " + String(estadoBotaoDualBt2));
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

  // Sensor
  else if (paginaAtual == 6)
  {

  }
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

  snprintf(temperaturaAmbiente, sizeof(temperaturaAmbiente), "%lu", valorTemperatura);
  textoSensorTemperatura.setText(temperaturaAmbiente);

  snprintf(umidadeAmbiente, sizeof(umidadeAmbiente), "%lu", valorUmidade);
  textoSensorUmidade.setText(umidadeAmbiente);

  snprintf(ruidoAmbiente, sizeof(ruidoAmbiente), "%lu", valorRuido);
  textoRuido.setText(ruidoAmbiente);
}