//final project

//4 digit display and shift register
const int dataPin  = 11;  // 74HC595 pin 8 DS
const int latchPin = 10;  // 74HC595 pin 9 STCP
const int clockPin = 9;   // 74HC595 pin 10 SHCP
const int digit0   = 6;   // 7-Segment pin D4
const int digit1   = 5;   // 7-Segment pin D3
const int digit2   = 4;   // 7-Segment pin D2
const int digit3   = 3;   // 7-Segment pin D1 

byte table[]= 
    {   0x5F,  // = 0
        0x44,  // = 1
        0x9D,  // = 2
        0xD5,  // = 3
        0xC6,  // = 4
        0xD3,  // = 5
        0xDB,  // = 6
        0x45,  // = 7
        0xDF,  // = 8
        0xC7,  // = 9
        0xCF,  // = A
        0xDA,  // = b
        0x1B,  // = C
        0xDC,  // = d
        0x9B,  // = E
        0x8B,  // = F
        0x00   // blank
    }; 
byte controlDigits[] = { digit0, digit1, digit2, digit3 }; 
byte displayDigits[] = { 0,0,0,0,0 };                 
              
int brightness = 100; 

//nokia 5110 variables
#define RST 13
#define CE  12
#define DC  8
#define DIN  7
#define CLK  2

unsigned char i;
unsigned char j;

const int x = 1;
static int y = 0;

const int x2 = 78;
static int y2 = 0;

//left char
const int button1 = A0;
int button1state = 0;

const int button2 = A1;
int button2state = 0;

//right char
const int button3 = A2;
int button3state = 0;

const int button4 = A3;
int button4state = 0;

//left attack
const int button5  = A4;
int button5state = 0;

//right attack
const int button6 = A5;
int button6state = 0;

//scores
static int player1_score = 20;
static int player2_score = 20;

//conversion table for lcd
static const byte ASCII[][5] =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j 
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ←
,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f →
};

void DisplaySegments(){

    for (int x=0; x<4; x++){
        for (int j=0; j<4; j++){
            digitalWrite(controlDigits[j],LOW);
        }
        digitalWrite(latchPin,LOW);
        shiftOut(dataPin,clockPin,MSBFIRST,displayDigits[x]);
        digitalWrite(latchPin,HIGH);
        digitalWrite(controlDigits[x],HIGH);
        Serial.println(x); }
}

void LcdWriteString(char *characters)
{
  while(*characters) 
  {
    LcdWriteCharacter(*characters++);
  }
}

void LcdWriteCharacter(char character)
{
  for(int i=0; i<5; i++) 
  {
    LcdWriteData(ASCII[character - 0x20][i]);
  }
  LcdWriteData(0x00);
}

void LcdWriteData(byte dat)
{
  digitalWrite(DC, HIGH); //DC pin is low for commands
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, dat); //transmit serial data
  digitalWrite(CE, HIGH);
}

void LcdXY(int x, int y)
{
  LcdWriteCmd(0x80 | x);  // Column.
  LcdWriteCmd(0x40 | y);  // Row.
}

void LcdWriteCmd(byte cmd)
{
  digitalWrite(DC, LOW); //DC pin is low for commands
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, cmd); //transmit serial data
  digitalWrite(CE, HIGH);
}

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);

} task;

int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum SM1_States { SM1_INIT, SM1_S0, SM1_S1};
int SM1_Tick(int state1) {
  switch (state1) { // State transitions
    case SM1_INIT:
      state1 = SM1_S0;
      break;
      
    case SM1_S0:
      if(player1_score > 5 && player2_score > 5)
      {
        state1 = SM1_S0;
      }
      else if(player1_score <= 5 || player2_score <= 5)
      {
        state1 = SM1_S1;
      }
      break;

    case SM1_S1:
      if(i <= 5){
        state1 = SM1_S1;
      }
      else if(i > 5)
      {
        state1 = SM1_S0;
        i = 0;
      }
      break;

    default:
      break;

  }
  switch (state1) { // State Action
    case SM1_INIT:
      break;
      
    case SM1_S0:
      LcdXY(x,y);
      LcdWriteString("x");
    
      LcdXY(x2,y2);
      LcdWriteString("x");
    
      button1state = digitalRead(button1);
      button2state = digitalRead(button2);
      button3state = digitalRead(button3);
      button4state = digitalRead(button4);
      button5state = digitalRead(button5);
      button6state = digitalRead(button6);
    
      if(button1state == HIGH)
      {
        y = y + 1;
    
        if(y > 5)
        {
          y = 5;
        }
        
        LcdXY(x,y-1);
        LcdWriteString(" ");
        LcdXY(x,y);
        LcdWriteString("x");
        //LcdWriteData(0x00);
      }
    
      if(button2state == HIGH)
      {
        y = y - 1;
    
        if(y < 0)
        {
          y = 0;
        }
        
        LcdXY(x,y+1);
        LcdWriteString(" ");
        LcdXY(x,y);
        LcdWriteString("x");
        //LcdWriteData(0x00);
      }
    
      if(button3state == HIGH)
      {
        y2 = y2 + 1;
    
        if(y2 > 5)
        {
          y2= 5;
        }
        
        LcdXY(x2,y2-1);
        LcdWriteString(" ");
        LcdXY(x2,y2);
        LcdWriteString("x");
        //LcdWriteData(0x00);
        Serial.println("y2 button 3"); Serial.println(y2);
      }
    
      if(button4state == HIGH)
      { 
        y2 = y2 - 1;
    
        if(y2 < 0)
        {
          y2 = 0;
        }
        
        LcdXY(x2,y2+1);
        LcdWriteString(" ");
        LcdXY(x2,y2);
        LcdWriteString("x");
        //LcdWriteData(0x00);
        Serial.println("y2 button 4"); Serial.println(y2);
      }
    
      if(button5state == HIGH)
      {
        Serial.print("val of y and y2: "); Serial.println(x); Serial.println(x2);
        if(y == y2)
          {
            player2_score = player2_score - 5;
            Serial.print("player2 score: "); Serial.println(player2_score);
          }
          
        for(int i = 10; i < 65; i++)
        {
          LcdXY(x+i, y);
          LcdWriteString("-");
          LcdXY(x-i, y);
          LcdWriteString(" ");
        }
    
        for(int i = 10; i < 65; i++)
        {
          LcdXY(x+i, y);
          LcdWriteString(" ");
        }     
      }
    
      if(button6state == HIGH)
      {
        if(y == y2)
          {
            player1_score = player1_score - 5;
            Serial.print("player1 score: "); Serial.println(player1_score);
          }
          
        for(int i = 10; i < 65; i++)
        {
          LcdXY(x2-i, y2);
          LcdWriteString("-");
          LcdXY(x2+i, y2);
          LcdWriteString(" ");
        }
    
        for(int i = 10; i < 65; i++)
        {
          LcdXY(x+i, y);
          LcdWriteString(" ");
        }
      }
    
      Serial.println("button4 state: "); Serial.println(button4state);
      Serial.print("player2 score: "); Serial.println(player2_score);
      break;

    case SM1_S1:
      if(player1_score > player2_score)
      {
        LcdXY(1,1);
        LcdWriteString("Player 1 Won!");
      }
      else if(player1_score < player2_score)
      {
        LcdXY(1,1);
        LcdWriteString("Player 2 Won!");
      }
      else if(player1_score == player2_score)
      {
        LcdXY(1,1);
        LcdWriteString("Players have tied!");
      }
      i++;
      break;

    default:
      break;

  }
  return state1;
}
 
