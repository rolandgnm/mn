#include <string.h>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

void modoConversao();

void modoSistemaLinear();

double **alocaMatriz(int l, int c);

void imprimeMatriz(double **M, int l, int c);

void resolveSL(double **m, int *indice, int n);

void jordan(double **m, int n);

void modoEquacao(char opcao);

void converteParteInteira(double parteInteira, int base);

char doubleParaBaseChar(int resto, int base);

char recebeHexChar(int resto);

void inverteVentorChar(char *saida);

void trocaPosicoes(char *posInicial, char *posFinal);

/*
 * EP de Metodos Numericos
 * Alunos:
 *     Daniele Delmiro
 *     Joamila Brito
 *     Jonatas Cartaxo
 *     Roland Gabriel
 */

int main(void) {
    char opcao = '0';

    while (opcao != 'F') {
        /*
         * Menu Inicial
         */
        printf("-> �C� � Convers�o, �S� � Sistema Linear, �E� � Equa��o Alg�brica e �F� � Finalizar:\n");
        scanf("%s",&opcao); 

        switch (opcao) {
            case 'C':
                modoConversao();
                break;
            case 'S':
                modoSistemaLinear();
                break;
            case 'E':
                modoEquacao(opcao);
                break;
            case 'F':
                return 0;
            default:
                printf("Erro! - Entrada desconhecida\n");
                break;
        }

        opcao = '0';
    }

    return 0;
}


/*
 * Para fins de organização do código,
 * utilizar os escopos definidos por comentarios
 * para agrupar funcoes relacionadas.
 */

/*
 * Escopo CONVERSAO:
 */
void modoConversao() {
    double entrada, parteInteira, parteFracionaria;
    char saida[41];

    //recebe valor de entrada
    printf("-> Entre com um numero Decimal: \n");
    scanf("%lf", &entrada);

    //Separa numero decimal em parte inteira e parte fracionaria.
    parteFracionaria = modf(entrada, &parteInteira);

    printf("entrada: %f , parte inteira: %f , parte fracionaria: %f\n", entrada, parteInteira,
           parteFracionaria); //TODO APAGAR DPS

//    /* char* = */ converteParteInteira(parteInteira, 2);
    //char* = converteParteInteira(parteFracionaria, 8);
    //char* = converteParteInteira(parteFracionaria, 16);
    converteParteInteira(parteInteira, 2);
    converteParteInteira(parteInteira, 8);
    converteParteInteira(parteInteira, 16);


    //TODO A FINALIZAR...



}


void converteParteInteira(double parteInteira, int base) {
    //TODO INVERTER char* saida ANTES DE RETORNAR.
    //TODO MUDAR RETORNO PARA char* NA ASSINATURA TAMBEM NO TOPO DO ARQUIVO

    double dividendo;
    char *saida = NULL; //Importante pra o realloc().
    int resto, posicao = 0;


    /*
     * int dividendo: tera papel de dividendo no inicio da iteracao e
     *                  quociente no fim da iteracao.
     */
    dividendo = parteInteira;

    /*
     * do-while cria palavra do numero saida' invertida;
     * TODO aplicar funcao de inversao para obter valor correto.
     */
    do {
        //aloca espaço na memoria dinamicamente.
        saida = (char *) realloc(saida, sizeof(char) * posicao + 1);

        resto = (int) fmod(dividendo, (double) base); //fmod: retorna o resto da operacao: param1/param2.
        dividendo = floor(dividendo / base); //floor: retorna maior inteiro menor que parametro de entrada.

        //coloca valor gerado na posicao criada na str dinamica.
        saida[posicao] = doubleParaBaseChar(resto, base);
        posicao += 1;

    } while (dividendo >= base);

    //aloca posicao na string para
    saida = (char *) realloc(saida, sizeof(char) * posicao + 2);
    saida[posicao] = doubleParaBaseChar(dividendo, base);
    saida[posicao + 1] = '\0'; //fecha string.
    //fim do algoritmo

    //todo inverter e retornar.
    inverteVentorChar(saida);

    printf("%s\n_\n", saida);
    //return saida;


}

void inverteVentorChar(char *saida) {
    int posFinal = (int) strlen(saida) - 1, posInicial = 0;

    if ((posFinal + 1) == 1) return;

    while ((posFinal - posInicial) > 0) {
        trocaPosicoes(&saida[posInicial], &saida[posFinal]);
        posInicial++;
        posFinal--;
    }


}

