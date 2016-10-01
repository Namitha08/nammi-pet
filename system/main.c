#include <xinu.h>
#include <kernel.h>

pid32 process1;
pid32 process2;



int N=10;


int number_of_itr = 100;

void tryToSendMessage(pid32 targetProcess, int message) {
	if(send(targetProcess, message)){
		printf("Sent message - %d \n", message);
	} else {
		printf("Error while sending message %s\n", message);
	}
}

int tryToRecieveNumber(void) {
	int message = receive();
	return message;
}

/**
	processes will start exchanging messages
*/
process communicateP1(void) {
	int i = 0;
	for(i = 0; i<10; i++){
		tryToSendMessage(process2, i);
		int message = tryToRecieveNumber();
		printf("Recieved message - %d \n", message);
	}
	return OK;
}

process communicateP2(void) {
	int i = 0;
	for(i = 0; i<10; i++){
		tryToSendMessage(process1, i);
		tryToRecieveNumber();
	}
	return OK;
}

process main(){
	recvclr();



	process1 = create(communicateP1, 4096, 50, "producer",0);
	process2 = create(communicateP2, 4096, 50, "consumer",0);

	int i = 0;
	for(i = 0; i < N; i++){

	}

	resume(process1);
	resume(process2);

	return OK;
}
