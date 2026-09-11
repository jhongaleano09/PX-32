#pragma once
using byte = unsigned char;
constexpr int HIGH=1, LOW=0, INPUT=0, OUTPUT=1;
constexpr byte LED_BUILTIN=13;
constexpr byte A0=54, A1=55, A2=56, A3=57, A4=58;
inline void pinMode(int,int) {}
inline void digitalWrite(int,int) {}
inline int digitalRead(int) { return 0; }
inline void analogWrite(int,int) {}
inline void delay(unsigned long) {}
inline void delayMicroseconds(unsigned int) {}
inline unsigned long millis() { return 0; }
inline unsigned long pulseIn(int,int,unsigned long=1000000UL) { return 0; }
struct SerialStub {
  void begin(unsigned long) {}
  int available() { return 0; }
  char read() { return 0; }
  void write(char) {}
  template<class T> void print(const T&) {}
  template<class T> void println(const T&) {}
  void println() {}
};
inline SerialStub Serial, Serial1;
