#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  



#include <RH_ASK.h>    // incluye libreria RadioHead.h
#include <SPI.h>    // incluye libreria SPI necesaria por RadioHead.h

RH_ASK rf_driver;   // crea objeto para modulacion por ASK


//int PinPulsador = 11;
//int PinPulsadorReset = 8;

int contador = 0;
String minutosStr; 
String segundosStr; 
String decimasStr; 
String milisegundosStr; 


int inicio = 0;
int milisegundos = 0;
int decimas = 0;
int segundos = 0;
int minutos = 0; 



void activarContador() {

    if (inicio == 1){
      milisegundos = millis();

      if(milisegundos % 1 == 0){
      decimas++;

      if(decimas == 10){
        decimas = 0;
        segundos++;
      }
      if(segundos == 60){
        segundos = 0;
        minutos++;
        
      }

      while(minutos == 10){
        minutos = 0;
        segundos = 0;
        decimas = 0;
        lcd.clear();
        
      }


      lcd.setCursor(0, 0);
        lcd.setCursor(3, 0);
        if (minutos < 10)      {
          lcd.print("0");      }
        minutosStr = String(minutos);
        lcd.print( minutos);
        lcd.print(":");
        lcd.setCursor(6, 0);
        if (segundos < 10)     {
        lcd.print("0");        }
        segundosStr = String(segundos);
        lcd.print(segundos);
    }
  
}

}






 
void setup(){
  
 //pinMode(PinPulsador, OUTPUT);
  //pinMode(PinPulsadorReset, OUTPUT);
  
    rf_driver.init();   // inicializa objeto con valores por defecto
  Serial.begin(9600);
        lcd.begin(16, 2);
  // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
}
 
void loop(){
    uint8_t buf[1];     // espacio para mensaje recibido de 1 caracter
    uint8_t buflen = sizeof(buf); // longitud de buffer


    
    if (rf_driver.recv(buf, &buflen)) // si se recibieron datos correctos
    {
      if((char)buf[0]=='1')   // si el caracter es el numero 1
        {
            activarContador();
  
        }           
                  
    }
}
