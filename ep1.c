#include <string.h>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define EPSILON 0.000001


void modoConversao();

void modoSistemaLinear(char opcao);

void modoEquacao(char opcao);

char *converteParteInteira(double dividendo, int base);

char intParaBaseChar(int resto, int base);

char recebeHexChar(int resto);

void inverteVentorChar(char *saida);

void trocaPosicoes(char *posInicial, char *posFinal);

char *converteParteFracionaria(double parteFracionada, int base);

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
        printf("-> ‘C’ – Conversão, ‘S’ – Sistema Linear, ‘E’ – Equação Algébrica e ‘F’ – Finalizar:\n");
//        scanf("%s",&opcao); TODO DESCOMENTAR.
        opcao = 'C';

        switch (opcao) {
            case 'C':
                modoConversao();
                break;
            case 'S':
                modoSistemaLinear(opcao);
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
    double entrada = 0.0, parteInteira = 0.0, parteFracionaria = 0.0;
    char *saida2, *saida8, *saida16, *fracao2, *fracao8, *fracao16;

    //recebe valor de entrada
    printf("-> Entre com um numero Decimal: \n");
    scanf("%lf", &entrada);

    //Separa numero decimal em parte inteira e parte fracionaria.
    parteFracionaria = modf(entrada, &parteInteira);

    // aloca espaço pro vetor de strings de saida.
    saida2 = converteParteInteira(parteInteira, 2);
    strcat(saida2, ".");
    fracao2 = converteParteFracionaria(parteFracionaria, 2);
    strcat(saida2, fracao2);
    printf("%s\n", saida2);

    saida8 = converteParteInteira(parteInteira, 8);
    strcat(saida8, ".");
    fracao8 = converteParteFracionaria(parteFracionaria, 8);
    strcat(saida2, fracao8);
    printf("%s\n", saida8);

    saida16 = converteParteInteira(parteInteira, 16);
    strcat(saida16, ".");
    fracao16 = converteParteFracionaria(parteFracionaria, 16);
    strcat(saida2, fracao16);
    printf("%s\n", saida16);

}

char *converteParteFracionaria(double fator, int base) {
    char *saida = NULL;
    int posicao = 0;
    double inteiro;

    /*
     * int fator: tera papel de fator  no inicio de iteracao
     *                e resultado no fim da operacao.
     */

    do {
        saida = (char *) realloc(saida, sizeof(char) * posicao + 1);
        fator = modf((fator * base), &inteiro); //modf()

        saida[posicao] = intParaBaseChar((int) inteiro, base);
        posicao += 1;

        if (fator < EPSILON) {
            break;
        }

    } while (strlen(saida) < 20);

    saida = (char *) realloc(saida, sizeof(char) * posicao + 1);
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
        //aloca espaço na memoria dinamicamente.
        saida = (char *) realloc(saida, sizeof(char) * posicao + 1);

        resto = (int) fmod(dividendo, (double) base); //fmod: retorna o resto da operacao: param1/param2.
        dividendo = floor(dividendo / base); //floor: retorna maior inteiro menor que parametro de entrada.

        //coloca valor gerado na posicao criada na str dinamica.
        saida[posicao] = intParaBaseChar(resto, base);
        posicao += 1;

    } while (dividendo >= base);

    //aloca posicao na string para o dividendo e \0

    if(dividendo != 0) {
        saida = (char *) realloc(saida, sizeof(char) * posicao + 2);
        saida[posicao] = intParaBaseChar(dividendo, base);
        saida[posicao + 1] = '\0'; //fecha string.
        inverteVentorChar(saida);
    } else {
        saida = (char *) realloc(saida, sizeof(char) * posicao + 1);
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
void modoSistemaLinear(char opcao) { printf("%c\n", opcao); }

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
