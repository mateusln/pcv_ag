/*Problema do Caixeiro Viajante com alg genetico 
	
1. Primeiro, um conjunto aleatório de rotas são criadas, inicializando assim a população. Este algoritmo cria uma população inicial 'gulosa', o qual dá preferência em montar conexões entre as cidades que estão mais próximas uma da outra.

2.  Segundo, escolha as 2 melhores rotas (menores) da população para o cruzamento (crossover) e combine-os para gerar 2 novas rotas filhas. Grandes chances destas novas rotas filhas serem melhores que os seus pais.

3.  Em raros casos, as rotas filhas sofrem o processo de mutação. Isto é feito para prevenir que todas as rotas da população sejam idênticas

4.  As novas rotas filhas são inseridas na população substituindo no lugar de 2 rotas das maiores existentes. O tamanho da população se mantém constante.

5.  As novas rotas filhas são repetidamente criadas até atingirem um critério de parada desejado (melhor rota).



*/

/***********************************************************************
* Adaptado - Bruno D'Amato && Mateus L. Nascimento
************************************************************************/
//=====================================================================
// BIBLIOTECAS
//=====================================================================
#include <stdio.h>//scanf
#include <cmath>//sqrt
#include <algorithm>    // std::next_permutation, std::sort
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
//#include <array>

using namespace std;

//=====================================================================
// DEFINICAO DE CONSTANTES
//=====================================================================
#define MAX_CITIES		 		100
#define NULO						-1
#define MAX_INT         		0x7FFFFFFF
//Populacao maxima
#define POP_MAX 362880



//=====================================================================
// DEFINICAO DE TIPOS
//=====================================================================

//=====================================================================
// CLASSE GRAFO
//=====================================================================

class Grafo {
   private:
      int numCidades;

	  int cidadesx[MAX_CITIES];
	  int cidadesy[MAX_CITIES];
      int matriz[MAX_CITIES][MAX_CITIES];//int
      int rotas[POP_MAX][MAX_CITIES];
      
   public:
      //--------------------------------------------------------------------
      // Construtor
      //--------------------------------------------------------------------
      Grafo(){
		 numCidades = 0;
		 limparCidadesXYeMATRIZ();
		 
      }//-------------------------------------------------------------------


      //--------------------------------------------------------------------
      // Destrutor
      //--------------------------------------------------------------------
      ~Grafo(){
      }//-------------------------------------------------------------------

	  
	  
	  //--------------------------------------------------------------------
      // lerVertice: Realiza a leitura do Vertice.
      //--------------------------------------------------------------------
	  
	  void lerVertice(){
		int x = 0, y = 0, casos;
	  	scanf ("%d",&casos); //0 a 100
		if(casos >= 0 && casos <= 100){
			while(casos--) {
				scanf("%d %d",&x,&y);//0 a 1000
				if( (x >= 0 && x <= 1000) && (y >= 0 && y <= 1000) && (numCidades < MAX_CITIES) ){
					//inserirCidade();
					cidadesx[numCidades]=x;
					cidadesy[numCidades]=y;
					numCidades++;
				}
			}
		}
	  }
	  
	  //--------------------------------------------------------------------
      // calcularDistancias: Insere coordenadas da cidade.
      //--------------------------------------------------------------------
	  
	  void calcularDistancias(){
		for(int lin = 0; lin < numCidades; lin++){
			for(int col = lin; col < numCidades; col++){
				matriz[lin][col] = sqrt((cidadesx[lin] - cidadesx[col])*(cidadesx[lin] - cidadesx[col]) + (cidadesy[lin] - cidadesy[col])*(cidadesy[lin] - cidadesy[col]));
				matriz[col][lin] = sqrt((cidadesx[lin] - cidadesx[col])*(cidadesx[lin] - cidadesx[col]) + (cidadesy[lin] - cidadesy[col])*(cidadesy[lin] - cidadesy[col]));
				//mirror matriz para não fazer comparação se pos ou pos+1 é < || >
			}
		}
	  
	  }
	  
	  
	  //--------------------------------------------------------------------
      // imprimirCidades: Imprimi cidades.
      //--------------------------------------------------------------------
	  
	  void imprimirCidades(){
		for(int pos = 0;pos < numCidades;pos++){
			printf("cidade:%d x:%d y:%d\n",pos,cidadesx[pos],cidadesy[pos]);
		}
	  }
	  
	  //--------------------------------------------------------------------
      // limparCidadesXYeMATRIZ
      //--------------------------------------------------------------------
	  
	  void limparCidadesXYeMATRIZ(){
		for(int pos = 0;pos < MAX_CITIES;pos++){
			cidadesx[pos] = NULO;
			cidadesy[pos] = NULO;
		}
		for(int l = 0; l<MAX_CITIES; l++){
			for(int c = 0; c<MAX_CITIES; c++){
				matriz[l][c] = NULO;
			}
		
		}
	  }
	  
      //--------------------------------------------------------------------
      // imprimirDistancias
      //--------------------------------------------------------------------
	  
