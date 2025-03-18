# Carrinho Robô com Câmera

Repositório do trabalho desenvolvido na disciplina de **Projeto Integrado de Computação I**.  
Trabalho feito pelos alunos **Davi Boni, Daniel Dayrell e Yan Simmer**.

## Sumário
* [Resumo](#resumo)
* [Descrição Detalhada](#descrição-detalhada)
* [Materiais Necessários](#materiais-necessários)
* [Esquemático](#esquemático)
* [Dependências](#dependências)

---

## Resumo

Projeto de um **carrinho robô controlado via WiFi** usando o **ESP32-CAM**, com **transmissão de vídeo em tempo real**.  
Ele inclui **motores DC, driver de motor** e uma **interface web para comando remoto**, unindo visão e movimento em um sistema integrado e interativo.

---

## Descrição Detalhada

### **Objetivo**
O objetivo é criar um veículo robótico que seja capaz de:

1. **Receber comandos de movimento** (frente, trás, esquerda, direita) e de iluminação por meio de uma **interface web**.
2. **Transmitir imagens ao vivo** capturadas pela câmera do **ESP32-CAM**, permitindo o controle baseado na visão do ambiente ao redor.

---

### **Plataforma de Controle e Comunicação**
#### **ESP32-CAM**
- Serve como o **cérebro** do sistema, controlando tanto os motores quanto a câmera.
- Através da **funcionalidade WiFi integrada**, o módulo cria um **servidor web** para transmitir o vídeo e receber os comandos do usuário.

---

### **Locomoção**
#### **Motores DC**
- Permitem o movimento do carrinho em todas as direções básicas.

#### **Driver de Motor (L298N)**
- Controla a **direção** e a **velocidade** dos motores com base nos sinais enviados pelo ESP32-CAM.

#### **Chassi e Rodas**
- Oferecem suporte físico e estrutura para o sistema.

---

### **Energia**
- Uma **fonte de alimentação externa (4 pilhas AA)** é usada para fornecer energia suficiente para o driver de motor.
- Outra fonte de energia (**Power Bank**) é usada para alimentar a ESP32-CAM.

---

### **Interface de Controle**
#### **Servidor Web**
- Exibe o **vídeo em tempo real** capturado pela câmera.
- Inclui **botões de comando** para controlar o movimento do robô.

---

### **Diferenciais do Projeto**
1. **Transmissão de Vídeo em Tempo Real**  
   - Facilita o controle remoto, especialmente em locais fora da linha de visão direta.
2. **Conexão WiFi**  
   - Dispensa o uso de módulos adicionais, como o Bluetooth.
3. **Integração de Sistemas**  
   - Combina a movimentação do carrinho com uma **interface intuitiva para o usuário**.

---

## Materiais Necessários

1. **ESP32-CAM**
2. **Chassi Robô** (estrutura, motores DC, rodas, suporte para pilhas)
3. **Módulo Driver Ponte H L298N**
4. **Fonte externa de energia** (Power Bank)
5. **Jumpers**
6. **Placa de circuito impresso**

---

## Esquemático

![Esquemático do projeto](https://i.imgur.com/Fnv3tiO.png)

---

## Dependências

Para programar o ESP32-CAM, é necessário utilizar a **Arduino IDE** com as seguintes bibliotecas:

1. `esp_camera.h`
2. `WiFi.h`
3. `WebServer.h`
4. `esp_http_server.h`
5. `Arduino.h`

---

🚀 **Desenvolvido por Davi Boni, Daniel Dayrell e Yan Simmer**  
📌 **Disciplina: Projeto Integrado de Computação I**
