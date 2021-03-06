/* 
   MIDI Monitor v1.0
   This is an exemple how to use the LCD with your Midilickuino
   at the moment only noteON, noteOFF, Control Change, Program Change, Start and Stop are used
   
   *plug your lcd to the Midilickuino
   *Put the switch in PROG position
   *Upload this application to your Arduino board
   *Switch to MIDI
   *plug your Midi OUT to the Midilickuino MIDI IN  
   *Wait until the LCD display "Waiting..."
   *Send MIDI Data and you should see what data you  sent 
   *Enjoy!!
   
   https://www.e-licktronic.com
 */  

#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins 
LiquidCrystal lcd(2,3,4,5,6,7);

byte incomingByte;//stock the first receive byte
byte note;//stock the second receive byte
byte velocity;// stock the 3rd receive byte
byte message;//Message type
byte channel;//MIDI channel

void setup(){
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  //set midi baud rate
  Serial.begin(31250);
  //Home message
  lcd.setCursor(0,0);
  lcd.print("  E-licktronic  ");
  lcd.setCursor(0,1);
  lcd.print("MidiMonitor v1.0");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Waiting...");
}

void loop() {

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    message = (incomingByte>>4)- B1000;//convert the first byte to find the message type
    channel = (incomingByte & B1111) +1;//convert the first byte to find the MIDI Channel
    //print the  MIDI channel 
    if(incomingByte<=240){// is it a message system?
      lcd.setCursor(9,0);
      lcd.print("Ch :   ");
      lcd.setCursor(14,0);
      lcd.print(channel,DEC);

      if (message ==1){  //is it a message noteON?   
        lcd.setCursor(0,0);
        lcd.print("noteON   ");
        note =Serial.read();
        lcd.setCursor(0,1);
        lcd.print("Note:    ");
        lcd.setCursor(6,1);
        lcd.print(note,DEC);
        velocity = Serial.read();
        lcd.setCursor(9,1);
        lcd.print("Vel:    ");
        lcd.setCursor(13,1);
        lcd.print(velocity,DEC);
      }
      if (message ==0){//is it a message noteOFF?
        lcd.setCursor(0,0);
        lcd.print("noteOFF  ");
        note =Serial.read();
        lcd.setCursor(0,1);
        lcd.print("Note:    ");
        lcd.setCursor(6,1);
        lcd.print(note,DEC);
        velocity = Serial.read();
        lcd.setCursor(9,1);
        lcd.print("Vel:   ");
        lcd.setCursor(13,1);
        lcd.print(velocity,DEC);
      }
      if (message ==3){//is it a message Control Change?
        lcd.setCursor(0,0);
        lcd.print("CChange  ");
        note =Serial.read();
        lcd.setCursor(0,1);
        lcd.print("CCnum:   ");
        lcd.setCursor(6,1);
        lcd.print(note,DEC);
        velocity = Serial.read();
        lcd.setCursor(9,1);
        lcd.print("Val:   ");
        lcd.setCursor(13,1);
        lcd.print(velocity,DEC);
      }
      if (message ==4){//is it a message Program Change?
        lcd.setCursor(0,0);
        lcd.print("PrgCh    ");
        note =Serial.read();
        lcd.setCursor(0,1);
        lcd.print("ProgNum:        ");
        lcd.setCursor(10,1);
        lcd.print(note+1,DEC);
      }
    }
    if (incomingByte ==250){//is it a message Start ?
      lcd.setCursor(0,0);
      lcd.print("  MIDI  Start   ");
      lcd.setCursor(0,1);
      lcd.print("                ");
    }
    else if(incomingByte ==252){//is it a message Stop?
      lcd.setCursor(0,0);
      lcd.print("  MIDI  Stop    ");
      lcd.setCursor(0,1);
      lcd.print("                ");
    }
  }  
}






