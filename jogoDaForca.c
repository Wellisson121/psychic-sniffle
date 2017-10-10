#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
  Matricula:2016101882
  Nome:Wellisson Galvao Lopes
  Turma: Engenharia de Computacao
  Periodo: 2017/1
*/



typedef struct jogador{
  char nome[30];
  int codigo;
  int erros;
}Jogador;

typedef struct boneco{
  char cabeca[1];
  char tronco[1];
  char bpd[1];
  char bpe[1];
}Boneco;


void imprimeMenu();
void exibeBoneco(Jogador *j1,Jogador *j2);
void novoJogo(char **dic,char **resp);
int contaLinhas(char *param);
char** criaLista(int valor);
void destroiLista(char** mat,int linha);
void preencheLista(char** mat, char* nomes,int linhas);
int validaCaracter(char ch);
char converteCaractere(char ch);
int ganhou(char* palavra, char* resposta);
void limpaBuffer();
int salvaArquivo(Jogador *j);
void limparHistorico();
void historico();
int contaLinhasHistorico(char *nome);

int main(int argc, char const *argv[]) {
  int op,dicas,respostas;
  char **dic,**resp;
  char dicasNome[] = {"dicas.dat"};
  char respostasNome[] = {"palavras.dat"};
  /*conta as linhas e aloca a memoria*/
  dicas = contaLinhas(dicasNome);
  respostas = contaLinhas(respostasNome);
  dic = criaLista(dicas);
  resp = criaLista(respostas);
  preencheLista(dic,dicasNome,dicas);
  preencheLista(resp,respostasNome,respostas);
  do {
    srand(time(NULL));
    imprimeMenu();
    scanf("%d",&op);
    switch (op) {
      case 1:
        novoJogo(dic,resp);
        break;
      case 2:
        historico();
      break;
      case 3:
        limparHistorico();
      break;
      case 4:
        destroiLista(dic,dicas);
        destroiLista(resp,respostas);
      break;
      default:
        printf("Esta opcao nao existe.Digite uma opcao valida!\n");
        getchar();/*impede o programa de entrar em loop infinito caso o usuario
        nao digite um numero*/
    }
  } while(op != 4);
  return 0;
}


/*Imprime um menu na tela mostrando ao usuario as opcoes disponiveis*/
void imprimeMenu() {
  printf("|------------------------------------------------------------|\n");
  printf("|                 Jogo da forca                              |\n");
  printf("|1 - Novo Jogo                                               |\n");
  printf("|2 - Ver classificacao                                       |\n");
  printf("|3 - Limpar Historico                                        |\n");
  printf("|4 - Sair                                                    |\n");
  printf("|------------------------------------------------------------|\n");
}


/*Imprime as partes do boneco para cada erro cometido pelo jogador*/
void exibeBoneco(Jogador *j1,Jogador *j2) {
  Boneco b;
  b.cabeca[0] = 'O';
  b.tronco[0] = '|';
  b.bpd[0] = '/';
  b.bpe[0] = '\\';
printf("-----------------------------------\n");
printf("------\t\t\t------\t\t\t\n");
printf("|    |\t\t\t|    |                      \n");
printf("|    %c\t\t\t|    %c                     \n",j1->erros >= 1 ? b.cabeca[0]:'\0' ,j2->erros >= 1 ? b.cabeca[0]:'\0');
printf("|   %c%c%c\t\t\t|   %c%c%c                   \n",j1->erros >= 3 ? b.bpd[0]:' ',j1->erros >= 2 ? b.tronco[0]:'\0',j1->erros >= 4 ? b.bpe[0]:'\0',j2->erros >= 3 ? b.bpd[0]:' ',j2->erros >= 2 ? b.tronco[0]:'\0',j2->erros >= 4 ? b.bpe[0]:'\0');
printf("|    %c\t\t\t|    %c                     \n",j1->erros >= 5 ? b.tronco[0]:'\0',j2->erros >= 5 ? b.tronco[0]:'\0');
printf("|   %c %c\t\t\t|   %c %c                   \n",j1->erros >= 6 ? b.bpd[0]:'\0',j1->erros >= 7 ? b.bpe[0]:'\0',j2->erros >= 6 ? b.bpd[0]:'\0',j2->erros >= 7 ? b.bpe[0]:'\0');
printf("^\t\t\t^                           \n");
printf("%s\t\t\t%s\n",j1->nome,j2->nome);
}


