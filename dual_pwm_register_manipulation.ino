void setup()
{
    Serial.begin(9600);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);


      
    /*Prescaler values:
    CSn2  CSn1  CSn0 (n = port 0,1 or 2)
    0     0     1     No Prescaler
    0     1     0     /8
    0     1     1     /64 (arduino default)
    1     0     0     /256
    1     0     1     /1024
    1     1     0     Using external clock on falling edge
    1     1     1     Using external clock on rising edge.

    16000000 Hz/(64*256)=976Hz (fast mode with prescaler 64), so within the audible range.
    16000000 Hz/510)=31372Hz (phase correct pwm mode with no prescaler), outside of the audible range.
    
    
    * |TCCR0A                                                     ||TCCR0B                                                    ||
    * |COM0A1 |COM0A0 |COM0B1 |COM0B0 | --- | --- | WGM01 | WGM00 ||FOC0A | FOC0B | --- | --- | WGM02 | CS02  | CS01  | CS00  ||
    */

    //IF possible dont change TCCR0A and TCCR0B as they affect the system clock.
    //TCCR0A = B10100011;  //Setting COM0A1,COM0A0, COM0B1, COM0B0 to 10 and 10 for Clear on compare, set to bottom. 
                                              //And the WGM01 and WGM00 bits to 11 for Fast PWM
    //TCCR0B = TCCR0B & B11111000 | B00000011; // Setting the CS00, CS01, and CS02 bits for Prescaler /64 
/*
 * Binary (Logic) AND (&) and OR (|)
      B10101010       B10100000
    & B11110000     | B00000011
    -----------     -----------
    = B10100000     = B10100011
*/

    /*======================
    * |TCCR1A                                                     ||TCCR1B                                                      ||
    * |COM1A1 |COM1A0 |COM1B1 |COM1B0 | --- | --- | WGM11 | WGM10 ||ICNC1 | ICES1 | --- | WGM13 | WGM12 | CS12  | CS11  | CS10  ||
    * 
    */

    TCCR1A = B10100001;  //Setting COM0A1,COM0A0, COM0B1, COM0B0 to 10 and 10 for Clear on compare set to bottom. And the WGM11 and WGM10 bits to 01 (along with WGM12 and WGM13 set to 00 in TCCR1B) for Phase correct PWM, 8 bit. (32kHz)
//                v- set to 1 for 8 bit Fast PWM (64kHz)                     
    TCCR1B = B00000001; // Setting the WGM12 and WGM13 to 00 (see comments for TCCR1A above), and CS00, CS01, and CS02 bits for Prescaler /1 (001) 

    /*======================
    * |TCCR2A                                                     ||TCCR2B                                                    ||
    * |COM2A1 |COM2A0 |COM2B1 |COM2B0 | --- | --- | WGM21 | WGM20 ||FOC2A | FOC2B | --- | --- | WGM22 | CS22  | CS21  | CS20  ||
    * 
    */
    TCCR2A = B10100011;  //Setting COM0A1,COM0A0, COM0B1, COM0B0 to 10 and 10 for Clear on compare set to bottom. 
                                              //And the WGM01 and WGM00 bits to 11
    TCCR2B = TCCR2B & B11111000 | B00000001; // Setting the CS00, CS01, and CS02 bits for Prescaler /1 (001) 
}
void loop()
 {
    Serial.print(TCCR0A, BIN);
    Serial.print(" ");
    Serial.println(TCCR0B, BIN);
    Serial.print(TCCR1A, BIN);
    Serial.print(" ");
    Serial.println(TCCR1B, BIN);
    Serial.print(TCCR2A, BIN);
    Serial.print(" ");
    Serial.println(TCCR2B, BIN);

    //using AnalogWrite
    //analogWrite(6,random(0,255));
    //analogWrite(5,random(0,255));
    
    //analogWrite(9,random(0,255));
    //analogWrite(10,random(0,255));
    
    //analogWrite(11,random(0,255));
    //analogWrite(3,random(0,255));
    
    //using Output Compare Registers direct manipulation
    //Again dont use these pins like this use analogWrite if possible,
    //OCR0A=random(0,255); //Pin 6
    //OCR0B=random(0,255); //Pin 5
    
    OCR1A=random(0,255); //Pin 9
    OCR1B=random(0,255); //Pin 10

    OCR2A=random(0,255); //Pin 11
    OCR2B=random(0,255); //Pin 3
    
    delay(1000);
}
