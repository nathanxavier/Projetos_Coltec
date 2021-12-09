#include <Servo.h>
int pos, data;
String message = "";
bool messageComplete;

#define cPeEsq 60
#define cPeDir 110
#define bPeEsq 180
#define bPeDir 0

#define MaxPeDir 150
#define MinPeDir 0
#define MaxPeEsq 180
#define MinPeEsq 30

class ZOWI {
  public:
    Servo PeEsq, PnEsq, PeDir, PnDir;
    int posPeEsq = 110, posPnEsq = 110, posPeDir = 70, posPnDir = 60;
    //    int cPeEsq = 60, cPeDir = 110;
    //    int bPeEsq = 180, bPeDir = 0;

    void PosNeutro() {
      posPeDir = 60;
      posPeEsq = 110;
      posPnDir = 60;
      posPnEsq = 110;

      MoveMotor(PeDir, posPeDir);
      MoveMotor(PeEsq, posPeEsq);
      MoveMotor(PnDir, posPnDir);
      MoveMotor(PnEsq, posPnEsq);
    }

    void Bye(char Side) {
      PosNeutro();

      if (Side == 'E') {
        LevantaEsq();
        Wave(PeDir, MaxPeDir, MinPeDir);
        Wave(PeDir, MaxPeDir, MinPeDir);
      }
      else {
        LevantaDir();
        Wave(PeEsq, MinPeEsq, MaxPeEsq);
        Wave(PeEsq, MinPeEsq, MaxPeEsq);

      }
    }

    void LevantaEsq() {
      while (posPeDir > bPeDir || posPeEsq > cPeEsq) {
        posPeDir = (posPeDir > bPeDir) ? posPeDir - 10 : bPeDir;
        posPeEsq = (posPeEsq > cPeEsq) ? posPeEsq - 5 : cPeEsq;

        MoveMotor(PeDir, posPeDir);
        MoveMotor(PeEsq, posPeEsq);
      }
    }

    void LevantaDir() {
      while (posPeDir < cPeDir || posPeEsq < bPeEsq) {
        posPeDir = (posPeDir < cPeDir) ? posPeDir + 5 : cPeDir ;
        posPeEsq = (posPeEsq < bPeEsq ) ? posPeEsq + 10 : bPeEsq;

        MoveMotor(PeDir, posPeDir);
        MoveMotor(PeEsq, posPeEsq);
      }
    }

    void Wave(Servo Motor, int Pos1, int Pos2) {
      MoveMotor(Motor, Pos1);
      delay(300);
      MoveMotor(Motor, Pos2);
      delay(300);
    }
    void MoveMotor(Servo Motor, int Pos) {
      Motor.write(Pos);
      delay(50);
    }
  private:

} Robo;

void setup() {
  Serial.begin(9600);

  Robo.PeDir.attach(11);  //Min(B) = 0; Max(C) = 150
  Robo.PnDir.attach(10);  //Min(F) = 0; Max(T) = 120
  Robo.PeEsq.attach(6);   //Min(C) = 30; Max(B) = 180
  Robo.PnEsq.attach(5);   //Min(T) = 50; Max(F) = 160

  Robo.PosNeutro();
}

void loop() {
  Robo.Bye('E');
  delay(1000);
  Robo.Bye('D');
  delay(1000);

  if (messageComplete) {
    messageComplete = 0;

    pos = message.toInt();

    Serial.print("Comando:");
    Serial.println(pos);

    //    Robo.MoveMotor(Robo.PeDir, pos);
    //    Robo.MoveMotor(Robo.PnDir, pos);
    //    Robo.MoveMotor(Robo.PeEsq, pos);
    //    Robo.MoveMotor(Robo.PnEsq, pos);

    message = "";
  }

}

void serialEvent() {
  while (Serial.available()) {
    data = Serial.read();
    message += (char)data;
    if (data == '\n')
      messageComplete = 1;
  }
}
//  int i;
//
//  for (i = 0; i < 5; i++) {
//    // Passo Direita
//    MovPeD(MinPeD, 10);
//    MovPeE(MinPeE, 10);
//    MovPeD(MedPeD, 10);
//    MovPnD(MedPnD, 10);
//    MovPnE(MaxPnE, 10);
//    MovPeE(MedPeE, 10);
//
//    // Passo Esq
//    MovPeE(MaxPeE, 10);
//    MovPeD(MaxPeD, 10);
//    MovPeE(MedPeE, 10);
//    MovPnE(MedPnE, 10);
//    MovPnD(MinPnD, 10);
//    MovPeD(MedPeD, 20);
//  }
//
//    MovPnD(MedPnD, 10);
//    MovPnE(MedPnE, 10);
//
//
//  for (i = 0; i < 5; i++) {
//    // Andar de Lado
//    MovPeD(MinPeD, 10);
//    MovPeE(MaxPeE, 10);
//    MovPeD(MedPeD, 10);
//    MovPeE(MedPeE, 10);
//  }
//
//  for (i = 0; i < 5; i++) {
//    // Andar de Lado
//    MovPeE(MaxPeE, 10);
//    MovPeD(MinPeD, 10);
//    MovPeE(MedPeE, 10);
//    MovPeD(MedPeD, 10);
//  }
//}
//
//void MovPeD(int PosFinal, int Delay) {
//  if (Pos[0] <= PosFinal) {
//    for (; Pos[0] <= PosFinal; Pos[0] += 1) {
//      PeDir.write(Pos[0]);
//      delay(Delay);
//    }
//  }
//  else if (Pos[0] >= PosFinal) {
//    for (; Pos[0] >= PosFinal; Pos[0] -= 1) {
//      PeDir.write(Pos[0]);
//      delay(Delay);
//    }
//  }
//}
//void MovPnD(int PosFinal, int Delay) {
//  if (Pos[1] <= PosFinal) {
//    for (; Pos[1] <= PosFinal; Pos[1] += 1) {
//      PnDir.write(Pos[1]);
//      delay(Delay);
//    }
//  }
//  else if (Pos[1] >= PosFinal) {
//    for (; Pos[1] >= PosFinal; Pos[1] -= 1) {
//      PnDir.write(Pos[1]);
//      delay(Delay);
//    }
//  }
//}
//void MovPeE(int PosFinal, int Delay) {
//  if (Pos[2] <= PosFinal) {
//    for (; Pos[2] <= PosFinal; Pos[2] += 1) {
//      PeEsq.write(Pos[2]);
//      delay(Delay);
//    }
//  }
//  else if (Pos[2] >= PosFinal) {
//    for (; Pos[2] >= PosFinal; Pos[2] -= 1) {
//      PeEsq.write(Pos[2]);
//      delay(Delay);
//    }
//  }
//}
//void MovPnE(int PosFinal, int Delay) {
//  if (Pos[3] <= PosFinal) {
//    for (; Pos[3] <= PosFinal; Pos[3] += 1) {
//      PnEsq.write(Pos[3]);
//      delay(Delay);
//    }
//  }
//  else if (Pos[3] >= PosFinal) {
//    for (; Pos[3] >= PosFinal; Pos[3] -= 1) {
//      PnEsq.write(Pos[3]);
//      delay(Delay);
//    }
//  }
//}