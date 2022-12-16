#include <stdio.h>
#include <stdbool.h>
#define MAX 100

struct elemento
{
  int id;
};
typedef struct elemento tipoElemento;

struct fila
{
  int primeiro;
  int ultimo;
  int tamanhoFila;
  tipoElemento elemento[MAX];
};
typedef struct fila tipoFC;

void inicializaFila (tipoFC *filaAux)
{
  filaAux->primeiro = -1;
  filaAux->ultimo = -1;
  filaAux->tamanhoFila = 0;
  for (int i = 0; i < MAX; i++)
    filaAux->elemento[i].id = 0;
}

bool filaVazia (tipoFC *filaAux)
{
  if (filaAux->tamanhoFila == 0)
    return true;
  else 
    return false;
}

bool filaCheia (tipoFC *filaAux)
{
  if (((filaAux->ultimo + 1) % MAX) == filaAux->primeiro)
    return true;
  else
    return false;
}

bool insereElemento (tipoFC *filaAux, int id)
{
  if (filaVazia(filaAux)) {
    filaAux->primeiro = 0;
    filaAux->ultimo = 0;
    filaAux->elemento[0].id = id;
    filaAux->tamanhoFila++;
    return true;
  }
  else if (!filaCheia(filaAux)) {
    int posicao = ((filaAux->ultimo + 1) % MAX);
    filaAux->elemento[posicao].id = id;
    filaAux->ultimo = posicao;
    filaAux->tamanhoFila++;
    return true;
  }
  else {
    return false;
  }
}

int removeElemento (tipoFC *filaAux)
{
  tipoElemento temp;
  if (filaVazia(filaAux)) {
    printf("vazia\n");
    return -1;
  }
  else {
    if (filaAux->tamanhoFila == 1) {
      temp.id = filaAux->elemento[filaAux->primeiro].id;
      inicializaFila(filaAux);
      return temp.id;
    }
    else {
      temp.id = filaAux->elemento[filaAux->primeiro].id;
      filaAux->elemento[filaAux->primeiro].id = 0;
      filaAux->primeiro += 1;
      filaAux->tamanhoFila--;
      return temp.id;
    }
  }
}


void concluiTarefa (tipoFC *filaAux)
{
  tipoElemento temp;
  int cont = filaAux->primeiro;

  temp.id = filaAux->elemento[filaAux->primeiro].id;
  
  while (cont < filaAux->ultimo) {
    filaAux->elemento[cont].id = filaAux->elemento[cont + 1].id;
    cont++;
  }

  filaAux->elemento[filaAux->ultimo].id = temp.id;
}

void imprimeLista (tipoFC *filaAux)
{
  for (int i = filaAux->ultimo; i > ((filaAux->primeiro) - 1); i--)
    printf("%d ", filaAux->elemento[i].id);
}

int main(void) {
  tipoFC minhaFila;

  inicializaFila(&minhaFila);

  int cont = 0, l, op, id;
  scanf("%d", &l);
  do {
    scanf("%d", &op);
    switch (op) {
      case 1:
        scanf("%d", &id);
        insereElemento(&minhaFila, id);
        break;
      case 2:
        removeElemento(&minhaFila);
        break;
      case 3:
        if (minhaFila.tamanhoFila != 0)
          concluiTarefa(&minhaFila);
        else
          printf("vazia\n");
        break;
      default:
        break;
    }
    cont++;
  } while (cont < l);

  imprimeLista(&minhaFila);
  
  return 0;
}