# Bafômetro com Sensor MQ-3 utilizando Raspberry Pi Pico e BitDogLab

## Descrição do Projeto

Este é um projeto de bafômetro utilizando o sensor **MQ-3** para detectar a presença de álcool no ar. O sistema foi desenvolvido com a **Raspberry Pi Pico W**, utilizando o **PicoSDK** e a plataforma de aprendizado **BitDogLab**. A saída de leitura é exibida em um **display OLED**, e LEDs indicam os diferentes níveis de concentração de álcool. O projeto também conta com um **buzzer** que emite um alerta sonoro caso o nível de álcool esteja elevado.

## Funcionalidades

- **Leitura de Nível de Álcool**: Utiliza o sensor MQ-3 para medir a concentração de álcool no ar.
- **Indicação Visual**: LEDs indicam diferentes níveis de álcool.
- **Exibição no Display OLED**: Mostra a porcentagem de álcool detectada.
- **Alerta Sonoro**: O buzzer emite um aviso caso o nível de álcool ultrapasse um limite seguro.

## Componentes Utilizados

- **Microcontrolador**: Raspberry Pi Pico W
- **Sensor**: MQ-3 (Sensor de Álcool)
- **Display**: OLED SSD1306
- **LEDs**: Verde, Azul e Vermelho
- **Buzzer**: Para alerta sonoro
- **Plataforma**: BitDogLab

## Simulação no Wokwi

![Circuito e Esquemático](https://i.imgur.com/uDFc9Ah.png)

Para simular o projeto no **Wokwi**, foi utilizado um potenciômetro no lugar do sensor MQ-3, permitindo variar manualmente o nível de entrada. Além da contagem para esquentar o sensor ser consideralvelmente menor.

[https://www.wokwi.com/projects/422423325632409601](https://www.wokwi.com/projects/422423325632409601)

## Fluxograma do Funcionamento

![Fluxograma do Projeto](https://i.imgur.com/bFbbROv.png)

## Implementação na BitDogLab

![BitDogLab](https://i.imgur.com/b1OIMVR.png)

Você pode ver o funcionamento da placa em video clicando no seguinte link:

[https://drive.google.com/file/d/1GUtW-r3_gfAd40jy-tzJgxOVqTSt9kOs/view?usp=drive_link](https://drive.google.com/file/d/1GUtW-r3_gfAd40jy-tzJgxOVqTSt9kOs/view?usp=drive_link)

## Relatório do Projeto

Você pode ver o trabalho escrito do projeto neste seguinte link:

[https://drive.google.com/file/d/10MXYvOk55-ewVJxlx2oqWJbTT0dgAt2n/view?usp=sharing](https://drive.google.com/file/d/10MXYvOk55-ewVJxlx2oqWJbTT0dgAt2n/view?usp=sharing)

## Como Utilizar

1. **Conecte os componentes** conforme o esquemático.
2. **Carregue o firmware** na Raspberry Pi Pico.
3. **Aguarde o aquecimento do sensor** MQ-3 (aproximadamente 3 minutos).
4. **Sopre levemente no sensor** após consumir bebida alcoólica.
5. **Observe os LEDs, display e buzzer** para verificar a leitura.





