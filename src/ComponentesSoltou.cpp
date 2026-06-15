#include <Nextion.h>

#include "ComponentesSoltou.h"
#include "IniciarNextion.h"
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
    atualizarTextoTemperaturaArCondicionado();
    atualizarTextoModoAr();
    atualizarTextoVento();
    debugInfo("b3 solto - Página 4 (Ar Condicionado)");
}
void botaoB4Soltou()
{
    sendCommand("page page5");
    paginaAtual = 5;
    debugInfo("b4 solto - Página 5 (TV)");
}
void botaoB5Soltou()
{
    sendCommand("page page6");
    paginaAtual = 6;
    atualizarTextoSensor();
    atualizarTextoSensor10();
    debugInfo("b5 solto - Página 6 (Sensor)");
}

// LÂMPADA
// TODO: melhorar nome dos botões da lâmpada
void botaoDualBt0Soltou()
{
    botaoDualBt0.getValue(&estadoBotaoDualBt0);
    sincronizarPaginaAtual();
    publicarJsonLampada();
    debugInfo("Bt0 solto. Estado = " + String(estadoBotaoDualBt0));
}
void botaoDualBt1Soltou()
{
    botaoDualBt1.getValue(&estadoBotaoDualBt1);
    sincronizarPaginaAtual();
    publicarJsonLampada();
    debugInfo("Bt1 solto. Estado = " + String(estadoBotaoDualBt1));
}
void botaoDualBt2Soltou()
{
    botaoDualBt2.getValue(&estadoBotaoDualBt2);
    sincronizarPaginaAtual();
    publicarJsonLampada();
    debugInfo("Bt2 solto. Estado = " + String(estadoBotaoDualBt2));
}
void botaoDualBt3Soltou()
{
    botaoDualBt3.getValue(&estadoBotaoDualBt3);
    sincronizarPaginaAtual();
    publicarJsonLampada();
    debugInfo("Bt3 solto. Estado = " + String(estadoBotaoDualBt3));
}
void botaoBackLampadaSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("B0 Back - Página 0 (Menu)");
}

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
    publicarJsonProjetor();
    debugInfo("Power solto. Estado = " + String(estadoBotaoDualPower));
}
void botaoDualFreezeSoltou()
{
    botaoDualFreeze.getValue(&estadoBotaoDualFreeze);
    sincronizarPaginaAtual();
    publicarJsonProjetor();
    debugInfo("Freeze solto. Estado = " + String(estadoBotaoDualFreeze));
}

void botaoDualPower10Soltou()
{
    botaoDualPower10.getValue(&estadoBotaoDualPower10);
    sincronizarPaginaAtual();
    publicarJsonProjetor10();
    debugInfo("Power 10 solto. Estado = " + String(estadoBotaoDualPower10));
}

void botaoDualFreeze10Soltou()
{
    botaoDualFreeze10.getValue(&estadoBotaoDualFreeze10);
    sincronizarPaginaAtual();
    publicarJsonProjetor10();
    debugInfo("Freeze 10 solto. Estado = " + String(estadoBotaoDualFreeze10));
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
    estadoComandoTela = 0;
    publicarJsonTelaRetratil();
    debugInfo("Up solto. Estado = " + String(estadoComandoTela));
}
void botaoDualDownSoltou()
{
    estadoComandoTela = 1;
    publicarJsonTelaRetratil();
    debugInfo("Down solto. Estado = " + String(estadoComandoTela));
}
void botaoDualSelectSoltou()
{
    estadoComandoTela = 2;
    publicarJsonTelaRetratil();
    debugInfo("Select solto. Estado = " + String(estadoComandoTela));
}

void botaoDualScreenSoltou()
{
    botaoDualScreen.getValue(&estadoBotaoDualScreen);
    sincronizarPaginaAtual();
    publicarJsonTelaRetratil();
    debugInfo("Screen solto. Estado = " + String(estadoBotaoDualScreen));
}
////////////////////////////////

