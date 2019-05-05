#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#define BUF_SIZE 1024
#define SHM_KEY 0x3963

struct shmseg {
	int cnt;
   	int complete;
   	char buf[BUF_SIZE];
};

const int SHMSZ = sizeof(struct shmseg);

int main(int argc, char *argv[]) {
	int shmid;
   	struct shmseg *shm;
	/* LOCATE SEGMENT */
   	if((shmid = shmget(SHM_KEY, SHMSZ, 0666)) < 0){
      		perror("Shared memory: shmget()");
      		exit(1);
   	}
   
   	/* ATTACH SEGMENT TO DATA SPACE */
	if((shm = shmat(shmid, NULL, 0)) < 0){
        	perror("Shared memory attach: shmat()");
               	exit(1);
        }
                     
	/* Transfer blocks of data from shared memory to stdout */
   	//while (shm->complete != 1) {
        // 	printf("segment contains : \n\"%s\"\n", shm->buf);
         //      	if (shm->cnt == -1) {
          //      	perror("read");
           //             return 1;
            //    }
	printf("Reading Process: Shared Memory: Read %d bytes\n%s\n", shm->cnt, shm->buf);
      	sleep(3);
       	//}
        
        printf("Reading Process: Reading Done, Detaching Shared Memory\n");
        if (shmdt(shm) == -1) {
         	perror("DETACHING SHARED MEMORY: shmdt()");
                return 1;
        }


	printf("Cleaning up: Deleting Memory Segment\n");
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
         	perror("DELETE MEMORY SEGMENT: shmctl()");
                return 1;
        }
        printf("Reading Process: Complete\n");
        exit(0);
}
