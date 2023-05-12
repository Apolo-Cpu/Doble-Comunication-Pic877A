#include<16F877A.h>
#FUSES XT,NOWDT,NOPROTECT,NOLVP
#USE DELAY(CLOCK=4000000)
#define lcd_enable_pin pin_E0
#define lcd_rs_pin pin_E1
#define lcd_rw_pin pin_E2
#byte portd = 0xf83 // Identificador para el puerto D. 
#include<lcdm.c> 
#include<KBD4X4.c>

float s1 = 5000, s2 = 3000, s3 = 4500, s4 = 8000, s5 = 6000, s6 = 2000, s7 = 8000, s8 = 2000, s9 = 6000, Ing, Sal;
  float precio;
  char *nombre;

void menu_principal();
void menu_seleccion();
void mostrar_cafe(int seleccion);
void mostrar_cambio(float cambio);
void mostrar_precio(float precio);
void Mocca();
void Irish();
void Latte();
void Frappe();
void Azteca();
void Americano();
void Carajillo();
void Capuccino();
void Vienes();

void main()  // ................................Inicializacion  LCD
{
    lcd_init(); //Inicializamos la LCD
    kbd_init(); //Inicializamos el teclado
    port_b_pullups(true); //Puerto B utiliza las resistencias internas de pull down

    for (;;) // Ciclo principal del programa
    {
        menu_principal();
        menu_seleccion();
        
   }
}

void menu_principal() //------------------------Animación Menu Base
{
      lcd_putc("\f");
     lcd_gotoxy(2, 1);
     lcd_putc(" CAFETERA DE RALU ");
     delay_ms(200);
     lcd_gotoxy(1, 2);
     lcd_putc("1. Mocca");
     delay_ms(50);
     lcd_gotoxy(21, 1);
     lcd_putc("2. Irish");
     delay_ms(50);
     lcd_gotoxy(21, 4);
     lcd_putc("3. Latte");
     delay_ms(500);
     lcd_putc("\f") ; //borra pantalla

    
      lcd_gotoxy(2, 1);
      lcd_putc(" CAFETERA DE RALU ");
      delay_ms(200);
      lcd_gotoxy(1,2);
      lcd_putc("4. Frappe");
      delay_ms(50);
      lcd_gotoxy(21,1);
      lcd_putc("5. Azteca ");
      delay_ms(50);
      lcd_gotoxy(21,4);
      lcd_putc("6. Americano");
      delay_ms(500);
      lcd_putc("\f") ;

    
      lcd_gotoxy(2, 1);
      lcd_putc(" CAFETERA DE RALU ");
      delay_ms(200);
      lcd_gotoxy(1,2);
      lcd_putc("7. Carajillo");
      delay_ms(50);
      lcd_gotoxy(21,1);
      lcd_putc("8. Cappuccino");
      delay_ms(50);
      lcd_gotoxy(21,4);
      lcd_putc("9. Vienes");
      delay_ms(500);
      lcd_putc("\f"); //borra pantalla
}

void mostrar_cambio(float cambio) {  // --------Preparando Pedido
 
  lcd_putc("\f");
  lcd_gotoxy(1, 1);
  lcd_putc("GRACIAS POR COMPRAR");
  delay_ms(100);
  lcd_gotoxy(21, 1);
  lcd_putc("Preparando Su Pedido");
  lcd_gotoxy(21, 4);
  delay_ms(2000);
  printf(lcd_putc, "Tome su Cambio: $ %.2f", cambio);
  delay_ms(2000);
  lcd_putc("\f"); // clears the LCD screen
  
   
   }
   