// AR CONDICIONADO
void botaoBackArSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("B0 Back - Página 0 (Menu)");
}
void botaoOnArSoltou()
{
    estadoBotaoOnOffAr = 1;
    publicarJsonArCondicionado();
    debugInfo("On solto. Estado = " + String(estadoBotaoOnOffAr));
}
void botaoOffArSoltou()
{
    estadoBotaoOnOffAr = 0;
    publicarJsonArCondicionado();
    debugInfo("Off solto. Estado = " + String(estadoBotaoOnOffAr));
}
void botaoArId1Soltou()
{
    botaoArId1.getValue(&estadoBotaoArId1);

    sincronizarPaginaAtual();
    publicarJsonArCondicionado();
    debugInfo("ArId1 solto. Estado = " + String(estadoBotaoArId1));
}
void botaoArId2Soltou()
{
    botaoArId2.getValue(&estadoBotaoArId2);

    sincronizarPaginaAtual();
    publicarJsonArCondicionado();
    debugInfo("ArId2 solto. Estado = " + String(estadoBotaoArId2));
}
void botaoArId3Soltou()
{
    botaoArId3.getValue(&estadoBotaoArId3);

    sincronizarPaginaAtual();
    publicarJsonArCondicionado();
    debugInfo("ArId3 solto. Estado = " + String(estadoBotaoArId3));
}
void botaoArId4Soltou()
{
    botaoArId4.getValue(&estadoBotaoArId4);

    sincronizarPaginaAtual();
    publicarJsonArCondicionado();
    debugInfo("ArId4 solto. Estado = " + String(estadoBotaoArId4));
}

void botaoModoArSoltou()
{
    estadoBotaoModoAr = (estadoBotaoModoAr + 1) % 4;
    publicarJsonArCondicionado();
    atualizarTextoModoAr();
    debugInfo("Modo solto. Estado = " + String(estadoBotaoModoAr));
}
void botaoVentoArSoltou()
{
    estadoBotaoVento++;
    if (estadoBotaoVento > 4)
    {
        estadoBotaoVento = 0;
    }
    publicarJsonArCondicionado();
    atualizarTextoVento();
    debugInfo("Vento solto. Estado = " + String(estadoBotaoVento));
}
void botaoTemperaturaUpSoltou()
{
    contadorTemperatura++;

    if (contadorTemperatura > 30)
    {
        contadorTemperatura = 30;
    }

    publicarJsonArCondicionado();
    atualizarTextoTemperaturaArCondicionado();
}

void botaoTemperaturaDownSoltou()
{
    contadorTemperatura--;

    if (contadorTemperatura < 18)
    {
        contadorTemperatura = 18;
    }

    publicarJsonArCondicionado();
    atualizarTextoTemperaturaArCondicionado();
}
// TODO: ESP
//////////////////////////////////

// TODO: FAZER A LÓGICA PARA OS BOTÕES DA TV E DO SENSOR
//  TV
void botaoBackTvSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("B0 Back - Página 0 (Menu)");
}
void botaoDualPowerTvSoltou()
{
    botaoDualPowerTv.getValue(&estadoComandoTV);
    sincronizarPaginaAtual();
    publicarJsonTV();
}
void botaoVolumeUpTvSoltou()
{
    estadoComandoTV = 2;
    publicarJsonTV();
}
void botaoVolumeDownTvSoltou()
{
    estadoComandoTV = 3;
    publicarJsonTV();
}
void botaoSetaDireitaTvSoltou()
{
    estadoComandoTV = 4;
    publicarJsonTV();
}
void botaoSetaEsquerdaTvSoltou()
{
    estadoComandoTV = 5;
    publicarJsonTV();
}
void botaoSetaCimaTvSoltou()
{
    estadoComandoTV = 6;
    publicarJsonTV();
}
void botaoSetaBaixoTvSoltou()
{
    estadoComandoTV = 7;
    publicarJsonTV();
}
void botaoSelectTvSoltou()
{
    estadoComandoTV = 8;
    publicarJsonTV();
}

void botaoReturnTvSoltou()
{
    estadoComandoTV = 9;
    publicarJsonTV();
}
// SENSOR
void botaoBackSensorSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("B0 Back - Página 0 (Menu)");
}
