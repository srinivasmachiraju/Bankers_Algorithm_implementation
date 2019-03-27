/*
please open with ATOM
	group members                                     RollNo
	S.Satya Pramod                                   AM.EN.U4CSE16255
	T.Venu Vardhan Reddy                             AM.EN.U4CSE16508
	N.Vinay Varma                                    AM.EN.U4CSE16505
  M.Srivasthasva Srinivas                          AM.EN.U4CSE16506
	*/

	/*    We produced 10 child processes and 1 parent process in each child we will take 5 random
	inputs for max,5 random inputs for allocation, 5 random inputs for request. Using shared memory
	we will pass this info to the parent and the process will implement bankers algorithm and if There
	is a safe sequence the the sequence is printed . Now the parent process looks at all the 10 requests
	and apply resource request algorithm to tell which all requests can be granted and which are granted and
	which are not granted*/




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include<wait.h>
#include<stdbool.h>

void sem_lock( int sem_id,int sem_num)
{
	struct sembuf sem_op;
	sem_op.sem_num = sem_num;
	sem_op.sem_op = -1;
	sem_op.sem_flg = 0;
	semop(sem_id, &sem_op, 1);

}
void sem_unlock(int sem_id,int sem_num)
{
	struct sembuf sem_op;
	sem_op.sem_num = sem_num;
	sem_op.sem_op = 1;
	sem_op.sem_flg = 0;
	semop(sem_id, &sem_op, 1);
}

