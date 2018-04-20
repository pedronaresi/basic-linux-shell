//Everton da Silva Coelho  101937
//Gabriel Borin Takahashi 101953
//Pedro Manhez Naresi 105615

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define max_comando 1000
#define max_linha 30
#define max_col 30

int main(int argc, char *argv[]){

	printf("Comando: ");
	char comando[max_comando];

	scanf("%[^\n]s", comando);

	char* token;
	char* espaco = {" "};
	int cont = 0;
	int i = 0;
	int flag = 1;
	int flag_in = 0, flag_out = 0, flag_out_acc = 0;

	int cmd_pos = 0;
	int* cmd_indice = (int*) calloc(max_linha*sizeof(int*), 1);

	char** cmd_matrix = (char**) calloc(max_linha*sizeof(char**), 1);

	token = strtok(comando, espaco);
	//printf("\n*Tokens*\n");
	if(token){
		do{
		cmd_matrix[cont] = (char*) calloc(sizeof(token)*sizeof(char*), 1);
			if(flag == 0){
				if (strcmp(token, "|") == 0){
					cmd_matrix[cont] = NULL;
					flag = 1;
				}
				else{
					strcpy(cmd_matrix[cont], token);
				}
			}
			else if(flag == 1){
				strcpy(cmd_matrix[cont], token);
				cmd_indice[cmd_pos] = cont;
				cmd_pos++;
				flag=0;
			}
			//printf("%s\n", token);
			token = strtok(NULL, espaco);
			cont++;
		}while(token != NULL);
		cmd_matrix[cont] = NULL;
	}
	else{
		printf("No token");
	}

	printf("\n\n*Print Matriz*\n");
	for(i=0; i<=cont; i++){
		if(cmd_matrix[i] == NULL){
			printf("\tNULL\n");
		}
		else{
			printf("\t%s\n", cmd_matrix[i]);
		}
	}

	printf("\n*Print vetor da posicao dos comandos*\n");
	for(i=0; i<cmd_pos; i++){
		printf("\tcmd_indice[%d]: %d\n", i, cmd_indice[i]);
	}

	printf("Saida do Shell:\n");

	pid_t pid;

	int fd[100][2];

	for(i=0; i<100; i++){
		pipe(fd[i]);
	}

	for(i=0; i<cmd_pos; i++){

		pid = fork();
		if (pid == 0) {//filho
			int arq_in, arq_out;
			int k=cmd_indice[i];
			while(cmd_matrix[k] != NULL){
				if (strcmp(cmd_matrix[k], "<") == 0){
					//printf("teste: %s\n", cmd_matrix[k+1]);
					arq_in = open(cmd_matrix[k+1], O_RDONLY, 0644);
					close(STDIN_FILENO);
					dup2(arq_in, STDIN_FILENO);
					cmd_matrix[k] = NULL;
				}
				else if (strcmp(cmd_matrix[k], ">") == 0){
					//printf("testeout2t1: %s\n", cmd_matrix[k+1]);
					arq_out = open(cmd_matrix[k+1], O_CREAT | O_RDWR | O_TRUNC, 0644);
					close(STDOUT_FILENO);
					dup2(arq_out, STDOUT_FILENO);
					cmd_matrix[k] = NULL;
				}
				else if (strcmp(cmd_matrix[k], ">>") == 0){
					//printf("testeout2: %s\n", cmd_matrix[k+1]);
					arq_out = open(cmd_matrix[k+1], O_CREAT | O_RDWR | O_APPEND, 0644);
					close(STDOUT_FILENO);
					dup2(arq_out, STDOUT_FILENO);
					cmd_matrix[k] = NULL;
				}
				k++;
			}
			if(i!=0){ // se nao for primeiro
				close(fd[i-1][1]);
				dup2(fd[i-1][0], STDIN_FILENO); //dup(fd2[0]);
				close(fd[i-1][0]);
			}
			if(i!=cmd_pos-1){ //se nao for ultimo
				close(fd[i][0]);
				dup2(fd[i][1], STDOUT_FILENO);// dup(fd[1]);
				close(fd[i][1]);
			}
			//printf("\ncomando aqui: %s\n",cmd_matrix[cmd_indice[i]]);
			execvp(cmd_matrix[cmd_indice[i]], &cmd_matrix[cmd_indice[i]]);
			close(arq_out);
			close(arq_in);

		} else { // pai
			if(i>0){
				close(fd[i-1][0]);
				close(fd[i-1][1]);
			}
			waitpid(-1, NULL, 0);
		}
	}

	return 0;
}
