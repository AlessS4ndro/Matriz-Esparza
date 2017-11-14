#include<iostream>
#include<fstream>
using namespace std;

template<class T>
struct Node
{
  T data;
  int i;
  int j;
  Node<T> * nextFila;
  Node<T> * nextColumna;
  Node(T data,int i,int j){
    this->data=data;
    this->i=i;
    this->j=j;
    nextFila=nextColumna=0;
  }
};

template<class T=int>
class MatrizEsparza
{
  Node<T>** filas;
  Node<T>** columnas;
  int nfilas;
  int ncolumnas;
 public:
  MatrizEsparza(int nfilas,int ncolumnas){
    this->nfilas=nfilas;
    this->ncolumnas=ncolumnas;
    filas= new Node<T>*[nfilas];
    columnas= new Node<T>*[ncolumnas];
    for(int i=0;i<nfilas;i++)
      filas[i]=0;
    for(int i=0;i<ncolumnas;i++)
      columnas[i]=NULL;
    
  }
  void print(ofstream &);
  bool find_fila(int ,int ,Node<T> **&);
  bool find_columna(int,int,Node<T> **&);
  bool add(T,int,int);
  int & get_set_nfilas(){return nfilas;}
  int & get_set_ncolumnas(){return ncolumnas;}
  T* get_data(int ,int );
};

template<class T>
T* MatrizEsparza<T>::get_data(int x,int y)
{
  Node<T> **p;
  if(find_fila(x,y,p))
    return &((*p)->data);
  return NULL;
}
template<class T>
bool MatrizEsparza<T>::find_fila(int i,int j,Node<T> **&p)
{
  p=&(columnas[j]);
  while(*p){
    if((*p)->i==i)return true;
    if((*p)->i > i)return false;
    p=&((*p)->nextFila);
  }
  return false;
}
template<class T>
bool MatrizEsparza<T>::find_columna(int i,int j,Node<T> **&p)
{
  p=&(filas[i]);
  while(*p){
    if((*p)->j==j)return true;
    if((*p)->j > j)return false;
    p=&((*p)->nextColumna);
  }
  return false;
}
template<class T>
bool MatrizEsparza<T>::add(T data,int i,int j)    
{
  Node<T> ** p;
  Node<T> ** q;
  bool ff=find_fila(i,j,q);
  bool fc=find_columna(i,j,p);
  if(!ff || !fc){
    Node<T> *nuevo=new Node<T>(data,i,j);
    nuevo->nextColumna=(*p);
  (*p)=nuevo;
    nuevo->nextFila=(*q);
    
    (*q)=nuevo;
    return true;    
  }
  return false;
}

template<class T>
void MatrizEsparza<T>::print(ofstream &os)
{
  for(int i=0;i<nfilas;i++){
    
    for(int j=0;j<ncolumnas;j++){
      if(columnas[j] && columnas[j]->i==i)
	  os<<columnas[j]->data<<" ";
      else
	os<<"0 ";
    }
    os<<endl;
  }
}
