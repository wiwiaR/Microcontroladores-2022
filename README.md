# Microcontroladores 2022.1 - Prof. Fábio Timbó

Códigos elaborados para a disciplina de Microcontroladores.

### 7Seg.c

Cronômetro indicado no display de 7 segmentos da placa PICGenios.

Funcionamento:

- Compilar o código;
- Carregar o arquivo na placa;
- A contagem começa ao apertar o botão 0;
- O display apaga ao finalizar a contagem;
- Para começar de novo, basta apertar o botão 0 novamente.

### Teclado_sem_timer.c

Programa de uma tranca eletrônica com as seguintes características: 

- Teclado matricial;
- Password: teclas 0 a 9;
- Enter: Tecla #.

Funcionamento:

- Ao ligar o programa o operador deve digitar 5 dígitos na sequência correspondentes ao últimos 5 dígitos de seu número de matrícula e apertar a tecla Enter correspondente. 
- Ao pressionar enter a fechadura liga (led verde) liga por 5 segundos e desliga.
- Se o password for digitado errado o led vermelho liga e SÓ DESLIGA quando o password for digitado corretamente.

O arquivo **12Keys.c** é usado como complemento para o funcionamento de algumas funções.

### Frequencimetro.c

Código de um frequencímetro utilizando o timer1 no PIC18F4550.
