#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> can3;
IntervalTimer timer1;
IntervalTimer timer2;
int state = 0;

enum gear {
  PARKING, // 0
  REVERSE, // 1
  NEUTRAL, // 2
  DRIVING // 3

};

gear currentGear = PARKING;

void canSniff1(const CAN_message_t &msg);
void canSniff2(const CAN_message_t &msg);
void canSniff3(const CAN_message_t &msg);
void kirimcan2(int addr, int data0, int data1, int data2, int data3, int data4, int data5, int data6, int data7);
void kirimcan3(int addr, int data0, int data1, int data2, int data3, int data4, int data5, int data6, int data7);


void kirimcan2(int addr, int data0, int data1, int data2, int data3, int data4, int data5, int data6, int data7){
CAN_message_t kirim;             // Buat objek pesan CAN

  kirim.id = addr;                // Set ID ke 0x418
  kirim.len = 8;                   // Panjang data = 8 byte
  kirim.buf[0] = data0;
  kirim.buf[1] = data1;
  kirim.buf[2] = data2;
  kirim.buf[3] = data3;
  kirim.buf[4] = data4;
  kirim.buf[5] = data5;
  kirim.buf[6] = data6;
  kirim.buf[7] = data7;

  can2.write(kirim);              // Kirim pesan CAN
}

void kirimcan3(int addr, int data0, int data1, int data2, int data3, int data4, int data5, int data6, int data7){
CAN_message_t kirim;             // Buat objek pesan CAN

  kirim.id = addr;                // Set ID ke 0x418
  kirim.len = 8;                   // Panjang data = 8 byte
  kirim.buf[0] = data0;
  kirim.buf[1] = data1;
  kirim.buf[2] = data2;
  kirim.buf[3] = data3;
  kirim.buf[4] = data4;
  kirim.buf[5] = data5;
  kirim.buf[6] = data6;
  kirim.buf[7] = data7;

  can3.write(kirim);              // Kirim pesan CAN
}

void setup() {
  can2.begin();
  can2.setBaudRate(500000);  // Set baud rate ke 500 kbps

  can3.begin();
  can3.setBaudRate(500000);  // Set baud rate ke 500 kbps


  timer1.begin(timerISR1, 50000);  // 50 ms
  timer2.begin(timerISR2, 50000);  // 50 ms
  Serial.println("Bismillah");
}




void timerISR1() {
switch (currentGear) {
    case PARKING:
      kirimcan2(0x230, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    break;
    case REVERSE:
      kirimcan2(0x230, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    break;
    case NEUTRAL:
      kirimcan2(0x230, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    break;
    case DRIVING:
      kirimcan2(0x230, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    break;
  }  
}

void timerISR2() {
switch (currentGear) {
    case PARKING:
      kirimcan2(0x230, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    break;
    case REVERSE:
      kirimcan2(0x230, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    break;
    case NEUTRAL:
      kirimcan2(0x230, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    break;
    case DRIVING:
      kirimcan2(0x230, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    break;
  }  
}

void loop() {
  currentGear = PARKING;
  Serial.println("PARKING");
  delay(3000);
  currentGear = REVERSE;
  Serial.println("REVERSE");
  delay(3000);
  currentGear = NEUTRAL;
  Serial.println("NEUTRAL");
  delay(3000);
  currentGear = DRIVING;
  Serial.println("DRIVING");
  delay(3000);
 



}



