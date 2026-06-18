#include <Nextion.h>

#include "ComponentesSoltou.h"
#include "IniciarNextion.h"
#include "DebugManager.h"
#include "NextionConfig.h"

// MENU
void botaoLampadaSoltou()
{
    sendCommand("page page1");
    paginaAtual = 1;
    sincronizarPaginaAtual();
    debugInfo("Botão lâmpada soltou - Página 1 (Lâmpada)");
}
void botaoProjetorSoltou()
{
    sendCommand("page page2");
    paginaAtual = 2;
    sincronizarPaginaAtual();
    debugInfo("Botão projetor soltou - Página 2 (Projetor)");
}
void botaoTelaRetratilSoltou()
{
    sendCommand("page page3");
    paginaAtual = 3;
    sincronizarPaginaAtual();
    debugInfo("Botão tela retrátil soltou - Página 3 (Tela Retrátil)");
}
void botaoArCondicionadoSoltou()
{
    sendCommand("page page4");
    paginaAtual = 4;
    sincronizarPaginaAtual();
    atualizarTextoTemperaturaArCondicionado();
    atualizarTextoModoAr();
    atualizarTextoVento();
    debugInfo("Botão ar-condicionado soltou - Página 4 (Ar-Condicionado)");
}
void botaoTvSoltou()
{
    sendCommand("page page5");
    paginaAtual = 5;
    sincronizarPaginaAtual();
    debugInfo("Botão TV soltou - Página 5 (TV)");
}
void botaoSensorSoltou()
{
    sendCommand("page page6");
    paginaAtual = 6;
    atualizarTextoSensor();
    atualizarTextoSensor10();
    debugInfo("Botão sensor soltou - Página 6 (Sensor)");
}

// LÂMPADA
void botaoDualInterruptor2Soltou()
{
    botaoDualInterruptor2.getValue(&estadoBotaoDualInterruptor2);
    sincronizarPaginaAtual();
    publicarJsonLampadaInterruptor2Sala09();
    debugInfo("Interruptor2 soltou. Estado = " + String(estadoBotaoDualInterruptor2));
}
void botaoDualInterruptor1Soltou()
{
    botaoDualInterruptor1.getValue(&estadoBotaoDualInterruptor1);
    sincronizarPaginaAtual();
    publicarJsonLampadaInterruptor1Sala09();
    debugInfo("Interruptor1 soltou. Estado = " + String(estadoBotaoDualInterruptor1));
}
void botaoDualInterruptor4Soltou()
{
    botaoDualInterruptor4.getValue(&estadoBotaoDualInterruptor4);
    sincronizarPaginaAtual();
    publicarJsonLampadaInterruptor4Sala10();
    debugInfo("Interruptor4 soltou. Estado = " + String(estadoBotaoDualInterruptor4));
}
void botaoDualInterruptor3Soltou()
{
    botaoDualInterruptor3.getValue(&estadoBotaoDualInterruptor3);
    sincronizarPaginaAtual();
    publicarJsonLampadaInterruptor3Sala10();
    debugInfo("Interruptor3 soltou. Estado = " + String(estadoBotaoDualInterruptor3));
}
void botaoBackLampadaSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("Botão back soltou - Página 0 (Menu)");
}

// PROJETOR
void botaoBackProjetorSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("Botão back soltou - Página 0 (Menu)");
}
void botaoDualPowerSoltou()
{
    botaoDualPower.getValue(&estadoBotaoDualPower);
    sincronizarPaginaAtual();
    // publicarJsonProjetor();
    publicarJsonPower();
    debugInfo("Botão power soltou. Estado = " + String(estadoBotaoDualPower));
}
void botaoDualFreezeSoltou()
{
    botaoDualFreeze.getValue(&estadoBotaoDualFreeze);
    sincronizarPaginaAtual();
    // publicarJsonProjetor();
    publicarJsonFreeze();
    debugInfo("Botão freeze soltou. Estado = " + String(estadoBotaoDualFreeze));
}
void botaoDualPower10Soltou()
{
    botaoDualPower10.getValue(&estadoBotaoDualPower10);
    sincronizarPaginaAtual();
    // publicarJsonProjetor10();
    publicarJsonPower10();
    debugInfo("Botão power10 soltou. Estado = " + String(estadoBotaoDualPower10));
}
void botaoDualFreeze10Soltou()
{
    botaoDualFreeze10.getValue(&estadoBotaoDualFreeze10);
    sincronizarPaginaAtual();
    // publicarJsonProjetor10();
    publicarJsonFreeze10();
    debugInfo("Botão freeze10 soltou. Estado = " + String(estadoBotaoDualFreeze10));
}

// TELA RETRÁTIL
void botaoBackTelaSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("Botão back soltou - Página 0 (Menu)");
}
void botaoDualUpSoltou()
{
    estadoComandoTela = 0;
    publicarJsonTelaRetratil();
    debugInfo("Botão up soltou. Estado = " + String(estadoComandoTela));
}
void botaoDualDownSoltou()
{
    estadoComandoTela = 1;
    publicarJsonTelaRetratil();
    debugInfo("Botão down soltou. Estado = " + String(estadoComandoTela));
}
void botaoDualStopSoltou()
{
    estadoComandoTela = 2;
    publicarJsonTelaRetratil();
    debugInfo("Botão stop soltou. Estado = " + String(estadoComandoTela));
}
void botaoDualScreenSoltou()
{
    botaoDualScreen.getValue(&estadoBotaoDualScreen);
    sincronizarPaginaAtual();
    publicarJsonTrocarTela();
    debugInfo("Botão screen soltou. Estado = " + String(estadoBotaoDualScreen));
}

