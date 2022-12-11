#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct elemento
{
  int num;
  struct elemento *prox;
  struct elemento *ant;
};
typedef struct elemento tipoElemento;

struct estruturaLDDE
{
  tipoElemento *primeiro;
  tipoElemento *ultimo;
  int tamanhoLista;
};
typedef struct estruturaLDDE tipoLDDE;

void inicializaLista (tipoLDDE *listaAux)
{
  listaAux->primeiro = NULL;
  listaAux->ultimo = NULL;
  listaAux->tamanhoLista = 0;
}

void insereListaInicial (tipoLDDE *listaAux, int num)
{
  tipoElemento *novoElem = (tipoElemento *) malloc(sizeof(tipoElemento));
  novoElem->num = num;

  novoElem->prox = NULL;
  novoElem->ant = NULL;

  if (listaAux->tamanhoLista == 0) {
    listaAux->primeiro = novoElem;
    listaAux->ultimo = novoElem;
  }
  else {
    novoElem->ant = listaAux->ultimo;
    listaAux->ultimo->prox = novoElem;
    listaAux->ultimo = novoElem;
  }

  listaAux->tamanhoLista++;
}

void insereNovoElemento (tipoLDDE *listaAux, int num, int pos)
{
  int cont = 0;
  bool removeu = false;

  listaAux->ultimo->prox = listaAux->primeiro;
  listaAux->primeiro->ant = listaAux->ultimo;
  
  tipoElemento *novoElem = (tipoElemento *) malloc(sizeof(tipoElemento));
  novoElem->num = num;
  novoElem->ant = NULL;
  novoElem->prox = NULL;
  
  tipoElemento *temp;
  temp = listaAux->primeiro;
  
  while (temp != NULL && cont != pos) {
    temp = temp->prox;
    cont++;
  }

  if (pos == 0) {
    novoElem->prox = temp;
    temp->ant = novoElem;
    listaAux->primeiro = novoElem;
    novoElem->ant = listaAux->ultimo;
    listaAux->ultimo->prox = listaAux->primeiro;
  }
  else {
    novoElem->ant = temp->ant;
    novoElem->prox = temp;
    temp->ant->prox = novoElem;
    temp->ant = novoElem;
  }

  listaAux->tamanhoLista++;
  
  temp = listaAux->primeiro;
  cont = 0;
  while (cont < listaAux->tamanhoLista) {
    if ((temp->ant->num + temp->num + temp->prox->num) == 10) {
      if (temp == listaAux->primeiro) {
        listaAux->primeiro = temp->prox->prox;
        listaAux->ultimo = listaAux->ultimo->ant;
        /*listaAux->primeiro->ant = listaAux->ultimo;
        listaAux->ultimo->prox = listaAux->primeiro;*/
      }
      else {
        if (temp->ant == listaAux->primeiro) {
          listaAux->primeiro = temp->prox->prox;
        }
        else {
          if (temp->prox == listaAux->primeiro) {
            listaAux->primeiro = listaAux->primeiro->prox;
            listaAux->ultimo = listaAux->ultimo->ant->ant;
          }
          else {
            if (temp->prox == listaAux->ultimo) {
              listaAux->ultimo = temp->ant->ant;
            }
            else {
              temp->ant->ant->prox = temp->prox->prox;
              temp->prox->prox->ant = temp->ant->ant;
            }
          }
        }
      }
      free(temp->ant);
      free(temp->prox);
      free(temp);
      listaAux->tamanhoLista -= 3;
      removeu = true;
    }
    temp = temp->prox;
    cont++;
  }

  /*verificação dupla*/
  if (removeu) {
    temp = listaAux->primeiro;
    cont = 0;
    while (cont < listaAux->tamanhoLista) {
      if ((temp->ant->num + temp->num + temp->prox->num) == 10) {
        if (temp == listaAux->primeiro) {
          listaAux->primeiro = temp->prox->prox;
          listaAux->ultimo = listaAux->ultimo->ant;
        }
        else {
          if (temp->ant == listaAux->primeiro) {
            listaAux->primeiro = temp->prox->prox;
          }
          else {
            if (temp->prox == listaAux->primeiro) {
              listaAux->primeiro = listaAux->primeiro->prox;
              listaAux->ultimo = listaAux->ultimo->ant->ant;
            }
            else {
              if (temp->prox == listaAux->ultimo) {
                listaAux->ultimo = temp->ant->ant;
              }
              else {
                temp->ant->ant->prox = temp->prox->prox;
                temp->prox->prox->ant = temp->ant->ant;
              }
            }
          }
        }
        free(temp->ant);
        free(temp->prox);
        free(temp);
        listaAux->tamanhoLista -= 3;
      }
      temp = temp->prox;
      cont++;
    }
  }
  
}

void imprimeLista (tipoLDDE *listaAux)
{
  int cont = 0;
  
  tipoElemento *temp;
  temp = listaAux->primeiro;
  while (cont < listaAux->tamanhoLista) {
    printf("%d ", temp->num);
    temp = temp->prox;
    cont++;
  }
  printf("\n");
}

int main(void) 
{
  tipoLDDE *minhaLista = (tipoLDDE *) malloc(sizeof(tipoLDDE));
  tipoElemento *temp;
  
  int cont = 0, num, pos;

  inicializaLista(minhaLista);
  
  while (cont < 10) {
    scanf("%d", &num);
    insereListaInicial(minhaLista, num);
    cont++;
  }
  
  temp = minhaLista->primeiro;
  while (temp) {
    printf("%d ", temp->num);
    temp = temp->prox;
  }
  
  printf("\n");

  cont = 0;

  while (cont < 5) {
    scanf("%d %d", &num, &pos);
    if (num >= 1 && num <= 9) {
      insereNovoElemento(minhaLista, num, pos);
      imprimeLista(minhaLista);
    }
    cont++;
  }

  if (minhaLista->tamanhoLista == 0)
    printf("ganhou\n");
  else
    printf("perdeu\n");

  free(minhaLista);
  
  return 0;
}
