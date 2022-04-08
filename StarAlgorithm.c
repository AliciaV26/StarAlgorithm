//El código funciona para un ejemplo específico de un grafo

# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <conio.h>
# include <stdbool.h>


struct nodo{
	float costo_h;
	int id;
	int nodo_relacionado1;
	float nr1_valor;
	int nodo_relacionado2;
	float nr2_valor;
	int nodo_relacionado3;
	float nr3_valor;
};

int Imprimir(float costo_total, int cerrados[], int nodos_cerrados);
int BuscaNodo(struct nodo ciudad[' '], float costo_total, int cerrados[], int nodos_cerrados, int n_inicial, int n_final);

int main(){
	
	struct nodo ciudad[6];
	int i;
	int cerrados[6];
	int nodos_cerrados = 0;
	char nodo_inicial, nodo_final;
	int n_inicial, n_final;
	float costo_total = 0;


	for (i=65; i<=70; i++ ){
		ciudad[i-65].id = i-64;  //Indicar id del nodo
	}
	
	
	//Costo heurísticos
	ciudad[0].costo_h = 2; //A
	ciudad[1].costo_h = 3; //B
	ciudad[2].costo_h = 1; //C
	ciudad[3].costo_h = 4; //D
	ciudad[4].costo_h = 2; //E
	ciudad[5].costo_h = 3; //F
	
	system("cls");
	
	//Nodos relacionados
	
	//A
	ciudad[0].nodo_relacionado1 = 2; //B
	ciudad[0].nr1_valor = 2;
	ciudad[0].nodo_relacionado2 = 3; //C
	ciudad[0].nr2_valor = 5;
	ciudad[0].nodo_relacionado3 = 5; //5
	ciudad[0].nr3_valor = 5;
	
	//B
	ciudad[1].nodo_relacionado1 = 1; //A
	ciudad[1].nr1_valor = 2;
	ciudad[1].nodo_relacionado2 = 5; //E
	ciudad[1].nr2_valor = 1;
	ciudad[1].nodo_relacionado3 = 6; //F
	ciudad[1].nr3_valor = 6; 
	
	//C
	ciudad[2].nodo_relacionado1 = 1; //A
	ciudad[2].nr1_valor = 5;
	ciudad[2].nodo_relacionado2 = 4; //D
	ciudad[2].nr2_valor = 4;
	ciudad[2].nodo_relacionado3 = 6; //F
	ciudad[2].nr3_valor = 1; 
	
	//D
	ciudad[3].nodo_relacionado1 = 3; //C
	ciudad[3].nr1_valor = 4;
	ciudad[3].nodo_relacionado2 = 6; //F
	ciudad[3].nr2_valor = 4;
	ciudad[3].nodo_relacionado3 = 5; //D
	ciudad[3].nr3_valor = 2; 
	
	//E
	ciudad[4].nodo_relacionado1 = 1; //A
	ciudad[4].nr1_valor = 5;
	ciudad[4].nodo_relacionado2 = 2; //B
	ciudad[4].nr2_valor = 1;
	ciudad[4].nodo_relacionado3 = 4; //F
	ciudad[4].nr3_valor = 2; 
	

	//F
	ciudad[5].nodo_relacionado1 = 2; //B
	ciudad[5].nr1_valor = 6;
	ciudad[5].nodo_relacionado2 = 3; //C
	ciudad[5].nr2_valor = 1;
	ciudad[5].nodo_relacionado3 = 4; //F
	ciudad[5].nr3_valor = 4;  
	
	
	//Nodo inicial y final
	printf("\nIngresa el nodo inicial: ");
	nodo_inicial = getche();  
	
	printf("\nIngresa el nodo final: ");
	nodo_final = getche();  
	
	puts("\n\n\n");
	system("pause");
	nodo_inicial = toupper (nodo_inicial);
	nodo_final = toupper (nodo_final);
	
	switch (nodo_inicial){
		case 'A': n_inicial = 1;
		break;
		case 'B': n_inicial = 2;
		break;
		case 'C': n_inicial = 3;
		break;
		case 'D': n_inicial = 4;
		break;
		case 'E': n_inicial = 5;
		break;
		case 'F': n_inicial = 6;
		break;
	}

	switch (nodo_final){
		case 'A': n_final = 1;
		break;
		case 'B': n_final = 2;
		break;
		case 'C': n_final = 3;
		break;
		case 'D': n_final = 4;
		break;
		case 'E': n_final = 5;
		break;
		case 'F': n_final = 6;
		break;
	}			
	
	//Iniciar búsqueda
	if (n_inicial == n_final){
		cerrados[0] = n_inicial;
		nodos_cerrados++;
		Imprimir(costo_total, cerrados, nodos_cerrados);
	}
	else{
		cerrados[0] = n_inicial;
		nodos_cerrados++;
		BuscaNodo(ciudad, costo_total, cerrados, nodos_cerrados, n_inicial, n_final);
	}
	
}

