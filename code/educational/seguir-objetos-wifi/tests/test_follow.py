#!/usr/bin/env python3
"""Compile the real sketch and exercise F6 with simulated sensors/motors.

Requires arduino-cli (AVR core, Servo, WiFiEsp) and clang++ or g++.
No serial port is opened and no physical motor is commanded.
"""
from pathlib import Path
import shutil
import subprocess
import tempfile

SKETCH = Path(__file__).resolve().parents[1]

ARDUINO = r'''
#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <deque>
#include <functional>
#include <vector>
using byte = uint8_t;
constexpr int LOW=0, HIGH=1, INPUT=0, OUTPUT=1;
constexpr int A0=54, A1=55, A2=56, A3=57, A4=58;
inline unsigned long testNow=1000;
inline int testPins[128]={}, testPwm[128]={};
inline unsigned long testEcho=466;
inline std::deque<unsigned long> testEchoes;
inline int testMeasurements=0;
inline int testMovingMeasurements=0, testStopWrites=0;
inline std::function<void()> duringMeasurement;
inline unsigned long millis() { return testNow; }
inline void delay(unsigned long ms) { testNow+=ms; }
inline void delayMicroseconds(unsigned int) {}
inline void pinMode(int,int) {}
inline void digitalWrite(int p,int v) { testPins[p]=v; }
inline int digitalRead(int p) { return testPins[p]; }
inline void analogWrite(int p,int v) { testPwm[p]=v; if (!v) ++testStopWrites; }
inline unsigned long pulseIn(int,int,unsigned long) {
  if (testPwm[9] || testPwm[10] || testPwm[11] || testPwm[12]) ++testMovingMeasurements;
  ++testMeasurements;
  if (duringMeasurement) duringMeasurement();
  unsigned long result=testEcho;
  if (!testEchoes.empty()) { result=testEchoes.front(); testEchoes.pop_front(); }
  testNow+=result ? 1 : 30;
  return result;
}
template<class T> T constrain(T x,T lo,T hi) { return std::min(hi,std::max(lo,x)); }
struct FakeSerial {
  void begin(unsigned long) {}
  int available() { return 0; }
  int read() { return -1; }
  template<class T> void print(T) {}
  template<class T> void println(T) {}
  void print(float,int) {}
};
inline FakeSerial Serial,Serial1;
'''

SERVO = r'''
#pragma once
struct Servo {
  bool active=false;
  int angle=-1;
  bool attached() { return active; }
  void attach(int) { active=true; }
  void detach() { active=false; }
  void write(int a) { angle=a; }
};
'''

WIFI = r'''
#pragma once
constexpr int WL_NO_SHIELD=255,WL_CONNECTED=3,ENC_TYPE_WPA2_PSK=4;
struct FakeWiFi {
  void init(void*) {}
  int status() { return WL_CONNECTED; }
  int beginAP(char*,int,char*,int) { return WL_CONNECTED; }
  const char* localIP() { return "192.168.4.1"; }
};
inline FakeWiFi WiFi;
'''

UDP = r'''
#pragma once
#include <Arduino.h>
struct WiFiEspUDP {
  std::deque<std::vector<uint8_t>> packets;
  bool failRead=false;
  int begin(unsigned int) { return 1; }
  int parsePacket() { return packets.empty() ? 0 : packets.front().size(); }
  int read(uint8_t* target,int capacity) {
    if (packets.empty()) return 0;
    auto packet=packets.front(); packets.pop_front();
    if (failRead) return 0;
    int size=std::min(capacity,int(packet.size()));
    std::copy_n(packet.begin(),size,target); return size;
  }
};
'''

