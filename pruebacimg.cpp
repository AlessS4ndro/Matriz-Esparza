#include<iostream>
#include<fstream>
#include"clases.h"
#include"CImg.h"

using namespace std;
using namespace cimg_library;

void escribir_en_disco(ofstream &,CImg<unsigned char> &,int,int);
unsigned char escala_de_grises(CImg<unsigned char> &,unsigned char ,int ,int );
int main(int argc,char *argv[])
{/*;
  CImg<unsigned char> img(400,400,1,3,0);
  img.fill(0);
  unsigned char purple[]={255,0,0};
  img.draw_text(100,100,"hello world",purple);
  img.display("My first cimg code");
 */ /*
	MatrizEsparza<> a(15,15);

	for(int i=0;i<13;i++)
	  a.add(i,i,i);
	 
	//a.add(1,1,1);
	a.print();
  */
  // CImg<unsigned char> img(640,480);/// imagen en tono de grises
  
  // CImg<unsigned char> img(640,480,1,1,0);//igual anterior pero inicialmente negra
  // CImg<unsigned char> img(3,3,1,1,1/9); //imagen de 3*3 en tono de grises
  //CImg<unsigned char> img(7,7,1,3,1/9); //imagen a color
  //img.display("jejejje");

  /*
  CImg<unsigned char> img1(100,100,1,1);
  //img1.fill(0);
  unsigned char purple[]={255,0,0};
  img1.draw_text(40,50,"hola gente",purple);
  img1.display("img1");
  CImg<unsigned char> img2(100,100,1,1);
  for(int i=1;i<img2.height();i++)
    for(int j=1;j<img2.width();j++){
      cout<<"("<<i<<","<<j<<")"<<endl;
      img2(i,j,0,0)=img1(img2.width()-i,img2.height()-j,0,0);
      img2(i,j,0,1)=img1(img2.width()-i,img2.height()-j,0,1);
      img2(i,j,0,2)=img1(img2.width()-i,img2.height()-j,0,2);
    }
  
  for(int i=0;i<img2.height();i++)
    for(int j=0;j<img2.width();j++){
      cout<<"("<<i<<","<<j<<")"
	  <<" R"<<img2(i,j,0,0)//=img1(i,j,0,0);
	  <<" G"<<img2(i,j,0,1)//=img1(i,j,0,1);
	  <<" B"<<img2(i,j,0,2);//=img1(i,j,0,2);
	  }
  cout<<"vamos a mostrar la imagen"<<endl;
  img2.display("img2");
  */  

  ofstream imagenOriginal("analisisImagenOriginal.txt");
  ofstream imagenModificada("analisisImagenModificada.txt");
  ofstream archivoMatriz("analisisMatriz.txt");
  CImg<unsigned char> img(argv[1]);
  CImg<unsigned char> arte(img.width(),img.height(),1,3);
  CImg<unsigned char> imagenNueva(img);
  MatrizEsparza<unsigned char> matrix(img.width(),img.height());
  int width=img.width();
  int height=img.height();
  int a,b,c;
  unsigned char * pixel;
  unsigned char umbral=50;
  
  cout<<width<<" * "<<height<<endl;
  for (int y=1;y<height;y++)
    for(int x=1;x<width;x++){
      pixel=img.data(x,y); /// almacenamos el pixel
      if(*pixel != 0 ){
	matrix.add((int)*pixel,x,y); 
	imagenNueva(x,y)=img(x,y);
        escribir_en_disco(imagenModificada,imagenNueva,x,y);
	}
      else cout<<"encontramos pixel = 0 en : "<<x<<" , "<<y<<endl;
      escribir_en_disco(imagenOriginal,img,x,y);
      //a=(int)img(width-x,height-y,0,0);
      //b=(int)img(width-x,height-y,0,1);
      //c=(int)img(width-x,height-y,0,2);
      //arte(x,y,0,0)=a;
      //arte(x,y,0,1)=b;
      //arte(x,y,0,2)=c;
     
      arte(x,y)=escala_de_grises(arte,umbral,x,y);
    }
  matrix.print(archivoMatriz);
  //imagenNueva.normalize(0,255);  
  imagenNueva.save("imagenNueva.png");
  imagenNueva.display("imagen nueva");
  arte.display("arte escala de grisses");
  //CImgDisplay ventana(img,"titulo perro",1);
  //while(!ventana.is_closed() && !ventana.is_keyQ()){}
  
  return 0;
}

void escribir_en_disco(ofstream & os,CImg<unsigned char> &img,int x,int y)
{
   os<<"("<<x<<","<<y<<")="<<" R"<<(int)img(x,y,0,0)<<" G"<<(int)img(x,y,0,1)<<" B"<<(int)img(x,y,0,2)<<" valor de pixel : "<<(int)img(x,y)<<endl;
}

unsigned char escala_de_grises(CImg<unsigned char> &img,unsigned char umbral,int x,int y)
{
  unsigned char gray=0;
  gray+=img(x,y,0,0)*0.3+img(x,y,0,1)*0.59+img(x,y,0,2)*0.11;
  if(gray > umbral)
    return 255;
  return 0;
}
