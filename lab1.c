/*

Algoritmo em linguagem C - utilizando lista estática sequencial -

que reproduza as atividades executadas pelo sistema de gerenciamento de reservas

da biblioteca. Nessa tarefa, vamos assumir que o seu programa será utilizado para

gerenciar as reservas de apenas um usuário. Além disso, são permitidas no máximo

10 reservas por usuário.

O programa deverá imprimir uma mensagem sempre que uma nova reserva for solicitada ou um livro for retirado. Se uma nova reserva for solicitada e a lista de reservas

estiver cheia, o programa deverá imprimir esta informação. Quando a reserva for

concluída, o programa deverá imprimir quantas reservas aquele usuário já realizou.

Quando um livro for retirado, a mensagem deverá incluir quantos livros aquele usuário

já retirou. Note que as inclusões de novas reservas ocorrem sempre ao final da lista.

*/

/*--------------------------- Bibliotecas Externas ---------------------------*/

 

#include <stdio.h>

#include <stdbool.h>

#define MAX 100

 

/*---------------------------------- TAD X.h ----------------------------------*/

 

struct listaES

{

  int ultimo;

  int tamanhoLista;

  int lista[MAX];

};

typedef struct listaES tipoListaES;

 

void inicializaLista (tipoListaES *listaAux)

{

  //zera a lista

  listaAux->tamanhoLista = 0;

  for(int i = 0; i < MAX; i++)

    listaAux->lista[i] = 0;

 

  //inicializa o último

  listaAux->ultimo = 0;

}

 

 

void insereElemento (tipoListaES *listaAux)

{

  //atualiza a lista

  listaAux->tamanhoLista++;

  

  //insere elemento ao final da lista

  scanf("%d", &listaAux->lista[listaAux->tamanhoLista-1]);

 

  //atualiza o último

  listaAux->ultimo = listaAux->tamanhoLista - 1;

}

 

/*------------------------- Funcoes e procedimentos -------------------------*/

 

bool verificaLivro(tipoListaES *listaAux, int livroPesquisado)

{

  for(int i = 0; i < listaAux->tamanhoLista; i++)

    if(listaAux->lista[i] == livroPesquisado)

      return true;

  

  return false;

}

 

void removeElemento(tipoListaES *listaAux, int livroPesquisado)

{

  int posicao;

  int j, i;

  

  for(i = 0; i < listaAux->tamanhoLista; i++)

    if(listaAux->lista[i] == livroPesquisado)

      posicao = i;

  

  for(i = posicao; i < listaAux->tamanhoLista; i++){

    for(j = i + 1; j < listaAux->tamanhoLista; j++){

      listaAux->lista[i] = listaAux->lista[j];

      i++;

    }

  }

 

  listaAux->tamanhoLista--;

}

 

/*------------------------------ Funcao main ------------------------------*/

 

int main(void)

{

  tipoListaES minhaLista;

  int l;

  int cont = 0;

  int nReservas = 0, nRetiradas = 0;

  int mov; /*variavel representando a movimentacao do usuario ("1" reservar, "2"         

             retirar)*/

  int livro;

    

  //lendo L (quantidade de movimentacoes que serao realizadas)

  scanf("%d", &l);

 

  inicializaLista(&minhaLista);

 

  if(l >= 1 && l <= 100){

    do{

      //lendo a movimentacao

      scanf("%d", &mov);

      

      //se for reservar, ler o numero do livro

      if(mov == 1){

        //verificacao se a lista de reserva nao esta cheia

        if(nReservas < 10){

          insereElemento(&minhaLista);

          nReservas++;

          printf("Sua reserva foi realizada\n");

        }

        else{

          printf("Lista de reserva cheia\n");

          cont--;

        }

      }

      else{

        //se for retirar, ler o numero do livro

        if(mov == 2){

          scanf("%d", &livro);

          

          //verificacao se o livro ja foi reservado para entao ser retirado

          if(verificaLivro(&minhaLista, livro)){

            removeElemento(&minhaLista, livro);

            printf("O livro foi retirado com sucesso\n");

            nRetiradas++;

          }

          else

            printf("Voce nao possui reserva desse livro\n");

        }

      }   

      cont++;

    } while(cont < l);

  }

 

  printf("Voce realizou %d reservas e %d retiradas\n", nReservas, nRetiradas);

  

  return 0;
}