void trocaPosicoes(char *posInicial, char *posFinal) {
    char temp = *posFinal;
    *posFinal = *posInicial;
    *posInicial = temp;
}

char doubleParaBaseChar(int resto, int base) {
    char c;
    switch (base) {
        case 2:
            c = (char) ('0' + resto);
            break;
        case 8:
            c = (char) ('0' + resto);
            break;
        case 16:
            c = recebeHexChar(resto);
            break;
        default:
            c = '-';
            break;
    }

    return c;

}

char recebeHexChar(int resto) {
    char c;

    if (resto > 9) {
        switch (resto) {
            case 10:
                c = 'A';
                break;
            case 11:
                c = 'B';
                break;
            case 12:
                c = 'C';
                break;
            case 13:
                c = 'D';
                break;
            case 14:
                c = 'E';
                break;
            case 15:
                c = 'F';
                break;
            default:
                c = '-';
                break;
        }
    } else {
        c = (char) ('0' + resto);
    }

    return c;
}


/*
 * Fim de CONVERVSAO!
 */

/*
 * Escopo SISTEMA:
 */
 
/*Se houver mem�ria dispon�vel, aloca dinamicamente uma matriz 
bidimensional de double com l linhas e c colunas. Devolve um ponteiro 
para essa matriz. Caso contr�rio, devolve um ponteiro nulo.*/
double **alocaMatriz(int l, int c){
	int i, j;
	double **M;
	
	/*Alocando as linhas da matriz*/
	M=malloc(sizeof(M)*l);
	if(M==NULL){//Falta de mem�ria
		return NULL;
	}
	
	/*Alocando as colunas da matriz*/
	for(i=0;i<l;i++){
		M[i]=malloc(sizeof(double)*c);
		if(M[i]==NULL){//Falta de mem�ria
			for(j=0;j<i;j++){
				free(M[j]);
			}
			free(M);
			return NULL;
		}
	}
	
	return M;
	/*Fim alocaMatriz*/
}

/*Imprime uma matriz com l linhas e c colunas*/
void imprimeMatriz(double **M, int l, int c){
	int i, j;
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			printf("%8.3lf ", M[i][j]);
		}
		printf("\n");
	}
	/*Fim imprimeMatriz*/
}

/*Recebe m, a matriz aumentada de um SL diagonal com n 
equa��es e n vari�veis. Se o SL for incompat�vel, devolve 2; se for 
determinado, devolve 0 e coloca em x a solu��o do SL; se for 
indeterminado, devolve 1 e coloca em x a solu��o do SL na qual as 
vari�veis livres tem valor 0.*/
void resolveSL(double **m, int *indice, int n){
	int i, j=0, tipo=0;
	double x[n], aux[n];
	
	for(i=0; i<n; i++){
		if(m[i][i]==0){
			if(m[i][n]==0){
				tipo = 1;
				x[i] = 0;
			}
			else{
				tipo = 2;
				printf("Sistema incompativel!\n");
				return;
			}
		}
		else{
			x[i] = m[i][n]/m[i][i];
		}	
	}
	
	/*Copia os valores de x em um vetor auxiliar, que ser� usado
	caso tenha ocorrido troca de colunas durante a execu��o da
	fun��o jordan.*/
	for(i=0; i<n; i++){
		aux[i] = x[i];
	}
	
	/*Ordena os valores de x caso tenha ocorrido troca de colunas*/
	while(j<n){
		if(indice[j]!=j+1){
			x[indice[j]-1] = aux[j];
		}
		j++;
	}
	
	//Resultado do SL
	if(tipo==0){
		printf("Sistema compativel determinado!\n");
	}
	else{
		printf("Sistema compativel indeterminado!\n");
	}
	for(i=0;i<n;i++){
	 	printf("%8.3lf ", x[i]);
	}
	printf("\n");
}
/*Fim da fun��o resolveSL*/

