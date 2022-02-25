// Yarden Mirko : 209329416
// Dan Sasi : 313369423
#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <sys/wait.h>
#include <libgen.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[])
{


    char buf1[50];
    char buf2[50] ;
    char buf3[50] ;
    char buf4[50];
    char test[50];
    char buf5[100] ;
    size_t len = 10;
    int newfolder;
    int newcom;
    int stat;
    pid_t pid;
	pid_t pid2;
    FILE* fp;
    int  fp1;
    int fp2;
	 pid_t pid3;
    int list;
    int s_fd;
    int status;
    int size;
    int count=0;
    int l;
	fp = fopen(argv[1], "r");
	if (fp < 0){
        perror("error");
        exit(3);
        }

        fgets(buf1, 150, fp);
        l = strlen(buf1);
        buf1[10] = '\0';
	printf(" line 1 of config.txt : %s\n",buf1);
        fgets(buf2, 150, fp);
        l = strlen(buf2);
        buf2[l-1] = '\0';
        printf(" line 2 of config.txt : %s\n",buf2);
        fgets(buf3, 150, fp);
        l = strlen(buf3);
        buf3[l-1] = '\0';
        printf(" line 3 of config.txt : %s\n",buf3);

        list = open("StudentList.txt", O_RDONLY| O_WRONLY | O_CREAT| O_TRUNC,0666);
        if (list < 0){
        perror("error");
        exit(3);
        }
	if ((pid = fork()) == 0)
    	{
		dup2(list,1);
        	execlp("ls","ls", buf1, NULL);
		exit(3);
    	}
 	else
    	{
          int waited3 =	wait(&status);
    	}

        fp1 = open("results.csv", O_RDONLY| O_WRONLY | O_CREAT| O_TRUNC,0666);
	if (fp1 < 0){
        perror("error");
        exit(3);
        }
	close(list);
        fp = fopen("StudentList.txt", "r");
	if (fp < 0){
        perror("error");
        exit(3);
        }
	int status3;
	int status2;
       	int fdoutput;
	int fdinput;
	int lenSt = 0;
	int screen_fd;
    	while ((fgets(buf4,100,fp)) != NULL)
    	{
		printf("Before Fork\n");
		lenSt = strlen(buf4);
		buf4[lenSt-1] = '\0';
		printf("studentName = %s\n",buf4);

		 fdoutput = open("output.txt",  O_CREAT | O_WRONLY|O_RDONLY|O_TRUNC |O_APPEND |O_SYNC ,0777);
		if (fdoutput < 0){
                 perror("error");
       		 exit(3);
                 }
		pid2 = fork();

        	if ( pid2 == 0 )
       		 {
			  printf("child 2\n");
                       
         		//printf("in child\n");
			 fdinput = open(buf2, O_RDONLY,0777);
                	 if (fdinput < 0){
               		 perror("error with create or write the input list");
               		 exit(3);
                         if(pid2 == pid)
                         {
                           perror("not the same Fork");
                          exit(-1);
                         } 
                	}
                	strcat(buf5,buf1); //./students
                	strcat(buf5,"/"); //./students/
                	strcat(buf5,buf4); //./students/studentName
                	strcat(buf5,"/"); //./students/studentName/
                	strcat(buf5,"main.out"); //./students/studentName/main.out
                	printf("%s\n",buf5);
                	dup2(fdinput,0);
                	dup2(fdoutput,1);
			if( (execl(buf5,buf5,NULL)) == -1){ //./students
                	        perror("failed\n");
                            exit(-1);
                	}
			exit(3);




                  }
		else//parent
                 {
                        
			printf("Parent wait to main.out\n");
 			int waited =  wait(&status2);
			pid3 = fork();
                         
			if(pid3 == 0)
			{
				     printf("child 3\n");
                                   
				fdoutput = open("./output.txt", O_RDONLY ,0777);
				if (fdoutput < 0){
       				 perror("error");
       				 exit(3);
       				 }
                                if (pid3 == pid2)
                                 {
                                    perror("not the same fork");
                                      exit(-1);
                                 } 
                                  
				 if((execl("./comp.out","./comp.out",buf3,"./output.txt",NULL))==-1)
                                    {
                                      perror("faild");
                                    exit (-1);
                                    }
                               exit(3);
                                  
                        }
                        else{
				 screen_fd = dup(1);
				printf("Parent wait to comp.out\n");
				int waited2 = wait(&status3);
			      //	if(WIFEXITED(status3))
			       //	{
				int exit_status = WEXITSTATUS(status3);
				printf("status of child : %d\n",exit_status);
				dup2(fp1,1);
                            
				 printf("%s , ",buf4);
                           
				if(exit_status == 2)
					printf("100\n");
				else
					printf("0\n");
			// 	}
				 dup2(screen_fd,1);
			}




                 }
       }




return 0;
}



