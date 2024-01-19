#include <LiquidCrystal.h>
int Contrast=10;
LiquidCrystal lcd(12, 11, 10, 9, 8,7);
// Define the pins for the buttons and the piezo buzzer
//bool sustain=0;
const int buttonPin1 = 14;
const int buttonPin2 = 15;
const int buttonPin3 = 16;
const int buttonPin4 = 17;
const int buttonPin5 = 18;
const int buttonPin6 = 19;
const int buttonPin7 = 5;
const int buttonPin8 = 4;

const int buzzerPin = 3;

// Define the frequencies for each note
const int C = 299;
const int D = 344;
const int E = 394;
const int F = 421;
const int G = 488;
const int A = 560;
const int B = 648;
const int C1 = 704;
const int Br=10;

const int keyPins[] = {14, 15, 16, 17, 18, 19, 5, 4};  // pins that are connected to the keys
const int keyMapping[] = {C, D, E, F, G, A, B, C1};  //corresponding keys

//pre-defining the songs
const int intro[]={C,E,G,C1,B,A,G,C1,C1,C1};
const int odetojoy[]={E,E,F,G,G,F,E,D,C,C,D,E,E,D,D,Br,E,E,F,G,G,F,E,D,C,C,D,E,D,C,C,Br,D,D,E,C,D,F,E,C,D,F,E,D,C,D,G,Br,E,E,F,G,G,F,E,D,C,C,D,E,D,C,C,Br};
const int star_wars[]={C,Br,G,Br,F,E,D,C1,Br,G,Br,F,E,D,C1,G,Br,F,E,F,D,C,Br,G,Br,F,E,D,C1,Br,G,Br,F,E,D,C1,G,Br,F,E,F,D};
const int mary[]={E,D,C,D,E,E,E,Br,D,D,D,Br,E,G,G,Br,E,D,C,D,E,E,E,E,D,D,E,D,C,E,D,C,D,E,E,E,Br,D,D,D,Br,E,G,G,Br,E,D,C,D,E,E,E,E,D,D,E,D,C,C1};
const int spring[] = {C,E,E,E,D,C,G,Br,G,F,E,E,E,D,C,G,Br,G,F,E,F,G,F,E,D,Br,E,G,F,E,F,E,A,G,Br,E,G,F,E,F,E,A,G,Br,E,A,G,Br,F,E,D,C,D,Br,C};
const int buttonPin = 2; 
const int selbuttonPin = 0; // Change this to the actual pin where your button is connected
  // Change this to the actual pin where your buzzer is connected




const int numSongs = 4;
const char *songNames[] = {"OdeToJoy", "Star Wars", "Mary had a little lamb", "Spring"};
int selectedSong = 0;
bool keyState[8] = {false, false, false, false, false, false, false, false};
int songs[4][64]={{E,E,F,G,G,F,E,D,C,C,D,E,E,D,D,Br,E,E,F,G,G,F,E,D,C,C,D,E,D,C,C,Br,D,D,E,C,D,F,E,C,D,F,E,D,C,D,G,Br,E,E,F,G,G,F,E,D,C,C,D,E,D,C,C,Br},
{C,Br,G,Br,F,E,D,C1,Br,G,Br,F,E,D,C1,G,Br,F,E,F,D,C,Br,G,Br,F,E,D,C1,Br,G,Br,F,E,D,C1,G,Br,F,E,F,D},{E,D,C,D,E,E,E,Br,D,D,D,Br,E,G,G,Br,E,D,C,D,E,E,E,E,D,D,E,D,C,E,D,C,D,E,E,E,Br,D,D,D,Br,E,G,G,Br,E,D,C,D,E,E,E,E,D,D,E,D,C,C1},
{C,E,E,E,D,C,G,Br,G,F,E,E,E,D,C,G,Br,G,F,E,F,G,F,E,D,Br,E,G,F,E,F,E,A,G,Br,E,G,F,E,F,E,A,G,Br,E,A,G,Br,F,E,D,C,D,Br,C}};

//int menuFSM[3]={1,2,3};
int menuFSM=0;


bool pause = false;  // for waiting for the keypress from the user

