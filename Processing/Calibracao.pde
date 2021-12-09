import processing.serial.*;

Serial myPort;
int nValue = 100, nSens = 0;
float[] sensValue, sensMean;
float[][] sensVec;

int meanPos = 0;
boolean fDrawLine = false, fDrawPoint = false;
float lineX = 0, lineY = 0, lineZ = 0;  //Linha
float pointX, pointY, pointZ;
float posMeansensX, posMeansensY, posMeansensZ;

void setup() {
  // Janela
  fullScreen();
  stroke(255);
  background(0);
  noSmooth();

  String portName = Serial.list()[32];
  myPort = new Serial(this, portName, 9600);

  print("Configuração do Sensor");
}

void draw() {
  //Cálculo da Média
  if (meanPos == nValue) {
    println("\nSensor Calibrado");
    for (int i=0; i<3; i++) {
      for (int j=0; j<nValue; j++) {
        sensMean[i] += sensVec[i][j];
      }
      meanPos++;
    }
  }

  // Plano Cartesiano
  if (fDrawLine) {
    background(0);

    float posLineX = map(lineX, -2, 2, 0, height);
    float posLineY = map(lineY, -2, 2, 0, width);

    line(0, posLineX, width, posLineX); //Posição X    
    line(posLineY, 0, posLineY, height); //Posição Y;

    fDrawLine = false;
  } else if (fDrawPoint) {
    pointX = (sensValue[0]-sensMean[0]);
    pointY = (sensValue[1]-sensMean[1]);
    pointZ = (sensValue[1]-sensMean[2]);

    float posLineX = map(pointX, -2, 2, 0, width);
    float posLineY = map(pointY, -2, 2, 0, height);
    float posLineZ = map(pointZ, -2, 2, 1, 10);

    circle(posLineX, posLineY, posLineZ);

    fDrawPoint = false;
  }
}

void serialEvent(Serial myPort) {
  try {
    String inString = myPort.readStringUntil('\n');
    //println(inString);
    float[] inValue = float(split(inString, " "));
    if (inValue[0] == 0 && nSens == 0 && !Float.isNaN(inValue[0])) {
      if (inValue[1] > 2 && inValue[1] == (inValue.length-2) && !Float.isNaN(inValue[1]) && nSens == 0) {
        nSens = (inValue.length-2);
        if (nSens >3) {
          nSens = 0;
          println("\nXxX MAX 3 VARIÁVEIS XxX");
          delay(1000);
          return;
        }
        sensValue = new float[nSens];
        sensMean = new float[nSens];
        sensVec = new float[nSens][nValue];

        //map(inValue[i+2], -0x8000, 0x7FFF, -2, 2);    //Indicar valores Menores e Maiores via Serial
        println("\nCalibrando Sensor");
      } else {
        println("\nXxX ERRO DE COMUNICAÇÃO XxX");
        delay(1000);
        return;
      }
    } else if (inString != null && nSens == int(inValue[1]) && !Float.isNaN(inValue[2]) && !Float.isNaN(inValue[3]) && !Float.isNaN(inValue[4])) {
      for (int i = 0; i<nSens; i++)
        sensValue[i] = map(inValue[i+2], -0x8000, 0x7FFF, -2, 2);    //Indicar valores Menores e Maiores via Serial

      if (meanPos < nValue) {
        for (int i = 0; i<nSens; i++)
          sensVec[i][meanPos] = sensValue[i]/nValue;
        meanPos++;


        switch (nSens) {
        case 3:
          lineZ = (lineZ*(meanPos-1)+sensValue[2])/meanPos;
        case 2:
          lineY = (lineY*(meanPos-1)+sensValue[1])/meanPos;
        case 1:
          lineX = (lineX*(meanPos-1)+sensValue[0])/meanPos;
        }

        print(".");

        fDrawLine = true;
      } else
        fDrawPoint = true;
    } else {
      println("\nXxX ERRO DE COMUNICAÇÃO XxX");
      delay(1000);
      return;
    }
  }
  catch (Exception e) {
    return;
  }
}
