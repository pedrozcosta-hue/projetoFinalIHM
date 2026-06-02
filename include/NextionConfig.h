#ifndef NEXTIONCONFIG_H
#define NEXTIONCONFIG_H

#include <ArduinoJson.h>

void montarJsonLampada(JsonDocument &doc);
void montarJsonProjetor(JsonDocument &doc);
void montarJsonTelaRetratil(JsonDocument &doc);
void montarJsonArCondicionado(JsonDocument &doc);
void montarJsonTelevisao(JsonDocument &doc);

void publicarJsonLampada();
void publicarJsonProjetor();
void publicarJsonTelaRetratil();
void publicarJsonArCondicionado();
void publicarJsonTV();
void sincronizarPaginaAtual();

#endif