void seleccionar_cafe(int num) {  //....... Nombre de Seleccion
  lcd_putc("\f");
 
  
  switch (num) {
    case 1:
      nombre = "Mocca";
      precio = s1;
      mostrar_precio(precio);
      Mocca();

      break;
    case 2:
      nombre = "Irish";
      precio = s2;
      mostrar_precio(precio);
      Irish();
      break;
    case 3:
      nombre = "Latte";
      precio = s3;
      mostrar_precio(precio);
       Latte();
      
      break;
    case 4:
      nombre = "Frappe";
      precio = s4;
      mostrar_precio(precio);
      Frappe();
    
      break;
    case 5:
      nombre = "Azteca";
      precio = s5;
      mostrar_precio(precio);
      Azteca();
     
      break;
    case 6:
      nombre = "Americano";
      precio = s6;
      mostrar_precio(precio);
      Americano();
    
      break;
    case 7:
      nombre = "Carajillo";
      precio = s7;
      mostrar_precio(precio);
      Carajillo();
      
      break;
    case 8:
      nombre = "Cappuccino";
      precio = s8;
      mostrar_precio(precio);
      Capuccino();
    
      break;
    case 9:
      nombre = "Vienes";
      precio = s9;
      mostrar_precio(precio);
      Vienes();
     
      break;

    
      return;
  }
 
// lcd_putc(nombre);
 // mostrar_precio(precio);
  delay_ms(400);
}

void mostrar_precio(float precio) {  //---------Factura y saldo
  //printf(lcd_putc, nombre);
  lcd_gotoxy(1, 2);
  printf(lcd_putc, "Precio: $ %.2f", precio);
  delay_ms(50);
  lcd_gotoxy(21, 1);
  lcd_putc("Ingrese Su Efectivo");
  delay_ms(50);
  Sal = precio;
  Ing = 0;
  lcd_gotoxy(21, 4);
  printf(lcd_putc, "Ing:%.0f", Ing);
  lcd_gotoxy(33, 4);
  printf(lcd_putc, "Sal:%.0f", Sal);

  while (true) {
    char k = kbd_getc();
    if (k == 'c' || k == 'C') {
      Ing += 1000;
      lcd_gotoxy(21, 4);
  
      printf(lcd_putc, "Ing:%.0f", Ing);
      
      if (Ing >= Sal) {
        float cambio = Ing - Sal;
        
       mostrar_cambio(cambio);
      
        
        Ing = 0;
        Sal = 0;
        
        break;
      }
    }
  }
}

void mostrar_menu_cafe() { //---------------Menu Seleccion en LCD
  lcd_putc("\f");
  lcd_gotoxy(2, 1);
  lcd_putc(" CAFETERA DE RALU ");
  delay_ms(200);
  lcd_gotoxy(21, 1);
  lcd_putc("Elija su Cafe (_)");
  lcd_gotoxy(21, 4);
  lcd_putc("Repetir Menu(D)");
}

void menu_seleccion() { //----------------------Seleccion Ruta
  char k;
  mostrar_menu_cafe();

  while (true) {
    k = kbd_getc();
    if (k == 'D' || k == 'd') {  // ---- Repite Menu
     // menu_principal();
      break;
    }
    else if (k >= '1' && k <= '9') {
      seleccionar_cafe(k - '0');  //------Factura
      break;
      
    } 
  }
  
}

void Mocca()

{
  lcd_putc("\f");
  lcd_gotoxy(8, 1);
  lcd_putc(" Mocca ");
   output_high(pin_d3);
    delay_ms(1000);
    output_low(pin_d3);
    output_high(pin_d0);
    delay_ms(1000);
    output_low(pin_d0);
    output_high(pin_d1);
    delay_ms(500);
    output_low(pin_d1);
        output_high(pin_d2);
    delay_ms(500);
    output_low(pin_d2);
     lcd_putc("\f");
  lcd_gotoxy(5, 2);
  lcd_putc(" GRACIAS :) ");
  delay_ms(800);
    
           break;

}

void Irish()

