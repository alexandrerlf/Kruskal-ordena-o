#include <iostream>                                     //biblioteca padrao
#include <fstream>                                      //biblioteca ler arquivo
#include <vector>                                       //biblioeca vector  
#include <sstream>                              
#include <math.h>                                       //biblioteca distancia euclidiana
#include <time.h>                                       //biblioteca calcular tempo
#include <list>

using namespace std;


vector<int> MaxHeapify(vector<int> heap, int i){

	
	//int pai = floor( (i-1)/2 );
	int filhoD = 2*i + 1;//adquiri os indices dos filhos
	int filhoE = 2*i + 2;
	int maior = i;//e do seu pai

	if( (filhoE <= heap.size() ) && (heap[filhoE] > heap[maior]) ){//se o conteudo do filho maior e nao chegou ao final do
		maior = filhoE;											  // heap atualiza maior	
	}
	if( (filhoD <= heap.size() ) && (heap[filhoD] > heap[maior]) ){
		maior = filhoD;
	}
	if(maior != i){//se maior foi atualizado, troca pai por filho
		swap(heap[i], heap[maior]);
		heap = MaxHeapify(heap, maior);//e desce na arvore do filho atualizado, fazendo trocas se necessario
		
	}
	return heap;
}

vector<int> BuildMaxHeap(vector<int> heap){

	//int tam_heap =  heap.size();
	
	int i = floor((heap.size())/2) - 1 ;//adquiri o indice do ultimo pai da arvore

	for(i ; i >= 0; i-- ){//e começa por ele, passando por todos os outros pai de indice maior para o menor ate a raiz
		cout << i << endl;
		heap = MaxHeapify(heap, i);	

	}

	return heap;
}

vector<int> Heapsort(vector<int> heap){

	heap = BuildMaxHeap(heap);			//constroi o heap maximo
	
	vector<int> ordenado;
	int i = heap.size() - 1;

	for(i ;i >= 0 ; i-- ){		
		ordenado.insert(ordenado.begin(), heap[0]);		//inseri na frente toda vez, "LIFO" em posição
		swap(heap[0], heap[i]);							//troca o conteudo da raiz com o conteudo do ultimo no heap
		heap.pop_back();								//retirar o maior valor do heap, q esta na ultima posição agora 
		heap = MaxHeapify(heap, 0);						//recoloca o maior valor na raiz				
	}
	return ordenado;
}

vector<int> counting(vector<int> in){
    
	
	vector<int> out;
    vector<int> aux;        
	int max = 0;
	out.resize(in.size());

	/*cout << "entrada: " << endl;
	for(int i = 0; i < in.size(); i++){
		cout << in[i] << ", ";
	}*/

	for(int i = 0; i < in.size(); i++){//descobre o maior valor
		if( in[i] > max){
			max = in[i];
		}
	}

	aux.resize(max+1);

	for( int i = 0; i <= max; i++){//inicializa aux com 0
		aux[i] = 0;
	}

	for( int i = 0; i < in.size(); i++){//soma as ocorrencias de cada numeros
		aux[ in[i] ] = aux[ in[i] ] + 1 ;//e armazena na posição deste numero		

	}

	for( int i = 0; i <= max; i++){//att o vetor auxiliar com a soma de cada posição
		aux[i+1] = aux[i] + aux[i+1];
	}

	for(int i = (in.size() - 1); i >= 0; i--){//varre o vector de entrada da direita para esquerda
											//a fim de garantir a ordem de numeros iguais no vetor final
		out[ aux[ in[i] ] - 1 ] = in[i];	//inseri na posição do vetor de saida o valor do de entrada a partir da posução no aux 	
		aux[ in[i] ] -= 1;					//decrementa o conteudo de aux
	}

	/*cout <<"\n";
	cout << "saida: " << endl;
	for(int i = 0; i < in.size(); i++){
		cout << out[i] << ", ";
	}*/
	
	return out;
}

int distaciaEuclidiana(double x1, double y1, double x2, double y2){

    int distancia;
    double hipotenusa;
    double x; 
    double y;
    x = x1 - x2;
    y = y1 - y2;     

    hipotenusa = hypot(x,y); 

    distancia = (int)round(hipotenusa);

    return distancia;
}

