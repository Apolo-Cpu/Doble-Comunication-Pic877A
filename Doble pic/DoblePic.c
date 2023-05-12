#include<16F877A.h>
#FUSES XT,NOWDT,NOPROTECT,NOLVP
#USE DELAY(CLOCK=4000000)
#USE RS232(baud=9600,xmit=pin_c6,rcv=pin_c7,bits=8)
#define lcd_enable_pin pin_E0
#define lcd_rs_pin pin_E1
#define lcd_rw_pin pin_E2
#byte portd = 0xf83
#include<lcdm.c>
#include<KBD4X4.c>

void main()
{
    lcd_init();
    kbd_init();
    port_b_pullups(true);

    lcd_gotoxy(2, 1);
    printf(lcd_putc," INTERACCION RALU ");

    while (true)
    {
        char key = kbd_getc();

        if (key != 0)  // Si Digit� el Dato
        {
            lcd_gotoxy(1, 2);
            printf(lcd_putc,"Enviando: %c       ", key);
            putc(key);
        }

        if (kbhit())  // Si recibi� el Dato
        {
            char received = getc();
            lcd_gotoxy(1, 2); 
            printf(lcd_putc,"Recibido: %c       ", received);
        }
    }
}

