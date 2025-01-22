#include "S6B0108lib.h"
long long power(int ch, int power){
    long long a = 1;
	for(int i = 0; i < power; i++){
		a *= ch;
	}
	return a;
}
bool intToBool(int a){
	if(a == 1) return true;
	else return false;
}
void S6B0108::reset(){
	delay(1);
	digitalWrite(_RST, true);
	delay(1);
	digitalWrite(_RST, false);
	delay(1);
	digitalWrite(_RST, true);
}
void S6B0108::initGLCD() {
	pinMode(_RW, true);
	pinMode(_RS, true);
	pinMode(_E, true);

	pinMode(_DB0, true);
	pinMode(_DB1, true);
	pinMode(_DB2, true);
	pinMode(_DB3, true);
	pinMode(_DB4, true);
	pinMode(_DB5, true);
	pinMode(_DB6, true);
	pinMode(_DB7, true);

	pinMode(_CSA, true);
	pinMode(_CSB, true);
	pinMode(_CSC, true);
	pinMode(_RST, true);

	chipDeSelect();

	reset();

	digitalWrite(_E, true);

	displayOn();//ЧИП
	//setDisplayStartLineZ();
}
void S6B0108::enable() {
	delayMicroseconds(1);
	digitalWrite(_E, true);
	delayMicroseconds(1);
	digitalWrite(_E, false);
	delayMicroseconds(1);
	digitalWrite(_E, true);
	
		digitalWrite(_DB0, 0);
		digitalWrite(_DB1, 0);
		digitalWrite(_DB2, 0);
		digitalWrite(_DB3, 0);
		digitalWrite(_DB4, 0);
		digitalWrite(_DB5, 0);
		digitalWrite(_DB6, 0);
		digitalWrite(_DB7, 0);
		digitalWrite(_RW, 0);
		digitalWrite(_RS, 0);
}
void S6B0108::chipSelect(int chipNumber) {
	int chipData = 0;
	int ch = 0;
	while(chipNumber > 0){
        chipData += (chipNumber % 2) * power(10, ch);
        ch++;
        chipNumber /= 2;
    }
	digitalWrite(_CSA, intToBool(chipData % 10));
	chipData /= 10;
	digitalWrite(_CSB, intToBool(chipData % 10));
	chipData /= 10;
	digitalWrite(_CSC, intToBool(chipData % 10));
	chipData /= 10;
}
void S6B0108::chipDeSelect() {
	digitalWrite(_CSC, true);
	digitalWrite(_CSB, false);
	digitalWrite(_CSA, false);
}
void S6B0108::displayOn() {
	for(int i = 0; i < 4; i++){
		chipSelect(i);
		digitalWrite(_RS, false);
		digitalWrite(_RW, false);
		digitalWrite(_DB7, false);
		digitalWrite(_DB6, false);
		digitalWrite(_DB5, true);
		digitalWrite(_DB4, true);
		digitalWrite(_DB3, true);
		digitalWrite(_DB2, true);
		digitalWrite(_DB1, true);
		digitalWrite(_DB0, true);
		enable();
	}	
}
long S6B0108::byteRead(){
	_byte = 1000000000;
	//открываем на чтение
	pinMode(_DB0, INPUT);
	pinMode(_DB1, INPUT);
	pinMode(_DB2, INPUT);
	pinMode(_DB3, INPUT);
	pinMode(_DB4, INPUT);
	pinMode(_DB5, INPUT);
	pinMode(_DB6, INPUT);
	pinMode(_DB7, INPUT);
	
	digitalWrite(_RS, true);
	digitalWrite(_RW, true);
	enable();
	_ch = 0;
	//Serial.println(digitalRead(_DB0));
	_byte += digitalRead(_DB0) * power(10, _ch);
	_ch++;
	_byte += digitalRead(_DB1) * power(10, _ch);
	_ch++;
	_byte += digitalRead(_DB2) * power(10, _ch);
	_ch++;
	_byte += digitalRead(_DB3) * power(10, _ch);
	_ch++;
	_byte += digitalRead(_DB4) * power(10, _ch);
	_ch++;
	_byte += digitalRead(_DB5) * power(10, _ch);
	_ch++;
	_byte += digitalRead(_DB6) * power(10, _ch);
	_ch++;
	_byte += digitalRead(_DB7) * power(10, _ch);
	
	pinMode(_DB0, true);
	pinMode(_DB1, true);
	pinMode(_DB2, true);
	pinMode(_DB3, true);
	pinMode(_DB4, true);
	pinMode(_DB5, true);
	pinMode(_DB6, true);
	pinMode(_DB7, true);
	
	return _byte;
	
	
}
void S6B0108::writeData(int data) {
	long binaryData = 0;
	int ch = 0;
	while(data > 0){//Перевод в двоичку
        binaryData += (data % 2) * power(10, ch);
         //Serial.println((data % 2) * power(10, ch));
        ch++;
        data /= 2;
    }
		digitalWrite(_DB0, intToBool(binaryData % 10));
		binaryData /= 10;
		digitalWrite(_DB1, intToBool(binaryData % 10));
		binaryData /= 10;
		digitalWrite(_DB2, intToBool(binaryData % 10));
		binaryData /= 10;
		digitalWrite(_DB3, intToBool(binaryData % 10));
		binaryData /= 10;
		digitalWrite(_DB4, intToBool(binaryData % 10));
		binaryData /= 10;
		digitalWrite(_DB5, intToBool(binaryData % 10));
		binaryData /= 10;
		digitalWrite(_DB6, intToBool(binaryData % 10));
		binaryData /= 10;
		digitalWrite(_DB7, intToBool(binaryData % 10));
		binaryData /= 10;
		digitalWrite(_RW, intToBool(binaryData % 10));
		binaryData /= 10;
		digitalWrite(_RS, intToBool(binaryData % 10));
		enable();
		
		
}
void S6B0108::writeData(int data, long data2){
	_byte = 0;
	_byte2 = 0;
	int ch = 0;
	while(data > 0){//Перевод в двоичку
        _byte += (data % 2) * power(10, ch);
         //Serial.println((data % 2) * power(10, ch));
        ch++;
        data /= 2;
    }
    for(short i = 0; i < 10; i++){ //дизъюнкция
        _byte2 += ((data2 % 10) || (_byte % 10)) * power(10, i);
        data2 /= 10;
        _byte /= 10;
        
    }
    
    
		digitalWrite(_DB0, intToBool(_byte2 % 10));
		_byte2 /= 10;
		digitalWrite(_DB1, intToBool(_byte2 % 10));
		_byte2 /= 10;
		digitalWrite(_DB2, intToBool(_byte2 % 10));
		_byte2 /= 10;
		digitalWrite(_DB3, intToBool(_byte2 % 10));
		_byte2 /= 10;
		digitalWrite(_DB4, intToBool(_byte2 % 10));
		_byte2 /= 10;
		digitalWrite(_DB5, intToBool(_byte2 % 10));
		_byte2 /= 10;
		digitalWrite(_DB6, intToBool(_byte2 % 10));
		_byte2 /= 10;
		digitalWrite(_DB7, intToBool(_byte2 % 10));
		_byte2 /= 10;
		digitalWrite(_RW, intToBool(_byte2 % 10));
		_byte2 /= 10;
		digitalWrite(_RS, intToBool(_byte2 % 10));
		enable();
		
	
}
void S6B0108::clearDisplay(){ //Очищает чип
	for(int chip = 0; chip < 4; chip++){
		chipSelect(chip);
		for (int i = 0b0010111000; i <= 0b0010111111; i++){
		
			writeData(i);//Ввод Page X
			for (int _ = 0; _ < 64; _++) {
				
				writeData(0b1000000000);
				
			}
		}
	}
}
void S6B0108::setPoint(int x, int y){
	int chip;
	if(x <= 64) chip = 0;
	else if(x <= 128) chip = 1;
	else if(x <= 192) chip = 2;
	else chip = 3;
	
	int page;
	if(y <= 8) page = 0b0010111000;
	else if(y <= 16) page = 0b0010111001;
	else if (y <= 24) page = 0b0010111010;
	else if (y <= 32) page = 0b0010111011;
	else if (y <= 40) page = 0b0010111100;
	else if (y <= 48) page = 0b0010111101;
	else if (y <= 56) page = 0b0010111110;
	else page = 0b0010111111;
	
	chipSelect(chip);
	writeData(page);
	
	int xCurrect = (x - 1) % 64;
	int yCurrect = (y - 1) % 8;
	
	writeData(0b0001000000 + xCurrect);
	_byte = byteRead();
	//Serial.println(_byte);
	writeData(0b0001000000 + xCurrect);
	
	writeData(0b1000000000 + power(2, yCurrect), _byte);
	
	//chipDeSelect();
	
}

void S6B0108::setLine(int x1, int y1, int x2, int y2){
	float L; //Кол-во шагов цикла расторизации
	if (abs(x2 - x1) > abs(y2 - y1)) L = abs(x2 - x1); 
	else if (abs(x2 - x1) == abs(y2 - y1)) L = abs(x2 - x1);
	else L = abs(y2 - y1);
	L++;
	
	float x = x1;
	float y = y1;
	setPoint(x1, y1);
	for(short i = 0; i < L; i++){
		x += (x2 - x1) / L;
		y += (y2 - y1) / L;
		
		setPoint(round(x), round(y));
	}
	
	
	
}
void S6B0108::rectangle(short x1, short y1, short x2, short y2){
	this->setLine(x1, y1, x2, y1);//Нижняя грань
	this->setLine(x2,y1,x2,y2);//Правая грань
	this->setLine(x1, y2, x2, y2);//Верхняя грань
	this->setLine(x1,y1,x1,y2);//Левая грань
}
