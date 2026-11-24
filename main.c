#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p,a[5],i,s,id,count=0;
    char path[50],name[100],state;
    FILE *f;
    setbuf(stdout, NULL);
    printf("ZOMBIE PROCESSES\n");

    for(i=0;i<5;i++){
        p =fork();
        if(p==0){
            printf("child process %d: PID = %d\n",i+1,getpid());
            exit(0);
        }
        else if(p>0){
            a[i]=p;
        }
        else{
            printf("fork process failed\n");
            return 1;
        }
    }
    sleep(2);
    printf("checking for zombie proceses\n");

    for(i=0;i<5;i++){
        sprintf(path,"/proc/%d/stat",a[i]);
        f=fopen(path,"r");
        if(f!=NULL){
            if(fscanf(f,"%d %99s %c",&id,name,&state)==3){
                if(state=='Z'){
                    printf("zombie proceses found: PID %d\n",a[i]);
                    count++;
                }
            }
            fclose(f);
        }
    }

    printf("total zombie processes found are: %d\n",count);
    printf("cleaning all of them\n");

    for(i=0;i<5;i++){
        waitpid(a[i],&s,0);
    }
    printf("cleaning process has been completed!");
    return 0;
}   
