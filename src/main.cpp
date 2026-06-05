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

const char TOPICO_SENSOR[] = "senai134/equipe/boo/sensor/status";

// Protótipos
void tratarMensagemRecebida(const char *topico, const String &mensagem);
void tratarJsonComando(const String &mensagem);
void tratarSensor(JsonDocument &doc);


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

    if (strcmp(topico, TOPICO_SENSOR) == 0)
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

    tratarSensor(doc);
    // TODO: reagir aos comandos recebidos via MQTT
}

void tratarSensor(JsonDocument &doc)
{
    if (doc["analise"].is<JsonObject>() &&
        doc["analise"]["timestemp"].is<unsigned long>() &&
        doc["analise"]["temperatura"].is<float>() &&
        doc["analise"]["umidade"].is<float>() &&
        doc["analise"]["ruido"].is<float>() &&
        doc["analise"]["comandoAr"].is<int>() &&
        doc["analise"]["alertaSom"].is<bool>() &&
        doc["analise"]["eco"].is<bool>())

    {   
        timestemp = doc["analise"]["timestemp"].as<unsigned long>();
        valorTemperatura = doc["analise"]["temperatura"].as<float>();
        valorUmidade = doc["analise"]["umidade"].as<float>();
        valorRuido = doc["analise"]["ruido"].as<float>();
        comandoAr = doc["analise"]["comandoAr"].as<int>();
        alertaSom = doc["analise"]["alertaSom"].as<bool>();
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

