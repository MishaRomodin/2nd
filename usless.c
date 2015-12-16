//secondTask from МС Мишаня & company
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

char NextLine = 10;
int MaxStringSize = 100;

int useless(char *str){
    int pause;
    char *argument=malloc(MaxStringSize);
    char *command=malloc(MaxStringSize),*p;//выделяем еще память с p
    pid_t pid;	
    if((pid=fork())<0){
	   printf("%s\n","Can't create child process.");
	   exit(-1);
    }
    if (pid>0) return 0;
    pause=strtol(str,&p,10);//преобразуем из строки в longint (до p) и присваем паузе
    sleep(pause);
    strcpy(command,p+1);//копируем строку command и вставляем ее в место с указателем p+1
    int i = strlen(command)-1;//i присваиваем длину строки command-1
    while(command[i] != '/'){//пока символ строки не равен слэшу, уменьшаем длину i и читаем предыдущий символ
        i--;
    }
    char mc[20];//создаем массив
    strncpy(mc, command, i)// (тоже самое что strcpy только с защиткой) скопировали в mc весь command начиная с i(т.е. со слэша). т.о. читаем только имя команды, ограниченное слэшами

    if(execl(command, mc, NULL)<0){
        printf("Error - %d", errno);
        printf("%s%s%s\n","Program ",command," failed to load.");
        exit(0);
    }
    exit(-1);
}
int main(){ 
    int file;
    char c,*str,*cur;
    ssize_t size;
    if((file=open("Input.txt",O_RDONLY))<0){
    	    printf("%s\n","Can't open file!");
            exit(-1);
    }
    str=malloc(MaxStringSize);
    cur=str;
    size=1;
    while (size!=0){
        size=read(file,&c,1);
	if((c == NextLine)||(size==0)){ 	    
            *cur=0;
            if(strlen(str)>0){ 
		      useless(str);
            }
            cur=str;
	    }
	    else{
		  *cur=c;
		  cur++;
	    }
	}    
    if(close(file)<0){
        printf("%s\n","Can't close file!");
	    exit(-1);
    }
}
