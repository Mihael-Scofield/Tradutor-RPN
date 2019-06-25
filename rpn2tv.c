/* Mihael Scofield de Azevedo GRR - 20182621. */

#include <stdio.h>
#include "rpn2tv.h"

int tamanho, NA, pilha[100];
char expressao[1000];
variaveis_t variaveis[6]; // Tipo definido em .h

/* Simplesmente carrega a expressao */
void ler_expressao (){
	scanf ("%[^\n]", expressao);
}

/* Procura elemento no vetor de variaveis */
int procura_elemento(char x){
	int i;
	for (i = 0; i < 6; i++){
		if (x == variaveis[i].nome){ // Encontrou.
			return 1;
		}
	}
	return 0; // Nao encontrou.
}

/* Facilita a manipulacao na geracao da tabela,
vendo quantas variaveis usarei e quais sao elas */
void preaparacao (){
	int i, j;
	j = 0;
	tamanho = 0;
	for (i = 0; expressao[i] != '\0'; i++){ // Comeco a procurar minhas variaveis na expressao.
		if ( ('a' <= expressao[i]) && (expressao[i] <= 'z')){ // Vejo se caracter eh valido.
			if (procura_elemento(expressao[i]) == 0){
				variaveis[j].nome = expressao[i];
				tamanho++;
				j++;
			}
		}
	}
}

/* Substituta da funcao pow fixo em 2, pois a mesma,
devolvia double e nao posso trabalhar com isso */
int pow_2 (int x){
	int i, aux;
	aux = 1;
	if (x == 0){
		return aux;
	}
	for (i = 1; i <= x; i++){
		aux *= 2;
	}
	return aux;
}

/* Imprime o cabecalho da tabela */
void topo_tabela(){
	int i;
	for (i = 0; i < tamanho; i++){
		printf ("| %c ", variaveis[i].nome);
	}
	printf ("||---|\n");
}

/* Calcula o valor atual da tabela */
void conteudo_tabela(){
	int i;
	for (i = (tamanho - 1); i >= 0; i--){ // Calculo do Numero Atual em binario.
		variaveis[i].valor = (NA & pow_2(i)) ?1 :0; // Se estou no maximo da variavel atual, recebe 1, caso contrario, 0.
	}
	for (i = (tamanho - 1); i >= 0; i--){ // Recheia o miolo da tabela.
		printf ("| %d ", variaveis[i].valor);
	}
	// Proxima saida devera ser do RPN
}

/* Procura o valor atual para a variavel x */
int val_equivalente(char x){
	int i, aux;
	for (i = 0; i < 6; i++){
		if (x == variaveis[i].nome){
			aux = (variaveis[i].valor);
		}
	}
	return aux;
}

/* Aplica RPN no Mintermo atual */
void RPN (){
	int i, j;
	j = 0; // Indice da pilha.
	/* Analise atual da expressao. */
	for (i = 0; expressao[i] != '\0'; i++){ // Percorro expressao, validando caracteres.
		if ( ('a' <= expressao[i]) && (expressao[i] <= 'z') ){
			pilha[j] = val_equivalente(expressao[i]);
			j++; // Incremento apenas se coloquei variavel no topo.
		}
		else{
			switch (expressao[i]){
				case '&':
					pilha[j-2] = (pilha[j-1] & pilha[j-2]); // Retira, retira, empilha.
					j--; // Volto um, para compensar operacao de cima.
					break;

				case '|':
					pilha[j-2] = (pilha[j-1] | pilha[j-2]); // Retira, retira, empilha.
					j--;
					break;

				case '~': // a b & c d & ~ | ; (teste).
					pilha[j-1] = ((pilha[j-1]+1) % 2);
					break; // Nao ha necessidade de voltar no indice.
			}
		}
	}
	/* Impressao do resultado */
	printf ("|| %d |\n", pilha[j-1]);
}

/* Responsavel pela saida do programa */
void gerar_tabela (){
	topo_tabela();
	for (NA = 0; NA < pow_2(tamanho); NA++){ // NA = Numero Atual da tabela
		conteudo_tabela();
		RPN();
	}
}

int main (void){
	ler_expressao();
	preaparacao();
	gerar_tabela();
}