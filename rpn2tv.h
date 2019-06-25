/* Mihael Scofield de Azevedo GRR - 20182621. */

typedef struct variaveis_t{
	char nome;
	int valor;
} variaveis_t;

/* Simplesmente carrega a expressao */
void ler_expressao () ;

/* Procura elemento no vetor de variaveis */
int procura_elemento(char x) ;

/* Facilita a manipulacao na geracao da tabela,
vendo quantas variaveis usarei e quais sao elas */
void preaparacao () ;

/* Substituta da funcao pow fixo em 2, pois a mesma,
devolvia double e nao posso trabalhar com isso */
int pow_2 (int x) ;

/* Imprime o cabecalho da tabela */
void topo_tabela() ;

/* Calcula o valor atual da tabela */
void conteudo_tabela() ;

/* Procura o valor atual para a variavel x */
int val_equivalente(char x) ;

/* Aplica RPN no Mintermo atual */
void RPN () ;

/* Responsavel pela saida do programa */
void gerar_tabela () ;