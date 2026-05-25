
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"

const int PINO_LAMPADA = 15;
const int PINO_LED_RGB = 48;
const int QUANTIDADE_LEDS = 1;

const char TOPICO_COMANDO[] =  "senai134/freire/esp32/comando";

Adafruit_NeoPixel ledRGB(
    QUANTIDADE_LEDS,
    PINO_LED_RGB,
    NEO_GRB + NEO_KHZ800);

void tratarMensagemRecebida(const char *topico, const String &mensagem);
void configurarLedRGB();
void alterarCorLedRGB(int vermelho, int verde, int azul);
void tratarJsonComando(const String &mensagem);

void setup()
{

  pinMode(PINO_LAMPADA, OUTPUT);

  configurarDebug();

  configurarLedRGB();

  conectarWiFi();
  configurarMQTT();
  registrarCallbackMensagem(tratarMensagemRecebida);
  conectarMQTT();
}

void loop()
{
  garantirWiFiConectado();
  garantirMQTTConectado();
  loopMQTT();
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

void configurarLedRGB()
{
  ledRGB.begin();
  ledRGB.setBrightness(80); // TODO: colocar a qtd de brilho para o led de 0 a 255
  ledRGB.clear();
  ledRGB.show(); //* Atualiza o estado do LED

  debugInfo("LED RGB configurado no GPIO " + String(PINO_LED_RGB));
}

void alterarCorLedRGB(int vermelho, int verde, int azul)
{
  vermelho = constrain(vermelho, 0, 255);
  verde = constrain(verde, 0, 255);
  azul = constrain(azul, 0, 255);

  ledRGB.setPixelColor(0, ledRGB.Color(vermelho, verde, azul));
  ledRGB.show();

  debugInfo("Cor aplicada no LED RGB");
  debugInfo("R: " + String(vermelho));
  debugInfo("G: " + String(verde));
  debugInfo("B: " + String(azul));
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

  if(doc["led"].is<JsonObject>())
  {
    if(!doc["led"]["r"].is<int>() || !doc["led"]["g"].is<int>() || !doc["led"]["b"].is<int>())
    {
      debugErro("JSON INVÁLIDO. Use led.r, led.g e led.b");
      return;
    }
  
  else
  {
     int vermelho = doc["led"]["r"].as<int>();
     int verde = doc["led"]["g"].as<int>();
     int azul = doc["led"]["b"].as<int>();

     alterarCorLedRGB(vermelho, verde, azul);
  }
  }

  if(doc["lampada"].is<bool>())
  {
    bool Estadolampada = doc["lampada"].as<bool>();
    digitalWrite(PINO_LAMPADA, Estadolampada);

    if(Estadolampada)
    debugInfo("Lâmpada ligada");
    else
    debugInfo("Lâmpada desligada");
  }

}