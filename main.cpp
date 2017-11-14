#include<iostream>
#include<fstream>
#include"clases.h"
#include"CImg.h"

using namespace std;
using namespace cimg_library;

void escribir_en_disco(ofstream &,CImg<unsigned char> &,int,int);
unsigned char escala_de_grises(CImg<unsigned char> &,unsigned char ,int ,int );
template<class T>
void levantar_matriz(MatrizEsparza<T> &);

int main(int argc,char *argv[])
{  
  ofstream imagenOriginal("analisisImagenOriginal.txt");
  ofstream imagenModificada("analisisImagenModificada.txt");
  ofstream archivoMatriz("analisisMatriz.txt");
  CImg<unsigned char> img("whiterose.png");
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
	matrix.add(*pixel,x,y); 
	imagenNueva(x,y)=img(x,y);
        escribir_en_disco(imagenModificada,imagenNueva,x,y);
	}
      else cout<<"encontramos pixel = 0 en : "<<x<<" , "<<y<<endl;
      escribir_en_disco(imagenOriginal,img,x,y);
     
      arte(x,y)=escala_de_grises(arte,umbral,x,y);
    }
  matrix.print(archivoMatriz);
  imagenNueva.save("imagenNueva.png");
  imagenNueva.display("imagen nueva");
  levantar_matriz(matrix);
  
  
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

template<class T>
void levantar_matriz(MatrizEsparza<T> &matrix)
{
  int filas=matrix.get_set_nfilas();
  int columnas=matrix.get_set_ncolumnas();
  CImg<T> img(filas,columnas);
  
  for(int i=0;i<filas;i++)
    for(int j=0;j<columnas;j++){
      if(matrix.get_data(i,j))
	img(i,j)=*matrix.get_data(i,j);
    }
  cout<<filas<<" * "<<columnas<<endl;
  img.display("imagen levantada dela matriz dispersa");
  img.save("imagenDeMatriz.png");
}
