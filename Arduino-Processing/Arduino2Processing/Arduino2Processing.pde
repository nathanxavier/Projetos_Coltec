import processing.serial.*;

Serial myPort;
String val;
void setup()
{
  // String portName = "COMx";            // Descomente essa linha caso esteja utilizando Windows
                                          // e indique o número da COM utilizada pelo Arduino
  String portName = Serial.list()[32]; // Descomente essa linha caso esteja utilizando Linux
  /*[0] "/dev/ttyS0"
   [1] "/dev/ttyS1"
   ...
   [31] "/dev/ttyS31"
   [32] "/dev/ttyUSBx"
   */
  myPort = new Serial(this, portName, 300);
}
void draw()
{
  if ( myPort.available() > 0) 
  {
    val = myPort.readStringUntil('\n');
  } 
  println(val);
}
