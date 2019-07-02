//////////////////////////////////////////////////////////////////////////////
//to be written to PORTD where the pin 0-7 value is stored. we use pin 2,3 (for x axis) 4,5,6 (for y axis)
 
/////////// 0000 1100 =12    first 4 bits y axis next 4 bits (LSB) x axis ////
/////////// 0000 1100 =12
/////////// 0000 1100 =12    
/////////// 0000 1100 =12   end of start bits 

/////////// 0000 0100 =4
/////////// 0000 1000 =8
/////////// 0000 1000 =8
/////////// 0000 0100 =4
/////////// 0000 0000 =0
/////////// 0000 0000 =0
/////////// 0000 0000 =0
/////////// 0000 0000 =0  end of x axis bits

/////////// 0010 1100 =44
/////////// 0101 1100 =92
/////////// 0001 1100 =28
/////////// 0110 1100 =108
/////////// 0111 1100 =124
/////////// 0000 1100 =12
/////////// 0111 1100 =124
/////////// 0000 1100 =12  end of y axis bits
/////////////////////////////////////////////////////////////////////////////////
const int numOfData=21;
byte t[numOfData]={12,12,12,12,////start bits
                   4,8,8,4,0,0,0,0,// 4 bits for x axis . 8 data becz of manchester coding
                   44,92,28,108,124,12,124,12, // 4 bits of y axis 
                   0};//stop bit



                   
int count=0;
void setup() {
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);

  
cli();//stop interrupts

//set timer1 interrupt at 1Hz
   TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 249;// = (16*10^6) / (1*1024) - 1 (must be <65536) . 249 is found by some calculation for giving 125micro seconds delay. 
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler.set cs11 for 8 prescaler.
  TCCR1B |= (1 << CS11);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts

}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 8kHz 
   
    PORTD = t[count]; 
    count= (++count)%numOfData;

}

void loop() {
  // put your main code here, to run repeatedly:

}
