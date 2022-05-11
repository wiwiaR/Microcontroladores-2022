#define vermelho pin_d2
#define amarelo pin_d0
#define verde pin_d1
#include <18F4550.h>
#use delay (clock=20000000)
#fuses HS,PLL5, CPUDIV1, USBDIV
#use rs232(baud=9600, xmit = PIN_C6, rcv = PIN_C7)
#include "12Keys.c"

boolean flag;

void main(){
   port_b_pullups(True);

   char minha_senha[5] = {'5','0','1','9','2'};
   char entrada[5] = {'0','0','0','0','0'};
   tecla_pres=0;
   int contador = 0;
   int verificador = 0;
   int tam = 5;

   while(TRUE){
      tecla = trata_teclas();

      if (tecla_pres) {
         printf("%c",tecla);
         entrada[contador++] = tecla;
         for(int i = 0; i < tam; i++) {
            printf("- %c\n", entrada[i]);
         }

         if (tecla == '#') {
             for (int i = 0; i < tam; i++) {
                if (minha_senha[i] == entrada[i]){
                    verificador++;
                }
             }
             if(verificador==5){
                 output_high(verde);
                 verificador = 0;
             } else {
                output_high(vermelho);
             }
         }
      }
   }
}