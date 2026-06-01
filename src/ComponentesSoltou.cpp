#include "ComponentesSoltou.h"
#include "IniciarNextion.h"
#include <Nextion.h>
#include "DebugManager.h"
#include "NextionConfig.h"

// MENU
void botaoB0Soltou()
{
    sendCommand("page page1");
    paginaAtual = 1;
    debugInfo("b0 solto - Página 1 (Lâmpada)");
}
void botaoB1Soltou()
{
    sendCommand("page page2");
    paginaAtual = 2;
    debugInfo("b1 solto - Página 2 (Projetor)");
}
void botaoB2Soltou()
{
    sendCommand("page page3");
    paginaAtual = 3;
    debugInfo("b2 solto - Página 3 (Tela Retrátil)");
}
void botaoB3Soltou()
{
    sendCommand("page page4");
    paginaAtual = 4;
    debugInfo("b3 solto - Página 4 (Ar Condicionado)");
}
void botaoB4Soltou()
{
    sendCommand("page page5");
    paginaAtual = 5;
    debugInfo("b4 solto - Página 5 (Sistema de Som)");
}
void botaoB5Soltou()
{
    sendCommand("page page6");
    paginaAtual = 6;
    debugInfo("b5 solto - Página 6 (Iluminação)");
}
//////////////////////

// LÂMPADA
void botaoDualBt0Soltou()
{
    botaoDualBt0.getValue(&estadoBotaoDualBt0);
    sincronizarPaginaAtual();
    publicarEstado();
    debugInfo("Bt0 solto. Estado = " + String(estadoBotaoDualBt0));
}
void botaoDualBt1Soltou()
{
    botaoDualBt1.getValue(&estadoBotaoDualBt1);
    sincronizarPaginaAtual();
    publicarEstado();
    debugInfo("Bt1 solto. Estado = " + String(estadoBotaoDualBt1));
}
void botaoDualBt2Soltou()
{
    botaoDualBt2.getValue(&estadoBotaoDualBt2);
    sincronizarPaginaAtual();
    publicarEstado();
    debugInfo("Bt2 solto. Estado = " + String(estadoBotaoDualBt2));
}
void botaoDualBt3Soltou()
{
    botaoDualBt3.getValue(&estadoBotaoDualBt3);
    sincronizarPaginaAtual();
    publicarEstado();
    debugInfo("Bt3 solto. Estado = " + String(estadoBotaoDualBt3));
}
void botaoBackLampadaSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("B0 Back - Página 0 (Menu)");
}
////////////////////////////

// PROJETOR
void botaoBackProjetorSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("B0 Back - Página 0 (Menu)");
}
void botaoDualPowerSoltou()
{
    botaoDualPower.getValue(&estadoBotaoDualPower);
    sincronizarPaginaAtual();
    publicarEstado();
    debugInfo("Power solto. Estado = " + String(estadoBotaoDualPower));
}
void botaoDualFreezeSoltou()
{
    botaoDualFreeze.getValue(&estadoBotaoDualFreeze);
    sincronizarPaginaAtual();
    publicarEstado();
    debugInfo("Freeze solto. Estado = " + String(estadoBotaoDualFreeze));
}
/////////////////////////////////

// TELA RETRÁTIL
void botaoBackTelaSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("B0 Back - Página 0 (Menu)");
}
void botaoDualUpSoltou()
{
    botaoDualUp.getValue(&estadoBotaoDualUp);
    sincronizarPaginaAtual();
    publicarEstado();
    debugInfo("Up solto. Estado = " + String(estadoBotaoDualUp));
}
void botaoDualDownSoltou()
{
    botaoDualDown.getValue(&estadoBotaoDualDown);
    sincronizarPaginaAtual();
    publicarEstado();
    debugInfo("Down solto. Estado = " + String(estadoBotaoDualDown));
}
void botaoDualSelectSoltou()
{
    botaoDualSelect.getValue(&estadoBotaoDualSelect);
    sincronizarPaginaAtual();
    publicarEstado();
    debugInfo("Select solto. Estado = " + String(estadoBotaoDualSelect));
}
////////////////////////////////

// AR CONDICIONADO
void botaoBackArSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("B0 Back - Página 0 (Menu)");
}
void botaoPowerArSoltou()
{
    botaoPowerAr.getValue(&estadoBotaoPowerAr);
    sincronizarPaginaAtual();
    publicarEstado();
    debugInfo("Power solto. Estado = " + String(estadoBotaoPowerAr));
}