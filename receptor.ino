#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27, 16, 2);



#include <RH_ASK.h>    // incluye libreria RadioHead.h
#include <SPI.h>    // incluye libreria SPI necesaria por RadioHead.h

RH_ASK rf_driver;   // crea objeto para modulacion por ASK






//CONTADOR TIMER//
int milisegundos = 0;
int decimas = 0;
int segundos = 0;
int minutos = 0;



int milisegundosSeg = 0;
int decimasSeg = 0;
int segundosSeg = 0;




//local//

int botonIncremento = 7;
//int botonDecremento = 10;

int estadoBotonIncremento;
int estadoBotonAnteriorIncremento;


int cuenta = 0;
int cuentaSeg4 = 0;

//visitante//

int cuentaVisi;
int estadoincrementoVisi;
int botonIncrementoVisi;
int estadoAnteriorIncrementoVisi;

void activarContador() {



  milisegundos = millis();


  decimas++;

  if (decimas == 10) {
    decimas = 0;
    segundos++;
  }
  if (segundos == 60) {
    segundos = 0;
    minutos++;

  }

  if (minutos == 10) {
    minutos = 0;
    decimas = 0;
    segundos = 0;
    lcd.clear();
  }





  lcd.setCursor(4, 0);
  if (minutos < 10)      {
    lcd.print("0");
  }
  lcd.print(minutos);
  lcd.print(":");
  lcd.setCursor(7, 0);
  if (segundos < 10)     {
    lcd.print("0");
  }
  lcd.print(segundos);
}








void activarContadorSeg() {



  milisegundosSeg = millis();


  decimasSeg++;

  if (decimasSeg == 10) {
    decimasSeg = 0;
    segundosSeg++;
  }
  if (segundosSeg == 25) {
    segundosSeg = 0;
    decimasSeg = 0;

  }





  lcd.setCursor(3, 1);
  lcd.setCursor(6, 1);
  if (segundosSeg < 10)     {
    lcd.print("0");
  }
  lcd.print(segundosSeg);
}




void resetearTiempo() {

  decimas = 0;
  segundos = 0;
  minutos = 0;

  decimasSeg = 0;
  segundosSeg = 0;

  cuenta = 0;
  cuentaVisi = 0;
  lcd.clear();
}

void segmentos4(){
  cuentaSeg4++;
  lcd.setCursor(4, 0);
  lcd.print("S");
  lcd.setCursor(4, 1);
  lcd.print(cuentaSeg4);
}



void puntosLocal() {

  cuenta++;
  //Serial.print(cuenta);

  lcd.setCursor(0, 0);
  lcd.print("L");

  lcd.setCursor(0, 1);
  lcd.print(cuenta);


}

void puntosLocalRes() {

  cuenta--;
  //Serial.print(cuenta);

  lcd.setCursor(0, 0);
  lcd.print("L");

  lcd.setCursor(0, 1);
  lcd.print(cuenta);


}



void puntosVisi() {

  cuentaVisi++;
  //Serial.print(cuenta);

  lcd.setCursor(13, 0);
  lcd.print("V");

  lcd.setCursor(13, 1);
  lcd.print(cuentaVisi);


}



void puntosVisiResta () {
  cuentaVisi--;
  lcd.setCursor(13, 0);
  lcd.print("V");
  lcd.setCursor(13, 1);
  lcd.print(cuentaVisi);
}
/*
  void puntosVisitantes(){
  estadoincrementoVisi= digitalRead (botonIncrementoVisi);
  if(estadobotonIncrementoVisi != estadoAnteriorIncrementoVisi){
  if(digitalRead (botonincrementoVisi)== 1){
    cuantaVisi++
    lcd.setCursor(13,1)
    ldc.print('V')
  }
  }
  }
*/

void setup() {

  rf_driver.init();   // inicializa objeto con valores por defecto
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Inicializar el LCD
  lcd.init();

  //Encender la luz de fondo.
  lcd.backlight();
}

void loop() {
  uint8_t buf[1];     // espacio para mensaje recibido de 1 caracter
  uint8_t buflen = sizeof(buf); // longitud de buffer



  if (rf_driver.recv(buf, &buflen)) // si se recibieron datos correctos
  {
    if ((char)buf[0] == '1') // si el caracter es el numero 1
    {


      activarContador();
      activarContadorSeg();

    }

    else if ((char)buf[0] == '2') // si el caracter es el numero 1
    {

      resetearTiempo();

    }


    else  if ((char)buf[0] == '3') // si el caracter es el numero 1
    {

      puntosLocal();

    }

    else  if ((char)buf[0] == '4') // si el caracter es el numero 1
    {

      puntosVisi();

    }

    else  if ((char)buf[0] == '5') // si el caracter es el numero 1
    {

      puntosVisiResta();

    }


    else  if ((char)buf[0] == '6') // si el caracter es el numero 1
    {

      puntosLocalRes();

    }
    else  if ((char)buf[0] == '7') // si el caracter es el numero 1
    {

      decimasSeg = 0;
      segundosSeg = 0;

    }


    else  if ((char)buf[0] == '8') // si el caracter es el numero 1
    {

   segmentos4();

    }




  }
}
