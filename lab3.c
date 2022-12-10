/*
Desenvolva um algoritmo em linguagem C - utilizando lista dinâmica encadeada -
que forneça uma lista com os produtos cadastrados na mercearia ordenados pelo
preço dos produtos. Ao final da execução, seu algoritmo deve informar o lucro obtido
pela venda de cada um dos produtos cadastrados.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct elemento
{
  int id;
  int qntd;
  int compras;
  float preco;
  float lucro;
  struct elemento *prox;
};
typedef struct elemento tipoElemento;

struct listaDE
{
  tipoElemento *primeiro;
  tipoElemento *ultimo;
  int tamanhoLista;
};
typedef struct listaDE tipoLDE;

void inicializaLista (tipoLDE *listaAux)
{
  listaAux->primeiro = NULL;
  listaAux->ultimo = NULL;
  listaAux->tamanhoLista = 0;
}

void insereElementoFinal (tipoLDE *listaAux, int id, int qntd, float preco)
{
  bool achou = false;

  /*Variavel auxiliar para percorrer lista*/
  tipoElemento *temp;
  temp = listaAux->primeiro;

  /*Checando se o elemento a ser inserido ja existe*/
  while (temp != NULL) {
    if (temp->id == id) {
      achou = true;
      break;
    }
    temp = temp->prox;
  }

  if (achou) {
    printf("ja existe\n");
  }
  else {
    /*Alocando espaco para o elemento*/
    tipoElemento *novoElem = (tipoElemento *) malloc(sizeof(tipoElemento));

    /*Atribuindo os dados de info*/
    novoElem->id = id;
    novoElem->qntd = qntd;
    novoElem->preco = preco;
    novoElem->compras = 0;

    novoElem->prox = NULL;
    
    if (listaAux->tamanhoLista == 0) {
      listaAux->primeiro = novoElem;
      listaAux->ultimo = novoElem;
    } 
    else {
      /*Analisando o caso de quando o preco do novo elemento for maior que o preco do primeiro elemento da lista*/
      if (preco > listaAux->primeiro->preco) {
        novoElem->prox = listaAux->primeiro;
        listaAux->primeiro = novoElem;
      }
      else {
        temp = listaAux->primeiro;
        /*Percorrendo a lista e parando antes do elemento que tiver o preco menor que o do novo elemento*/
        while (temp->prox != NULL && temp->prox->preco > preco)
          temp = temp->prox;

        /*A variavel temp->prox so vai parar no null quando o preco do novo elemento for menor que o preco do ultimo elemento*/            
        /*Se o preco do novo elemento for menor que o preco do ultimo elemento da lista*/
        if (temp->prox == NULL) {
          listaAux->ultimo->prox = novoElem;
          listaAux->ultimo = novoElem;
        }
        else {
          novoElem->prox = temp->prox;
          temp->prox = novoElem;
        }
      }
    }
    listaAux->tamanhoLista++;
  } 
}

void aumentaQuantidade (tipoLDE *listaAux, int id, int qntd)
{
  bool achou = false;

  tipoElemento *temp;
  temp = listaAux->primeiro;

  while (temp != NULL) {
    if (temp->id == id) {
      temp->qntd += qntd;
      achou = true;
      break;
    }
    temp = temp->prox;
  }

  if (!achou)
    printf("nao existe\n");
}

void compra (tipoLDE *listaAux, int id)
{
  bool achou = false;
  
  tipoElemento *temp;
  temp = listaAux->primeiro;
  
  while (temp != NULL) {
    if (temp->id == id) {
      achou = true;
      break;
    }
    temp = temp->prox;
  }

  if (!achou || temp->qntd == 0)
    printf("nao existe\n");
  else {
    temp->compras++;
    temp->lucro += temp->preco;
    temp->qntd--;
  }
}

void removeElemento (tipoLDE *listaAux, int id)
{
  bool achou = false;
  
  tipoElemento *temp;
  tipoElemento *antecessor;
  temp = listaAux->primeiro;

  if (id == temp->id) {
    listaAux->primeiro = temp->prox;
    free(temp);
    achou = true;
    listaAux->tamanhoLista--;
  }
  else {
    while (temp->prox != NULL) {
      if (temp->prox->id == id) {
        antecessor = temp;
        temp = temp->prox;
        achou = true;
        break;
      }
    temp = temp->prox;
    }
    if (achou) {
      if (id == listaAux->ultimo->id) {
        listaAux->ultimo = antecessor;
        free(temp);
        listaAux->tamanhoLista--;
      }
      else {
        antecessor->prox = temp->prox;
        free(temp);
        listaAux->tamanhoLista--;
      }
    }
  }

  if (!achou)
    printf("nao existe\n");
}

void lucro (tipoLDE *listaAux)
{
  tipoElemento *temp;
  temp = listaAux->primeiro;
  
  while (temp != NULL) {
    if (temp->compras >= 1) {
      //temp->lucro = temp->compras * temp->preco;
      printf("%d %f\n", temp->id, temp->lucro);
    }
    temp = temp->prox;
  }
}

int main(void) {
  tipoLDE *minhaLista = (tipoLDE*) malloc(sizeof(tipoLDE));
  int l, cont = 0, p;
  int id, qntd;
  float preco;
  tipoElemento *temp;  

  /*Inicializando lista*/
  inicializaLista(minhaLista);

  /*Lendo quantidade de movimentos a serem realizados*/
  scanf("%d", &l);

  if (l >= 1 && l <= 100) {
    do {
      scanf("%d", &p);
      switch (p) {
        case 1:
          scanf("%d %d %f", &id, &qntd, &preco);
          insereElementoFinal(minhaLista, id, qntd, preco);          
          break;
        case 2:
          scanf("%d %d", &id, &qntd);
          aumentaQuantidade(minhaLista, id, qntd);
          break;
        case 3:
          scanf("%d", &id);
          compra(minhaLista, id);
          break;
        case 4:
          scanf("%d", &id);
          removeElemento(minhaLista, id);
          break;
        default:
          break;
      }     
      
      cont++;
    } while (cont < l);
  }

  /*temp = minhaLista->primeiro;

  while (temp != NULL) {
      printf("%d %f \n", temp->id, temp->preco);
      temp = temp->prox;
  }
  
  printf("Primeiro: id %d preco %f", minhaLista->primeiro->id, minhaLista->primeiro->preco);  
  printf("Ultimo: id %d preco %f", minhaLista->ultimo->id, minhaLista->ultimo->preco);
  */
  lucro(minhaLista);
  
  free(minhaLista);
  return 0;
}