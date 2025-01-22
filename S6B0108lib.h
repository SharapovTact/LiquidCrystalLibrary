#pragma once
#include <Arduino.h>
#include <math.h>
class S6B0108 {
private:
	long _byte;
	long _byte2;
	short _ch;
	int _RS;
	int _RW;
	int _E;
	int _DB0;
	int _DB1;
	int _DB2;
	int _DB3;
	int _DB4;
	int _DB5;
	int _DB6;
	int _DB7;
	int _CSA;
	int _CSB;
	int _CSC;
	int _RST;
	void chipSelect(int chipNumber);//Выбор чипа (ДОДЕЛАТЬ)
	void chipDeSelect();//Отмена выбора чипа
	void enable();//Стробирующий сигнал
	void displayOn();//Включение отображения МК
	void writeData(int data);//ВРЕМЕННО вывод команды
	void writeData(int data, long data2);//data2 вводится ввиде binary числа и дизъюнктируется с data
	long byteRead();//Возвращает значение байта
	
public:
	S6B0108(int _RS, int _RW, int _E, int _DB0, int _DB1, int _DB2, int _DB3, int _DB4, int _DB5, int _DB6, int _DB7, int _CSA, int _CSB, int _CSC, int _RST) :
		_RS{ _RS }, _RW{ _RW }, _E{ _E }, _DB0{ _DB0 }, _DB1{ _DB1 }, _DB2{ _DB2 }, _DB3{ _DB3 }, _DB4{ _DB4 }, _DB5{ _DB5 }, _DB6{ _DB6 }, _DB7{ _DB7 }, _CSA{_CSA}, _CSB{_CSB}, _CSC{_CSC}, _RST{_RST} {};
	void initGLCD();//Инициализация дисплея
	void clearDisplay();//Очистка чипа
	void setPoint(int x, int y);
	void setLine(int x1, int y1, int x2, int y2);
	void reset();
	void rectangle(short x1, short y1, short x2, short y2);
	
};