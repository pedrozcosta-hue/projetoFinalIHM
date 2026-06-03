#include "NextionConfig.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "IniciarNextion.h"
#include "WiFiManager.h"

#include <ArduinoJson.h>

// Tópico de publicação — definido aqui, main.cpp usa o de recebimento
const char TOPICO_LAMPADA[] = "senai134/equipe/boo/lampada/estado";
const char TOPICO_PROJETOR[] = "senai134/equipe/boo/projetor/estado";
const char TOPICO_TELA_RETRATIL[] = "senai134/equipe/boo/telaretratil/estado";
const char TOPICO_AR_CONDICIONADO[] = "senai134/equipe/boo/arcondicionado/estado";
const char TOPICO_TELEVISAO[] = "senai134/equipe/boo/televisao/estado";

void montarJsonLampada(JsonDocument &doc)
{
  // TODO: TRATAR DEBUGINFO, REFATORAR OS JSONS
  if (paginaAtual == 1)
  {
    doc["lampadaSala09"]["interruptor2"] = (estadoBotaoDualBt0 == 1) ? 1 : 0;
    doc["lampadaSala09"]["interruptor1"] = (estadoBotaoDualBt1 == 1) ? 1 : 0;
    doc["lampadaSala10"]["interruptor4"] = (estadoBotaoDualBt2 == 1) ? 1 : 0;
    doc["lampadaSala10"]["interruptor3"] = (estadoBotaoDualBt3 == 1) ? 1 : 0;
  }

  else
   debugErro("Json não enviado, pois paginaAtual é diferente de 1");
}

void montarJsonProjetor(JsonDocument &doc)
{
  if (paginaAtual == 2)
  {
    doc["projetor"]["estadoPower"] = (estadoBotaoDualPower == 1) ? 1 : 0;
    doc["projetor"]["estadoCongelamento"] = (estadoBotaoDualFreeze == 1) ? 1 : 0;
  }

  else
   debugErro("Json não enviado, pois paginaAtual é diferente de 2");
}


void montarJsonTelaRetratil(JsonDocument &doc)
{
  if (paginaAtual == 3)
  {
    // Tela Retrátil
    doc["tela"]["Up"] = (estadoBotaoDualUp == 1) ? 1 : 0;
    doc["tela"]["Down"] = (estadoBotaoDualDown == 1) ? 1 : 0;
    doc["tela"]["Select"] = (estadoBotaoDualSelect == 1) ? 1 : 0;
  }
  
  else
  debugErro("Json não enviado, pois paginaAtual é diferente de 1");
}

void montarJsonArCondicionado(JsonDocument &doc)
{
  if (paginaAtual == 4)
  {
    //Temperatura
    doc["arCondicionado"]["temperatura"] = valorSliderTemperatura;
  
    //Power
    doc["arCondicionado"]["power"] = (estadoBotaoDualPowerAr == 1) ? 1 : 0;
  
    //Modo
    if (estadoBotaoModoAr == 0) // modo 0 = cool
      doc["arCondicionado"]["modo"] = estadoBotaoModoAr;
    else if (estadoBotaoModoAr == 1) // modo 1 = dry
      doc["arCondicionado"]["modo"] = estadoBotaoModoAr;
    else if (estadoBotaoModoAr == 2) // modo 2 = fan
      doc["arCondicionado"]["modo"] = estadoBotaoModoAr;
    else if (estadoBotaoModoAr == 3) // modo 3 = heat
      doc["arCondicionado"]["modo"] = estadoBotaoModoAr;
  
    //* Ar-Condicionado - Estado do Vento
    if (estadoBotaoVento == 0) // velocidade do vento 0 = auto
      doc["arCondicionado"]["vento"] = estadoBotaoVento;
    else if (estadoBotaoVento == 1) // velocidade do vento 1 = quiet
      doc["arCondicionado"]["vento"] = estadoBotaoVento;
    else if (estadoBotaoVento == 2) // velocidade do vento 2 = low
      doc["arCondicionado"]["vento"] = estadoBotaoVento;
    else if (estadoBotaoVento == 3) // velocidade do vento 3 = med
      doc["arCondicionado"]["vento"] = estadoBotaoVento;
    else if (estadoBotaoVento == 4) // velocidade do vento 4 = high
    doc["arCondicionado"]["vento"] = estadoBotaoVento;
  }
  
  else
  debugErro("Json não enviado, pois paginaAtual é diferente de 1");
}
/*void montarJsonTelevisao(JsonDocument &doc, int comando)
{
  if (paginaAtual == 5)
  {
    // TODO: JSON DA TV
    //  doc["televisao"]["comando"] = comando;

    
    if(comando == 1)//Botao                                      uint32_t comando = 0;
      doc["televisao"]["comando"] = comando 
    else if(comando == 2)//Botao Volume Up
      doc["televisao"]["comando"] = comando
    else if(comando == 3)//Botao Volume Down
      doc["televisao"]["comando"] = comando
    
    
   
  }

  else
   debugErro("Json não enviado, pois paginaAtual é diferente de 1");
}*/

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
void publicarJsonTV(int comando)
{
  JsonDocument doc;
  doc["televisao"]["comando"] = comando;

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_TELEVISAO, mensagem.c_str());
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
  }

  // Ar-condicionado
  else if (paginaAtual == 4)
  {
    botaoDualPowerAr.setValue(estadoBotaoDualPowerAr);
    sliderTemperatura.setValue(valorSliderTemperatura);
  }

  // TV
  else if (paginaAtual == 5)
  {
    botaoDualPowerTv.setValue(estadoBotaoDualPowerTv);
  }

  // Sensor
  else if (paginaAtual == 6)
  {
    // TODO: COMPONENTES PAGINA 6
  }
}
