//
// Thermometer by Defi sensor
//
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1309_128X64_NONAME2_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);  
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

#define COUNTOF(ary) (sizeof(ary) / sizeof(ary[0]))
const int SENSOR = 0; 
const int PRESSURE_SENSOR = 1; 

int input_for_temp = 0;// 温度用入力抵抗値
float r = 0; // 抵抗値
float water_temp_history[] = {0,0,0,0,0,0,0,0,0,0}; 

void setup() {
 Serial.begin(9600);   
 u8g2.begin();
 //show_logo();
 delay(2000);

 for(int i = 0; i < 10; i++) { water_temp_history[i] = get_water_temp(); }
}


int loop_count = 0;
unsigned long updated_at = millis();
float water_temp;
float sum;

void loop() {
 // loop count
 loop_count += 1;
 if(loop_count >= 10){ loop_count = 0; }

 // 水温
 water_temp_history[loop_count] = get_water_temp();
 display(water_temps_avg(), get_oil_pressure());
 

 delay(1000);
}

//--------------------
// First view
//--------------------
// ロゴ表示
void show_logo() {
 u8g2.firstPage( );
  do {
    // フォント設定
    u8g2.setFont( u8g_font_9x18B ); 
    u8g2.setFontPosTop();
    u8g2.drawStr( 50, 20, "KTK");
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.setFontPosTop();
    u8g2.drawStr(30, 38, "engineering");
  } while( u8g2.nextPage( ) );
}

//--------------------
// サーミスタ
//--------------------
const int R25C   = 10000; // R25℃ = Ω
const int B      = 3380;  // B定数
const float K    = 273.16; // ケルビン
const float C25  = K + 25; // 摂氏25度
// NTCサーミスタでの温度
float convert_temp_by_ntc(float r) {
  return B / (log(r/R25C) + (B/C25)) - K;
}

// 入力から抵抗値を求める(5V)
float resistance_by_input(int input) {
  float vout = input / 1023.0f * 5.0f; //分圧した出力電圧の計算
  float r = ( 5.0f / vout -1 ) * R25C; //サーミスタ抵抗計算
  return r;
}


//--------------------
// 水温計算
//--------------------
// 水温(摂氏)を取得
float get_water_temp(){
 input_for_temp = analogRead(SENSOR); 
 r = resistance_by_input(input_for_temp);
 water_temp = convert_temp_by_ntc(r);
 println_temp_log(r, water_temp);
 
 return water_temp;
}



// 水温補正
// 取得した値の直近10つの平均を表示する
float water_temps_avg(){
 float sum = 0;
 int count = COUNTOF(water_temp_history);
 for(int i = 0; i < count ; i++){ sum += water_temp_history[i]; }

 return sum / count;
}


//--------------------
// 油圧関連
//--------------------
// 油圧取得(Kpa)
float get_oil_pressure(){
  float vo = analogRead(PRESSURE_SENSOR) * 5.0f / 1023.0f;
  return 250 * (vo - 0.480) * 0.0101972;
}


//--------------------
// ディスプレイ表示
//--------------------
void display(float water_temp, float oil_pressure){
 char value[8];
 dtostrf(water_temp, 6, 1, value);
 
 u8g2.firstPage();
  do {
    u8g2.setFontPosTop();

    // 水温
    dtostrf(water_temp, 6, 1, value);
    u8g2.setFont( u8g2_font_tenthinguys_tf );
    u8g2.drawStr(0, 0, "WTR.T");
     u8g2.setFont( u8g2_font_tenthinguys_tf );
    u8g2.drawStr(0, 12, value);
    
    // 油圧
    dtostrf(oil_pressure, 6, 1, value);
    u8g2.setFont( u8g2_font_tenthinguys_tf );
    u8g2.drawStr(0, 30, "OIL.P");
     u8g2.setFont( u8g2_font_tenthinguys_tf );
    u8g2.drawStr(0, 42, value);

    
  } while( u8g2.nextPage() );
}


//--------------------
// Dev
//--------------------
// 開発用Log
float vo = 0;
void println_temp_log(float r, float temp){
  Serial.print("圧力: "); 
  vo = analogRead(PRESSURE_SENSOR) * 5.0f / 1023.0f;
  Serial.print(250 * (vo - 0.480) * 0.0101972); 
  Serial.println("kpa");   
  Serial.print("抵抗値: "); 
  Serial.println(r); 
  Serial.print("温度: "); 
  Serial.println(temp); 
}
