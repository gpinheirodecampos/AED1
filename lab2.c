/*
Algoritmo em linguagem C - utilizando lista estática encadeada -
que forneça uma lista com os números de RA’s ordenados dos alunos que realizaram
a reserva de um determinado livro. Além disso, seu algoritmo também deve fornecer
quantos usuários de cada ano realizaram a reserva daquele livro.
Para obter essa informação, considere que o RA dos alunos do ICT muda de acordo
com o ano de entrada na universidade. Por exemplo, todos os alunos que entraram
em 2013 possuem um RA de 5 dígitos que inicia com 86. Os alunos que entraram em
2014, possuem um RA de 5 dígitos que inicia com 96. Os alunos que entraram em
2015 possuem RA de 6 dígitos que inicia com 106, assim por diante.
*/
/* Bibliotecas e constantes */
#include <stdio.h>
#include <stdbool.h>
#define MAX 100
 
/*--------------- TAD X.h ---------------*/
struct info
{
  int valor;
  int prox;
};
typedef struct info tipoInfo;
 
struct listaEE
{
  int tamanhoLista;
  int primeiro;
  int ultimo;
 
  /* 0 - ocupado, 1 - livre */
  int posLivre[MAX];
  tipoInfo elemento[MAX];
};
typedef struct listaEE tipoListaEE;
 
void inicializaLista (tipoListaEE *listaAux)
{
  listaAux->tamanhoLista = 0;
  listaAux->primeiro = -1;
  listaAux->ultimo = -1;
 
  for (int i = 0; i < MAX; i++) {
    listaAux->elemento[i].valor = 0;
    listaAux->elemento[i].prox = -1;
    listaAux->posLivre[i] = 1;
  }
}
 
int proxPosLivre (tipoListaEE *listaAux, int l)
{
  for (int i = 0; i < l; i++) {
    if (listaAux->posLivre[i] == 1)
      return i;
  }  
  return -1;
}
 
bool insereElementoFinal (tipoListaEE *listaAux, int posicao, int x)
{
  if (posicao != -1)
  {
    /* atribui elemento lido à lista */
    listaAux->elemento[posicao].valor = x;
    
    /* atualiza elementos da lista */
    if (listaAux->tamanhoLista == 0)
      listaAux->primeiro = posicao;
    else
      listaAux->elemento[listaAux->ultimo].prox = posicao;
 
    listaAux->elemento[posicao].prox = -1;
    listaAux->tamanhoLista++;
    listaAux->ultimo = posicao;
    listaAux->posLivre[posicao] = 0;
 
    return true;
  }
  else
    return false;
}
 
bool removeElemento (tipoListaEE *listaAux, int l)
{
  int x, posicao, i;
  bool achou = false;
 
  /* leitura do elemento que será retirado se estiver na lista */
  scanf("%d", &x);
  
  for (i = 0; i < l; i++) {
    if (listaAux->elemento[i].valor == x) {
      posicao = i;
      achou = true;
      break;
    }
  }
 
  if (!achou) {
    printf("nao existe\n");
    return false;
  }
  else {
    /* se o elemento a ser retirado for o primeiro */
    if (posicao == listaAux->primeiro)
      listaAux->primeiro = listaAux->elemento[posicao].prox;
    else {
      int antecessor;
      for (i = 0; i < l; i++) {
        if (listaAux->elemento[i].prox == posicao) {
          antecessor = i;
          break;
        }
      }
      /* se o elemento a ser retirado for o intermediário */
      if (posicao != listaAux->ultimo) {
        listaAux->elemento[antecessor].prox = listaAux->elemento[posicao].prox;        
      }
      else {
        /* se o elemento a ser retirado for o último */
        listaAux->ultimo = antecessor;
        listaAux->elemento[antecessor].prox = -1;
      }
    }
    /* atualizações que serão feitas em todos os casos */
    listaAux->elemento[posicao].valor = 0;
    listaAux->elemento[posicao].prox = -1;
    listaAux->tamanhoLista--;
    listaAux->posLivre[posicao] = 1;
 
    return true;
  }
}
 
int vet[MAX];
 
void ordenaLista (tipoListaEE *listaAux, int l)
{
  int aux;
  int n = listaAux->tamanhoLista;
  
   /* ordenando vetor */
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (n - 1 - i); j++) {
      if (listaAux->elemento[j].valor > listaAux->elemento[j + 1].valor) {
        aux = listaAux->elemento[j].valor;
        listaAux->elemento[j].valor = listaAux->elemento[j + 1].valor;
        listaAux->elemento[j + 1].valor = aux;
      }
    }
  }
 
  /* imprimindo vetor */
  for (int i = 0; i < l; i++)
    if (listaAux->elemento[i].valor != 0)
      printf("%d ", listaAux->elemento[i].valor);
 
  printf("\n");
}
 
void insereAno (int x, int aux[8][2])
{
  int z;  
  
  z = x / 1000;
 
  switch (z)
  {
    case 66 ... 75:
      aux[0][1]++;
      break;
 
    case 76 ... 85:
      aux[1][1]++;
      break;
 
    case 86 ... 95:
      aux[2][1]++;
      break;
 
    case 96 ... 105:
      aux[3][1]++;
      break;
 
    case 106 ... 115:
      aux[4][1]++;
      break;
 
    case 116 ... 125:
      aux[5][1]++;
      break;
 
    case 126 ... 135:
      aux[6][1]++;
      break;
 
    case 136 ... 140:
      aux[7][1]++;
      break;
    
    default:
      break;
  }
}
 
/*------------- Funcao main -------------*/
int main(void) 
{
  tipoListaEE minhaLista;
  int l, cont = 0, nReservas = 0;
  int r; //1 para reservar, 2 para retirar
  int matriz[8][2];
  int x, ano = 2011;
  bool inseriu = false;
  bool removeu = false;
 
  scanf("%d", &l);
  
  inicializaLista(&minhaLista);
 
  for (int i = 0; i < 8; i++) {
    matriz[i][0] = ano;
    matriz[i][1] = 0;
    ano++;
  }
  
  if (l >= 1 && l <= 100) {
    do {
      scanf("%d", &r);
      if (r == 1) {
        if (nReservas < 10) {
          scanf("%d", &x);
          inseriu = insereElementoFinal(&minhaLista, proxPosLivre(&minhaLista, l), x);
          if (inseriu) {
            insereAno(x, matriz);
            ordenaLista(&minhaLista, l);
            nReservas++;
          }
        }
        else {
          printf("lista cheia\n");
          ordenaLista(&minhaLista, l);
        }
      }
      else {
        if (r == 2) {
          removeu = removeElemento(&minhaLista, l);
          if (removeu)
            nReservas--;
          ordenaLista(&minhaLista, l);
        }        
      }
      cont++;
    } while (cont < l);
  }
 
  /* Imprimindo a matriz */
  //printf("\n");
  
  for (int i = 0; i < 8; i++)
    printf("%d: %d\n", matriz[i][0], matriz[i][1]);
 
  return 0;
}