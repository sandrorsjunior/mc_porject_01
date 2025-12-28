# **Projeto 01: Monitorização de Porta com ATmega328P (FSM & HAL)**

## **📋 Sobre o Projeto**

Este projeto implementa um sistema embarcado para monitorização de segurança de portas utilizando o microcontrolador **ATmega328P**. O sistema foi desenvolvido em **Linguagem C** utilizando uma abordagem *bare-metal* (sem sistema operacional), focando na eficiência e no controle direto do hardware.

A lógica de controle baseia-se em uma **Máquina de Estados Finitos (FSM)** para garantir determinismo e robustez, enquanto o acesso ao hardware é mediado por uma camada de abstração (HAL \- Hardware Abstraction Layer) personalizada para controle de GPIOs.

### **🎯 Funcionalidades**

* **Leitura de Sensor:** Monitoriza um sensor de porta (simulado por switch) com filtro de ruído básico (*debounce* via delay).  
* **Atuação Visual:** Controla um indicador LED para sinalizar o estado da porta.  
* **Eficiência:** Uso de resistores de *pull-up* internos para reduzir componentes externos.  
* **Portabilidade:** Estrutura de projeto baseada em CMake, independente de IDEs proprietárias.

## **🛠️ Hardware e Esquemático**

O projeto foi validado no microcontrolador ATmega328P (comum nas placas Arduino Uno/Nano).

### **Pinagem (Pinout)**

| Componente | Pino AVR | Pino Arduino | Configuração | Descrição |
| :---- | :---- | :---- | :---- | :---- |
| **Sensor (Switch)** | PB1 | D9 | INPUT\_PULLUP | Fecha curto com GND quando acionado. |
| **Atuador (LED)** | PC5 | A5 | OUTPUT | Nível Alto (5V) acende o LED. |

**Nota de Engenharia:** Originalmente, o pino PC6 (Reset) seria considerado, mas foi substituído pelo PC5 para evitar a desabilitação do fusível de Reset, o que dificultaria a gravação via ISP/Serial.

### **Requisitos Elétricos**

* **VCC:** 5V  
* **Resistor do LED:** 220Ω ou 330Ω (Limitador de corrente para \< 20mA).  
* **Sensor:** Conectado entre PB1 e GND. Não é necessário resistor externo (Pull-up interno ativado via software).

## **📂 Estrutura do Projeto**

A arquitetura de diretórios segue as boas práticas de engenharia de software embarcado, separando código fonte, cabeçalhos e configurações de build.

mc\_project\_01/  
├── cmake/  
│   └── avr-toolchain.cmake   \# Configurações do Cross-Compiler (AVR-GCC)  
├── include/  
│   └── gpio.h                \# Cabeçalho da HAL (Interface)  
├── src/  
│   ├── gpio.c                \# Implementação da HAL (Driver)  
│   └── main.c                \# Lógica da Aplicação (FSM)  
├── CMakeLists.txt            \# Configuração Principal do CMake  
└── README.md                 \# Esta documentação

## **⚙️ Detalhes da Implementação**

### **1\. Camada de Abstração de Hardware (HAL)**

Arquivos: include/gpio.h e src/gpio.c

Para evitar a manipulação direta de bits mágicos no código principal (*bit-banging*), foi criada uma biblioteca gpio. Ela encapsula operações bit-a-bit (|=, &= \~) oferecendo uma API legível:

* gpio\_config(): Configura os registrador DDRx.  
* gpio\_write(): Escreve nos registradores PORTx.  
* gpio\_read(): Lê os registradores PINx.

### **2\. Máquina de Estados (FSM)**

Arquivo: src/main.c

A aplicação não é bloqueante e segue um fluxo definido por estados:

1. **STATE\_CONFIG:**  
   * Inicializa os periféricos.  
   * Configura PB1 como entrada com *pull-up* (PORTB |= (1\<\<1)).  
   * Configura PC5 como saída.  
   * Transita imediatamente para STATE\_CLOSED.  
2. **STATE\_CLOSED (Repouso):**  
   * **Ação:** Mantém LED desligado (PC5 LOW).  
   * **Transição:** Se PB1 for lido como LOW (GND), entende-se que a porta abriu \-\> vai para STATE\_OPEN.  
3. **STATE\_OPEN (Alerta):**  
   * **Ação:** Liga o LED (PC5 HIGH).  
   * **Transição:** Se PB1 for lido como HIGH (VCC), entende-se que a porta fechou \-\> vai para STATE\_CLOSED.

## **🚀 Como Compilar e Gravar**

Este projeto utiliza **CMake** como sistema de build, permitindo a compilação via linha de comando em Linux, Windows ou macOS.

### **Pré-requisitos**

* **CMake** (v3.10 ou superior)  
* **AVR-GCC Toolchain** (avr-gcc, avr-g++, avr-objcopy, avr-size)  
* **AVRDUDE** (Para upload)

### **Passo a Passo**

1. Criar diretório de build:  
   Mantenha a raiz do projeto limpa gerando os arquivos temporários em uma pasta separada.  
   mkdir build  
   cd build

2. Gerar Makefiles:  
   Execute o CMake apontando para a raiz (..) e especificando a toolchain.  
   cmake \-DCMAKE\_TOOLCHAIN\_FILE=../cmake/avr-toolchain.cmake ..

3. **Compilar:**  
   make

   Sucesso: O arquivo mc\_porject\_01.hex será gerado na pasta build.  
   O comando também exibirá o tamanho do binário (Flash e RAM).  
4. Upload (Gravação):  
   Utilize o avrdude. Exemplo para Arduino Uno conectado na porta /dev/ttyUSB0 (Linux) ou COM3 (Windows):  
   avrdude \-c arduino \-p atmega328p \-P /dev/ttyUSB0 \-b 115200 \-U flash:w:mc\_porject\_01.hex:i

## **🔧 Configurações do CMake**

O arquivo CMakeLists.txt define automações críticas para AVR:

* **Definição de Frequência:** \-DF\_CPU=16000000UL garante que os delays (\_delay\_ms) sejam calculados corretamente para um clock de 16MHz.  
* **Geração de HEX:** Um comando POST\_BUILD converte automaticamente o binário .elf para .hex.  
* **Análise de Tamanho:** Exibe automaticamente o consumo de memória após cada compilação, essencial para sistemas embarcados com recursos limitados.

## **👨‍💻 Autores**

* **Sandro Ribeiro** \- Engenharia de Firmware  
* **Mafalda Sofia** \- Engenharia de Hardware  
* **Daniel Oliveira** \- Testes e Validação

*Desenvolvido no âmbito da disciplina de Microcontroladores e Sistemas Digitais \- IPCA (2025/2026)*