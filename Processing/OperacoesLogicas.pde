int sizeX1, sizeY1;
int sizeX2, sizeY2;
char input = '9';

void setup() {
  // Janela
  size(300, 500);
  noStroke();
  background(0, 0);
  noSmooth();
  rectMode(CENTER);
  sizeX1 = width/3; 
  sizeY1 = height/2;
  sizeX2 = width/4; 
  sizeY2 = height/3;


  println("Relações Lógicas de 0~4", "\n   0) Conjunção\n   1) Disjunção\n   2) Disjunção Exclusiva\n   3) Condicional\n   4) Bicondicional");
}

void draw() {
  background(0, 0);
  createForm(255, 50, 0, mouseX, mouseY, sizeX1, sizeY1);
  createForm(0, 50, 255, width-mouseX, height-mouseY, sizeX2, sizeY2);

  colorPoints();
}

void createForm(int R, int G, int B, float X0, float Y0, float sizeX, float sizeY) {
  fill(R, G, B, 200);
  rect(X0, Y0, sizeX, sizeY);
}

void colorPoints() {
  for (int i = 0; i<width; i+=20) {
    for (int j = 0; j<height; j+=20) {


      switch(input) {

      case '0': // Conjunção (A AND B)
        if (abs(i-mouseX)<sizeX1/2 && abs(i-(width-mouseX))<sizeX2/2 && abs(j-mouseY)<sizeY1/2 && abs(j-(height-mouseY))<sizeY2/2)
          fill(0, 255, 0);
        else if (abs(i-mouseX)<sizeX1/2 && abs(j-mouseY)<sizeY1/2)
          fill(255, 0, 0);
        else if (abs(i-(width-mouseX))<sizeX2/2 && abs(j-(height-mouseY))<sizeY2/2)
          fill(0, 0, 255);
        else
          fill(0, 0, 0);
        break;

      case '1': // Disjunção (A OR B)
        if (abs(i-mouseX)<sizeX1/2 && abs(j-mouseY)<sizeY1/2)
          fill(0, 255, 0);
        else if (abs(i-(width-mouseX))<sizeX2/2 && abs(j-(height-mouseY))<sizeY2/2)
          fill(0, 255, 0);
        else
          fill(0, 0, 0);
        break;

      case '2': // Disjunção Exclusiva(A+B)
        if (abs(i-mouseX)<sizeX1/2 && abs(i-(width-mouseX))<sizeX2/2 && abs(j-mouseY)<sizeY1/2 && abs(j-(height-mouseY))<sizeY2/2)
          fill(0, 0, 0);
        else if (abs(i-mouseX)<sizeX1/2 && abs(j-mouseY)<sizeY1/2)
          fill(0, 255, 0);
        else if (abs(i-(width-mouseX))<sizeX2/2 && abs(j-(height-mouseY))<sizeY2/2)
          fill(0, 255, 0);
        else
          fill(0, 0, 0);
        break;

      case '3': // Condicional (A->B)
        if (abs(i-mouseX)<sizeX1/2 && abs(i-(width-mouseX))<sizeX2/2 && abs(j-mouseY)<sizeY1/2 && abs(j-(height-mouseY))<sizeY2/2)
          fill(0, 255, 0);
        else if (abs(i-mouseX)<sizeX1/2 && abs(j-mouseY)<sizeY1/2)
          fill(0, 0, 0);
        else if (abs(i-(width-mouseX))<sizeX2/2 && abs(j-(height-mouseY))<sizeY2/2)
          fill(0, 255, 0);
        else
          fill(0, 255, 0);
        break;

      case '4': // Bicondicional (A<->B)
        if (abs(i-mouseX)<sizeX1/2 && abs(i-(width-mouseX))<sizeX2/2 && abs(j-mouseY)<sizeY1/2 && abs(j-(height-mouseY))<sizeY2/2)
          fill(0, 255, 0);
        else if (abs(i-mouseX)<sizeX1/2 && abs(j-mouseY)<sizeY1/2)
          fill(0, 0, 0);
        else if (abs(i-(width-mouseX))<sizeX2/2 && abs(j-(height-mouseY))<sizeY2/2)
          fill(0, 0, 0);
        else
          fill(0, 255, 0);
        break;

      default:
        fill(0, 0, 0);
      }

      circle(i, j, 7);
    }
  }
}

void keyPressed() {
  if ((key >= '0' && key <= '9')) {
    input = key;
    switch (input) {
    case '0': 
      print("\n", input, " Conjunção");
      break;
    case '1': 
      print("\n", input, " Disjunção");
      break;
    case '2': 
      print("\n", input, " Disjunção Exclusiva");
      break;
    case '3': 
      print("\n", input, " Condicional");
      break;
    case '4': 
      print("\n", input, " Bicondicional");
      break;
    default: 
      print("\n", input, " ...");
    }
  }
}
