import processing.serial.*;

Serial myPort;
String val;
void setup() {
  String portName = Serial.list()[32];
  /*[0] "/dev/ttyS0"
   [1] "/dev/ttyS1"
   ...
   [31] "/dev/ttyS31"
   [32] "/dev/ttyUSB0"
   */
  myPort = new Serial(this, portName, 9600);
}
void draw() {
  if ( myPort.available() > 0) {
    val = myPort.readStringUntil('\n');
    if (val != null)
      println(val);
  }
}
