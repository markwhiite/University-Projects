#include "major2.h"

//compile with gcc major2.c
//run with ./a.out

char currentDirectory[PATHLENGTH];
char PS1[100];
char PATH[255];
int returnStatus = 0;
char *programName;
typedef enum { CD, CMD, PWD, ECHO, EXIT } COMMANDTYPE;


//Funtion is executed at the beginning of the shell
int initialize()
{
	strcpy(PS1, "[batchFile] ");
	if (getcwd(currentDirectory, PATHLENGTH) == NULL)
	{
		perror("getcwd");
		exit(1);
	}
	strcpy(PATH, "/bin");
}

//Prints the prompt string
void printPrompt()
{
	printf("%s:%s", currentDirectory, PS1);
}

//parse the command line entered in the shell
void parseCommand(const char *cmdline, char *cmd, char ***cmd_argv, int *cmd_argc)
{
	int i = 0;
	int temp_argc = 0;
	int start_index;
	char **temp_argv = NULL;

	while (cmdline[i] != ' ' && cmdline[i] != '\0' && i < CMDLENGTH)
	{
		cmd[i] = cmdline[i];
		i++;
	}

	if (i == CMDLENGTH)
	{
		fprintf(stderr, "Cmd buffer overflow.\n");
		exit(1);
	}

	cmd[i] = '\0';


	temp_argv = malloc(sizeof(char*));
	temp_argv[temp_argc] = (char *) malloc((strlen(cmd)+1)*sizeof(char));
	strcpy(temp_argv[temp_argc], cmd);
	temp_argc++;

	while (cmdline[i] != '\0')
	{
		while (cmdline[i] == ' ')
		i++;
		start_index = i;

		while (cmdline[i] != ' ' && cmdline[i] != '\0')
		i++;

		if (temp_argv == NULL)
		temp_argv = malloc(sizeof(char*));
		else
		temp_argv = realloc(temp_argv, (temp_argc+1)*sizeof(char*));
		temp_argv[temp_argc] = (char *) malloc((i - start_index + 1) * sizeof(char));

		strncpy(temp_argv[temp_argc], cmdline+start_index, (i - start_index));
		temp_argv[temp_argc][i-start_index] = '\0';
		temp_argc++;
	}

	temp_argv = realloc(temp_argv, (temp_argc+1)*sizeof(char*));
	temp_argv[temp_argc] = NULL;

	(*cmd_argv) = temp_argv;
	(*cmd_argc) = temp_argc;

	return;

}

//frees/deallocates the memory assigned 
void freeCommandArgs(char ***cmd_argv, int *cmd_argc)
{
	int i;
	for (i = 0; i < (*cmd_argc); i++)
	free((*cmd_argv)[i]);
	if ((*cmd_argc) != 0)
	free((*cmd_argv));
	(*cmd_argc) = 0;

}


//Helper function to identify the type of command (string)
COMMANDTYPE getCommand(const char *cmd)
{
	if (strcmp(cmd, "exit") == 0)
	return EXIT;

	if (strcmp(cmd, "cd") == 0)
	return CD;

	if (strcmp(cmd, "pwd") == 0)
	return PWD;

	if (strcmp(cmd, "echo") == 0)
	return ECHO;

	return CMD;
}

//Echo command -  options: $?, $$, $<name>, <string>
void echoCommand(int argc, char **argv)
{
	int i;
	char *envVal;

	for (i = 1; i < argc; i++)
	{
		// Prints last exit status
		if (strcmp(argv[i], "$?") == 0)
		{
			printf("%d", returnStatus);
		}

		// Prints shell's pid
		else if (strcmp(argv[i], "$$") == 0)
		{
			printf("%d", getpid());
		}

		else if (argv[i][0] == '$')
		{
			if ((envVal = getenv(argv[i]+1)) == NULL)
			{
				perror("getenv");
				return;
			}

			else
			printf("%s", envVal);

		}

		else
		printf("%s", argv[i]);
		printf(" ");
	}

printf("\n");
}


