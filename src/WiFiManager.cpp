#include <Arduino.h>
#include <WiFi.h>

#include "WiFiManager.h"
#include "secrets.h"
#include "DebugManager.h"

bool wifiEstaConectado()
{
  return WiFi.status() == WL_CONNECTED;
}

void conectarWiFi()
{
  debugInfo("===========================");
  debugInfo("Iniciando conexão WiFi...");
  debugInfo("===========================");

  // Configura o ESP32 como station, ou seja
  // ele vai se conectar a um roteador existente.
  WiFi.mode(WIFI_STA);

  WiFi.begin(WIFI_SSID, WIFI_SENHA);

  debugInfo("conectando");

  int tentativas = 0;
  const int maxtentativa = 30;

  while (WiFi.status() != WL_CONNECTED && tentativas < maxtentativa)
  {
    debugInfoSemLinha(".");
    delay(500);
    tentativas++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED)
  {
    debugInfo("WiFi conectado com sucesso!");
    debugInfoSemLinha("[INFO] Endereço IP: ");
    debugInfoSemLinha(String(WiFi.localIP()));
    debugInfoSemLinha("\n\r");
  }

  else
  {
    debugErro("Falha ao conectar ao WiFi.");
    debugErro("Verifique o SSID, senha e sinal de rede");
  }
}

void garantirWiFiConectado()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    debugErro("WiFi desconectado. Tentando reconectar...");
    conectarWiFi();
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    debugErro("Não foi possível reconectar ao WiFi");
  }
}