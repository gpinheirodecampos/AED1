/*
Algoritmo em linguagem C que receba um valor inteiro L, 1 ≤ L ≤
100, relativo à quantidade de encomendas de sapatos, e L pares (N, G) com dois
valores inteiros correspondentes à numeração no sistema brasileiro (N) e o gênero
(masculino / feminino) (G). O algoritmo deve retornar, para cada gênero, a quantidade
de sapatos encomendada para cada numeração americana.
A numeração de cada sapato no sistema americano pode ser encontrada de acordo
com o gênero e o comprimento do pé em milímetros. Considere que cada unidade da
numeração no sistema brasileiro é equivalente a um pé de 6,67 mm.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

typedef struct{
  int tamBR[MAX];
  double tamUSA_F[MAX], tamUSA_M[MAX];
  int parFem[MAX], parMasc[MAX];
}regPares;
regPares Pares;

int nFem = 0;
int nMasc = 0;

void leituraDados(int *n)
{
  int i, g;
  //lendo numero de pares digitado pelo usuario
  scanf("%d", n);
  
  for(i = 0; i < *n; i++){
    scanf("%d", &Pares.tamBR[i]);
    //lendo genero
    scanf("%d", &g);
    if(g == 0){
      //se masculino
      Pares.parMasc[i] = Pares.tamBR[i];
      nMasc++;
    }
    else if (g == 1){
      //se feminino
      Pares.parFem[i] = Pares.tamBR[i];
      nFem++;
    }
  }
}

void converteMasc(int n)
{
  int aux;
  for (int i = 0; i < n; i++){
    if (Pares.parMasc[i] != 0){
      Pares.tamUSA_M[i] = ((((Pares.parMasc[i] * 6.67) + 19) / 25.4) * 3) - 24;
      printf("numero %f\n", Pares.tamUSA_M[i]);
        
    }
  }
}

void converteFem(int n)
{
  int aux;
  for (int i = 0; i < n; i++){
    if (Pares.parFem[i] != 0){
      Pares.tamUSA_F[i] = ((((Pares.parFem[i] * 6.67) + 19) / 25.4) * 3) - 23;
      printf("numero %f\n", Pares.tamUSA_F[i]);
    }
  }
}




void arredondaMasc(int n)
{
  float resto;
  int numInteiro;
  
  for (int i = 0; i < n; i++){
        if (Pares.tamUSA_M[i] != 0){
          resto = 0;
          numInteiro = 0;
          numInteiro = floor(Pares.tamUSA_M[i]);
          resto = Pares.tamUSA_M[i] - numInteiro;
          
          if (resto < 0.4)
            Pares.tamUSA_M[i] = floor(Pares.tamUSA_M[i]);
          else 
            if (resto >= 0.4 && resto < 0.8)
              Pares.tamUSA_M[i] = floor(Pares.tamUSA_M[i]) + 0.5;
            else
              if (resto >= 0.8)
                Pares.tamUSA_M[i] = floor(Pares.tamUSA_M[i]) + 1;
        }
    }
}


void arredondaFem(int n)
{
  float resto;
  int numInteiro;
  
  for (int i = 0; i < n; i++){
        if (Pares.tamUSA_F[i] != 0){
          resto = 0;
          numInteiro = 0;
          numInteiro = floor(Pares.tamUSA_F[i]);
          resto = Pares.tamUSA_F[i] - numInteiro;
          printf("inteiro %d\n", numInteiro);
          printf("resto %f\n", resto);
          if (resto < 0.4)
            Pares.tamUSA_F[i] = floor(Pares.tamUSA_F[i]);
          else 
            if (resto >= 0.4 && resto < 0.8)
              Pares.tamUSA_F[i] = floor(Pares.tamUSA_F[i]) + 0.5;
            else
              if (resto >= 0.8)
                Pares.tamUSA_F[i] = floor(Pares.tamUSA_F[i]) + 1;
        }
    }
}

void ordenaFem(int n)
{
  int ordenadas, menor;
  float temp;
  
  ordenadas = -1;
  
  do {
      ordenadas++;

      menor = ordenadas;

      for (int i = ordenadas + 1; i < n; i++)
         if (Pares.tamUSA_F[i] < Pares.tamUSA_F[menor])
            menor = i;

      temp = Pares.tamUSA_F[ordenadas];
      Pares.tamUSA_F[ordenadas] = Pares.tamUSA_F[menor];
      Pares.tamUSA_F[menor] = temp;
   }
   while (ordenadas < n);
}

void ordenaMasc(int n)
{
  int ordenadas, menor;
  float temp;
  
  ordenadas = -1;
  
  do {
      ordenadas++;

      menor = ordenadas;

      for (int i = ordenadas + 1; i < n; i++)
         if (Pares.tamUSA_M[i] < Pares.tamUSA_M[menor])
            menor = i;

      temp = Pares.tamUSA_M[ordenadas];
      Pares.tamUSA_M[ordenadas] = Pares.tamUSA_M[menor];
      Pares.tamUSA_M[menor] = temp;
   }
   while (ordenadas < n);
}



void imprimeFem(int n)
{
  printf("F ");
  int contador = 1;
  for (int i = 0; i < n; i++){    
    if (Pares.tamUSA_F[i] != 0){
      for (int j = i + 1; j < n; j++){
        if (Pares.tamUSA_F[i] == Pares.tamUSA_F[j]){
          contador++;
          i++;
        }
      }
    printf("%.1f-(%d) ", Pares.tamUSA_F[i], contador);
    }
    contador = 1;
  }
  printf("\n");
}

void imprimeMasc(int n)
{
  printf("M ");
  int contador = 1;
  for (int i = 0; i < n; i++){    
    if (Pares.tamUSA_M[i] != 0){
      for (int j = i + 1; j < n; j++){
        if (Pares.tamUSA_M[i] == Pares.tamUSA_M[j])
          contador++;        
      }
      printf("%.1f-(%d) ", Pares.tamUSA_M[i], contador);
    }
    contador = 1;
  }
}

int main(void) 
{
  int numPares;
  leituraDados(&numPares);

  if(nFem != 0){
    converteFem(numPares);
    arredondaFem(numPares);
    ordenaFem(numPares);
    imprimeFem(numPares);
  }

  if(nMasc != 0){
    converteMasc(numPares);
    arredondaMasc(numPares);
    ordenaMasc(numPares);
    imprimeMasc(numPares);
  }
  
  return 0;
}