# 🔊 Sistema de Alarme Inteligente com Detecção de Som e Feedback Visual 🔴🟡🟢  

## 📖 Sobre o Projeto  
Este projeto implementa um **sistema de alarme baseado em captação de som**, utilizando a **Raspberry Pi Pico W** e o **kit de desenvolvimento BitDogLab**. O sistema **monitora o ambiente** através de um **sensor de microfone** 🎤 e **dispara um alarme** caso o nível de som ultrapasse um **limite predefinido**.  

Para indicar o estado do sistema, o projeto conta com um **display OLED**, uma **matriz de LEDs RGB 5x5**, um **LED RGB individual** e **buzzers**, garantindo um **feedback visual e sonoro eficiente**.  

Além disso, o sistema registra o **horário do disparo do alarme**, com base no tempo decorrido desde que a placa foi ligada.  

---

## 🎯 Objetivos do Projeto  
✅ Monitorar sons do ambiente com um **sensor de microfone** 🎤.  
✅ Acionar **alarme sonoro e visual** quando o som ultrapassa um limite 🚨.  
✅ Exibir informações em tempo real no **display OLED SSD1306** 📟.  
✅ Controlar o sistema com **botões físicos**.  
✅ Utilizar **PWM** para ajustar o brilho dos LEDs 💡.  
✅ Criar **animações dinâmicas** na **matriz de LEDs RGB** 🎇.  
✅ Exibir a **hora do disparo do alarme** ⏰.  

---

## 🛠️ **Componentes Utilizados e Conexões**  

| **Componente**                 | **GPIO**  | **Descrição** |
|--------------------------------|----------|--------------|
| 🖥 **Raspberry Pi Pico W**     | -        | Microcontrolador principal |
| 📟 **Display OLED SSD1306**    | 14 (SDA), 15 (SCL) | Comunicação via **I2C** |
| 🔲 **Matriz de LEDs WS2812 (5x5)** | 7 | Controlada via **PIO** |
| 🎤 **Microfone**               | 28       | Entrada **ADC** |
| 🔴 **LED RGB** - Vermelho      | 13       | Controle via **PWM** |
| 🟢 **LED RGB** - Verde         | 11       | Controle via **PWM** |
| 🔵 **LED RGB** - Azul          | 12       | Não utilizado diretamente |
| 🔊 **Buzzer A**                | 10       | Emite som de alarme |
| 🔊 **Buzzer B**                | 21       | Complementa o alarme |
| ⏺ **Botão A**                 | 5        | Ativa/desativa o alarme |
| ⏺ **Botão B**                 | 6        | Desliga o alarme disparado |

---

## 🚀 **Funcionamento do Sistema**  

### **🔄 Estados do Sistema**  

1️⃣ **Alarme Desligado** (`Botão A: OFF`)  
✅ LED RGB **verde fixo** 🟢.  
✅ Matriz de LEDs exibe **animações verdes**.  
✅ Display OLED exibe **"ALARME: OFF"**.  

2️⃣ **Alarme Ligado (mas não disparado)** (`Botão A: ON`)  
🟡 LED RGB **amarelo piscando** (brilho controlado pelo som) 🟡.  
🟡 Matriz de LEDs mantém **animações verdes**.  
🟡 Display OLED exibe **"ALARME: ON"** e a **leitura do microfone** 📊.  

3️⃣ **Alarme Disparado** (som acima do limite)  
🔴 LED RGB **piscando em vermelho** 🔴.  
🔴 Matriz de LEDs **piscando em vermelho**.  
🔴 **Buzzers emitindo sirene** 🔊.  
🔴 **Display OLED exibe "ALARME DISPARADO!" e a hora do disparo** ⏰.  
⚠️ O **alarme só pode ser desligado pelo Botão B**.  

---

## 🎮 **Controles e Interações**  

- **🔘 Botão A:** Liga/desliga o sistema de alarme **antes de ser disparado**.  
- **🔘 Botão B:** **Desativa o alarme** após ele ser disparado.  

---

## 📜 **Explicação do Código**  

### 🛠 **1. Configuração do Hardware**  
- Inicializa **GPIOs** para LEDs, buzzers e botões.  
- Configura o **ADC** para o microfone 🎤.  
- Configura **I2C** para comunicação com o **display OLED** 📟.  
- Inicializa **PWM** para controle da intensidade dos LEDs.  

### 📡 **2. Monitoramento do Som**  
- O **ADC** captura valores do microfone **em tempo real**.  
- Se o som captado for maior que o **limite predefinido**, o **alarme é acionado**.  

### 🎇 **3. Indicação Visual e Sonora**  
- **LED RGB e Matriz de LEDs** indicam os estados do sistema 🔴🟡🟢.  
- **PWM controla o brilho dos LEDs** para suavidade visual.  
- **Buzzers alternam frequências** para criar um **som de sirene** 🚨.  
- **O display OLED exibe informações dinâmicas**, como a leitura do microfone e a hora do disparo do alarme.  

### ⏰ **4. Registro do Horário do Disparo**  
- O tempo é registrado usando `hardware/timer.h`, **contando desde o início da execução** do código.  
- O horário do disparo é exibido no display OLED no formato `HH:MM:SS`.  

### 🎮 **5. Controle via Botões**  
- O **Botão A** ativa ou desativa o sistema **antes do disparo**.  
- O **Botão B** desliga o **alarme depois que ele foi disparado**.  

---

## 📊 **Vídeo Demonstrativo do Projeto**  

📹 **[Link para acessar o vídeo demonstrativo do projeto](https://drive.google.com/file/d/1Ya6SjHECfObIo5NIXUbTYfqO7XaALwYh/view?usp=drivesdk)**

---

## 📌 **Conclusão**  
Este projeto demonstra um **sistema de alarme inteligente**, que usa **múltiplos componentes eletrônicos** para criar uma **solução completa de segurança baseada em áudio** 🎤.  

🔹 **Diferenciais do Projeto:**  
✅ Combina **feedback sonoro e visual** 📟🔊.  
✅ Usa **PWM para suavizar a experiência visual** 💡.  
✅ Implementa **animações na matriz de LEDs** 🎇.  
✅ Exibe **a leitura do microfone em tempo real** 📊.  
✅ Registra **o horário do disparo do alarme** ⏰.  

### 🔍 **Possíveis Melhorias Futuras**  
🚀 Adicionar **Wi-Fi** para enviar alertas remotos 📡.  
🚀 Utilizar um **RTC (Relógio em Tempo Real)** para mostrar **horário real** 🕒.  
🚀 Implementar **ajuste dinâmico do limite de detecção** com aprendizado de máquina 🤖.  

---

📌 **Desenvolvido por:** **Gabriel Marcone Magalhães Santos** 🚀