enum SM2_States { SM2_INIT, SM2_S0};
int SM2_Tick(int state2) {
  switch (state2) { // State transitions
    case SM2_INIT:
      //State Transition
      if(player1_score <= 5 || player2_score <= 5)
      {
        state2 = SM2_S0;
      }
      else
      {
        state2 = SM2_INIT;
      }
      break;
      
    case SM2_S0:
      if(j <= 10)
      {
        state2 = SM2_S0;
      }
      else if(j > 10)
      {
        state2 = SM2_INIT;
      }
      break;

    default:
      break;

  }
  switch (state2) { // State Action
    case SM2_INIT:
      break;

    case SM2_S0:
      unsigned int a, b = 0;
      if(player1_score > player2_score)
      {
        if(player1_score == 20)
        {
          displayDigits[0] = B01011111; // 0
          displayDigits[1] = B10011101; // 2
        }
        else if(player1_score == 15)
        {
          displayDigits[0] = B11010011;  // 5
          displayDigits[1] = B01000100;  // 1
        }
        else if(player1_score == 10)
        {
          displayDigits[1] = B01000100;  // 1
          displayDigits[0] = B01011111; // 0
        }
        else if(player1_score == 5)
        {
          displayDigits[0] = B11010011;  // 5
          displayDigits[1] = B01011111; // 0
        }
      displayDigits[2] = B01000100;  // 1
      displayDigits[3] = B10001111;  // P
      displayDigits[4] = B1111;
      DisplaySegments();
    }
    else if(player1_score < player2_score)
    {
      if(player2_score == 20)
      {
        displayDigits[0] = B01011111; // 0
        displayDigits[1] = B10011101; // 2
        displayDigits[2] = B10011101; // 2
        displayDigits[3] = B10001111;  // P
      }
      else if(player2_score == 15)
      {
        displayDigits[0] = B11010011;  // 5
        displayDigits[1] = B01000100;  // 1
      }
      else if(player2_score == 10)
      {
        displayDigits[0] = B01000100;  // 1
        displayDigits[1] = B01011111; // 0
      }
      else if(player2_score == 5)
      {
        displayDigits[0] = B11010011;  // 5
        displayDigits[1] = B01011111; // 0
      }
      displayDigits[2] = B10011101; // 2
      displayDigits[3] = B10001111;  // P
      displayDigits[4] = B1111;
      DisplaySegments();
    }

    
    j++;
      break;

    default:
      break;

  }

  return state2;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(RST, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(DC, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(RST, LOW);
  digitalWrite(RST, HIGH);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(button6, INPUT);
  
  LcdWriteCmd(0x21);  // LCD extended commands
  LcdWriteCmd(0xBF);  // set LCD Vop (contrast)
  LcdWriteCmd(0x04);  // set temp coefficent
  LcdWriteCmd(0x14);  // LCD bias mode 1:40
  LcdWriteCmd(0x20);  // LCD basic commands
  LcdWriteCmd(0x0C);  // LCD normal video
  
  for(int i=0; i<504; i++) 
  {
    LcdWriteData(0x00); // clear LCD
  }

  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  for (int x=0; x<4; x++){
     pinMode(controlDigits[x],OUTPUT);
     digitalWrite(controlDigits[x],LOW);
    }
  DisplaySegments(); 
    
  Serial.begin(9600);


  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 1000;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;   
  tasks[i].state = SM2_INIT;
  tasks[i].period = 1;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;
  
  delay_gcd = 1000; // GCD
}

void loop() {
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
}
