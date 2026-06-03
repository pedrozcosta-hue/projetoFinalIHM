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
    debugInfo("b5 solto - Página 6 (Sensor)");
}
//////////////////////

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
    publicarJsonTelaRetratil();
    debugInfo("Up solto. Estado = " + String(estadoBotaoDualUp));
}
void botaoDualDownSoltou()
{
    botaoDualDown.getValue(&estadoBotaoDualDown);
    sincronizarPaginaAtual();
    publicarJsonTelaRetratil();
    debugInfo("Down solto. Estado = " + String(estadoBotaoDualDown));
}
void botaoDualSelectSoltou()
{
    botaoDualSelect.getValue(&estadoBotaoDualSelect);
    sincronizarPaginaAtual();
    publicarJsonTelaRetratil();
    debugInfo("Select solto. Estado = " + String(estadoBotaoDualSelect));
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
void botaoDualPowerArSoltou()
{
    botaoDualPowerAr.getValue(&estadoBotaoDualPowerAr);
    sincronizarPaginaAtual();
    publicarJsonArCondicionado();
    debugInfo("Power solto. Estado = " + String(estadoBotaoDualPowerAr));
}
void botaoModoArSoltou()
{
    estadoBotaoModoAr = (estadoBotaoModoAr + 1) % 4;
    publicarJsonArCondicionado();
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
    debugInfo("Vento solto. Estado = " + String(estadoBotaoVento));
}
void sliderTemperaturaSoltou()
{
    sliderTemperatura.getValue(&valorSliderTemperatura);
    sincronizarPaginaAtual();
    publicarJsonArCondicionado();
    debugInfo("Temperatura solta. Valor = " + String(valorSliderTemperatura));
}
// TODO: ESP
//////////////////////////////////

//TODO: FAZER A LÓGICA PARA OS BOTÕES DA TV E DO SENSOR
// TV
void botaoBackTvSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("B0 Back - Página 0 (Menu)");
}
void botaoDualPowerTvSoltou()
{
    /*botaoDualPowerTv.getValue(&estadoBotaoDualPowerTv);
    sincronizarPaginaAtual();
    publicarJsonTV();
    debugInfo("Power TV solto. Estado = " + String(estadoBotaoDualPowerTv));*/
    sincronizarPaginaAtual();
    publicarJsonTV(1);
}
void botaoVolumeUpTvSoltou()
{
    sincronizarPaginaAtual();
    publicarJsonTV(2);
}
void botaoVolumeDownTvSoltou()
{
    sincronizarPaginaAtual();
    publicarJsonTV(3);
}
void botaoSelectTvSoltou()
{
    sincronizarPaginaAtual();
    publicarJsonTV(8);
}
void botaoSetaEsquerdaTvSoltou()
{
    sincronizarPaginaAtual();
    publicarJsonTV(5);
}
void botaoSetaDireitaTvSoltou()
{
    sincronizarPaginaAtual();
    publicarJsonTV(4);
}
void botaoSetaCimaTvSoltou()
{
    sincronizarPaginaAtual();
    publicarJsonTV(6);
}
void botaoSetaBaixoTvSoltou()
{
    sincronizarPaginaAtual();
    publicarJsonTV(7);
}
////////////////////////

// SENSOR
void botaoBackSensorSoltou()
{
    sendCommand("page page0");
    paginaAtual = 0;
    debugInfo("B0 Back - Página 0 (Menu)");
}

void botaoSensorMenu0Soltou()
{
}

void botaoDualSensorEco()
{
}