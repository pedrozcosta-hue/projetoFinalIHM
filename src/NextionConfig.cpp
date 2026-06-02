#include "NextionConfig.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "IniciarNextion.h"
#include <ArduinoJson.h>

const char TOPICO_COMANDO[] = "senai134/freire/esp32/comando";

void publicarEstado()
{
  //TODO: TRATAR DEBUGINFO, REFATORAR OS JSONS 
  JsonDocument doc;
  if (paginaAtual == 1)
  {
    // Lâmpada
    doc["lampadaSala09"]["lampadaFrente"] = (estadoBotaoDualBt0 == 1) ? 1 : 0;
    doc["lampadaSala09"]["lampadaTras"] = (estadoBotaoDualBt1 == 1) ? 1 : 0;
    doc["lampadaSala10"]["lampadaFrente"] = (estadoBotaoDualBt2 == 1) ? 1 : 0;
    doc["lampadaSala10"]["lampadaTras"] = (estadoBotaoDualBt3 == 1) ? 1 : 0;
  }
  if (paginaAtual == 2)
  {
    // Projetor
    doc["projetor"]["estadoPower"] = (estadoBotaoDualPower == 1) ? 1 : 0;
    doc["projetor"]["estadoCongelamento"] = (estadoBotaoDualFreeze == 1) ? 1 : 0;
  }
  if (paginaAtual == 3)
  {
    // Tela Retrátil
    doc["tela"]["Up"] = (estadoBotaoDualUp == 1) ? 1 : 0;
    doc["tela"]["Down"] = (estadoBotaoDualDown == 1) ? 1 : 0;
    doc["tela"]["Select"] = (estadoBotaoDualSelect == 1) ? 1 : 0;
  }

  if (paginaAtual == 4)
  {
    //* Ar-condicionado - Temperatura
    doc["arCondicionado"]["temperatura"] = valorSliderTemperatura;

    //* Ar-condicionado - Power
    doc["arCondicionado"]["power"] = (estadoBotaoDualPowerAr == 1) ? 1 : 0;

    //* Ar-condicionado - Modo
    if (estadoBotaoModoAr == 0) // modo 0 = cool
    {
      doc["arCondicionado"]["modo"] = estadoBotaoModoAr;
    }

    else if (estadoBotaoModoAr == 1) // modo 1 = dry
    {
      doc["arCondicionado"]["modo"] = estadoBotaoModoAr;
    }

    else if (estadoBotaoModoAr == 2) // modo 2 = fan
    {
      doc["arCondicionado"]["modo"] = estadoBotaoModoAr;
    }

    else if (estadoBotaoModoAr == 3) // modo 3 = heat
    {
      doc["arCondicionado"]["modo"] = estadoBotaoModoAr;
    }

    //* Ar-Condicionado - Estado do Vento
    if (estadoBotaoVento == 0) // velocidade do vento 0 = auto
    {
      doc["arCondicionado"]["vento"] = estadoBotaoVento;
    }

    else if (estadoBotaoVento == 1) // velocidade do vento 1 = quiet
    {
      doc["arCondicionado"]["vento"] = estadoBotaoVento;
    }

    else if (estadoBotaoVento == 2) // velocidade do vento 2 = low
    {
      doc["arCondicionado"]["vento"] = estadoBotaoVento;
    }
    else if (estadoBotaoVento == 3) // velocidade do vento 3 = med
    {
      doc["arCondicionado"]["vento"] = estadoBotaoVento;
    }
    else if (estadoBotaoVento == 4) // velocidade do vento 4 = high
    {
      doc["arCondicionado"]["vento"] = estadoBotaoVento;
    }
  }

  if (paginaAtual == 5)
  {
    //TODO: JSON DA TV
    // doc["televisao"]["comando"] =
  }

  if (paginaAtual == 6)
  {
    // Sensor de análise
    doc["analise"]["timeStamp"] = // TODO: TIMESTAMP
    doc["analise"]["temperatura"] = valorTemperatura;
    doc["analise"]["umidade"] = valorUmidade;
    doc["analise"]["ruido"] = valorRuido;
    doc["analise"]["comandoAr"] = comandoAr;
    doc["analise"]["alertaSom"] = alertaSom;
    doc["analise"]["eco"] = eco;
  }

  String mensagem;
  serializeJson(doc, mensagem);
  publicarMensagem(TOPICO_COMANDO, mensagem.c_str());
}

//======================================
// ATUALIZA BOTÕES DA PÁGINA ATIVA
//======================================

void sincronizarPaginaAtual()
{
  // Lâmpada
  if (paginaAtual == 1)
  {
    //TODO: MELHORAR O NOME DAS VARIÁVEIS
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