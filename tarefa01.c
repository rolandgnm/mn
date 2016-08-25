#include "stdio.h"
#include "stdlib.h"

void modoConversao();

void modoSistemaLinear(char opcao);

void modoEquacao(char opcao);

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
        printf("\n‘C’ – Conversão, ‘S’ – Sistema Linear, ‘E’ – Equação Algébrica e ‘F’ – Finalizar: ");
        scanf("%s",&opcao);

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
                printf("Erro! - Entrada desconhecida");
                break;
        }
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
    float entrada = 0.0;

    printf("Entre com um numero Decimal: ");
    scanf("%f", &entrada);

    printf("%f", entrada);

}

/*
 * Fim de CONVERVSAO!
 */

/*
 * Escopo SISTEMA:
 */
void modoSistemaLinear(char opcao) { printf("%c", opcao); }

/*
 * Fim de SISTEMA:
 */

/*
 * Escopo EQUACAO:
 */
void modoEquacao(char opcao) { printf("%c", opcao); }

/*
 * Fim de EQUACAO:
 */