int main(){

	ifstream file;	
	stringstream output; 

	file.open("n1500A.txt");

	int i, l, c; //interadores
	int v = 1500;
	double aux2;
	vector<double> coorX;
	vector<double> coorY;
	vector<int> prioridade;
	int min = 100000;
	bool vertice[v]; 
	int linha, coluna;
	clock_t tempo_inicial, tempo_final; // calculo tenmpo de exercução

    int **matrix = new int*[v]; //instancia a matrix de adjacencia de 1500x1500
	for(int l = 0; l < v; l++)
		matrix[l] = new int[v];
	for(int l = 0; l < v; l++)
		for(int c = 0; c < v; c++)//e inicia ela zerada
			matrix[l][c] = 0;

	for(i = 0; i < v; i++){//adquirir as coordenadas
    	file >> aux2;
        coorX.push_back(aux2);
        file >> aux2;
        coorY.push_back(aux2);
    }   
    file.close(); 

    for(i = 0; i < v; i++){
    	vertice[i] = false;
    }	

   for(l = 0; l < v; l++){//e cria a matrix de adjacencia ponderada
    	for(c = 0; c < v ; c++){
    		matrix[l][c] = distaciaEuclidiana(coorX[l], coorY[l], coorX[c], coorY[c]);	
    	}
    }

	for(l = 0; l < v ; l++){            
    	for (c = l+1 ; c < v; c++){//c=l para pegar a matrix triangular superior                                     	                   
            	min = matrix[l][c];  
            	prioridade.push_back(min);         	          
        }
    }   

    vector<int> ordenado;
    ordenado.resize(prioridade.size());

	tempo_inicial = clock();	
	//ordenado = counting(prioridade);
	ordenado = Heapsort(prioridade);
	tempo_final = clock()

	output << "\n";
	output << "ordenado por Heapsort" << endl;
	//output << "ordenado por counting" << endl;
	output << "\t" << "Tempo de exercucao " << ": " << (tempo_final - tempo_inicial) / (double)CLOCKS_PER_SEC << " seg" << endl;


    reverse(ordenado.begin(),ordenado.end());
    vector<int> grafo;

    it = ordenado.begin();
    while(it != ordenado.end()){

    	
    	aresta_segura  = ordenado.back(); // retorna o conteudo da ultima posicao
    	ordenado.pop_back();

		for(l = 0; l < v ; l++){            
	    	for (c = l+1 ; c < v; c++){//c=l para pegar a matrix triangular superior                                     	                   
	            	if( (matrix[l][c] == aresta_segura) && (vertice[c] == false) ){
	            		vertice[c] = true;
	            		grafo.push_back(aresta_segura);
	            	}              	         	          
	        }
	    }

    }
    reverse(grafo.begin(),grafo.end());
    
    /*//VERIFICAÇÃO DE ENTRADAS
    cout << "coordenadas: " << endl;
    for(i = 0; i < v; i++){//adquirir as coordenadas
    	cout << "(" << coorX[i] << "," << coorY[i] << ")" << endl;
    }
    cout << "Matrix: " << endl;  
   	for(l = 0; l < v; l++){//e cria a matrix de adjacencia ponderada
    	for(c = 0; c < v ; c++){
    		cout << matrix[l][c] << " ";	
    	}
    cout << " \n";	
    }
    cout << "Prioridade: " << endl;
    for(int i = 0; i < prioridade.size(); i++){
    	cout << prioridade[i] << " ";
    }
    cout << " \n";
    //FIM VERIFICAÇÃO*/

    /*//TESTE ORDENAÇÃO - VECTOR PRIORIDADE
	vector<int> ordenado;
	ordenado.resize(prioridade.size());
	
	cout << "TAM ORDENADO: " << ordenado.size() << endl;
	cout << "TAM PRIORIDADE: " << prioridade.size() << endl;

	//output << "TESTE COUNTING" << endl;
	output << "TESTE HEAPSORT" << endl;
	output << "\n";

	tempo_inicial = clock();	
	//ordenado = counting(prioridade);
	ordenado = Heapsort(prioridade);
	tempo_final = clock();

	output << "\n";
	for(int i = 0; i < ordenado.size(); i++){
		output << ordenado[i] << ", ";	}

	output << "\n";
	output << "\t" << "Tempo de exercucao " << ": " << (tempo_final - tempo_inicial) / (double)CLOCKS_PER_SEC << " seg" << endl;
	//FIM TESTE*/

    ofstream saida("saida.txt", ofstream::out);
    saida << output.str();	

	#if defined(_WIN32)
    //ABRE O .TXT SAIDA NO WIN
    system("start notepad saida.txt");
    #endif

    delete[] matrix;

	return 0;
}