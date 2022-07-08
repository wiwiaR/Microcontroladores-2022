#include <18F4550.h>
#fuses HS, NOWDT, PUT, BROWNOUT, NOLVP, CPUDIV1 
#device adc=10
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)

float ad;
unsigned int32 ad0;

int digito[10] =
               {0b00111111,    //Dígito 0
                0b00000110,    //Dígito 1
                0b01011011,    //Dígito 2
                0b01001111,    //Dígito 3
                0b01100110,    //Dígito 4
                0b01101101,    //Dígito 5
                0b01111101,    //Dígito 6
                0b00000111,    //Dígito 7
                0b01111111,    //Dígito 8
                0b01101111     //Dígito 9
               };

#int_timer0              
void trata_t0() {
    static unsigned int32 n;
    SET_TIMER0(100+get_timer0()); 
    n++;
    
    set_adc_channel(0);
    ad = read_adc();
    delay_ms(10);
    ad0 = ad * 100.0/1023;
     
    if (ad0 >= 10 && ad0 < 30) {
      output_d(digito[0]);
      output_a(0b00100000);
    } else if (ad0 >= 30 && ad0 < 60) {
        output_d(digito[0]);
        output_a(0b00100000);
        delay_ms(20);
        output_d(digito[1]);
        output_a(0b00010000);
        delay_ms(20);
    } else if (ad0 >= 60 && ad0 < 90) {
        output_d(digito[0]);
        output_a(0b00100000);
        delay_ms(20);
        output_d(digito[1]);
        output_a(0b00010000);
        delay_ms(20);
        output_d(digito[2]);
        output_a(0b00001000);
        delay_ms(20);
    } else if (ad0 >= 90) {
        output_d(digito[0]);
        output_a(0b00100000);
        delay_ms(20);
        output_d(digito[1]);
        output_a(0b00010000);
        delay_ms(20);
        output_d(digito[2]);
        output_a(0b00001000);
        delay_ms(20);
        output_d(digito[3]);
        output_a(0b00000100);
        delay_ms(20);
    }
    
}

void main(){
   port_b_pullups(TRUE);
   output_d(0);
   output_a(0);
   
   SET_TRIS_C(0x00);
   SET_TRIS_D(0x00);
   ENABLE_INTERRUPTS(GLOBAL|INT_TIMER0);   
   SETUP_TIMER_0(RTCC_INTERNAL | RTCC_DIV_256 | RTCC_8_BIT);
   setup_adc_ports(an0);
   setup_adc(adc_clock_internal);
   SET_TIMER0(100);    
   
   while(true) {

   }
}