TEST = r'''
#include <iostream>
#include "SKETCH_CPP"
bool stopped() { return !testPwm[9] && !testPwm[10] && !testPwm[11] && !testPwm[12]; }
void mask(byte value) {
  testPins[SENSOR_IR_IZQUIERDO]=(value&1) ? LOW : HIGH;
  testPins[SENSOR_IR_DERECHO]=(value&2) ? LOW : HIGH;
}
void distance(float cm) { testEcho=static_cast<unsigned long>(cm*2/SONIDO_CM_POR_US); }
void reset(byte value=3) {
  std::fill_n(testPins,128,HIGH); std::fill_n(testPwm,128,0);
  testNow=1000; testMeasurements=0; testMovingMeasurements=0; testStopWrites=0;
  testEchoes.clear(); duringMeasurement=nullptr;
  controlUdp.packets.clear(); controlUdp.failRead=false;
  wifiListo=true; modoAutonomoWifi=false; modoSeguidorLineaWifi=false;
  modoSeguidorObjetoWifi=false; sistemaArmado=false;
  distance(8.5); mask(value); aceptarOrdenWifi('K');
  assert(stopped() && modoSeguidorObjetoWifi && cabeza.angle==90);
}
void firstSample() {
  ejecutarSeguidorObjeto();
  assert(stopped() && testMeasurements==0);
  testNow+=ESTABILIDAD_IR_OBJETO_MS;
  ejecutarSeguidorObjeto();
}
void nextSample() { testNow+=INTERVALO_MEDICION_OBJETO_MS; ejecutarSeguidorObjeto(); }
void startMoving() {
  firstSample(); assert(stopped() && confirmacionesObjeto==1);
  nextSample(); assert(stopped() && confirmacionesObjeto==2);
  nextSample(); assert(!stopped() && confirmacionesObjeto==3);
}
int main() {
  // No automatic movement at startup.
  std::fill_n(testPins,128,HIGH); setup(); assert(stopped());
  assert(!modoSeguidorObjetoWifi && !sistemaArmado);

  reset(); startMoving();
  assert(testMeasurements==3);
  assert(testPwm[9]==125 && testPwm[10]==125 && testPwm[11]==125 && testPwm[12]==125);
  assert(testPins[BK1_IN1]==HIGH && testPins[BK3_IN3]==HIGH);
  assert(testPins[AK3_IN3]==HIGH && testPins[AK3_IN4]==LOW);
  auto previousMeasurement=ultimaMedicionObjetoMs;
  aceptarOrdenWifi('K'); assert(ultimaMedicionObjetoMs==previousMeasurement && !stopped());
  auto beforeStops=testStopWrites;
  for (int step=0;step<100;++step) {
    testNow+=15; ejecutarSeguidorObjeto();
    assert(!stopped() && testPwm[9]==125 && testPwm[10]==125 && testPwm[11]==125 && testPwm[12]==125);
  }
  assert(testStopWrites==beforeStops && testMovingMeasurements>10);

  reset(1); startMoving();
  assert(!stopped() && testPins[BK1_IN1]==HIGH && testPins[BK3_IN3]==LOW);
  assert(testPwm[9]==125 && testPwm[10]==125 && testPwm[11]==125 && testPwm[12]==125);
  reset(2); startMoving();
  assert(!stopped() && testPins[BK1_IN1]==LOW && testPins[BK3_IN3]==HIGH);
  assert(testPwm[9]==125 && testPwm[10]==125 && testPwm[11]==125 && testPwm[12]==125);

  reset(0); firstSample(); assert(stopped() && testMeasurements==0);
  reset(); startMoving(); mask(0); ejecutarSeguidorObjeto();
  assert(stopped() && confirmacionesObjeto==0);
  mask(1); ejecutarSeguidorObjeto(); assert(stopped());
  nextSample(); assert(stopped()); nextSample(); assert(stopped());
  nextSample(); assert(!stopped() && testPins[BK3_IN3]==LOW);

  // Side changes retain movement while filtering the new direction.
  reset(); startMoving(); beforeStops=testStopWrites;
  mask(1); ejecutarSeguidorObjeto(); assert(!stopped() && direccionObjeto==3);
  nextSample(); assert(!stopped() && direccionObjeto==1 && testPins[BK3_IN3]==LOW);
  assert(testStopWrites==beforeStops);

  reset(); distance(6.9); firstSample(); assert(stopped() && objetoDemasiadoCerca);
  distance(7.5); nextSample(); assert(stopped());
  distance(8.1); nextSample(); assert(stopped()); nextSample(); assert(stopped());
  nextSample(); assert(!stopped());
  distance(7.5); nextSample(); assert(!stopped());
  distance(6.9); nextSample(); assert(stopped());

  reset(); testEcho=0; firstSample(); assert(stopped());
  assert(ultimoEstadoObjeto=='N'); ejecutarSeguidorObjeto(); assert(ultimoEstadoObjeto=='N');
  reset(); testEchoes={495,0,495}; firstSample(); assert(stopped());
  nextSample(); assert(stopped() && confirmacionesObjeto==0);
  nextSample(); assert(stopped() && confirmacionesObjeto==1);
  reset(); distance(12.1); firstSample(); assert(stopped());
  reset(); sistemaArmado=false; firstSample(); assert(stopped() && testMeasurements==0);

  // A single bad/close reading stops a moving robot; no median delay.
  for (float cm : {6.9f,12.1f}) {
    reset(); startMoving(); distance(cm); nextSample(); assert(stopped());
  }
  reset(); startMoving(); testEcho=0; nextSample(); assert(stopped());

  // A queued STOP during measurement cancels startup or current movement.
  reset(); duringMeasurement=[] {
    if (testMeasurements==1) controlUdp.packets.push_back({'E'});
  };
  firstSample(); assert(stopped() && !modoSeguidorObjetoWifi && !sistemaArmado);
  assert(confirmacionesObjeto==0);
  reset(); startMoving();
  duringMeasurement=[] { controlUdp.packets.push_back({'E'}); };
  nextSample(); assert(stopped() && !modoSeguidorObjetoWifi);

  // Losing the IR target during measurement also prevents movement.
  reset(); duringMeasurement=[] { mask(0); };
  firstSample(); assert(stopped());
  reset(); startMoving(); duringMeasurement=[] { mask(0); };
  nextSample(); assert(stopped());

  // Direction filtering cannot bypass a simultaneous dangerous echo.
  reset(); startMoving(); distance(6.9);
  duringMeasurement=[] { mask(1); }; nextSample(); assert(stopped());

  // STOP remains latched even if the box stays visible.
  reset(); startMoving(); aceptarOrdenWifi('E');
  assert(stopped() && !modoSeguidorObjetoWifi && !sistemaArmado);
  ejecutarOrdenWifi(); assert(stopped());
  for (char command : {'F','G','H','I','J','A','B','L','R','?'}) {
    reset(); startMoving(); aceptarOrdenWifi(command);
    assert(stopped() && !modoSeguidorObjetoWifi);
    if (command=='I') assert(modoAutonomoWifi && !modoSeguidorLineaWifi);
    if (command=='J') assert(!modoAutonomoWifi && modoSeguidorLineaWifi);
  }
  reset(); startMoving(); controlUdp.failRead=true;
  controlUdp.packets.push_back({'K'}); recibirOrdenWifi();
  assert(stopped() && !modoSeguidorObjetoWifi && !sistemaArmado);
  reset(); aceptarOrdenWifi('E'); controlUdp.packets.push_back({'k'});
  recibirOrdenWifi(); assert(modoSeguidorObjetoWifi && stopped());
  std::cout << "PASS: continuous F6, equal PWM, live sonar, direction filter, hysteresis, target loss, STOP and mode transitions\n";
}
'''


def main():
    compiler = shutil.which('clang++') or shutil.which('g++')
    if not compiler:
        raise SystemExit('clang++ or g++ is required')
    with tempfile.TemporaryDirectory(prefix='osoyoo-follow-tests-') as directory:
        root = Path(directory)
        build = root / 'build'
        subprocess.run(['arduino-cli', 'compile', '--fqbn', 'arduino:avr:mega',
                        '--build-path', str(build), str(SKETCH)], check=True)
        generated = build / 'sketch' / (SKETCH.name + '.ino.cpp')
        for name, content in [('Arduino.h', ARDUINO), ('Servo.h', SERVO),
                              ('WiFiEsp.h', WIFI), ('WiFiEspUdp.h', UDP)]:
            (root / name).write_text(content)
        harness = root / 'test.cpp'
        harness.write_text(TEST.replace('SKETCH_CPP', str(generated)))
        binary = root / 'test'
        subprocess.run([compiler, '-std=c++17', '-I', str(root), str(harness),
                        '-o', str(binary)], check=True)
        subprocess.run([str(binary)], check=True)


if __name__ == '__main__':
    main()
