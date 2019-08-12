//
// Thermometer by Defi sensor
//
const int SENSOR = 0; 

int input_for_temp = 0;// 温度用入力抵抗値
float r = 0; // 抵抗値
float temp = 0; // 温度

void setup() {
 Serial.begin(9600);   
}

void loop() {
 input_for_temp = analogRead(SENSOR); 
 r = resistance_by_input(input_for_temp);
 temp = convert_temp_by_ntc(r);

 // Logs
 Serial.print("入力値: "); 
 Serial.println(input_for_temp); 
 Serial.print("抵抗値: "); 
 Serial.println(r); 
 Serial.print("温度: "); 
 Serial.println(temp); 

 delay(1000); 
}

// NTCサーミスタでの温度
const int R25C   = 10000; // R25℃ = Ω
const int B      = 3380;  // B定数
const float K    = 273.16; // ケルビン
const float C25  = K + 25; // 摂氏25度
float convert_temp_by_ntc(float r) {
  return B / (log(r/R25C) + (B/C25)) - K;
}

// 入力から抵抗値を求める(5V)
float resistance_by_input(int input) {
  float vout = input / 1023.0f * 5.0f; //分圧した出力電圧の計算
  float r = ( 5.0f / vout -1 ) * R25C; //サーミスタ抵抗計算
  return r;
}
