#include <FastLED.h>

#define NUM_LEDS 4
#define LED_PIN 2
CRGB led[NUM_LEDS];

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 6;
bool on = false;
int currentRed, currentBlue, currentGreen, newRed, newBlue, newGreen;
long randNumber;

// the setup routine runs once when you press reset:
void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(led, NUM_LEDS);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial.println(buttonState);
  delay(5);        // delay in between reads for stability

  checkSerial(buttonState);
}

void checkSerial(int state)
{
  if(state == 0) //If the tilt switch is tilted
  {
    switchColors();
  }
 //Else turn off light
  else
  {
    
    
      for(int i = 0; i < NUM_LEDS; i = i + 1)
      {
        led[i] = CRGB(0,0,0);// Off
      }
      FastLED.show();
      
      on = false;
    
  }
}


void switchColors()
{
  if(on)
  {
    //Get new coordinates (by a randomizer)
    getCoords();
    //fade into new coordinate colors while
    //Set current coordinates
    setColors();
  }
  else //Once turned on, this will activate.
  {
    currentRed = 0;
    currentGreen = 255;
    currentBlue = 0;
    
    for(int i = 0; i < NUM_LEDS; i = i + 1)
     {
      led[i] = CRGB(0,0, 255);//blue
     }
     FastLED.show();

     on = true;
  }
}





void getCoords()
{
  int initialRand = 20;
  initialRand = randNumber;
  
  if(initialRand == randNumber)//Make sure it doesn't choose the same number
    randNumber = random(9); //Based on how many colors we want

  if(randNumber == 0){ //if random becomes white
    newRed = newBlue = newGreen = 255;
  }
  else if(randNumber == 1){ //if random becomes red
    newRed = 255;
    newBlue = newGreen = 0;
  }
  else if(randNumber == 2){ //if random becomes green
     newGreen = 255;
     newBlue = newRed = 0;
  }
  else if(randNumber == 3){ //if random becomes blue
    newBlue = 255;
    newRed = newGreen = 0;
  }
  else if (randNumber == 4){ //if random becomes orange
    newRed = 255;
    newGreen = 102;
    newBlue = 0;
  }
  else if(randNumber == 5){ //if random becomes teal
    newRed = 0;
    newGreen = 188;
    newBlue = 202;
  }
  else if(randNumber == 6){ //if random becomes purple
    newRed = 155;
    newGreen = 0;
    newBlue = 235;
  }
  else if(randNumber == 7){ //if random becomes pink
    newRed = 255;
    newGreen = 50;
    newBlue = 235;
  }
  else if(randNumber == 8){ //if random becomes pastel green
    newRed = 196;
    newGreen = 255;
    newBlue = 210;
  }
}


void setColors() //Changing the color from current to new
{
  //Figure out, how many points it has  to travel between the two (new - current)
  int red, green, blue;
  red = newRed - currentRed;
  green = newGreen - currentGreen;
  blue = newBlue - currentBlue;
  
  //Divide and figure out how many points per .1 seconds to travel (50 iterations over 5 seconds)
  red = red / 50;
  green = green / 50;
  blue = blue / 50;

  //Iterate through 20 times, adding current to red/green/blue, and changing those colors
  for(int iter = 0; (iter < 50); iter++)
  {
    currentRed = currentRed + red;
    currentBlue = currentBlue + blue;
    currentGreen = currentGreen + green;
    doubleCheck(); //Makes sure numbers can't go past 255 or bellow 0

    //Change to those colors
    for(int i = 0; i < NUM_LEDS; i = i + 1)
    {
      led[i] = CRGB(currentRed, currentGreen, currentBlue);
    }
    FastLED.show();

    //Check to see if scissors are still open, if not, turn off
    int button = digitalRead(pushButton); //If button = 0, it's on, if 1, it's off
    if(button == 1)
    {
      checkSerial(button);
      break;
    }
    delay(100); //Iterating at .1 seconds, for 5 seconds, over 50 iterations
  }
}

void doubleCheck()
{
  if(currentRed > 255)
    currentRed = 255;
  if(currentRed < 0)
    currentRed = 0;
  if(currentBlue > 255)
    currentBlue = 255;
  if(currentBlue < 0)
    currentBlue = 0;
  if(currentGreen > 255)
    currentGreen = 255;
  if(currentGreen < 0)
    currentGreen = 0;
}
