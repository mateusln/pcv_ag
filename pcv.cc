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

using namespace std;

//=====================================================================
// DEFINICAO DE CONSTANTES
//=====================================================================
#define MAX_CITIES		 		100
#define NULO						-1
#define MAX_INT         		0x7FFFFFFF



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


};

//=====================================================================
// FUNCAO PRINCIPAL
//=====================================================================
int main(int argc, char **argv){

Grafo *g = new Grafo;

		g->lerVertice();
		//g->imprimirCidades();
		//g->calcularDistancias();
		//g->imprimirDistancias();
		//g->imprimiBruteForce();
		//g->imprimiAG();
		//g->imprimiBB();

   
   delete g;

   return 0;
}

