#include <18F4550.h>
#fuses HS, NOWDT, PUT, BROWNOUT, NOLVP, CPUDIV1 
#device adc=10
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)

float ad;
unsigned int32 ad0, ad1;

#int_timer0              
void trata_t0() {
    static unsigned int32 n;
    SET_TIMER0(100+get_timer0()); 
    n++;
    
    if (n==100) {
      n = 0;
      
      set_adc_channel(0);
      ad = read_adc();
      delay_ms(10);
      ad0 = ad * 99.9999999999/1023;
      
      set_adc_channel(1);
      ad = read_adc();
      delay_ms(10);
      ad1 = ad * 99.9999999999/1023;
      
      if (ad0 < ad1) {
         output_high(pin_c2);
      } else {
         output_low(pin_c2);
      }
    }
}

void main(){
    SET_TRIS_C(0x00);
    SET_TRIS_D(0x00);
    ENABLE_INTERRUPTS(GLOBAL|INT_TIMER0);   
    SETUP_TIMER_0(RTCC_INTERNAL | RTCC_DIV_256 | RTCC_8_BIT);
    setup_adc_ports(an0_to_an2);
    setup_adc(adc_clock_internal);
    SET_TIMER0(100);                  
    while(true) {
    }
}