// AR CONDICIONADO
void botaoBackArSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("Botão back soltou - Página 0 (Menu)");
}
void botaoOnArSoltou()
{
    estadoBotaoOnOffAr = 1;
    publicarJsonOnOffAr();
    debugInfo("Botão on soltou. Estado = " + String(estadoBotaoOnOffAr));
}
void botaoOffArSoltou()
{
    estadoBotaoOnOffAr = 0;
    publicarJsonOnOffAr();
    debugInfo("Botão off soltou. Estado = " + String(estadoBotaoOnOffAr));
}
void botaoArId1Soltou()
{
    botaoArId1.getValue(&estadoBotaoArId1);

    sincronizarPaginaAtual();
    //publicarJsonArId1();
    debugInfo("Botão arId1 soltou. Estado = " + String(estadoBotaoArId1));
}
void botaoArId2Soltou()
{
    botaoArId2.getValue(&estadoBotaoArId2);

    sincronizarPaginaAtual();
    //publicarJsonArId2();
    debugInfo("Botão arId2 soltou. Estado = " + String(estadoBotaoArId2));
}
void botaoArId3Soltou()
{
    botaoArId3.getValue(&estadoBotaoArId3);

    sincronizarPaginaAtual();
    //publicarJsonArId3();
    debugInfo("Botão arId3 soltou. Estado = " + String(estadoBotaoArId3));
}
void botaoArId4Soltou()
{
    botaoArId4.getValue(&estadoBotaoArId4);

    sincronizarPaginaAtual();
    //publicarJsonArId4();
    debugInfo("Botão arId4 soltou. Estado = " + String(estadoBotaoArId4));
}
void botaoModoArSoltou()
{
    estadoBotaoModoAr = (estadoBotaoModoAr + 1) % 4;
    publicarJsonModoAr();
    atualizarTextoModoAr();
    debugInfo("Botão modo soltou. Estado = " + String(estadoBotaoModoAr));
}
void botaoVentoArSoltou()
{
    estadoBotaoVento++;
    if (estadoBotaoVento > 4)
    {
        estadoBotaoVento = 0;
    }
    publicarJsonVentoAr();
    atualizarTextoVento();
    debugInfo("Botão vento soltou. Estado = " + String(estadoBotaoVento));
}
void botaoTemperaturaUpSoltou()
{
    contadorTemperatura++;

    if (contadorTemperatura > 30)
    {
        contadorTemperatura = 30;
    }

    publicarJsonTemperatura();
    atualizarTextoTemperaturaArCondicionado();
    debugInfo("Botão up ar soltou. Temperatura = " + String(contadorTemperatura));
}
void botaoTemperaturaDownSoltou()
{
    contadorTemperatura--;

    if (contadorTemperatura < 18)
    {
        contadorTemperatura = 18;
    }

    publicarJsonTemperatura();
    atualizarTextoTemperaturaArCondicionado();
    debugInfo("Botão down ar soltou. Temperatura = " + String(contadorTemperatura));
}

//  TV
void botaoBackTvSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("Botão back soltou - Página 0 (Menu)");
}
void botaoDualPowerTvSoltou()
{
    botaoDualPowerTv.getValue(&estadoComandoTV);
    sincronizarPaginaAtual();
    publicarJsonTV();
    debugInfo("Botão power tv soltou. Comando = " + String(estadoComandoTV));
}
void botaoVolumeUpTvSoltou()
{
    estadoComandoTV = 2;
    publicarJsonTV();
    debugInfo("Botão volume up tv soltou. Comando = " + String(estadoComandoTV));
}
void botaoVolumeDownTvSoltou()
{
    estadoComandoTV = 3;
    publicarJsonTV();
    debugInfo("Botão volume down tv soltou. Comando = " + String(estadoComandoTV));
}
void botaoSetaDireitaTvSoltou()
{
    estadoComandoTV = 4;
    publicarJsonTV();
    debugInfo("Botão direita tv soltou. Comando = " + String(estadoComandoTV));
}
void botaoSetaEsquerdaTvSoltou()
{
    estadoComandoTV = 5;
    publicarJsonTV();
    debugInfo("Botão esquerda tv soltou. Comando = " + String(estadoComandoTV));
}
void botaoSetaCimaTvSoltou()
{
    estadoComandoTV = 6;
    publicarJsonTV();
    debugInfo("Botão cima tv soltou. Comando = " + String(estadoComandoTV));
}
void botaoSetaBaixoTvSoltou()
{
    estadoComandoTV = 7;
    publicarJsonTV();
    debugInfo("Botão baixo tv soltou. Comando = " + String(estadoComandoTV));
}
void botaoSelectTvSoltou()
{
    estadoComandoTV = 8;
    publicarJsonTV();
    debugInfo("Botão select tv soltou. Comando = " + String(estadoComandoTV));
}
void botaoReturnTvSoltou()
{
    estadoComandoTV = 9;
    publicarJsonTV();
    debugInfo("Botão return tv soltou. Comando = " + String(estadoComandoTV));
}

// SENSOR
void botaoBackSensorSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("Botão back soltou - Página 0 (Menu)");
}
