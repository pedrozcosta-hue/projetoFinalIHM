#include <Arduino.h>
#include <ArduinoJson.h>
#include <ezTime.h>

#include "WiFiManager.h"
#include "MqttManager.h"
#include "DebugManager.h"
#include "NextionConfig.h"
#include "IniciarNextion.h"
#include "secrets.h"

Timezone fusoLocal;

const char TOPICO_SENSOR09[] = "senai134/shared/projeto/analise09";
const char TOPICO_SENSOR10[] = "senai134/shared/projeto/analise10";

// Protótipos
void tratarMensagemRecebida(const char *topico, const String &mensagem);
void tratarJsonComando(const String &mensagem);
void tratarJsonComandoSala10(const String &mensagem);
void tratarSensor09(JsonDocument &doc);
void tratarSensorSala10(JsonDocument &doc);

void setup()
{
    configurarDebug();

    conectarWiFi();

    waitForSync();
    fusoLocal.setLocation("America/Sao_Paulo");

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
    events();
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

    if (strcmp(topico, TOPICO_SENSOR09) == 0)
    {
        tratarJsonComando(mensagem);
        return;
    }

    else if (strcmp(topico, TOPICO_SENSOR10) == 0)
    {
        tratarJsonComandoSala10(mensagem);
    }
     
    else
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

    tratarSensor09(doc);
    // TODO: reagir aos comandos recebidos via MQTT
}

void tratarJsonComandoSala10(const String &mensagem)
{
    JsonDocument doc;

    DeserializationError erro = deserializeJson(doc, mensagem);

    if (erro)
    {
        debugErro("Erro ao interpretar o JSON");
        debugErro(erro.c_str());
        return;
    }

    tratarSensorSala10(doc);
}

void tratarSensor09(JsonDocument &doc)
{
    if (doc["analise"].is<JsonObject>())

    {
        timestemp = doc["analise"]["timestamp"].as<unsigned long>();
        valorTemperatura = doc["analise"]["temperatura"].as<float>();
        valorUmidade = doc["analise"]["umidade"].as<float>();
        valorRuido = doc["analise"]["ruido"].as<float>();
        comandoAr = doc["analise"]["comandoAr"].as<int>();
        alertaSom = doc["analise"]["alertaSom"].as<int>();
        eco = doc["analise"]["eco"].as<bool>();

        debugInfo("Timestemp: " + String(timestemp));
        debugInfo("Temperatura: " + String(valorTemperatura));
        debugInfo("Umidade: " + String(valorUmidade));
        debugInfo("Ruído: " + String(valorRuido));
        debugInfo("Comando Ar: " + String(comandoAr));
        debugInfo("Alerta Som: " + String(alertaSom));
        debugInfo("Eco: " + String(eco));
    }

    else
    {
        debugErro("A mensagem recebida não esta no formato chave-valor ou o valor não é correspondente ao tipo");
        return;
    }
}

void tratarSensorSala10(JsonDocument &doc)
{
    if (doc["analise"].is<JsonObject>())

    {
        timestemp10= doc["analise"]["timestamp"].as<unsigned long>();
        valorTemperatura10 = doc["analise"]["temperatura"].as<float>();
        valorUmidade10 = doc["analise"]["umidade"].as<float>();
        valorRuido10 = doc["analise"]["ruido"].as<float>();
        comandoAr10 = doc["analise"]["comandoAr"].as<int>();
        alertaSom10 = doc["analise"]["alertaSom"].as<int>();
        eco10 = doc["analise"]["eco"].as<bool>();

        debugInfo("Timestemp: " + String(timestemp10));
        debugInfo("Temperatura: " + String(valorTemperatura10));
        debugInfo("Umidade: " + String(valorUmidade10));
        debugInfo("Ruído: " + String(valorRuido10));
        debugInfo("Comando Ar: " + String(comandoAr10));
        debugInfo("Alerta Som: " + String(alertaSom10));
        debugInfo("Eco: " + String(eco10));
    }

    else
    {
        debugErro("A mensagem recebida não esta no formato chave-valor ou o valor não é correspondente ao tipo");
        return;
    }
}
