

#define ADDR_NOOP        0
#define ADDR_DIGIT0      1
#define ADDR_DIGIT1      2
#define ADDR_DIGIT2      3
#define ADDR_DIGIT3      4
#define ADDR_DIGIT4      5
#define ADDR_DIGIT5      6
#define ADDR_DIGIT6      7
#define ADDR_DIGIT7      8
#define ADDR_DECODEMODE  9
#define ADDR_INTENSITY   10
#define ADDR_SCANLIMIT   11
#define ADDR_SHUTDOWN    12
#define ADDR_DISPLAYTEST 15

int SPI_MOSI = 2;
int SPI_CLK  = 0;
int SPI_CS   = 1;

char max7219Buffer[8] = {0,0,0,0,0,0,0,0};

void max7219Write(byte addr, byte data) {
  shiftOut(SPI_MOSI,SPI_CLK,MSBFIRST,addr);
  shiftOut(SPI_MOSI,SPI_CLK,MSBFIRST,data);  
}

void max7219Init() {
  pinMode(SPI_MOSI, OUTPUT);
  pinMode(SPI_CLK, OUTPUT);
  pinMode(SPI_CS, OUTPUT);
  digitalWrite(SPI_CS,HIGH);

  digitalWrite(SPI_CS,LOW);
  max7219Write(ADDR_DECODEMODE, 0xff);
  digitalWrite(SPI_CS,HIGH);
  
  digitalWrite(SPI_CS,LOW);
  max7219Write(ADDR_INTENSITY, 0);
  digitalWrite(SPI_CS,HIGH);
  
  digitalWrite(SPI_CS,LOW);
  max7219Write(ADDR_SCANLIMIT, 7);
  digitalWrite(SPI_CS,HIGH);
  
  digitalWrite(SPI_CS,LOW);
  max7219Write(ADDR_SHUTDOWN, 1);
  digitalWrite(SPI_CS,HIGH);
  
  digitalWrite(SPI_CS,LOW);
  max7219Write(ADDR_DISPLAYTEST, 0);
  digitalWrite(SPI_CS,HIGH);
}


// Code B Font
//    0 - '0'
//    1 - '1'
//    2 - '2'
//    3 - '3'
//    4 - '4'
//    5 - '5'
//    6 - '6'
//    7 - '7'
//    8 - '8'
//    9 - '9'
//   10 - '-'
//   11 - 'E'
//   12 - 'H'
//   13 - 'L'
//   14 - 'P'
//   15 - blank
void max7219SetBuffer(int index, char b) {
  max7219Buffer[index] = b;
}

void max7219Refresh() {
  for (int i=0;i<8;i++) {
    digitalWrite(SPI_CS,LOW);
    max7219Write(i+1, max7219Buffer[i]);
    digitalWrite(SPI_CS,HIGH);
  }
}

void setup() {
  max7219Init();
}

int s = 0;

void loop() {
  s++;
  int d = s;

  for (int i=0;i<8;i++) {
    max7219SetBuffer(i, d%10);
    d /= 10;
  }
  
  max7219Refresh();
  
  delay(1000);
}