/* Recebe m, a matriz aumentada de um SL com n vari�veis e n 
equa��es e transforma a matriz de coeficientes do SL numa 
matriz diagonal. Em seguida, chama a fun��o resolveSL para resolver
o SL, efetivamente.*/
void jordan(double **m, int n){
	int i, j, k, w, aux;
	double mult, coluna[n+1];
	int indice[n];
	
	//Vetor com a ordem das colunas dos coeficientes
	for(i=0; i<n; i++){
		indice[i] = i+1;
	}
	
	for(i=0;i<n;i++){
		//Piv� igual a 0
		if(m[i][i]==0){
			j=i+1;
			while(j<n && m[i][j]==0){
				j++;
			}
			
			if(j<n){
				for(w=0; w<n; w++){
					//Troca as colunas
					coluna[w] = m[w][i];
					m[w][i] = m[w][j];
					m[w][j] = coluna[w];
					
					//Troca o �ndice das colunas
					aux = indice[i];
					indice[i] = indice[j];
					indice[j] = aux;
 				}
			}
			if(j==n-1){
				for(w=0; w<n; w++){
					m[w][j] = 0;
				}
			}
		}
		
		//Piv� diferente de 0
		if(m[i][i]!=0){
			for(j=i-1;j>=0;j--){
				mult=-m[j][i]/m[i][i];
				m[j][i]=0;
				for(k=i+1;k<=n;k++){
					m[j][k]+=mult*m[i][k];
				}
			}
			
			for(j=i+1;j<n;j++){
				mult=-m[j][i]/m[i][i];
				m[j][i]=0;
				for(k=i+1;k<=n;k++){
					m[j][k]+=mult*m[i][k];
				}
			}
		}
	}
	
	printf("SL diagonalizado!\n");
	imprimeMatriz(m, n, n+1);
	
	//Chamada da fun��o resolveSL que resolve o SL.
	resolveSL(m, indice, n);
}
/*Fim do m�todo jordan*/

/*O m�todo pede que o usu�rio digite o nome de um arquivo .txt (nome_arq) que contenha
o grau (grau) e os coeficientes (coef) de um SL. Os caracteres do arquivo s�o convertidos
para valores inteiros. Uma matriz M � alocada e os coeficientes s�o adicionados
nela. Por fim, a fun��o jordan � chamada para diagonalizar a matriz e resolver o SL.*/
void modoSistemaLinear(){
	char nome_arq[37], grau_c[14];
	int grau=0, i=0, j=0, linha=0, count=0, i_neg=0;
	char coef_c[18];
	double **M;
	FILE *arq;
	
	//Leitura do nome do arquivo pelo teclado. Omite-se a extens�o.
	printf("Nome de um arquivo (com ate 32 caracteres): ");
	scanf("%s", &nome_arq);
	
	//Abertura do arquivo
	strcat(nome_arq, ".txt");
	arq = fopen(nome_arq, "r");
	if(arq==NULL){
		printf("ERRO, nao foi possivel abrir o arquivo!\n");
	}
	else{
		//Extra��o do grau do SL
		fscanf(arq, "%s\n", &grau_c);
		grau = atoi(grau_c);
		printf("%d\n", grau);
		
		char coef[(grau*18)+(grau+1)];
		
		/*Aloca-se uma matriz com quantidade de linhas igual ao grau do SL.
		E quantidade de colunas igual ao grau do SL + 1.*/
		M = alocaMatriz(grau, grau+1);
		if(M==NULL){//Falta mem�ria
			printf("Deu pau!");
			return;
		}
		
		/*Leitura dos coeficientes e atribui��o de cada um deles a uma
		posi��o da matriz.*/ 
		while(!feof(arq)){
			fgets(coef, sizeof(coef), arq);
			
			while(coef[i]!='\0'){
				if(coef[i] != ' '){
					coef_c[j] = coef[i];
					j++;	
				}
				else{
					if(coef_c[j]!='\0') coef_c[j]='\0';
					M[linha][count] = atoi(coef_c);
					count++;
					j = 0;
				}
				i++;	
			} 
			if(coef[i]=='\0'){
				if(coef_c[j]!='\0') coef_c[j]='\0';
				M[linha][count] = atoi(coef_c);
				linha++;
			}
			
			i = 0;
			j = 0;
			count = 0;
		}
	}
	fclose(arq);
	
	//Chamada da fun��o jordan.
	jordan(M, grau);
}
/*Fim do m�todo modoSistemaLinear*/

/*
 * Fim de SISTEMA:
 */

/*
 * Escopo EQUACAO:
 */
void modoEquacao(char opcao) { printf("%c\n", opcao); }

/*
 * Fim de EQUACAO:
 */
