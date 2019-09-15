const byte DS1307 = 0x68; //Địa chỉ của DS1307
const byte NumberOfFields = 7; //Số byte dữ liệu sẽ đọc từ DS1307
int second , minute , hour , day , wday , month , year;


void readDS1307()
{
  Wire.beginTransmission(DS1307);
  Wire.write((byte)0x00);
  Wire.endTransmission();
  Wire.requestFrom(DS1307, NumberOfFields);
 
  second = bcd2dec(Wire.read() & 0x7f);
  minute = bcd2dec(Wire.read() );
  hour   = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.
  wday   = bcd2dec(Wire.read() );
  day    = bcd2dec(Wire.read() );
  month  = bcd2dec(Wire.read() );
  year   = bcd2dec(Wire.read() );
  year += 2000;
}

int bcd2dec(byte num) {
  return ((num/16 * 10) + (num % 16));
}

int dec2bcd(byte num) {
  return ((num/10 * 16) + (num % 10));
}

void setTime(byte hr, byte mn, byte sec, byte wd, byte d, byte mth, byte yr)
{
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x00)); // đặt lại pointer
  Wire.write(dec2bcd(sec));
  Wire.write(dec2bcd(mn));
  Wire.write(dec2bcd(hr));
  Wire.write(dec2bcd(wd)); // day of week: Sunday = 1, Saturday = 7
  Wire.write(dec2bcd(d));
  Wire.write(dec2bcd(mth));
  Wire.write(dec2bcd(yr));
  Wire.endTransmission();
}

void serialClock() {
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.print(second);
  Serial.print(" ");
  Serial.print(day);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.print(year); 
  Serial.println(); 
}