int BuscaNodo(struct nodo ciudad[' '], float costo_total, int cerrados[], int nodos_cerrados, int n_inicial, int n_final){
	
	bool nre; //nodo relacionado encontrado
	int i, nodo_conectado1, nodo_conectado2, nodo_conectado3;
	bool nodo_encontrado = false;
	float costo_f;
	float costos[3]; //Arreglo de los costos de los nodos relacionados
	int nodo_mejor;
	
	
	
	while(nodo_encontrado == false){
			nodo_encontrado = false;
			
			//Buscar id de los nodos conectados para saber su coste heurístico
			for(i=0;i<6;i++){
				if(ciudad[i].id == ciudad[n_inicial-1].nodo_relacionado1){
					nodo_conectado1 = i;
				}
				if(ciudad[i].id == ciudad[n_inicial-1].nodo_relacionado2){
					nodo_conectado2 = i;
				}
				if(ciudad[i].id == ciudad[n_inicial-1].nodo_relacionado3){
					nodo_conectado3 = i;
				}
			}
			
			
			
			//Costos de los nodos conectados
			costos[0] = ciudad[nodo_conectado1].costo_h + ciudad[n_inicial-1].nr1_valor;
			costos[1] = ciudad[nodo_conectado2].costo_h + ciudad[n_inicial-1].nr2_valor;
			costos[2] = ciudad[nodo_conectado3].costo_h + ciudad[n_inicial-1].nr3_valor;
				
		
			//Encontrar mejor(menor) costo
			costo_f = costos[0];
			nodo_mejor = nodo_conectado1+1;
			
			if((costos[1] < costo_f)){ 
				costo_f = costos[1];
				nodo_mejor = nodo_conectado2+1;
			}
			if((costos[2] < costo_f) ) { 
				costo_f = costos[2];
				nodo_mejor = nodo_conectado3+1;
			}
			if(n_final == (nodo_conectado1+1)){
				costo_f = costos[0];
				nodo_mejor = nodo_conectado1+1;	
			}
			if(n_final == (nodo_conectado2+1)){
				costo_f = costos[1];
				nodo_mejor = nodo_conectado2+1;	
			}
			
			if(n_final == (nodo_conectado3+1)){
				costo_f = costos[2];	
				nodo_mejor = nodo_conectado3+1;		
			}	
		
			
		
			costo_total += costo_f; 
			nodos_cerrados++;
			cerrados[nodos_cerrados-1] = nodo_mejor;
			if((nodo_mejor) == n_final){
				nodo_encontrado = true;
			}
			else{
				n_inicial = nodo_mejor;
				BuscaNodo(ciudad, costo_total, cerrados, nodos_cerrados, n_inicial, n_final);
			}
			
	}//encontrado = false
		
	if (nodo_encontrado == true){
		Imprimir(costo_total, cerrados, nodos_cerrados);
	}

};


int Imprimir(float costo_total, int cerrados[], int nodos_cerrados){
	
	int i;
	system("cls");
	printf("\nEl costo total y camino fueron encontrados");
	printf("\nCosto total = %c%.2f", 36,costo_total);
	printf("\nCamino: ");
	for(i=0;i<nodos_cerrados;i++){
		if(i<nodos_cerrados-1){
			printf("%c, ", cerrados[i]+64);
		}
		else{
			printf("%c", cerrados[i]+64);
		}
			
	}
	return 0;
	
};