//Command path and executing the command by forking a child process
int execCommand (char *cmd, int argc, char **argv)
{
	char cmdPath[PATHLENGTH];
	pid_t child_pid;
	int retStat;

	#ifdef DEBUG

	printf ("cmd: %s\n", cmd);
	printf ("PATH: %s\n", PATH);

	#endif

	if (cmd[0] == '/')
	{
		strcpy(cmdPath, cmd);
	}

	else if (cmd[0] == '.')
	{
		if (realpath(cmd, cmdPath) == NULL)
		{
			fprintf(stderr, "%s: '%s' not found\n", programName, cmd);
			return 1;
		}
	}

	else
	{
		strcpy(cmdPath, PATH);
		strcat(cmdPath, "/");
		strcat(cmdPath, cmd);
	}

	#ifdef DEBUG
	printf("cmdPath: %s\n", cmdPath);
	#endif

	if (access(cmdPath, F_OK) != 0)
	{
		fprintf(stderr, "%s: '%s' not found\n", programName, cmd);
		return 1;
	}

	else
	{
		child_pid = fork();

	if (child_pid < 0)
	{
		perror("fork");
		return -1;
	}

	else if (child_pid == 0)
	{
		if (execv(cmdPath, argv) == -1)
		{
			perror("execv");
			return 1;
		}

	}

	else
	{
		wait(&retStat);
		return retStat;

	}

}

}


//Changes the current working directory of the shell
void changeDirectory(char *target)
{
	char tempPath[PATHLENGTH];
	char tempCurDir[PATHLENGTH];

	//target variable contains an address
	//ex: /var/lib

	if (target[0] == '/')
	{
		strcpy(tempPath, target);
	}


	//target contains a relative address
	//ex: foo/bar
	else
	{
		strcpy(tempPath, currentDirectory);
		strcat(tempPath, "/");
		strcat(tempPath, target);
	}

	//heck for the new path
	if (realpath(tempPath, tempCurDir) == NULL)
	{
		fprintf(stderr, "%s: cd: '%s': %s\n", programName, tempPath, strerror(errno));
		return;
	}

	else
	{
		if (chdir(tempCurDir) == -1)
		{
			perror("chdir");
			return;
		}
		strcpy(currentDirectory, tempCurDir);
	}

}


//Print the current working directory
void printcwd()
{
	char tempPath[PATHLENGTH];
	if (getcwd(tempPath, PATHLENGTH) == NULL)
	{
		perror("getcwd");
	}
	else
	printf("%s\n", tempPath);
}

int main(int argc, char **argv, char **envp)
{
	char cmdline[CMDLINELENGTH];
	char cmd[CMDLENGTH];
	char **cmd_argv = NULL;
	int cmd_argc;
	int i;
	int closeShell = FALSE;
	char tempPath[PATHLENGTH];
      

	programName = argv[0];
	initialize();
	printWelcome();

	while (closeShell != TRUE)
	{
		printPrompt();

		//COME BACK TO KEEP RECEIVING ERROR
		char *fgets(char *str, int size, FILE* cmdline);

		parseCommand(cmdline, cmd, &cmd_argv, &cmd_argc);
		#ifdef DEBUG
		printf("------\n");
		for (i = 0; i < cmd_argc; i++)
		{
		printf("argv[%d] = %s\n", i, cmd_argv[i]);
		}
		printf("------\n");
		#endif

		switch(getCommand(cmd))
		{
			case ECHO:
			echoCommand(cmd_argc, cmd_argv);
			break;

			case PWD:
			printf("%s\n", currentDirectory);
			break;

			case EXIT:
			closeShell = TRUE;
			break;

			case CD:
			changeDirectory(cmd_argv[1]);
			break;

			case CMD:
			returnStatus = execCommand(cmd, cmd_argc, cmd_argv);
			break;
		}

		freeCommandArgs(&cmd_argv, &cmd_argc);
	}

	return 0;
}
