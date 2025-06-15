
//writer

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SHM_SIZE 1024 //size if shared memory segment

int main(){
	key_t key =  ftok("shmfile",54); // generate unique key
	int shmid = shmget(key,SHM_SIZE, IPC_CREAT| 0666); //create shared memeory segmewnt
	
	if(shmid == -1){
		perror("shmget");
		exit(1);
	}
	
	char *shmaddr = (char*) shmat(shmid,NULL,0); //Attach to shared memory
	if(shmaddr == (char*) -1) {
		perror("shmat");
		exit(1);
	}
	
	printf("Write Data: ");
	fgets(shmaddr, SHM_SIZE,stdin); //write data to shared memory
	printf("Data written in memory: %s\n", shmaddr);
	
	shmdt(shmaddr);  //Detach from shared memory
	
	return 0;
}

//reader

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SHM_SIZE 1024 //size if shared memory segment

int main(){
	key_t key =  ftok("shmfile",54); // generate unique key
	int shmid = shmget(key,SHM_SIZE ,0666); //create shared memeory segmewnt
	
	if(shmid == -1){
		perror("shmget");
		exit(1);
	}
	
	char *shmaddr = (char*) shmat(shmid,NULL,0); //Attach to shared memory
	if(shmaddr == (char*) -1) {
		perror("shmat");
		exit(1);
	}
	
	printf("Data read from memory: %s\n", shmaddr); //Read data from shared memory
	
	shmdt(shmaddr);  //Detach from shared memory
	
	shmctl(shmid,IPC_RMID,NULL); //Removed shared memory segment
	
	return 0;
}



[Yasho@LAPTOP-JKTQHF95 ~]$ touch shmfile
[Yasho@LAPTOP-JKTQHF95 ~]$ chmod 644 shmfile
[Yasho@LAPTOP-JKTQHF95 ~]$ vi smWriter.c
[Yasho@LAPTOP-JKTQHF95 ~]$ vi smWriter.c
[Yasho@LAPTOP-JKTQHF95 ~]$ vi smReader.c
[Yasho@LAPTOP-JKTQHF95 ~]$ gcc smWriter.c -o smWriter
[Yasho@LAPTOP-JKTQHF95 ~]$ gcc smReader.c -o smReader
[Yasho@LAPTOP-JKTQHF95 ~]$ ./smWriter
Write Data: Hello !!!
Data written in memory: Hello !!!

[Yasho@LAPTOP-JKTQHF95 ~]$ ./smReader
Data read from memory: Hello !!!
