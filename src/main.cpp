#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <Nextion.h>

#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"

const int pinLed = 39;

const char TOPICO_COMANDO[] =  "senai134/freire/esp32/comando";

const uint32_t BAUD_NEXTION = 9600;
const int8_t PINO_RX_NEXTION = 18;
const int8_t PINO_TX_NEXTION = 17;

//barra de progresso
//*trocar o nome da barra, para nao confundir com funcao matematica

//componentes que recebem toque
NexButton botaoB0(0, 1, "b0");

    
//NexSlider sliderH0(0, 4, "h0");
NexDSButton botaoDualBt0(1, 3, "bt0");

//Textos usados para mostrar o estado dos componentes
//NexText textoT1(0, 6, "t1");
//NexText textoT2(0, 7, "t2");  //TODO: ALTERAR A PAGE, ID,0 PINOS DO IHM, E NOME
//NexText textoT3(0, 8, "t3");
//NexText textoT4(0, 0, "t4");

//*======================================
//* VARIÁVEIS DE CONTROLE DA PLICAÇÃO
//*======================================

uint32_t estadoBotaoDual = 0;

char texto[50];

void tratarMensagemRecebida(const char *topico, const String &mensagem);
void configurarLedRGB();
void alterarCorLedRGB(int vermelho, int verde, int azul);
void tratarJsonComando(const String &mensagem);

void configurarNextion();
void configurarTelaInicial();
void configurarEventosNextion();

void botaoB0Soltou();

void sliderH0Soltou();
void botaoDualBt0Pressionado();

void atualizarTextoBarra();
void atualizarTextoBotao();
void atualizarTextoSlider();
void atualizarTextoBotaoDual();

void atualizarEstadoLampada();

void setup()
{
 
  pinMode(pinLed, OUTPUT);
 digitalWrite(pinLed, LOW);
  configurarDebug();

  conectarWiFi();
  configurarMQTT();
  registrarCallbackMensagem(tratarMensagemRecebida);
  conectarMQTT();

  configurarNextion();
  configurarTelaInicial();
  configurarEventosNextion();
}

void loop()
{
  garantirWiFiConectado();
  garantirMQTTConectado();
  loopMQTT();

  nexLoop();
}

void tratarMensagemRecebida(const char *topico, const String &mensagem)
{
  debugInfo("===============================");
  debugInfo("Mensagem recebida na aplicação");
  debugInfo("===============================");
  
  if(topico == nullptr)
  {
    debugErro("Tópico MQTT inválido");
    return;
  }

  debugInfo("Tópico: " + String(topico));
  debugInfo("Mensagem: " + mensagem);

  if(strcmp(topico, TOPICO_COMANDO) == 0)
  {
    tratarJsonComando(mensagem);
    return;
  }
  
  debugErro("Tópico não tratado: " + String(topico));
  

}

void tratarJsonComando(const String &mensagem)
{
  JsonDocument doc;

  DeserializationError erro = deserializeJson(doc, mensagem);

  if(erro)
  {
    debugErro("Erro ao interpretar o JSON");
    debugErro(erro.c_str());
    return;
  }
 
 
}

void configurarNextion()
{
 bool nextionOk = nexInit(BAUD_NEXTION, PINO_RX_NEXTION, PINO_TX_NEXTION);

 if(!nextionOk)
  debugErro("Aviso: o Nextion não confirmou a inicialização");
 else
  debugInfo("Nextion inicializado");
}

void configurarTelaInicial()
{
  //*Garante que o disp;ay esteja na página principal
  sendCommand("page page0");

  delay(500);

  //*define os valores iniciais da aplicação
  
  estadoBotaoDual = 0;

 //*Atualiza os componentes visuais do display
 /*
  barraj0.setValue(valorBarra);
  sliderH0.setValue(valorSlider);
  //botaoDualBt0.setValue(estadoBotaoDual);

  //*Atualiza os textos inicias
  textoT1.setText("j0 = 0%");
  textoT2.setText("b0 aguardando");
  textoT3.setText("h0 = 0");
  textoT4.setText("bt0 = Desligado"); 
  */
}

void configurarEventosNextion()
{
 //*attachpop() executa a função quando o componente é solto.
 //*No Nextion Editor, "use Send Component ID" em Touch Release Event
 
 botaoB0.attachPop(botaoB0Soltou);


 //sliderH0.attachPop(sliderH0Soltou);

 botaoDualBt0.attachPush(botaoDualBt0Pressionado);

 //*limpa a lista interna de componentes monitorados
 nexClearListenList();

 //*Registra quais componentes devem ser ouvidos pelo ESP32
 nexListen(botaoB0);
 

 //nexListen(sliderH0);

 nexListen(botaoDualBt0);

}

//*MENU PRINCIPAL

void botaoB0Soltou()
{
  sendCommand("page page1");
  
  debugInfo("Botao b0 solto");
  debugInfo("Página 1");
}

//*botao liga / desliga lampada

void botaoDualBt0Pressionado()
{
  debugInfo("Botao dual bt0 Pressionado.");

  //* lê o valor atual do Dual State Button
  //* 0 = desligado
  //* 1 = ligado

  botaoDualBt0.getValue(&estadoBotaoDual);

  atualizarEstadoLampada();
  atualizarTextoBotaoDual();
  debugInfo("Estado do bt0 = ");
}

void atualizarEstadoLampada()
{
 if(estadoBotaoDual == 1)
  digitalWrite(pinLed, HIGH);
 else 
  digitalWrite(pinLed, LOW);
}

void atualizarTextoBotaoDual()
{
  if(estadoBotaoDual == 1)
  {
   //textoT4.setText("bt0 = ligado");
   digitalWrite(pinLed, HIGH);
  }
  else
  {
   //textoT4.setText("bt0 = desligado"); 
   digitalWrite(pinLed, LOW);
  }
  
}