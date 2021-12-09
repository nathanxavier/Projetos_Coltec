void setup() {
  size(300,300);
  background(255);
  noStroke();
  smooth();
  
  fill(255,0,0);
  triangle(width/2, height/2, 0,0, width,0);
  fill(255,255,0);
  triangle(width/2, height/2, 0,0, 0,height);
  fill(0,255,0);
  triangle(width/2, height/2, 0,height, width,height);
  fill(0,0,255);
  triangle(width/2, height/2, width,0, width,height);

  stroke(255);
  fill(255,255,255,0);
  for(int i=width/2; i<1.5*width; i+=2)
    for(int j=height/2; j<1.5*height; j+=2)
      ellipse(width/2, height/2, i, j);

  fill(255,255,255);
  ellipse(width/2, height/2, 100,100);
  triangle(width/2, height/2, width,0, width,height/2);
  
  
  int size = 20;
  noStroke();
  fill(0,0,255);
  rect(width/2, height/2-(size/2), width/4, size);
}

void draw() {
}