	void imprimirDistancias(){
	
		printf("\nN = (%i)\n\t",numCidades);
		  for(int lin = 0; lin < numCidades; lin++){
		    if (lin == 100){
               printf("\t(%i) ",lin);
            }else if(lin >= 10){
               printf("\t(0%i) ",lin);
            }else{
               printf("\t(00%i) ",lin);
            }
		  }
		  
		    for(int lin = 0; lin < numCidades; lin++){
				if (lin == 100){
				   printf("\n(%i) ",lin);
				}else if(lin >= 10){
				   printf("\n(0%i) ",lin);
				}else{
				   printf("\n(00%i) ",lin);
				}
				
				for(int col = 0;col < numCidades ; col++){
					if(matriz[lin][col] == NULO){
					   printf("\t.     ");
					}else{
					   printf("\t%i     ",matriz[lin][col]);
					}
				}
		    }
	}
	
	int distanciaDoVetor(int permutation[]){
		
		int resp = 0;
		/*printf("\n");
		for(int pos = 0; pos < numCidades; pos++){
				printf("%d ",permutation[pos]);
		}*/
		for(int pos = 0; pos < numCidades-1; pos++){
			//printf("(%d-%d)resp:%d mat:%d \n",permutation[pos],permutation[pos+1],resp,matriz[permutation[pos]][permutation[pos+1]]);
			resp = resp + matriz[permutation[pos]][permutation[pos+1]];
			
		}	
		resp = resp + matriz[permutation[0]][permutation[numCidades-1]]; //se a ultima cidade volta pra primeira
		//printf("ini-fim: %d\n",matriz[permutation[0]][permutation[numCidades-1]]);
		//printf("resp:%d\n",resp);
		return resp;

	}
	
	void permuta(){
		int permutationO[MAX_CITIES], distance=0;
		int conta_pop=0;
		int distancias[POP_MAX];
		int min = MAX_INT, min2=MAX_INT,pos=0,pos2=0;
		
		
		for(int pos = 0; pos < MAX_CITIES; pos++){//inicializa vetor
			permutationO[pos] = NULO;
			
		}	
		for(int pos = 0; pos < numCidades; pos++){//constroi indice
			permutationO[pos] = pos;
		}
		
		do{
			
			distancias[conta_pop] = distanciaDoVetor(permutationO);
			if( distancias[conta_pop] < min){//procura menor distancia
				pos2=pos;//posicao do segundo menor elem
				min2=min;
				min = distancias[conta_pop]; 
				pos=conta_pop;//posicao do menor elemento
			}
		   for(int i = 0; i <  numCidades ; i++){ 
                rotas[conta_pop][i]=permutationO[i];
                //cout<<rotas[conta_pop][i]<<" ";
           }
           //cout<<distancias[conta_pop] ;
        	conta_pop++;
			//cout<<" "<<endl;
			//crossover(rotas[0],rotas[conta_pop-1]);
		}while(next_permutation(permutationO+1,permutationO+numCidades) && conta_pop<POP_MAX);
		
			crossover(rotas[pos2],rotas[pos]);
			rotas[pos2]=-1;
			rotas[pos]=-1;
			
			//cout<<pos2<<" min "<<min2 <<endl;
			//cout<<pos<<" min "<<min <<endl;
	
	}
	
	//crossover
	
	void crossover(int p1[],int p2[]){//recebe pai1 e pai2
	srand (time(NULL));
		//numCidades=4;
		int f1[numCidades];
		int particao=rand() % (numCidades);
		int particao2= ( rand() % (numCidades/2) ) + numCidades/2;
		cout<<particao2<<endl;
		
		//f1[2]==NULL;
/*		for(int i=0; i< numCidades; i++){
			if (i<particao  )
				f1[i]=p1[i];
			else 
				f1[i]=p2[i];
			//else
				//f1[i]=p1[i];
			
				
			cout<<f1[i]<< " ";
		}
	*/	
	for(int i=0 , j=numCidades; i< particao; i++,j--){
			if ( contem(f1,p1[i])==-1  )
				f1[i]=p1[i];
			else 
				f1[i]=p2[i];
				
			
		}
		
		for(int i=particao; i< numCidades; i++)
		if ( contem(f1,p2[i])==-1  )
				f1[i]=p2[i];
			else 
				f1[i]=p1[i];
		
		for(int i=0; i< numCidades; i++)
			cout<<f1[i]<< " ";
	cout<<endl;
	cout<<distanciaDoVetor(f1)<<endl;
			
		
	
	}
	
	int contem(int vet [], int x){ // retorna a posicao do elemento x se ele existir e -1 se ele n existir no vetor
		for(int i=0; i< sizeof(vet) / sizeof(int) ; i++)
			if ( vet[i]==x )
				return i;
		
		return -1;
	}
		


};

//=====================================================================
// FUNCAO PRINCIPAL
//=====================================================================
int main(int argc, char **argv){
/* initialize random seed: */
//  srand (time(NULL));
Grafo *g = new Grafo;
		int p1[4]={1,2,3,4};
		int p2[]={4,3,2,1};
		//std::find(p1.begin(), p1.end(), 1) ;
		
		/*size_t p1size = sizeof(p1) / sizeof(int);
		int *end = p1 + p1size;
		if(std::find(p1, end, 10)!=end)
		cout<<"achei";
		*/
		//cout<< g->contem(p1,4,10)<< endl;
		
		g->lerVertice();
		g->calcularDistancias();
		//g->crossover(p1,p2);
		//g->imprimirDistancias();
		g->permuta();
		//g->imprimiBruteForce();
		//g->imprimiAG();
		//g->imprimiBB();

   
   delete g;

   return 0;
}

