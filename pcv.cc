/*Problema do Caixeiro Viajante com alg genetico 
	
1. Primeiro, um conjunto aleatório de rotas são criadas, inicializando assim a população. Este algoritmo cria uma população inicial 'gulosa', o qual dá preferência em montar conexões entre as cidades que estão mais próximas uma da outra.

2.  Segundo, escolha as 2 melhores rotas (menores) da população para o cruzamento (crossover) e combine-os para gerar 2 novas rotas filhas. Grandes chances destas novas rotas filhas serem melhores que os seus pais.

3.  Em raros casos, as rotas filhas sofrem o processo de mutação. Isto é feito para prevenir que todas as rotas da população sejam idênticas

4.  As novas rotas filhas são inseridas na população substituindo no lugar de 2 rotas das maiores existentes. O tamanho da população se mantém constante.

5.  As novas rotas filhas são repetidamente criadas até atingirem um critério de parada desejado (melhor rota).



*/