void setup() {
  // Set button pins as inputs
  menuFSM=0;
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  pinMode(buttonPin, INPUT);   
  pinMode(selbuttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.clear();  //initialising the LCD
  lcd.setCursor(0, 0);
  
  lcd.print("HELLO THERE!");  //initializing the LCD display
  introjingle();  //intro music
  delay(1000);  //wait
  menuFSM=1;
  displayMenu();
  
  //initialising the buttons
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
  pinMode(buttonPin7, INPUT);
  pinMode(buttonPin8, INPUT);

  // Set the buzzer pin as an output
  pinMode(buzzerPin, OUTPUT);
  
}

void loop() {
  //playsong();
  // Check if each button is pressed and play the corresponding note
  
  if(digitalRead(buttonPin) == LOW && digitalRead(selbuttonPin)==LOW)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Returning to Main:");
    displayMenu();
  }
  for (int i = 0; i < 8; i++) {
    if (digitalRead(keyPins[i]) == LOW && !keyState[i]) {
      playToneman(keyMapping[i]);
      keyState[i] = true;
      //delay(100);
      if (menuFSM==1){
        delay(300);
        displayMenu();
      }
    } else if (digitalRead(keyPins[i]) == HIGH) {
      keyState[i] = false;
    }
  }
  
  if (digitalRead(buttonPin) == LOW) {
    delay(300); // Debounce delay
    selectedSong += 1; // choosing the song to be played and learnt
    if (selectedSong >= numSongs) {
      selectedSong = 0;
    }
    displayMenu();
  }
  
  if (digitalRead(selbuttonPin) == LOW) {
    // If the last option is selected, play the chosen song
    
      Simonsays(songs[selectedSong]);
      delay(1000);
    
   
    
     // Add a delay to show that the song is playing
    displayMenu();
  }
  
}

// Function to play a tone on the buzzer
void playToneauto(int frequency) {
  //delay(200);
  
  tone1(buzzerPin, frequency, 250);
  //delay(200);
  noTone1(buzzerPin);
   
 // delay(150);
 
}

void playToneman(int frequency) {
  //delay(200);
  
  tone1(buzzerPin, frequency, 250);
  printkeyman(frequency);
  //delay(200);
  noTone1(buzzerPin);
  

 // delay(150);
  return ;
 
}


void tone1(int buzzerPin, int frequency, long unsigned duration) {
  int period = 1000000L / frequency; // Calculate the period in microseconds
  long  startTime = millis(); // Get the current time

  while (millis() - startTime < duration) {
    digitalWrite(buzzerPin, HIGH); // Turn the buzzer on
    delayMicroseconds(period / 2); // Wait for half of the period
    digitalWrite(buzzerPin, LOW); // Turn the buzzer off
    delayMicroseconds(period / 2); // Wait for the other half of the period
  }
}

/*
void tone1(byte pin, uint16_t frequency, uint16_t duration)
{                                                             // input parameters: Arduino pin number, frequency in Hz, duration in milliseconds
  unsigned long startTime=millis();
  unsigned long halfPeriod= 1000000L/(frequency*10/16);
  pinMode(pin,OUTPUT);
  while (millis()-startTime< duration)
  {
    digitalWrite(pin,HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(pin,LOW);
    delayMicroseconds(halfPeriod);
  }
  pinMode(pin,INPUT);
}*/
/*
void tone1(int buzzerPin, int frequency, int duration) {
  int halfPeriod = 500000L / frequency; // Calculate the half-period in microseconds

  long startTime = micros(); // Get the current time

  while (micros() - startTime < duration * 1000) {
    digitalWrite(buzzerPin, HIGH); // Turn the buzzer on
    delayMicroseconds(halfPeriod); // Wait for half of the period
    digitalWrite(buzzerPin, LOW); // Turn the buzzer off
    delayMicroseconds(halfPeriod); // Wait for the other half of the period
  }
}
*/
//function to play the selected song
void playsong(int song[])
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Now Playing :");
  lcd.setCursor(0, 1);
  lcd.print(songNames[selectedSong]);
  for(int i=0;i<32;i++)
  {
    playToneauto(song[i]); //playing induvidual notes in the song
    printkey(song[i]);
  }  
  return;
}

