#include<iostream>

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
    nextFila=nextColumna=NULL;
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
    filas= new Node<T>*[nfilas]();
    columnas= new Node<T>*[ncolumnas]();
    
  }
  void print();
  bool find_fila(int ,int ,Node<T> **);
  bool find_columna(int,int,Node<T> **);
  bool add(T,int,int);
};

template<clas T>
bool find_fila(int i,int j,Node<T> **p)
{
  p=&(columnas[j]);
  while(*p){
    if((*p)->i==i)return true;
    if((*p)->i > i)return false;
    p=&((*p)->nextFila);
  }
  return false;
}
bool find_columna(int i,int j,Node<T> **p)
{
  p=&(filas[i]);
  while(*p){
    if((*p)->j==j)return true;
    if((*p)->j > j)return false;
    p=&((*p)->nextColumna);
  }
  return false;
bool add(T data,int i,int j)
{
  Node<T> ** p;
  Node<T> ** q;
  if(!find_columna(i,j,p) && !find_fila(i,j,q)){
    Node<T> *nuevo=new Node<T>(data);
    nuevo->nextColumna=(*p)->nextColumna;
    nuevo->nextFila=(*q)->nextFila;
    (*p)->nextColumna=nuevo;
    (*q)->nextFila=nuevo;
    return true;
     
  }
  return false;
}

template<class T>
void MatrizEsparza<T>::print()
{
  for(int i=0;i<nfilas;i++){
    for(int j=0;j<ncolumnas;j++){
      if()
    }  
  }
}
