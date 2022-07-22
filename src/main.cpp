#include <data.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN  2 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 16*16 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

String s_word;
int pixelColor =  pixels.Color(150,150,0);

int convert(int x, int y) {
  if (x < 0 || x>16 || y < 0 || y > 16) return -1;
  int z = y % 2 == 1 ? y*16+x : y*16+15-x;
  return z;
}

void showLetter(bool letterArr[16][16], int axeX) {
  for (int x = 0; x<16; x++) {
    for (int y = 0; y < 16; y++) {
      if (letterArr[y][x] == true) {
          pixels.setPixelColor(convert(x-axeX,y), pixelColor);
      }
    }

  }
  pixels.show();
}

int showLetterByLetter(char input, int axeX) {
    if(input == 'a') showLetter(lettera, axeX);
    if(input == 'b') showLetter(letterb, axeX);
    if(input == 'c') showLetter(letterc, axeX);
    if(input == 'd') showLetter(letterd, axeX);
    if(input == 'e') showLetter(lettere, axeX);
    if(input == 'f') showLetter(letterf, axeX);
    if(input == 'g') showLetter(letterg, axeX);
    if(input == 'h') showLetter(letterh, axeX);
    if(input == 'i') showLetter(letteri, axeX);
    if(input == 'j') showLetter(letterj, axeX);
    if(input == 'k') showLetter(letterk, axeX);
    if(input == 'l') showLetter(letterl, axeX);
    if(input == 'm') showLetter(letterm, axeX);
    if(input == 'n') showLetter(lettern, axeX);
    if(input == 'o') showLetter(lettero, axeX);
    if(input == 'p') showLetter(letterp, axeX);
    if(input == 'q') showLetter(letterq, axeX);
    if(input == 'r') showLetter(letterr, axeX);
    if(input == 's') showLetter(letters, axeX);
    if(input == 't') showLetter(lettert, axeX);
    if(input == 'u') showLetter(letteru, axeX);
    if(input == 'v') showLetter(letterv, axeX);
    if(input == 'w') showLetter(letterw, axeX);
    if(input == 'x') showLetter(letterx, axeX);
    if(input == 'y') showLetter(lettery, axeX);
    if(input == 'z') showLetter(letterz, axeX);
    return 1;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED
  pixels.setBrightness(1);
  
}

void loop() {

  if (Serial.available()) 
  {
    char c = Serial.read();
    if (c == '\n') {
        Serial.println(" ");
        int numberLetters = s_word.length();
        for (int x = -17; x < 16*numberLetters; x++) {
            for (int k=0; k < numberLetters; k++) {
                char letter = s_word[k];
                showLetterByLetter(letter, x-16*k);
            }
            pixels.clear();
        }
        s_word = "";
    } else if (c == '*') {
      s_word = s_word.substring(0, s_word.length()-1);
      Serial.println(" ");
      Serial.print(s_word);
    } else if (c == '&') {
      pixelColor = pixels.Color(250,0,0); 
    } else if (c == '#') {
      pixelColor = pixels.Color(0,250,0);
    } else if (c == '-') {
      pixelColor = pixels.Color(250,250,0);
    } else if (c == '_') {
      pixelColor = pixels.Color(130,130,250);
    } else {
      s_word = s_word + c;
      Serial.print(c);
    }
  }
            
             
             
             
  delay(50);
}