#include "CComplex.h"
 void setup()
 {

  Serial.begin(115200);
  
float vp1=1;  //voltage mag of phas 1
float vp2=1; //voltage mag of phas 2
float vp3=1; //voltage mag of phas 3
float va1=0; //voltage ang of phas 1
float va2=0; //voltage ang of phas 2
float va3=0; //voltage ang of phas 3

float ip1=0; //current mag of phas 1
float ip2=0; //current mag of phas 2
float ip3=15; //current mag of phas 3
float ia1=0; //current ang of phas 1
float ia2=0; //current ang of phas 1
float ia3=240;

float vo=0; 
float v1=0; 
float v2=0; 

float io=0;
float i1=0;
float i2=0;

float a=120;
float a2=240;

float rv1= vp1*cos(deg2rad(va1));
float iv1= vp1*sin(deg2rad(va1));

float rv2=vp2*cos(deg2rad(va2));
float iv2=vp2*sin(deg2rad(va2));

float rv3=vp3*cos(deg2rad(va3));
float iv3=vp3*sin(deg2rad(va3));

float ri1= ip1*cos(deg2rad(ia1));
float ii1= ip1*sin(deg2rad(ia1));

float ri2=ip2*cos(deg2rad(ia2));
float ii2=ip2*sin(deg2rad(ia2));

float ri3=ip3*cos(deg2rad(ia3));
float ii3=ip3*sin(deg2rad(ia3));

float ra= 1*cos(deg2rad(a));
float ia=1*sin(deg2rad(a));


float rio= ri1+ri2+ri3;
float iio= ii1+ii2+ii3;

Complex A(ra,ia);
Complex A2(-0.5,-0.866);

Complex Ia(ri1,ii1);
Complex Ib(ri2,ii2);
Complex Ic(ri3,ii3);

Complex tempib(0,0);
tempib=A*Ib;

Complex tempic(0,0);
tempic=Ic*A2;

Complex tempib2(0,0);
tempib2=A2*Ib;

Complex tempic2(0,0);
tempic2=A*Ic;



Complex I1(0,0);
Complex I2(0,0);



Complex Io(rio,iio);    // zero seq of current
Io = Io / 3;
I1= (Ia + tempib + tempic) / 3;  // +ve seq of current
I2= (Ia + tempib2 + tempic2) / 3;


//NOW WORKING FOR VOLTAGE

Complex Va(rv1,iv1);
Complex Vb(rv2,iv2);
Complex Vc(rv3,iv3);

Complex tempvb(0,0);
tempvb=A*Vb;

Complex tempvc(0,0);
tempvc=Vc*A2;

Complex tempvb2(0,0);
tempvb2=A2*Vb;

Complex tempvc2(0,0);
tempvc2=A*Vc;



Complex V1(0,0);
Complex V2(0,0);



float rvo= rv1+rv2+rv3;
float ivo= iv1+iv2+iv3;
Complex Vo(rvo,ivo);    // zero seq of voltage
Vo = Vo / 3;
V1= (Va + tempvb + tempvc)/3;  // +ve seq of voltage
V2= (Va + tempvb2 + tempvc2)/3;

//polar form for sequence components

int vmo=Vo.modulus();
double vao=Vo.phase();

int vm2=V1.modulus();  // previously, 1
double v2a=V1.phase();

int vm1=V2.modulus();
double v1a=V2.phase();

int imo=Io.modulus();
double ioa=Io.phase();

int im2=I1.modulus(); // previously, 1
double i2a=I1.phase();

int im1=I2.modulus();
double i1a=I2.phase();

//Serial.println(Io);
//Serial.println(I1);
//Serial.println(I2);
//
//
//Serial.println(V2);
//Serial.println(I2);
Serial.println(imo);
Serial.println(vmo);
Serial.println(im2);
Serial.println(vm2);

if (imo == 0 && vmo == 0 && im2 == 0 && vm2 == 0 ){
  Serial.println("THREE PHASE FAULT DETECTED");
}
 

else if (imo==0 && vmo==0 &&((vp1==0)||(vp2==0)||(vp3==0))){
  Serial.println("DOUBLE LINE FAULT DETECTED");
}

else if ((imo>0)&&(im2>0)&&((vp1==0)||(vp2==0)||(vp3==0)))
{
  Serial.println("DOUBLE LINE TO GROUND FAULT DETECTED");
}

else if ((imo>0)&&(im2>0)&&(((ip1==0)&&(ip2==0))||((ip1==0)&&(ip3==0))||((ip3==0)&&(ip2==0)))){
  Serial.println("SINGLE LINE TO GROUND FAULT DETECTED");
}
}

 
 void loop()
 {

  }

float deg2rad ( float ang)
{
  float rad=ang*0.0174533;
  return rad;
}