{
  lcd_putc("\f");
  lcd_gotoxy(8, 2);
  lcd_putc(" Irish ");
   output_high(pin_d0);
    delay_ms(1000);
    output_low(pin_d0);
    output_high(pin_d4);
    delay_ms(800);
    output_low(pin_d4);
    output_high(pin_d2);
    delay_ms(500);
    output_low(pin_d2);

     lcd_putc("\f");
  lcd_gotoxy(5, 2);
  lcd_putc(" GRACIAS :) ");
  delay_ms(800);
    
           break;
}

void Latte()

{
  lcd_putc("\f");
  lcd_gotoxy(8, 2);
  lcd_putc(" Latte ");
   output_high(pin_d0);
    delay_ms(800);
    output_low(pin_d0);
    output_high(pin_d1);
    delay_ms(1500);
    output_low(pin_d1);
        output_high(pin_d2);
    delay_ms(500);
    output_low(pin_d2);

     lcd_putc("\f");
  lcd_gotoxy(5, 2);
  lcd_putc(" GRACIAS :) ");
  delay_ms(800);
    
           break;

}

void Frappe()

{
  lcd_putc("\f");
  lcd_gotoxy(8, 2);
  lcd_putc(" Frappe ");
   output_high(pin_d0);
    delay_ms(800);
    output_low(pin_d0);
    output_high(pin_d6);
    delay_ms(1500);
    output_low(pin_d6);
        
     lcd_putc("\f");
  lcd_gotoxy(5, 2);
  lcd_putc(" GRACIAS :) ");
  delay_ms(800);
    
           break;

}

void Azteca()

{
  lcd_putc("\f");
  lcd_gotoxy(8, 2);
  lcd_putc(" Azteca ");
   output_high(pin_d0);
    delay_ms(800);
    output_low(pin_d0);
    output_high(pin_d7);
    delay_ms(2000);
    output_low(pin_d7);
    output_high(pin_d2);
    delay_ms(1000);
    output_low(pin_d2);
        
     lcd_putc("\f");
  lcd_gotoxy(5, 2);
  lcd_putc(" GRACIAS :) ");
  delay_ms(800);
    
           break;

}

void Americano()

{
  lcd_putc("\f");
  lcd_gotoxy(8, 2);
  lcd_putc(" Americano ");
   output_high(pin_d0);
    delay_ms(800);
    output_low(pin_d0);
    output_high(pin_d5);
    delay_ms(2000);
    output_low(pin_d5);

        
     lcd_putc("\f");
  lcd_gotoxy(5, 2);
  lcd_putc(" GRACIAS :) ");
  delay_ms(800);
    
           break;

}

void Carajillo()

{
  lcd_putc("\f");
  lcd_gotoxy(8, 2);
  lcd_putc(" Carajillo ");
   output_high(pin_d0);
    delay_ms(800);
    output_low(pin_d0);
    output_high(pin_d4);
    delay_ms(1000);
    output_low(pin_d4);

        
     lcd_putc("\f");
  lcd_gotoxy(5, 2);
  lcd_putc(" GRACIAS :) ");
  delay_ms(800);
    
           break;

}

void Capuccino()
{
  lcd_putc("\f");
  lcd_gotoxy(8, 2);
  lcd_putc(" Capuccino ");
   output_high(pin_d0);
    delay_ms(800);
    output_low(pin_d0);
    output_high(pin_d1);
    delay_ms(1000);
    output_low(pin_d1);
    output_high(pin_d2);
    delay_ms(500);
    output_low(pin_d2);

        
     lcd_putc("\f");
  lcd_gotoxy(5, 2);
  lcd_putc(" GRACIAS :) ");
  delay_ms(800);
    
           break;

}

void Vienes()
{
  lcd_putc("\f");
  lcd_gotoxy(8, 2);
  lcd_putc(" Vienes ");
   output_high(pin_d0);
    delay_ms(800);
    output_low(pin_d0);
    output_high(pin_d6);
    delay_ms(1000);
    output_low(pin_d6);

        
     lcd_putc("\f");
  lcd_gotoxy(5, 2);
  lcd_putc(" GRACIAS :) ");
  delay_ms(800);
    
           break;

}
