//Selvin Peralta
//Carnet 131376
//lab 05

#include <SPI.h>
#include <SD.h>

char get;

File myFile;
File root;

void setup()
{
  SPI.setModule(0);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(10, OUTPUT);

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");


  root = SD.open("/");
  Directorio(root, 0);

  //USUARIO
  Serial.println("Ingrese el numero según las opciones numeradas");
  Serial.println("Envie 1) si quiere mostrar NIKE.TXT");
  Serial.println("Envie 2) si quiere mostrar ARTICUNO.TXT");
  Serial.println("Envie 3) si quiere mostrar CHAMPION.TXT");
  Serial.println("Envie 4) si quiere mostrar OW.TXT");
  Serial.println("Envie 5) si quiere mostrar los archivos en la SD");





  /*
    // re-open the file for reading:
    myFile = SD.open("ow.txt");
    if (myFile) {
      //Serial.println("test.txt:");
      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      // close the file:
      myFile.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
    }
  */
}

void loop() {
  get = Serial.read();
  char  a = (get, DEC);
  switch (get) {
    case '1':
      myFile = SD.open("NIKE.txt");
      if (myFile) {
        //Serial.println("test.txt:");

        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
      Serial.println("Ingrese el numero según las opciones numeradas");
      Serial.println("Envie 1) si quiere mostrar NIKE.TXT");
      Serial.println("Envie 2) si quiere mostrar ARTICUNO.TXT");
      Serial.println("Envie 3) si quiere mostrar CHAMPION.TXT");
      Serial.println("Envie 4) si quiere mostrar OW.TXT");
      Serial.println("Envie 5) si quiere mostrar los archivos en la SD");
      break;

    case '2':
      myFile = SD.open("articuno.txt");
      if (myFile) {
        //Serial.println("test.txt:");

        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
      Serial.println("Ingrese el numero según las opciones numeradas");
      Serial.println("Envie 1) si quiere mostrar NIKE.TXT");
      Serial.println("Envie 2) si quiere mostrar ARTICUNO.TXT");
      Serial.println("Envie 3) si quiere mostrar CHAMPION.TXT");
      Serial.println("Envie 4) si quiere mostrar OW.TXT");
      Serial.println("Envie 5) si quiere mostrar los archivos en la SD");
      break;

    case '3':
      myFile = SD.open("CHAMPION.txt");
      if (myFile) {
        //Serial.println("test.txt:");

        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
      Serial.println("Ingrese el numero según las opciones numeradas");
      Serial.println("Envie 1) si quiere mostrar NIKE.TXT");
      Serial.println("Envie 2) si quiere mostrar ARTICUNO.TXT");
      Serial.println("Envie 3) si quiere mostrar CHAMPION.TXT");
      Serial.println("Envie 4) si quiere mostrar OW.TXT");
      Serial.println("Envie 5) si quiere mostrar los archivos en la SD");
      break;

    case '4':
      myFile = SD.open("ow.txt");
      if (myFile) {
        //Serial.println("test.txt:");

        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
      Serial.println("Ingrese el numero según las opciones numeradas");
      Serial.println("Envie 1) si quiere mostrar NIKE.TXT");
      Serial.println("Envie 2) si quiere mostrar ARTICUNO.TXT");
      Serial.println("Envie 3) si quiere mostrar CHAMPION.TXT");
      Serial.println("Envie 4) si quiere mostrar OW.TXT");
      Serial.println("Envie 5) si quiere mostrar los archivos en la SD");
      break;

    case '5':
      root = SD.open("/");
      Directorio(root, 0);

      //USUARIO
      Serial.println("Ingrese el numero según las opciones numeradas");
      Serial.println("Envie 1) si quiere mostrar NIKE.TXT");
      Serial.println("Envie 2) si quiere mostrar ARTICUNO.TXT");
      Serial.println("Envie 3) si quiere mostrar CHAMPION.TXT");
      Serial.println("Envie 4) si quiere mostrar OW.TXT");
      Serial.println("Envie 5) si quiere mostrar los archivos en la SD");
  }

}

void Directorio(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no hay mas archivos
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      Directorio(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
