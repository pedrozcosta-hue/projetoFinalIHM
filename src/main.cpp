#include <Arduino.h>
#include <ArduinoJson.h>

#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "NextionConfig.h"
#include "IniciarNextion.h"
#include "secrets.h"

const char TOPICO_COMANDO[] = "senai/freire/esp32/comando";

// Protótipos
void tratarMensagemRecebida(const char *topico, const String &mensagem);
void tratarJsonComando(const String &mensagem);

void setup()
{
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

    if (topico == nullptr || strlen(topico) == 0)
    {
        debugErro("Tópico MQTT inválido");
        return;
    }

    debugInfo("Tópico: " + String(topico));
    debugInfo("Mensagem: " + mensagem);

    if (strcmp(topico, TOPICO_COMANDO) == 0)
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

    if (erro)
    {
        debugErro("Erro ao interpretar o JSON");
        debugErro(erro.c_str());
        return;
    }
    // TODO: reagir aos comandos recebidos via MQTT
}
