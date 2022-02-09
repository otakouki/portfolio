#include <Wire.h>



// I2Cアドレス
#define DRV_ADR_R 0x64 // RightDRV8830のI2Cアドレス
#define DRV_ADR_L 0x60 // LeftDRV8830のI2Cアドレス
#define CTR_ADR 0x00 // CONTROLレジスタのサブアドレス
#define FLT_ADR 0x01 // FAULTレジスタのアドレス



// ブリッジ制御
#define M_STANBY B00 // スタンバイ
#define M_REVERSE B01 // 逆転
#define M_NORMAL B10 // 正転
#define M_BRAKE B11 // ブレーキ



// 電圧定義
#define MAX_VSET 0x23 // 5.06V
#define MIN_VSET 0x09 // 0.72V
//#define R_VSET 0x0D // 2.97V
//#define L_VSET 0x25 // 2.97V
#define CSPEED 0x23 //2.81V


#include <SPI.h>
#define slaveSelectPin0 4
#define slaveSelectPin1 5

int num = 0;

int analogData[16];
int r_analogData[6];
int l_analogData[6];

// 制御コマンド送信
// 制御コマンド送信
int write_vset_r(byte vs, byte ctr) {
  Wire.beginTransmission(DRV_ADR_R);
  Wire.write(CTR_ADR);
  Wire.write( ctr + (vs << 2) );
  Wire.endTransmission();
  return 0;
}



// 制御コマンド送信
int write_vset_l(byte vs, byte ctr) {
  Wire.beginTransmission(DRV_ADR_L);
  Wire.write(CTR_ADR);
  Wire.write( ctr + (vs << 2) );
  Wire.endTransmission();
  return 0;
}

// 制御コマンド送信
int stop_r() {
  Wire.beginTransmission(DRV_ADR_R);
  Wire.write(CTR_ADR);
  Wire.write( 0x00 << 2 | 0x00 );
  Wire.endTransmission();
  return 1;
}



// 制御コマンド送信
int stop_l() {
  Wire.beginTransmission(DRV_ADR_L);
  Wire.write(CTR_ADR);
  Wire.write( 0x00 << 2 | 0x00 );
  Wire.endTransmission();
  return 1;
}



void setup() {
  Wire.begin();
  Serial.begin(115200);
  pinMode(slaveSelectPin0, OUTPUT);          //SS(10)を出力に設定
  pinMode(slaveSelectPin1, OUTPUT);
  SPI.setBitOrder(MSBFIRST);                //MSBから送信
  SPI.setClockDivider(SPI_CLOCK_DIV2);      //クロック分周設定
  SPI.setDataMode(SPI_MODE0);               //SPIモード0
  SPI.begin();                              //SPI通信開始
  stop_l();
  stop_r();
}



void loop() {
  for (int i = 0; i < 4; i++) {
    get_adc(i);


    r_analogData[3 - i] = analogData[0];
    l_analogData[i] = analogData[1];

  }
  Serial.println(r_analogData[0]);
  // byte vset = R_VSET;


  //モータドライバブリッジ制御をスタンバイ、最低電圧に設定
  if (r_analogData[0] < 100 && num == 0 ) {
    Serial.println("start");
    num = 1;
    for (byte i = MIN_VSET; i <= MAX_VSET; i += 3) {
      write_vset_l(i, M_REVERSE);
      write_vset_r(i, M_REVERSE);
      //      Serial.print(i);
      delay(1000);
    }
  }
  stop_l();
  stop_r();
  if (num == 1) {
    if (l_analogData[1] < 100 || l_analogData[2] < 100 || l_analogData[3] < 100) {
      Serial.println("右寄り");
      for (byte i = MIN_VSET; i <= MAX_VSET; i += 3) {
        write_vset_l(i, M_REVERSE);
        write_vset_r(i, M_REVERSE);
        //      Serial.print(i);
        delay(1000);
      }
    }
    stop_l();
    stop_r();
    if (r_analogData[1] < 100 || r_analogData[2] < 100 || r_analogData[3] < 100) {
      Serial.println("左寄り");
      for (byte i = MIN_VSET; i <= MAX_VSET; i += 3) {
        write_vset_l(i, M_REVERSE);
        write_vset_r(i, M_REVERSE);
        //      Serial.print(i);
        delay(1000);
      }

    }
    stop_l();
    stop_r();
  }
}
void get_adc(byte ch)
{
  byte data[4] = {0, 0, 0, 0};                               //SPI通信用変数


  //------[ ADC0のデータを取得する ]------
  digitalWrite(slaveSelectPin0, LOW);       //CS LOW
  SPI.transfer(0x01);                       //①スタートビット送信
  data[0] = SPI.transfer((ch << 4) | 0x80);  //②Single-ended チャンネル選択,ADC0のbit9,8取得
  data[1] = SPI.transfer(0);                //③ADC0のbit7～0取得
  digitalWrite(slaveSelectPin0, HIGH);                  //CS HIGH



  // ------[ ADC1のデータを取得する ]------
  digitalWrite(slaveSelectPin1, LOW);       //CS LOW
  SPI.transfer(0x01);                       //①スタートビット送信
  data[2] = SPI.transfer((ch << 4) | 0x80);  //②Single-ended チャンネル選択,ADC0のbit9,8取得
  data[3] = SPI.transfer(0);                //③ADC0のbit7～0取得
  digitalWrite(slaveSelectPin1, HIGH);                  //CS HIGH



  analogData[0] = ((data[0] & 0x03) << 8) | data[1];  //ADC0
  analogData[1] = ((data[2] & 0x03) << 8) | data[3];  //ADC1
  //return analogData[0];
}
