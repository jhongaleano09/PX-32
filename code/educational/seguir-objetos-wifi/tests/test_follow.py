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
inline std::function<void()> duringMeasurement;
inline unsigned long millis() { return testNow; }
inline void delay(unsigned long ms) { testNow+=ms; }
inline void delayMicroseconds(unsigned int) {}
inline void pinMode(int,int) {}
inline void digitalWrite(int p,int v) { testPins[p]=v; }
inline int digitalRead(int p) { return testPins[p]; }
inline void analogWrite(int p,int v) { testPwm[p]=v; }
inline unsigned long pulseIn(int,int,unsigned long) {
  // Every F6 ultrasonic sample must happen with all motors stopped.
  assert(!testPwm[9] && !testPwm[10] && !testPwm[11] && !testPwm[12]);
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
  testNow=1000; testMeasurements=0; testEchoes.clear(); duringMeasurement=nullptr;
  controlUdp.packets.clear(); controlUdp.failRead=false;
  wifiListo=true; modoAutonomoWifi=false; modoSeguidorLineaWifi=false;
  modoSeguidorObjetoWifi=false; sistemaArmado=false;
  distance(8); mask(value); aceptarOrdenWifi('K');
  assert(stopped() && modoSeguidorObjetoWifi && cabeza.angle==90);
}
void firstSample() {
  ejecutarSeguidorObjeto();
  assert(stopped() && testMeasurements==0);
  testNow+=PAUSA_OBJETO_MS;
  ejecutarSeguidorObjeto();
}
void finishPulse() {
  testNow+=IMPULSO_OBJETO_MS;
  ejecutarSeguidorObjeto();
  assert(stopped() && !impulsoObjetoActivo);
}
void nextSample() { testNow+=PAUSA_OBJETO_MS; ejecutarSeguidorObjeto(); }
int main() {
  // No automatic movement at startup.
  std::fill_n(testPins,128,HIGH); setup(); assert(stopped());
  assert(!modoSeguidorObjetoWifi && !sistemaArmado);

  reset(); firstSample();
  assert(impulsoObjetoActivo && testMeasurements==3);
  assert(testPwm[9]==100 && testPwm[10]==90 && testPwm[11]==85 && testPwm[12]==95);
  assert(testPins[BK1_IN1]==HIGH && testPins[BK3_IN3]==HIGH);
  assert(testPins[AK3_IN3]==HIGH && testPins[AK3_IN4]==LOW);
  auto pulseStart=inicioImpulsoObjetoMs;
  aceptarOrdenWifi('K'); assert(inicioImpulsoObjetoMs==pulseStart);
  testNow+=IMPULSO_OBJETO_MS-1; ejecutarSeguidorObjeto(); assert(!stopped());
  ++testNow; ejecutarSeguidorObjeto(); assert(stopped());
  assert(testMeasurements==3);
  testNow+=PAUSA_OBJETO_MS-1; ejecutarSeguidorObjeto(); assert(testMeasurements==3);
  ++testNow; ejecutarSeguidorObjeto(); assert(!stopped() && testMeasurements==6);

  reset(1); firstSample();
  assert(!stopped() && testPins[BK1_IN1]==HIGH && testPins[BK3_IN3]==LOW);
  reset(2); firstSample();
  assert(!stopped() && testPins[BK1_IN1]==LOW && testPins[BK3_IN3]==HIGH);

  reset(0); firstSample(); assert(stopped() && testMeasurements==0);
  reset(); firstSample(); mask(0); ejecutarSeguidorObjeto();
  assert(stopped() && !impulsoObjetoActivo);
  mask(1); ejecutarSeguidorObjeto(); assert(stopped());
  nextSample(); assert(!stopped() && testPins[BK3_IN3]==LOW);

  reset(); distance(5.9); firstSample(); assert(stopped() && objetoDemasiadoCerca);
  distance(6.5); nextSample(); assert(stopped());
  distance(7.1); nextSample(); assert(!stopped());
  finishPulse(); distance(6.5); nextSample(); assert(!stopped());
  finishPulse(); distance(5.9); nextSample(); assert(stopped());

  reset(); testEcho=0; firstSample(); assert(stopped());
  reset(); testEchoes={466,0,466}; firstSample(); assert(stopped());
  reset(); distance(12.1); firstSample(); assert(stopped());
  reset(); sistemaArmado=false; firstSample(); assert(stopped() && testMeasurements==0);

  // A queued STOP during measurement must prevent the next motor impulse.
  reset(); duringMeasurement=[] {
    if (testMeasurements==1) controlUdp.packets.push_back({'E'});
  };
  firstSample(); assert(stopped() && !modoSeguidorObjetoWifi && !sistemaArmado);
  assert(!impulsoObjetoActivo);

  // Losing the IR target during measurement also prevents movement.
  reset(); duringMeasurement=[] { mask(0); };
  firstSample(); assert(stopped());

  // STOP remains latched even if the box stays visible.
  reset(); firstSample(); aceptarOrdenWifi('E');
  assert(stopped() && !modoSeguidorObjetoWifi && !sistemaArmado);
  ejecutarOrdenWifi(); assert(stopped());
  for (char command : {'F','G','H','I','J','A','B','L','R','?'}) {
    reset(); firstSample(); aceptarOrdenWifi(command);
    assert(stopped() && !modoSeguidorObjetoWifi);
    if (command=='I') assert(modoAutonomoWifi && !modoSeguidorLineaWifi);
    if (command=='J') assert(!modoAutonomoWifi && modoSeguidorLineaWifi);
  }
  reset(); firstSample(); controlUdp.failRead=true;
  controlUdp.packets.push_back({'K'}); recibirOrdenWifi();
  assert(stopped() && !modoSeguidorObjetoWifi && !sistemaArmado);
  reset(); aceptarOrdenWifi('E'); controlUdp.packets.push_back({'k'});
  recibirOrdenWifi(); assert(modoSeguidorObjetoWifi && stopped());
  std::cout << "PASS: F6 direction, pulses, hysteresis, invalid echoes, target loss, STOP and mode transitions\n";
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
