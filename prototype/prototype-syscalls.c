//followed tutortial https://www.youtube.com/watch?v=9seb8hddeK4&t=628s

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

//bin file located in ../../../bin (hammer)
//this program will execute ls -a
//this program will execute echo hello
//this program will execute mkdir test

void foo(const char *name){
	for(int i=0; i<5; i++){
		sleep(rand()%2);
		printf("done pass %d for %s\n", i, name);
	}
}


int main(int argc, char *argv[]){
	
	printf("This is a prototype. It tests the functionality of fork(), execvp(), and waitpid()\n");

	printf("I am %d\n", (int)getpid()); //getpid returns the id of the current process

	pid_t pid = fork();
	srand((int)pid);
	printf("fork returned %d\n", (int)pid);

	if(pid < 0){
		perror("Fork failed");
	}
	if(pid == 0){ //isolates fork
		printf("I am the child witth pid %d\n", (int)getpid());
		foo("child");

		exit(42);
	}

	//} else if (pid > 0){
		printf("I am the parent waitng for child to end\n");
	//	sleep(30);
		//foo("Parent");
		int status = 0;
		pid_t childpid = wait(&status);
		printf("Parent knows child %d finished. %d\n", (int)childpid, status);
		int childReturnValue = WEXITSTATUS(status); //masks for the 42
		printf("Retur value was %d\n", childReturnValue);
		//}
	
	char const *args[] = {"ls", "-l", "-h", "-a", NULL};
	execvp(args[0], argv);
	return 0;
}

