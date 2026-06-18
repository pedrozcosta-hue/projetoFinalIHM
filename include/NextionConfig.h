#ifndef NEXTIONCONFIG_H
#define NEXTIONCONFIG_H

#include <ArduinoJson.h>

// LAMPADA
void montarJsonLampadaInterruptor1Sala09(JsonDocument &doc);
void montarJsonLampadaInterruptor2Sala09(JsonDocument &doc);
void montarJsonLampadaInterruptor3Sala10(JsonDocument &doc);
void montarJsonLampadaInterruptor4Sala10(JsonDocument &doc);

void publicarJsonLampadaInterruptor1Sala09();
void publicarJsonLampadaInterruptor2Sala09();
void publicarJsonLampadaInterruptor3Sala10();
void publicarJsonLampadaInterruptor4Sala10();

// PROJETOR
void montarJsonProjetor(JsonDocument &doc);
void montarJsonProjetor10(JsonDocument &doc);

void publicarJsonPower();
void publicarJsonFreeze();
void publicarJsonPower10();
void publicarJsonFreeze10();

// AC
void montarJsonVentoAr(JsonDocument &doc);
void montarJsonModoAr(JsonDocument &doc);
void montarJsonTemperatura(JsonDocument &doc);
void montarJsonOnOffAr(JsonDocument &doc);
void montarJsonArId4(JsonDocument &doc);
void montarJsonArId3(JsonDocument &doc);
void montarJsonArId2(JsonDocument &doc);
void montarJsonArId1(JsonDocument &doc);

void publicarJsonVentoAr();
void publicarJsonModoAr();
void publicarJsonTemperatura();
void publicarJsonOnOffAr();
void publicarJsonArId4();
void publicarJsonArId3();
void publicarJsonArId2();
void publicarJsonArId1();

void atualizarTextoTemperaturaArCondicionado();
void atualizarTextoModoAr();
void atualizarTextoVento();

// TELA-RETRATIL
void montarJsonTelaRetratil(JsonDocument &doc);
void montarJsonTrocarTela(JsonDocument &doc);


void publicarJsonTelaRetratil();
void publicarJsonTrocarTela();

// TV
void montarJsonTelevisao(JsonDocument &doc);

void publicarJsonTV();

// SENSOR
void atualizarTextoSensor();
void atualizarTextoSensor10();

//ATUALIZAR PÁGINA
void sincronizarPaginaAtual();

#endif