int  main()
{

	int shmid = shmget(IPC_PRIVATE, 300 * sizeof(int), 0777 | IPC_CREAT);
	int sem_id = semget(IPC_PRIVATE, 17 , IPC_CREAT | 0777 );
	printf("enter available resources");
	int available[5];
	for(int j=0;j<5;j++){
			scanf("%d",&available[j]);
	}
	semctl(sem_id , 0, SETVAL, 1);
	semctl(sem_id , 1, SETVAL, 1);
	int *a,*b;
	int need[11][5];
	int request[11][5];
	int max[11][5];
	int work[5];
	int reqneed[11][5];
	int reqmax[11][5];
	int reqwork[5];
	int reqallo[11][5];
	int allo[11][5];
  bool state[11];
	int order[10];
	int flag5=0;
	for(int i=1;i<11;i++){
		state[i]=false;
	}
	{
	int pid1=fork();
	if(pid1==0){
										sem_lock(sem_id,0);
											sem_lock(sem_id,1);
						a=shmat(shmid,0,0);
								//child 1 process
								for(int i=0;i<5;i++){
									int c=rand()%10;
										max[1][i]=c;
										a[0*10+i]=c;
										allo[1][i]=rand()%(max[1][i]+1);
										a[0*10+i+5]=allo[1][i];
										 c=rand()%1;
										a[10*10+i]=c;
										int n;
								}
							sem_unlock(sem_id,1);

	}
	else {
			int pid2=fork();
			if(pid2==0){
									//child 2 process
										sem_lock(sem_id,1);
										a=shmat(shmid,0,0);
									for(int i=0;i<5;i++){
											int c=rand()%5;
												max[2][i]=c;
													a[1*10+i]=max[2][i];
												allo[2][i]=rand()%(max[2][i]+1);
													a[1*10+i+5]=allo[2][i];
													 c=rand()%2;
													a[11*10+i]=c;

									}
									sem_unlock(sem_id,1);

			}
			else{
			  	int pid3=fork();
					if(pid3==0){
										sem_lock(sem_id,1);
									 	//child 3 process
											a=shmat(shmid,0,0);
										for(int i=0;i<5;i++){
												int c=rand()%20;
												max[3][i]=c;
													a[2*10+i]=max[3][i];
												allo[3][i]=rand()%(max[3][i]+1);
													a[2*10+i+5]=allo[3][i];
													 c=rand()%1;
													a[12*10+i]=c;


										}

										sem_unlock(sem_id,1);

					}
					else{
							int pid4=fork();
							if(pid4==0){
														sem_lock(sem_id,1);
													//child 4 process
														a=shmat(shmid,0,0);
													for(int i=0;i<5;i++){
															int c=rand()%11;
															max[4][i]=c;
																a[3*10+i]=max[4][i];
															allo[4][i]=rand()%(max[4][i]+1);
																a[3*10+i+5]=allo[4][i];
																 c=rand()%2;
																a[13*10+i]=c;


													}
													sem_unlock(sem_id,1);
												}
							else{
									int pid5=fork();
									if(pid5==0){
														//child 5 process
															sem_lock(sem_id,1);
															a=shmat(shmid,0,0);
														for(int i=0;i<5;i++){
																int c=rand()%8;
																	max[5][i]=c;
																		a[4*10+i]=max[5][i];
																	allo[5][i]=rand()%(max[5][i]+1);
																		a[4*10+i+5]=allo[5][i];
																		 c=rand()%1;
																		a[14*10+i]=c;

														}
														sem_unlock(sem_id,1);

									}
									else{
											int pid6=fork();
											if(pid6==0){
													sem_lock(sem_id,1);
													a=shmat(shmid,0,0);
																//child 6 process
																for(int i=0;i<5;i++){
																		int c=rand()%4;
																			max[6][i]=c;
																				a[5*10+i]=max[6][i];
																			allo[6][i]=rand()%(max[6][i]+1);
																				 c=rand()%2;
																				a[15*10+i]=c;

																}
																sem_unlock(sem_id,1);
															}

											else{
													int pid7=fork();
													if(pid7==0){
															sem_lock(sem_id,1);
															a=shmat(shmid,0,0);
																		//child 7 process
																		for(int i=0;i<5;i++){
																				int c=rand()%15;
																					max[7][i]=c;
																						a[6*10+i]=max[7][i];
																					allo[7][i]=rand()%(max[7][i]+1);
																						a[6*10+i+5]=allo[7][i];
																						 c=rand()%1;
																						a[16*10+i]=c;

																		}
																		sem_unlock(sem_id,1);


													}
													else{
															int pid8=fork();
															if(pid8==0){
																	sem_lock(sem_id,1);
																	a=shmat(shmid,0,0);
																			//child 8 process
																			for(int i=0;i<5;i++){
																					int c=rand()%9;
																					max[8][i]=c;
																						a[7*10+i]=max[8][i];
																					allo[8][i]=rand()%(max[8][i]+1);
																						a[7*10+i+5]=allo[8][i];
																						 c=rand()%2;
																						a[17*10+i]=c;

																			}

																			sem_unlock(sem_id,1);


															}
															else{
																	int pid9=fork();
																	if(pid9==0){
																			sem_lock(sem_id,1);
																			a=shmat(shmid,0,0);
																		//child 9 process
																		for(int i=0;i<5;i++){
																				int c=rand()%7;
																					max[9][i]=c;
																						a[8*10+i]=max[9][i];
																					allo[9][i]=rand()%(max[9][i]+1);
																						a[8*10+i+5]=allo[9][i];
																					 c=rand()%1;
																						a[18*10+i]=c;

																		}

																		sem_unlock(sem_id,1);


																	}
																	else{
																			int pid10=fork();
																			if(pid10==0){
																					sem_lock(sem_id,1);
																					a=shmat(shmid,0,0);
																				// chile 10 process
																				for(int i=0;i<5;i++){
																						int c=rand()%6;
																							max[10][i]=c;
																								a[9*10+i]=max[10][i];
																							allo[10][i]=rand()%(max[10][i]+1);
																								a[9*10+i+5]=allo[10][i];
																								 c=rand()%2;
																								a[19*10+i]=c;
																				}
																					sem_unlock(sem_id,1);
																				sem_unlock(sem_id,0);
																			}
																			else{
																					//parent process
																					sem_lock(sem_id,0);
																				b=shmat(shmid,0,0);
																					printf("The maximum resources required are\n");
																					for(int i=0;i<10;i++){
																								for(int j=0;j<5;j++){
																											printf("%d ",b[i*10+j]);
																											max[i+1][j]=b[i*10+j];
																								}
																								printf("\n");
																					}
																					int count=1;//for checking no of processes left
																				printf("The allocated resources required are\n");
																				for(int i=0;i<10;i++){
																							for(int j=0;j<5;j++){
																										printf("%d ",b[i*10+j+5]);
																										allo[i+1][j]=b[i*10+j+5];
																										reqallo[i+1][j]=allo[i+1][j];
																							}
																							printf("\n");
																				}

																				printf("The needed resources are \n");
																				for(int i=1;i<11;i++){
																					 for(int j=0;j<5;j++){
																						 			need[i][j]=max[i][j]-allo[i][j];
																									printf("%d ",need[i][j]);
																									reqneed[i][j]=need[i][j];

																					 }
																					 printf("\n");
																				}
																				printf("The  resources requested are\n");
																				for(int i=10;i<20;i++){
																							for(int j=0;j<5;j++){
																									printf("%d ",b[i*10+j]);
																										request[i-9][j]=b[i*10+j];
																							}
																							printf("\n");
																				}
																				for(int i=0;i<5;i++){
																						work[i]=available[i];
																						reqwork[i]=work[i];
																				}
																				int k=0;//for order;
																				for(int i=1;i<11;i++){
																					int flag=0;
																						if(state[i]==false){
																						for(int j=0;j<5;j++){
																										if((need[i][j]>reqwork[j])){
																												flag=1;
																										}
																						}
																						if(flag==0){
																									for(int j=0;j<5;j++){
																											reqwork[j]=reqwork[j]+allo[i][j];
																											state[i]=true;
																									}
																									order[k]=i;
																									k++;
																						}
																				}
																					if(i==10){

																							for(int j=1;j<11;j++)
																								{
																										if(state[j]==false){
																												count++;
																												if(count>=10){
																													printf("There is no safe sequence") ;
																													return 0;
																												}
																												else{
																													if(flag5>10){
																														printf("There is no safe sequence") ;
																														return 0;
																													}
																													else{
																													i=0;
																													flag5++;
																												}
																												}

																										}
																								}

																					}
																		}
																			printf("The Safe Sequence is");
																			for(int k=0;k<10;k++){
																					printf("%d ",order[k]);
																			}
																			printf("\n");
																			 k=0;
																			for(int i=1;i<11;i++){
																				 flag5=0;
																					int flag2=0;
																					for(int j=0;j<5;j++){
																							reqwork[j]=work[j];
																					}
																							for(int j=0;j<5;j++){
																							if((request[i][j]>reqneed[i][j])||(request[i][j]>reqwork[i])){
																									flag2=1;
																							}
																						}
																						if(flag2==1){
																								b[200+i]=0;
																								printf("procees %d Request can not be granted\n",i);
																						}

																						else{

																							for(int j=0;j<5;j++){
																									reqneed[i][j]=reqneed[i][j]-request[i][j];
																										reqwork[j]=reqwork[j]-request[i][j];
																										reqallo[i][j]=reqallo[i][j]+request[i][j];

																							}
																							int flag3=0;

																						//for order;
																							for(int j=1;j<11;j++){
																									state[j]=false;
																							}
																							for(int m=1;m<11;m++){

																								int flag=0;
																									if(state[m]==false){
																									for(int j=0;j<5;j++){
																													if((reqneed[m][j]>reqwork[j])){
																															flag=1;
																													}
																									}
																									if(flag!=1){
																												for(int j=0;j<5;j++){
																														reqwork[j]=reqwork[j]+reqallo[m][j];
																												}
																												state[m]=true;

																									}
																							}
																								if(m==10){
																										for(int j=1;j<11;j++)
																											{
																													if(state[j]==false){
																															count++;
																															if(count>=10){
																																b[200+i]=0;
																																flag3=1;

																															}
																															else{
																																	if(flag5>15){
																																				flag3=1;
																																	}
																																	else{
																																m=0;
																																flag5++;
																															}

																															}

																													}
																											}
																								}
																					}
																							if(flag3==0){
																								printf("for process %d request can be granted\n", i);
																								printf("The maximum resources required are\n");
																					for(int i=0;i<10;i++){
																								for(int j=0;j<5;j++){
																											printf("%d ",max[i+1][j]);
																								}
																								printf("\n");
																					}
																					int count=1;//for checking no of processes left
																				//parent process
																				printf("The allocated resources required are\n");
																				for(int i=0;i<10;i++){
																							for(int j=0;j<5;j++){
																										printf("%d ",reqallo[i+1][j]);
																							}
																							printf("\n");
																				}

																				printf("The needed resources are \n");
																				for(int i=1;i<11;i++){
																					 for(int j=0;j<5;j++){
																						printf("%d ",need[i][j]);
																					 }
																					 printf("\n");
																				}

																							}
																							else if(flag3==1){

																											printf(" process %d  request will push the system in to unsafe state so request can not be granted\n",i) ;
																							}

																						}


																			}
																	sem_unlock(sem_id,0);
																	}

																	}
															}
													}
											 	}
										}
								}
						}
				}
	 }
 }
}