/*executa o jogo*/
void novoJogo(char **dic,char **resp) {
  int num,respSort,i,cont=0,teste,vez=0,respErrada;
  Jogador j1,j2;
  char *palavra,*resposta,letrasUsadas[27];
  char l;
  j1.erros = 0;
  j2.erros = 0;


  /*Recebe os nomes*/
  printf("jogador 1:\n");
  getchar();
  fgets(j1.nome,30,stdin);
  printf("jogador 2:\n");
  fgets(j2.nome,30,stdin);

  /*o fgets le o \n que foi digitado, fazendo que um nome seja impresso
  em uma linha e o outro na linha de baixo.Para impedir isso, procuramos o \n e
  inserimos um \0 no lugar*/
  for (i = 0; j1.nome[i]!='\0'; i++) {
    if (j1.nome[i] == '\n') {
      j1.nome[i] = '\0';
      break;
    }
  }

  for (i = 0; j1.nome[i]!='\0'; i++) {
    if (j2.nome[i] == '\n') {
      j2.nome[i] = '\0';
    }
  }

  /*sorteia a dica e a resposta*/

  num = 1 + (rand() % 5);
  printf("dica : %d\n",num);
  respSort = strlen(resp[num]);
  printf("%d\n",respSort);
  palavra = malloc(respSort*sizeof(char));
  resposta = malloc(respSort*sizeof(char));
  for (i = 0; i < respSort; i++) {
    resposta[i] = resp[num][i];
  }
  for (i = 0; i < respSort-1; i++) {
    palavra[i] = '_';
  }
  /*ao importar as palavras do arquivo, o \n vem junto, e para ajudar na
  comparacao preenchemos as duas ultimas posicoes do vetor que sera preenchido
  pelo usuario com \n e \0 respectivamente*/
  palavra[respSort-1]='\n';
  palavra[respSort] ='\0';

exibeBoneco(&j1,&j2);

do {
  printf("Dica: %s\n",dic[num]);
  printf("Palavra:%s\n",palavra);
  if (!validaCaracter(letrasUsadas[0])) {
    printf("Letras: \n");
  }else{
    printf("Letras: %s\n",letrasUsadas);
  }
  if (vez % 2 == 0) {
    if (j1.erros < 7) {
      printf("Vez: %s\n",j1.nome);
    }else{
      printf("Vez: %s\n",j2.nome);
    }

  } else {
    if (j2.erros < 7) {
      printf("Vez: %s\n",j2.nome);
    }else{
      printf("Vez: %s\n",j1.nome);
    }

  }
  printf("Tentativa: %d\n",vez+1);
  teste = 1;
  respErrada = 0;
  /*pega uma letra do usuario.Se o caractere for invalido, pede novamente*/
  do {

      printf("Digite uma letra:\n");
      scanf("%c",&l);
      limpaBuffer();
  } while(!validaCaracter(l));

    /*converte o caractere */
    l = converteCaractere(l);
    /*e verifica se ele ja foi usado*/
      for (i = 0; letrasUsadas[i] != '\0' ; i++) {
        if (l == letrasUsadas[i]) {
          exibeBoneco(&j1,&j2);
          printf("Esta letra ja foi usada. Digite outra letra!\n");
          teste = 0;
          break;
        }
      }



  /*Insere o caractere no vetor de resposta*/
    if (teste == 1) {
      letrasUsadas[cont] = l;
      cont++;
      letrasUsadas[cont] = '\0';
      for (i = 0; i < respSort; i++) {
        if (l == resposta[i]) {
          palavra[i] = l;
          respErrada=1;/*se houve acerto, respErrada recebe 1 e os erros nao sao
          contados*/
        }
      }
      if (respErrada == 0) {
        if (vez % 2 == 0)  {
          if (j1.erros < 7) {
            j1.erros++;
          }else{
            j2.erros++;
          }
        } else {
        if (vez % 2 != 0) {
          if (j2.erros < 7) {
            j2.erros++;
          }else{
            j1.erros++;
          }

        }
      }
    }
      exibeBoneco(&j1,&j2);
      vez++;

   }
} while((ganhou(palavra,resposta) == 0) && (j1.erros < 7) && (j2.erros < 7));

printf("%s\n",resposta);


if (j1.erros < j2.erros) {
  printf("%s venceu com %d erros!\n",j1.nome,j1.erros);
  printf("Codigo\n");
  scanf("%d",&j1.codigo);
  salvaArquivo(&j1);
} else if (j1.erros > j2.erros) {
  printf("%s venceu com %d erros!\n",j2.nome,j2.erros);
  printf("Codigo\n");
  scanf("%d",&j2.codigo);
  salvaArquivo(&j2);
} else {
  printf("Nao houveram vencedores\n");
}
/*Ao chamar a funcao novamente, jogo estava considerando letras usadas no jogo
anterior como usadas no jogo atual.Para impedir isso substituimos as letras do
vetor por espacos*/
for (i = 0; letrasUsadas[i] != '\0' ; i++) {
  letrasUsadas[i]=' ';
}
  /*Libera a memoria alocada*/
  free(resposta);
  resposta = 0x0;
  free(palavra);
  palavra = 0x0;


}


/*Abre o arquivo e verifica quantas linhas ele possui lendo a primeira linha do
 arquivo*/
int contaLinhas(char *param){
  int linhas;
  FILE *arquivo;
  arquivo = fopen(param,"r");
  if (arquivo == NULL) {
    printf("Erro! Arquivo nao encontrado!\n");
  }else{
    fscanf(arquivo,"%d",&linhas);
    fclose(arquivo);
  }
  return linhas+1;
}