//finding the corresponding LED that has to glow, for a note played during playback
int getLedPin(int index) {
  switch (index) {
    case C: return buttonPin1;
    case D: return buttonPin2;
    case E: return buttonPin3;
    case F: return buttonPin4;
    case G: return buttonPin5;
    case A: return buttonPin6;
    case B: return buttonPin7;
    case C1: return buttonPin8;
    default: return buttonPin1;
  }
}

void noTone1(int buzzerPin) {
  digitalWrite(buzzerPin, LOW); // Set the buzzer pin to LOW
}


//intro music
void introjingle()
{
  for(int i=0;i<10;i++)
  {
    playToneauto(intro[i]);
  }
  
}


int readButton() {
  for (;;) {
    for (int i = 0; i < 8; i++) {
      int buttonPin = keyMapping[i];
      if (digitalRead(getLedPin(buttonPin)) == LOW) {
        playToneman(buttonPin);
        return buttonPin;
      }
    }
    delay(50);
  }
}


//The main code for our idea
void Simonsays(int song[])
{
  // play the song throughout
  playsong(song);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your turn!:");  //user should play now
 
  //int count = 0;
  int start = 0;  //first portion of the learning block
  int bar = 4;   // size of the learning portion
  //int length = sizeof(song)/sizeof(song[0]);
  int length=32;  //length of the song
  while (start<length)
  {
    //int ans[4];
    //int play[4];   
    //int c = 0;
    lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Now Listen!:"); 
      delay(2000);
      for(int i=start;i<(start+bar);i++)    // getting the portion of the song that is to be learned
      {
        playToneauto(song[i]); //playing the portion slowly
        printkey(song[i]);
        //printkey(song[i]);
        //lcd.clear();
        //lcd.setCursor(0, 0);
        //lcd.print("Play now!: "); 

        delay(200);
        //play[c] = song[i];
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Play now!:"); 
      pinMode(buttonPin1, INPUT);
      pinMode(buttonPin2, INPUT);
      pinMode(buttonPin3, INPUT);
      pinMode(buttonPin4, INPUT);
      pinMode(buttonPin5, INPUT); 
      pinMode(buttonPin6, INPUT);
      pinMode(buttonPin7, INPUT);
      pinMode(buttonPin8, INPUT);     


    for (int i = 0; i < 4; i++) {
      int expectedButton = song[start+i];
      if(expectedButton == Br)
      {
        continue;
      }
      int actualButton = readButton();

      if (expectedButton == actualButton) {
        
        continue;
      }
      else {
        lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("OOPS! Wrong Note!"); 
      delay(3000);
      start = start-bar;
      break;
      }
    //++count;
  }  
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("NICE! KEEP GOING!:"); 
    delay(1000); 
    start = start+bar;  // moving to the next section of the song 
}

}

// code to control the 1602 LCD panel
void displayMenu(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Selection Menu:");
  lcd.setCursor(0, 1);
  lcd.print(songNames[selectedSong]);
}

   

void printkeyman(int note)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  switch(note)
  {
    case C:
      lcd.print("Note :C");
      break;
    case D:
      lcd.print("Note :D");
      break;
    case E:
      lcd.print("Note :E");
      break;
    case F:
      lcd.print("Note :F");
      break;
    case G:
      lcd.print("Note :G");
      break;
    case A:
      lcd.print("Note :A");
      break;
    case B:
      lcd.print("Note :B");
      break;
    case C1:
      lcd.print("Note :C1");
      break;
    default:
      lcd.print("Rest");
      break;
  }

}

void printkey(int note)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  switch(note)
  {
    case C:
      lcd.print("Play note : C");
      break;
    case D:
      lcd.print("Play note : D");
      break;
    case E:
      lcd.print("Play note : E");
      break;
    case F:
      lcd.print("Play note : F");
      break;
    case G:
      lcd.print("Play note : G");
      break;
    case A:
      lcd.print("Play note : A");
      break;
    case B:
      lcd.print("Play note : B");
      break;
    case C1:
      lcd.print("Play note : C1");
      break;
    default:
      lcd.print("Rest");
      break;
  }

 

}