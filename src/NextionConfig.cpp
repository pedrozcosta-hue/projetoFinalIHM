#include "NextionConfig.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "ComponentesSoltou.h"
#include "IniciarNextion.h"
#include <ArduinoJson.h>

//*======================================
//* TÓPICO MQTT (usado ao publicar)
//*======================================

static const char TOPICO_COMANDO[] = "senai134/freire/esp32/comando";

// TODO TOPICOS PARA CADA COMPONENTE

//*======================================
//* PUBLICAÇÃO JSON — estado completo
//*======================================

static void publicarEstado()
{
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
    debugInfo("");
  }
  if (paginaAtual == 3)
  {
    // Tela Retrátil
    doc["tela"]["Up"] = (estadoBotaoDualUp == 1) ? 1 : 0;
    doc["tela"]["Down"] = (estadoBotaoDualDown == 1) ? 1 : 0;
    doc["tela"]["Select"] = (estadoBotaoDualSelect == 1) ? 1 : 0;
    debugInfo("");
  }

  if (paginaAtual == 4)
  {
    // Ar-condicionado
    if (contadorBotao == 0)//modo 0 = cool
    {
      doc ["arCondicionado"]["modo"] = 0;
    }

    else if (contadorBotao == 1)//modo 1 = dry
    {
      doc ["arCondicionado"]["modo"] = 1;
    }

    else if (contadorBotao == 2)//modo 2 = fan
    {
      doc ["arCondicionado"]["modo"] = 2;
    }

    else if (contadorBotao == 3)//modo 3 = heat
    {
      doc ["arCondicionado"]["modo"] = 3;
    }
  }

  if (paginaAtual == 5)
  {
    // TV
    doc["televisao"]["comando"] = botaoDosComandosTv;
  }

  if (paginaAtual == 6)
  {
    // Sensor de análise
    doc["analise"]["timeStamp"] =
    doc["analise"]["temperatura"] = valorTemperatura;
    doc["analise"]["umidade"] = valorUmidade;
    doc["analise"]["ruido"] = valorRuido;
    doc["analise"]["comandoAr"] = comandoAr;
    doc["analise"]["alertaSom"] = alertaSom;
    doc["analise"]["eco"] = eco;
  }

  // TODO: JSON AR, TV E SENSOR

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
    // TODO: COMPONENTEDPAGINA 4
  }
  else
  {
    // TODO: COMPONENTED PAGINA 5
  }
}