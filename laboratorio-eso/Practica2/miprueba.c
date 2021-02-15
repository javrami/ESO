// UVash

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

char error_message[30] = "An error has occurred\n";

void cleanstring(char *string) {
	for (int i = 0; i < strlen(string); i++)
		if (string[i] == '\t')
			string[i] = ' ';
	for (int i = 1; i < strlen(string); i++) {
		if (string[i] == '>' && string[i] == string[i - 1])
			fprintf(stderr, "%s", error_message);
		while (string[i] == ' ' && string[i] == string[i - 1]) {
			for (int j = (i - 1); j < strlen(string); j++)
				string[j] = string[j + 1];
			string[strlen(string) - 1] = ' ';
		}
		while (string[i] == '&' && string[i] == string[i - 1]) {
                        for (int j = (i - 1); j < strlen(string); j++)
                                string[j] = string[j + 1];
                        string[strlen(string) - 1] = ' ';
                }
		while (string[i] == '&' && string[i-1] == ' ') {
			for (int j = (i - 1); j < strlen(string); j++)
				string[j] = string[j + 1];
			string[strlen(string) - 1] = ' ';
		}
		while (string[i] == ' ' && string[i - 1] == '&') {
			for (int j = i; j < strlen(string); j++)
                                string[j] = string[j + 1];
                        string[strlen(string) - 1] = ' ';
                }
	}
	while (string[0] == ' ' || string[0] == '&') {
		for (int i = 1; i < strlen(string); i++)
			string[i - 1] = string[i];
		string[strlen(string) - 1] = '\0';
	}
	while (string[strlen(string) - 1] == '\n' || string[strlen(string) - 1] == ' ')
		string[strlen(string) - 1] = '\0';
}

int numberofelements(char c, char *line) {
	int cont = 0;
	char *aux;
	char* line2 = malloc(strlen(line) + 1);
	strcpy(line2, line);
	while ((aux = strsep(&line2, &c)) != NULL)
		cont++;
	free(line2);
	return cont;
}

void getarguments(int cont, char *command, char **arg) {
	char *aux;
	for (int i = 0; i < cont; i++) {
		aux = strsep(&command, " ");
		arg[i] = malloc((strlen(aux) + 1) * sizeof(char));	//allocate memory for argument
		strcpy(arg[i], aux);
	}
	arg[cont] = NULL; //end of argv
}

int checkredirection(int cont, char **arg) {
	for (int i = 0; i < cont; i++)
		if(strlen(arg[i]) == 1 && arg[i][0] == '>'){
			if(arg[i + 1] == NULL)
				fprintf(stderr, "%s", error_message);
			else if ((i + 2) != cont)
				fprintf(stderr, "%s", error_message);
			else {

				FILE *fptr = fopen(arg[i + 1], "a");
				if(fptr == NULL) 
					 fprintf(stderr, "%s", error_message);
                        	else {
					int file = open(arg[i + 1], O_WRONLY);
					dup2(file, 1);
					dup2(file, 2);
					arg[i] = NULL;
					arg[i + 1] = NULL;
					cont = cont - 2;
				}
			}
		}
	return cont;
}

void execute(char *command, bool newprocess) {
	cleanstring(command);	//clear string
	int cont = numberofelements(' ', command);
	char **arg;
	arg = malloc((cont + 1) * sizeof(char*));	//allocate memory for argument pointers
	getarguments(cont, command, arg);	//retrieve arguments

	//built-in command: exit
	if (strcmp(arg[0], "exit") == 0)
		exit(0);

	//built-in commands: cd
	else if (strcmp(arg[0], "cd") == 0) {
		if (cont != 2)
			fprintf(stderr, "%s", error_message);
		else if (chdir(arg[1]) != 0)
			fprintf(stderr, "%s", error_message);
	}

	//execvp
	else
		if(newprocess) {
			pid_t pid;
			if((pid=fork())<0) 
				fprintf(stderr, "%s", error_message);
			else if (pid==0) {
				cont=checkredirection(cont, arg);
				if (execvp(*arg, arg)<0) {
					fprintf(stderr, "%s", error_message);
					exit(1);
				}
			}
			else
				while (wait(&cont) != pid)
					;
		} else {
			if (execvp(*arg, arg) < 0) {
				fprintf(stderr, "%s", error_message);
		}
	}

	free(arg);
}

void executemany(char *line) {
	int nopids;
	char *aux;
	char **command;
	pid_t *pid;
	nopids = numberofelements('&', line);
	pid = malloc((nopids) * sizeof(pid_t));
	command = malloc((nopids) * sizeof(char*));
	for (int p = 0; p < nopids; p++) {
		aux = strsep(&line, "&");
		command[p] = malloc((strlen(aux) + 1) * sizeof(char));
		strcpy(command[p], aux);
	}
	for (int p = 0; p < nopids; p++) { //parsing each command
		pid[p] = fork();
		if (pid[p] == 0) {
			execute(command[p], false);	//process command
			exit(0);
		}
		if (pid[p] < 0) {
			fprintf(stderr, "%s", error_message);
			//exit(1);
		}
	}
	for (int p = 0; p < nopids; p++) { //wait for each fork
		if (pid[p] > 0) {
			int status;
			waitpid(pid[p], &status, 0);
			if (status > 0) {
				fprintf(stderr, "%s", error_message);
			}
		} else {
			fprintf(stderr, "%s", error_message);
		}
	}
	free(pid);
}

int main(int argc, char *argv[]) {
	char *lineBuf;
	size_t lineBufSize = 0;
	ssize_t lineSize;
	if (argc > 1) { //batch
		for (int i = 1; i < argc; i++) {
			FILE *file = fopen(argv[i], "r");
			if (file == NULL) {
				fprintf(stderr, "%s", error_message);
				exit(1);
			}
			else{
				lineSize = getline(&lineBuf, &lineBufSize, file);
				cleanstring(lineBuf);
				while (lineSize >= 0) {
					if (strchr(lineBuf, '&') == NULL){
						execute(lineBuf, true);
						printf("%s\n", lineBuf);
					}else{
						executemany(lineBuf);
					lineSize = getline(&lineBuf, &lineBufSize, file);
					}
				}
				free(lineBuf);
			}
			fclose(file);
		}
	}
	else { //interactive
		do {
			printf("UVash> ");
			lineSize = getline(&lineBuf, &lineBufSize, stdin);
			cleanstring(lineBuf);
			if (strchr(lineBuf, '&') == NULL)
				execute(lineBuf, true);
			else
				executemany(lineBuf);
		} while (true);
		free(lineBuf);
	}
}
