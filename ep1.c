/**
 * EP de Metodos Numericos
 * Alunos:
 *     Daniele Delmiro
 *     Joamila Brito
 *     Jonatas Cartaxo
 *     Roland Gabriel
 */

#include <string.h>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define EPSILON 0.000001


void modoConversao();

void modoSistemaLinear();

double **alocaMatriz(int l, int c);

void imprimeMatriz(double **M, int l, int c);

void resolveSL(double **m, int *indice, int n);

void jordan(double **m, int n);

void modoEquacao();

void bolzano(int n, float *coef, float *intervalo);

char *converteParteInteira(double dividendo, int base);

char intParaBaseChar(int resto, int base);

char recebeHexChar(int resto);

void inverteVentorChar(char *saida);

void trocaPosicoes(char *posInicial, char *posFinal);

char *converteParteFracionaria(double parteFracionada, int base);


void resolveOutput(double entrada, int base);

int main(void) {
    char opcao = '0';

    while (opcao != 'F') {
        /*
         * Menu Inicial
         */
        printf("-> â€˜Câ€™ â€“ Conversao, â€˜Sâ€™ â€“ Sistema Linear, â€˜Eâ€™ â€“ Equacao Algebrica e â€˜Fâ€™ â€“ Finalizar:\n");
        scanf("%s",&opcao);

        switch (opcao) {
            case 'c':
            case 'C':
                modoConversao();
                break;

            case 's':
            case 'S':
                modoSistemaLinear();
                break;

            case 'e':
            case 'E':
                modoEquacao();
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
 * Para fins de organizacao do codigo,
 * utilizar os escopos definidos por comentarios
 * para agrupar funcoes relacionadas.
 */

/*
 * Escopo CONVERSAO:
 */
void modoConversao() {
	double entrada = 0.0;

    //recebe valor de entrada
    printf("-> Entre com um numero Decimal: ");
    scanf("%lf", &entrada);

	resolveOutput(entrada, 2);
	resolveOutput(entrada, 8);
	resolveOutput(entrada, 16);

}

void resolveOutput(double entrada, int base) {
	double parteInteira = 0.0, parteFracionaria;
	int tamanhoFinal;
	char *inteiro, *fracao, *saida;

	parteFracionaria = modf(entrada, &parteInteira); 			//alimenta int partInteira e retorna parte fracionaria

	//Recebe em cada char* os numeros resultante na base aplicada.
	inteiro = converteParteInteira(parteInteira, base);
	fracao = converteParteFracionaria(parteFracionaria, base);

	tamanhoFinal = (int) (strlen(fracao) + strlen(inteiro)) + 2;
	saida = malloc(sizeof(saida) * tamanhoFinal);
	strcpy(saida, inteiro);
	strcat(saida, ".");
	strcat(saida, fracao);

	printf("%s\n",saida);

	free(inteiro);
	free(fracao);
	free(saida);
}

char *converteParteFracionaria(double fator, int base) {
    char *saida = NULL;
    int posicao = 0;
    double inteiro;

    /**
     * LICAO APRENDIDA:
     * NAO FAZER CAST DO RESULTADO DE MALLOC, REALLOC
     * e dar free sempre que usar!
     */

    /*
     * int fator: tera papel de fator  no inicio de iteracao
     *                e resultado no fim da operacao.
     */

    do {
        saida = realloc(saida, sizeof(saida) * posicao + 1);

		fator = modf((fator * base), &inteiro); //modf() quebra resultado da mult. e alimenta int inteiro e fator.

        saida[posicao] = intParaBaseChar((int) inteiro, base);
        posicao += 1;

        if (fator < EPSILON) {
            break;
        }

    } while (strlen(saida) < 20);

    saida = realloc(saida, sizeof(saida) * posicao + 1);
    saida[posicao] = '\0'; //fecha string.
    return saida;
}


char *converteParteInteira(double dividendo, int base) {

    char *saida = NULL; //Importante pra o realloc().
    int resto, posicao = 0;


    /*
     * int dividendo: tera papel de dividendo no inicio da iteracao e
     *                  quociente no fim da iteracao.
     */

    /*
     * do-while cria palavra do numero saida' invertida;
     */
    do {
        //aloca espaco na memoria dinamicamente.
        saida = realloc(saida, sizeof(saida) * posicao + 1);

        resto = (int) fmod(dividendo, (double) base); //fmod: retorna o resto da operacao: param1/param2.
        dividendo = floor(dividendo / base); //floor: retorna maior inteiro menor que parametro de entrada.

        //coloca valor gerado na posicao criada na str dinamica.
        saida[posicao] = intParaBaseChar(resto, base);
        posicao += 1;

    } while (dividendo >= base);

    //aloca posicao na string para o dividendo e \0

    if(dividendo != 0) {
        saida = realloc(saida, sizeof(saida) * posicao + 2);
        saida[posicao] = intParaBaseChar(dividendo, base);
        saida[posicao + 1] = '\0'; //fecha string.
        inverteVentorChar(saida);
    } else {
        saida = realloc(saida, sizeof(saida) * posicao + 1);
        saida[posicao + 0] = '\0'; //fecha string.
    }

    return saida;


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

char intParaBaseChar(int resto, int base) {
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

/*Se houver memoria disponivel, aloca dinamicamente uma matriz
bidimensional de double com l linhas e c colunas. Devolve um ponteiro
para essa matriz. Caso contrario, devolve um ponteiro nulo.*/
double **alocaMatriz(int l, int c){
	int i, j;
	double **M;

	/*Alocando as linhas da matriz*/
	M=malloc(sizeof(M)*l);
	if(M==NULL){//Falta de memoria
		return NULL;
	}

	/*Alocando as colunas da matriz*/
	for(i=0;i<l;i++){
		M[i]=malloc(sizeof(double)*c);
		if(M[i]==NULL){//Falta de memoria
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
equacoes e n variaveis. Se o SL for incompativel, devolve 2; se for
determinado, devolve 0 e coloca em x a solucao do SL; se for
indeterminado, devolve 1 e coloca em x a solucao do SL na qual as
variaveis livres tem valor 0.*/
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

	/*Copia os valores de x em um vetor auxiliar, que sera usado
	caso tenha ocorrido troca de colunas durante a execucao da
	funcao jordan.*/
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
/*Fim da funcao resolveSL*/

/* Recebe m, a matriz aumentada de um SL com n variaveis e n
equacoes e transforma a matriz de coeficientes do SL numa
matriz diagonal. Em seguida, chama a fun??o resolveSL para resolver
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
		//Pivo igual a 0
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

					//Troca o indice das colunas
					aux = indice[i];
					indice[i] = indice[j];
					indice[j] = aux;
 				}
			}
			if(j==n){
				for(w=0; w<n; w++){
					m[w][j-1] = 0;
				}
			}
		}

		//Pivo diferente de 0
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

	//Chamada da funcao resolveSL que resolve o SL.
	resolveSL(m, indice, n);
}
/*Fim do metodo jordan*/

/*O metodo pede que o usuario digite o nome de um arquivo .txt (nome_arq) que contenha
o grau (grau) e os coeficientes (coef) de um SL. Os caracteres do arquivo sao convertidos
para valores inteiros. Uma matriz M eh alocada e os coeficientes sao adicionados
nela. Por fim, a funcao jordan e chamada para diagonalizar a matriz e resolver o SL.*/
void modoSistemaLinear(){
	char nome_arq[37], grau_c[14];
	int grau=0, i=0, j=0, linha=0, count=0, i_neg=0;
	char coef_c[16], *txt;
	double **M;
	FILE *arq;

	//Leitura do nome do arquivo pelo teclado. Omite-se a extensao.
	printf("Nome de um arquivo (com ate 32 caracteres): ");
	scanf("%s", &nome_arq);

	//Abertura do arquivo
	txt = strstr(nome_arq, ".txt");
	if(txt == NULL){
		strcat(nome_arq, ".txt");	
	}
	arq = fopen(nome_arq, "r");
	if(arq==NULL){
		printf("ERRO, nao foi possivel abrir o arquivo!\n");
		return;
	}
	else{
		//Extracao do grau do SL
		fscanf(arq, "%s\n", &grau_c);
		grau = atoi(grau_c);

		char coef[((grau+1)*16)+grau];

		/*Aloca-se uma matriz com quantidade de linhas igual ao grau do SL.
		E quantidade de colunas igual ao grau do SL + 1.*/
		M = alocaMatriz(grau, grau+1);
		if(M==NULL){//Falta mem?ria
			printf("Deu pau!");
			return;
		}

		/*Leitura dos coeficientes e atribuicao de cada um deles a uma
		posicao da matriz.*/
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

	//Chamada da funcao jordan.
	jordan(M, grau);
}
/*Fim do metodo modoSistemaLinear*/

/*
 * Fim de SISTEMA:
 */

/*
 * Escopo EQUACAO:
 */

//Essa função lê uma equação algébrica da forma anxn + an-1xn-1 + ... + a1x + a0, com an > 0 e a0 # 0
	//Utilizando o Teorema de Lagrange, o programa  calcula e exibi os intervalos onde se encontram as raízes reais negativas e as raízes reais positivas da equação. 
	//Entradas do usuário: Grau e coeficientes da equação algébrica
	//Saida do programa: Intervalos onde se encontram as raízes (Teorema de Lagrange)
void modoEquacao(){ 
	 int g,i,n;
	float v[100],v1[100],v2[100],v3[100];
	float B0=0,B1=0,B2=0,B3=0,aux=0,k=0,k0,k1,k2,k3;
	float a,x,L0=0,L1=0,L2=0,L3=0;
	float lim_positivo[2], lim_negativo[2];
	char escolha;
	
	do{
		printf("Favor, digite o grau da equa%c%co: ",135,198);  // entrada de dados do grau da equação
 		scanf("%d",&g); // leitura da variavel grau da equação
 		printf("Favor, digite os coeficientes da equacao\n");
		printf("O primeiro valor deve ser maior do que zero e o ultimo valor diferente de zero\n");  
		n=g;
		
		// entrada de dados do polinômio p(x)
		for (i=0;i<=g;i++)
 		{
 	   		printf("a[%d]: ",n);  
 	    	scanf("%f",&v[i]); // leitura dos coeficientes do polinômio p(x)
 	    	n--;
		}
		
		if(v[0]<0 || v[g]==0)
			printf("Entrada errada!\n");
	}while(v[0]<0 || v[g]==0);
	
   // calculando o polinômio p1(x)
    if(v[g]>=0)
    {
		for(i=0; i<=g; i++)
		{
			v1[i] = v[g-i];
		}
    }
    else
    {
		for(i=0; i<=g; i++)
		{
			v1[i] = -1*v[g-i];
		}
    }
    
	// calculando o polinômio p2(x)
	if(v1[g]>=0)
    {
		for(i=0; i<=g; i++)
		{
			if ((g-i)%2==0)
			v2[i] = v1[g-i];
			else
			v2[i] = -1*v1[g-i];
			
		}
    }
    else
    {
		for(i=0; i<=g; i++)
		{
			if ((g-i)%2==0)
			v2[i] = -1*v1[g-i];
			else
			v2[i] =v1[g-i];
		}
    }
    
	// calculando o polinômio p3(x)
	if(v2[g]>=0)
    {
		for(i=0; i<=g; i++)
		{
			
			v3[i] = v2[g-i];
			
		}
    }
    else
    {
		for(i=0; i<=g; i++)
		{
			if ((g-i)%2==0)
			 v3[i] = -1*v2[g-i];
			else
			v3[i] =-1*v2[g-i];
		}
    }

	k0=0;
	
	// calculando o B e K de p(x)
    for(i=0; i<=g; i++)
    {
    	if(v[i]<0)
    	{
    		if(k0<g-i)
    		{
    			k0=g-i;
			}
    		
		}
		if(v[i]<0)
    	{
    		if(aux>v[i])
    		{
				aux= v[i];
			}
		}
    }
    B0 = -1*aux;

	//calculando L0 de p(x)
    x = (g-k0);
    a=(B0/v[0]);
    L0 = 1+ pow(a,1/x);
    
	k1 = 0;
    aux=0;
    
    // calculando o B e K de p1(x)
    for(i=0; i<=g; i++)
    {
    	
		if(v1[i]<0)
    	{
    		if(k1<g-i)
    		{
    			k1=g-i;	
			}
    		
		}
		if(v1[i]<0)
    	{
    		if(aux>v1[i])
    		{
				aux= v1[i];
			}
		}
    }
    B1 = -1*aux;

	//calculando L1 de p1(x)
	x = (g-k1);
	a= (B1/v1[0]);
    L1 = 1+pow(a,1/x);
    
	k2 = 0;
    aux=0;
    
    // calculando o B e K de p2(x)
    for(i=0; i<=g; i++)
    {
    	
		if(v2[i]<0)
    	{
    		if(k2<g-i)
    		{
    			k2=g-i;	
			}
		}
		if(v2[i]<0)
    	{
    		if(aux>v2[i])
    		{
				aux= v2[i];
			}
		}
    }
    B2 = -1*aux;
    
     a=0;
	//calculando L2 de p2(x)
    x = (g-k2);
	a= (B2/v2[0]);
    L2 = 1+pow(a,1/x);
    
    // calculando o B e K de p3(x)
    k3=0;
	aux=0;
	for(i=0; i<=g; i++)
    {
    	
		if(v3[i]<0)
    	{
    		if(k3<g-i)
    		{
    			k3=g-i;	
			}
		}
		if(v3[i]<0)
    	{
    		if(aux>v3[i])
    		{
				aux= v3[i];
			}
		}
    }
    B3 = -1*aux;
    
     a=0;
	//calculando L3 de p3(x)
    x = (g-k3);
	a= (B3/v3[0]);
    L3 = 1+pow(a,1/x);
    
    lim_positivo[0] = 1/L1;
    lim_positivo[1] = L0;
    lim_negativo[0] = -1*L2;
    lim_negativo[1] = -1/L3;
    
    // Teorema de lagrange
	// exibindo os limites: primeiramente, das raízes reais positivas e depois das negativas
	printf("\n Os intervalos das raizes reais positivas e negativas da equa%c%co s%co:",135,198,198);
    printf("\n  %.3f <= E+ <= %.3f", lim_positivo[0], lim_positivo[1]);  
    printf("\n %.3f <= E- <= %.3f\n\n", lim_negativo[0], lim_negativo[1]); 
    
    //Escolha do intervalo a ser usado no teorema de Bolzano
	do{
    	printf("Qual intervalo sera usado? (p-> positivo; n-> negativo): ");
    	fflush(stdin);
    	scanf("%c", &escolha);
    	
    	switch(escolha){
    		case 'p':
    		case 'P':
    			bolzano(g, v, lim_positivo);
    			break;
    		case 'n':
    		case 'N':
    			bolzano(g, v, lim_negativo);
    			break;
    		default:
    			printf("Escolha errada!\n");
    	}
	}while(escolha !='p' && escolha !='P' && escolha !='n' && escolha !='N');
} //Fim da função modoEquacao

/*A função recebe grau, grau da equação; coef, vetor de coeficientes da equação;
intervalo, intervalo onde se encontram as raízes positivas ou negativas. Ela calcula
se o intervalo tem um número par ou ímpar de raízes, usando, para isso, o teorema de 
Bolzano. Se a quantidade de raízes for ímpar a função para calcular uma raiz aproximada
é chamada.*/
void bolzano(int grau, float *coef, float *intervalo){
	int i;
	float fa, fb;
	
	for(i=0; i<=grau; i++){
		fa += coef[i]*pow(intervalo[0], grau-i);
		fb += coef[i]*pow(intervalo[1], grau-i);
	}
	
	if(fa*fb<0){
		printf("Numero impar de raizes.\n");
		//CHAMAR A FUNÇÃO bisseção AQUI!
		//bissecao(grau, coef, intervalo);
	}
	else{
		printf("Numero par de raizes.\n");
	}
}
/*Fim da função bolzano*/

/*
 * Fim de EQUACAO:
 */
