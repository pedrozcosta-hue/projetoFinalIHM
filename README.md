

# Projeto Final IHM
Sistema embarcado baseado em ESP32 e Display Nextion para monitoramento e controle através de uma Interface Homem-Máquina (IHM).

Autores: Pedro Z. Costa, Nicolas M. Lopes, Artur de Medeiros Cruz, Gustavo F. Bicho, Veronica Ramalho.

---
## Visão Geral
O projeto consiste em uma interface gráfica desenvolvida para o display Nextion, integrada a um ESP32 responsável pelo processamento dos dados e pela comunicação com dispositivos externos.
A aplicação foi desenvolvida com foco em:
Interface intuitiva para o usuário;
Comunicação serial entre ESP32 e Nextion;
Arquitetura modular utilizando PlatformIO;
Facilidade de manutenção e expansão;
Integração com sistemas IoT e MQTT.

## Por que utilizar Nextion?
A abordagem tradicional exige que o microcontrolador desenhe e atualize toda a interface gráfica.
Com o Nextion, a interface é processada pelo próprio display, reduzindo significativamente o consumo de processamento do ESP32.
Isso permite que o ESP32 fique responsável apenas pela lógica da aplicação e comunicação.

---
## Funcionalidades
* ✅ Interface gráfica utilizando Nextion
* ✅ Comunicação serial entre ESP32 e display
* ✅ Arquitetura organizada em módulos
* ✅ Desenvolvimento utilizando PlatformIO
* ✅ Código em C/C++
* ✅ Estrutura preparada para integração MQTT
* ✅ Atualização dinâmica de componentes da interface

## Tecnologias Utilizadas
| Tecnologia | Finalidade |
|------------|------------|
| ESP32 | Processamento principal |
| Nextion | Interface Homem-Máquina |
| C/C++ | Desenvolvimento embarcado |
| PlatformIO | Ambiente de desenvolvimento |
| UART | Comunicação ESP32 ↔ Nextion |
---
## Estrutura do Projeto
```
projetoFinalIHM/
│
├── include/      # Arquivos de cabeçalho
├── lib/          # Bibliotecas próprias
├── src/          # Código-fonte principal
│
├── platformio.ini
└── README.md
```
---
## Hardware Utilizado
* ESP32
* Display Nextion
* Fonte de alimentação 5V
* Cabos de comunicação serial
* Comunicação ESP32 ↔ Nextion
* A comunicação ocorre através da UART.

## Fluxo simplificado:
```
┌──────────┐
│ Nextion  │
└────┬─────┘
     │ UART
     ▼
┌──────────┐
│  ESP32   │
└────┬─────┘
     │
     ▼
Lógica da Aplicação
```
---

## Como Executar o Projeto
Pré-requisitos
Instale:
Visual Studio Code
PlatformIO
Clonar o repositório
```
git clone https://github.com/pedrozcosta-hue/projetoFinalIHM.git
```
---
## Fluxo de Funcionamento
```
Usuário
   │
   ▼
Display Nextion
   │
   ▼
ESP32
   │
   ▼
Processamento
   │
   ▼
Atualização da interface

```
---

## Licença
Projeto desenvolvido para fins acadêmicos e educacionais.

---

## Repositório
GitHub: https://github.com/pedrozcosta-hue/projetoFinalIHM