/*Recebe como parametro um inteiro para fazer alocacao
de memoria de forma dinamica para os vetores dicas e respostas*/
char** criaLista(int valor) {
  int i;
  char** lista;
    lista = malloc(valor*sizeof(char*));
    for (i = 0;i < valor ; i++) {
      lista[i] = malloc(46*sizeof(char));
    }
    return lista;

}


/*Libera a memoria alocada para os nomes e as dicas*/
void destroiLista(char** mat,int linha) {
  int i;
    for (i = 0; i <= linha; i++) {
      free(mat[i]);
      mat[i] = 0x0;
    }
    free(mat);
    mat = 0x0;
  }

/*Le o arquivo e preenche as matrizes alocadas dinamicamente*/
void preencheLista(char** mat, char* nomes,int linhas) {
  int i=0;
  FILE *arquivo;
  arquivo = fopen(nomes,"r");
  if (nomes == NULL) {
    printf("Erro! Arquivo nao encontrado!\n");
  }else{
    for (i = 0; i <= linhas; i++) {
        fgets(mat[i],46,arquivo);
    }
  }
  fclose(arquivo);
}

/*Funcao criada para limpeza de buffer de teclado*/
void limpaBuffer() {
  int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){

    }
}

/*Verifica se o usuario digitou um caractere entre a e z*/
int validaCaracter(char ch) {
  return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

/*Verifica se o usuario digitou um caractere minusculo.Se verdadeiro,converte
para maiusculo e retorna o caracter modificado.Caso contrario, retorna o proprio
caractere*/
char converteCaractere(char ch) {
  if ((ch >= 'a') && (ch <= 'z')) {
    ch-=32;
  }
  return ch;
}

/*Verifica se a palavra jogada e igual a resposta.Se sim, retorna 1 e o jogo
encerra*/
int ganhou(char* palavra, char* resposta){
  int i;
  i = strcmp(palavra,resposta);
  if (i == 0) {
    return 1;
  }else{
    return 0;
  }

}

/*Exporta os dados do jogador vencedor para um arquivo chamado ranking.dat*/
int salvaArquivo(Jogador *j) {
  char nome[] = {"ranking.dat"};
  FILE *f;
  /*Verifica se o arquivo existe.Se nao existir,cria um novo*/
  if (fopen(nome,"r") == NULL) {
    f = fopen(nome,"a");
  }else{
    f = fopen(nome,"a");
  }
  if (j->codigo < 100) {
    fprintf(f,"%03d | %02d | %s\n",j->codigo,j->erros,j->nome);
  } else {
    fprintf(f,"%d | %02d | %s\n",j->codigo,j->erros,j->nome);
  }
  fclose(f);
  return 0;
}

/*Limpa o arquivo ranking.dat*/
void limparHistorico(){
  FILE *arquivo;
  arquivo = fopen("ranking.dat","w");
  printf("Historico zerado!\n");
  fclose(arquivo);
}

/*exibe o historico na tela*/
void historico(){
  int linhas,i,j,menor;
  FILE *arquivo;
  Jogador *jog,aux;
  char nome[] = "ranking.dat";
  linhas = contaLinhasHistorico(nome);
  printf("Classificacao:\n");
  printf("## | CDG | Erros | Nome Funcionario\n");
  if (linhas > 0) {
    jog=malloc(linhas * sizeof(Jogador));
    arquivo = fopen(nome,"r");
    for (i = 0; i < linhas; i++) {
      fscanf(arquivo,"%d | %d | %s\n",&jog[i].codigo,&jog[i].erros,jog[i].nome);
    }
    /*Faz a ordenacao dos dados do arquivo ranking pelo metodo select sort*/
    for (i = 0; i < linhas-1; i++) {
      menor = i;
      for (j = i+1; j < linhas; j++) {
        if (jog[j].erros < jog[menor].erros) {
          menor = j;
        }
        if (jog[i].erros != jog[menor].erros) {
          aux = jog[i];
          jog[i] = jog[menor];
          jog[menor] = aux;
        }
      }

    }
    if (linhas > 10) {
      linhas = 10;
    }
    for (i = 0; i < linhas; i++) {
      printf("%02d | %03d | %02d    | %s\n",i+1,jog[i].codigo,jog[i].erros,jog[i].nome);
    }
    fclose(arquivo);
    free(jog);
    jog = 0x0;
  }
}

int contaLinhasHistorico(char *nome){
  int num=0;
  char ch;
  FILE *arquivo;
  arquivo = fopen(nome,"r");
  if (arquivo == NULL) {
    printf("Erro! O arquivo nao pode ser aberto!\n");
    return 0;
  }
  while( (ch=fgetc(arquivo))!= EOF ){
			if(ch == '\n'){
         num++;
    }
	}
  fclose(arquivo);
  return num;
}
