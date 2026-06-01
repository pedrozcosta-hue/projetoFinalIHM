#ifndef NEXTIONCONFIG_H
#define NEXTIONCONFIG_H

#include <Arduino.h>
#include <Nextion.h>

//*======================================
//* CONFIGURAÇÃO DE PINOS E BAUDRATE
//*======================================
const uint32_t BAUD_NEXTION   = 9600;
const int8_t   PINO_RX_NEXTION = 18;
const int8_t   PINO_TX_NEXTION = 17;

//*======================================
//* FUNÇÕES PÚBLICAS
//*======================================

// Inicializa o Nextion (serial + eventos)
void configurarNextion();

// Zera variáveis e inicializa cada página
void configurarTelaInicial();

// Registra callbacks e chama nexListen para cada componente
void configurarEventosNextion();

void publicarEstado();
void sincronizarPaginaAtual();

#endif