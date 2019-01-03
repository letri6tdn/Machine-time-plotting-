/*Submitting student: TRI NGUYEN
* Collaborating classmates: Changxin Zhan
* Other collaborators: NONE
* References (excluding textbook and lecture slides):
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define max(a,b) ((a)>(b)?(a):(b))//max between a and b
#define list_size 10000

int max_n,min_n,sum_n;

int print_error() {  
	printf("\nError in reading the instace!\n");
	exit(0);	
}

int find_max_min_sum(int j,int array[j][4]){
	int a[j];
	int i;

	for (i= 0;i < j;++i){
		a[i]= array[i][0];
	}
	
	max_n= a[0]; 
	for (i = 1; i < j; i++)
	{
		if (max_n< a[i]) {		
		max_n= a[i]; 
		}
	}

	min_n= a[0];
	for (i= 1; i< j; i++)
	{
		if (min_n> a[i]) {		
		min_n= a[i]; 
		}
	}
	
	sum_n = 0;
	for (i= 0;i< j;++i){
		sum_n+= a[i];
	}	
	sum_n= sum_n- min_n;
	
	return 0;
}

//the lpt fuction 
int lpt(int j,int array[j][4],int t,int mc){
	
	//t is set in the main as 0 
	//all the machine is avalible at beginning
	int time[j];// time of the corresponding position of jobs
	int jobs[j][3];//1.jobs id 2.which machine process 3.start time
	int machine[mc][3];//1.machine id 2.rest of process time 3.total time have processed
	int T,temp,tep;
	int i,x,y,z;
	int makespan;
	int flag;
		
	//set the id of each time and jobs
	for (i= 0;i< j;++i){
		time[i]= array[i][0];
		jobs[i][0]= array[i][3];
	}
	//order the jobs and time
	for (x= 0;x< j;++x){
		for (y= x+ 1;y< j;++y){		
			if (time[y]> time[x]){
				
				temp= time[x];
				time[x]= time[y];
				time[y]= temp;
				tep= jobs[x][0];
				jobs[x][0]= jobs[y][0];
				jobs[y][0]= tep;
			}
		}
	}
	
	//set the machine number and the time of machine to be 0
	for (i= 0;i< mc;++i){
		
		machine[i][0]= i + 1;
		machine[i][1]= 0;
		machine[i][2]= t;
	} 	
	
	//decide which job set in which machine
	z= 0;
	while(z< j) {//iteration untill all the jobs have been process		
		for(i= 0;i< mc;++i){		
			if (machine[i][1]== 0 && z < j){//if there is machine is availble
				
				jobs[z][1]= machine[i][0];//decide which machine process the job
				jobs[z][2]= machine[i][2];//decide the start time
				machine[i][1]= time[z];//increse the rest of time
				machine[i][2]+= time[z];//increse the total tim
				z++;
			}
		}
		for (x= 0;x< mc;++x){
		//for every iteration that minus 1 on the machine rest of processing time
			machine[x][1]=machine[x][1] - 1;
		}
	}

	//largest time in the total time of the machine to print out the T
	T= machine[0][2];
	for (i= 0;i< mc;++i){
		if (machine[i][2] > T){
			T= machine[i][2];
		}
	}
	makespan= T-t;	
	return makespan;
}

//the johnson function 
int johnson(int j,int array[j][4],int t,int mc){
	
	int cp_list[j];//this is the time comparing list
	int time[j][4];//1.the B machine processing time 2.C macine processing time 3.the remaining time done by machine B 4.the remaining time done bu machine C
	int jobs[j][3];//1.jobs id 2.start time on machine B 3.start time on machine C
	int machineB[3];//1.machine id b 2.the rest of time 3.the total time
	int machineC[3];//1.machine id c 2.the rest of time 3.the total time
	int temp,tmp,tp,p;
	int i,x,y,z;
	int T;
	int makespan;
	
	//set the id of machine and initialize the time of machine
	machineB[0]= 1;
	machineC[0]= 2;
	machineB[1]= 0;
	machineB[2]= t;
	machineC[1]= 0;
	machineC[2]= t;
	//set each time and the job id
	for (i= 0;i< j;++i){
		
		time[i][0]= array[i][1];
		time[i][1]= array[i][2];
		jobs[i][0]= array[i][3];
	}
	
	//choose the smaller time in one job in the B and C processing time
	//and put it into the time comparing list
	for(i= 0;i < j;++i){		
		if (time[i][0]<= time[i][1]){
			
			cp_list[i]= time[i][0];		
		}
		else{
			
			cp_list[i]= time[i][1];
		}		
	}	
	
	//order the cp_list and jobs and time
	for (x= 0;x< j;++x){
		for (y= x + 1;y< j;++y){		
			if (cp_list[y]< cp_list[x]){
				
				temp= cp_list[x];
				cp_list[x]= cp_list[y];
				cp_list[y]= temp;
				
				tmp= jobs[x][0];
				jobs[x][0]= jobs[y][0];
				jobs[y][0]= tmp;
				
				tp= time[x][0]; 
				p= time[x][1];
				time[x][0]= time[y][0];
				time[x][1]= time[y][1];
				time[y][0]= tp;
				time[y][1]= p;
			}
		}
	}
	
	//reoder it by decide the shortest time is from B or C 
	x= j;
	for (i= 0;i< x;++i){
		if (cp_list[i]!= time[i][0]){			
			temp= cp_list[i];
			tmp= jobs[i][0];
			tp= time[i][0]; 
			p= time[i][1];
			
			for (y= i;y< x;++y){				
				cp_list[y]= cp_list[y+1]; 
				jobs[y][0]= jobs[y+1][0];
				time[y][0]= time[y+1][0];
				time[y][1]= time[y+1][1];
			}
			cp_list[x-1]= temp;
			jobs[x-1][0]= tmp;
			time[x-1][0]= tp;
			time[x-1][1]= p;
			x--;
			i--;	
		}
	}

	//seting the remaining time done by B and C
	for (i= 0;i< j;++i){
		time[i][2]= time[i][0];
		time[i][3]= time[i][1];
	}
	
	z= 0;
	x= 0;
	machineC[2]+= time[0][0];//presetting the total time of machine C
	while(x < j) {//iteration untill all the jobs have been process		
	
		if (machineB[1]== 0){//if there is machine is availble
								
			jobs[z][1]= machineB[2];//decide the start time
			machineB[1]= time[z][0];//increse the rest of time
			machineB[2]+= time[z][0];//increse the total tim
			z++;
		}
		
		if (machineC[1]== 0 && time[x][2]== 0){
			
			jobs[x][2]= machineC[2];//decide the start time
			machineC[1]= time[x][1];//increse the rest of time
			machineC[2]+= time[x][1];//increse the total tim
			x++;
		}		
		if(x> 0){
		
			if (machineC[1]== 0 && time[x-1][3]== 0){//if the machine is avalible and noting is processed
				machineC[2]++;//increase the total time
			}
		}
		if (z < j){
			machineB[1]-= 1;//minus 1 for each iteration when not all the job is done by B
		}
		if (time[z-1][2]> 0){
			time[z-1][2]--;//minus 1 remaining time of machine b,if it is 0 the it is finished by B
		} 
		if (machineC[1]> 0){
			machineC[1]--;//minus 1 for each iteration if is 0 the it is avalible
		}
		if (x > 0){
			if (time[x-1][3]                                > 0){
				time[x-1][3]--;//minus 1 remaining time of machine C,if it is 0 the it is finished by C
			}
		}
	}
	//set T
	T= machineC[2];

	//print out the time and set the makespan
	makespan= T-t;
	/*printf("\n\nThe job processing time interval is [%d, %d] , and the makespan is %d .\n\n",t,T,makespan);*/
	return makespan;
}

int final_t(int j,int mc,int array[j][4],int t){
	//this is the fuction that print out the overall makespan
	int J1[mc][4];//set the J1
	int J2[j-mc][4];//set the J2
	int x,y,i;
	int temp,tmp,tp,p;
	int t1,t2,t3,t4,T;
	//set the jobs id
	for (i = 0;i < j;++i){
		array[i][3] = i + 1;
	}
	//sort the array (the longest processing time 
	for (x= 0;x< j;++x){
		for (y= x + 1;y< j;++y){		
			if (array[x][0]< array[y][0]){
				
				temp= array[x][0];
				array[x][0]= array[y][0];
				array[y][0]= temp;
				
				tmp= array[x][1];
				array[x][1]= array[y][1];
				array[y][1]= tmp;
				
				tp= array[x][2];
				array[x][2]= array[y][2];
				array[y][2]= tp;
				
				p= array[x][3];
				array[x][3]= array[y][3];
				array[y][3]= p;
			}
			//lower id first
			else if (array[x][0]== array[y][0]){
				if(array[x][3]> array[y][3]){
				
					temp= array[x][0];
					array[x][0]= array[y][0];
					array[y][0]= temp;
				
					tmp= array[x][1];
					array[x][1]= array[y][1];
					array[y][1]= tmp;
				
					tp= array[x][2];
					array[x][2]= array[y][2];
					array[y][2]= tp;
				
					p= array[x][3];
					array[x][3]= array[y][3];
					array[y][3]= p;
				}
			}
		}
	}	
	x= 0;
	if (j< mc){
		x= j;
	}
	else{
		x= mc;
	}
	//set the J1 and J2
	for (i= 0;i< x;++i){
		J1[i][0]= array[i][0];
		J1[i][1]= array[i][1];
		J1[i][2]= array[i][2];		
		J1[i][3]= array[i][3];	
	}
	y= 0;
	for (i;i<j;++i){
		J2[y][0]= array[i][0];
		J2[y][1]= array[i][1];
		J2[y][2]= array[i][2];
		J2[y][3]= array[i][3];
		y++;
	}
	//get the t1,t2,t3,t4 and judge the mc and x
	t1= lpt(x,J1,t,mc);
	if (j - mc> 0){
	
		t2= johnson(j-mc,J2,t,mc);
	}
	else{
		
		t2= 0;
	}
	t= max(t1,t2);
	if (j - mc> 0){
	
		t3 = lpt(j-mc,J2,t,mc);
	}
	else{
		
		t3 = 0;
	}
	t4 = johnson(x,J1,t,mc);
	T = max(t+t3,t+t4);
	
	return T;
}

int main(int argc,char *argv[]) {
	
	int mc,j;
	int x,y;
	int m,n,z;
	int i;
	int t = 0;
	int L2,S;
	double L,L1,r,ave;
	
	if (!strcmp(argv[1],"-i")) {
		
		printf("Enter the number of machines in stage 1 : ");
		if (!scanf("%d", &mc)){//get the number of machines
			print_error();	
		
		}
		printf("Enter the number of jobs : ");
		if(!scanf("%d", &j)){//get the number of jobs
			print_error();
		}
		
		int array[j][4];//create the array 1.A processing time 2.B ...3.C....4.empty
		
		printf("Enter in each line the processing times for a job:\n");
		
		for (x= 0; x< j; ++x) {			
		
			for (y= 0;y< 3; ++y) {			
				
				if (!scanf("%d", &array[x][y])) {//get the input of the array which is the time of each machine processing time
					
					print_error();
				}	
			}
		}
		
		printf("\n#instance%d_%d_1.txt\n", mc, j);
		printf("#number of stage 1 machines\n%d\n",mc);
		printf("#number of jobs\n%d\n",j);
		printf("#job processing times\n");//print out all the information
		
		for (x= 0; x < j; ++x) {
			
			for (y= 0; y < 3; ++y) {
				
				printf("%d ", array[x][y]);
			}
			printf("\n");//print out the array
		}
		
		printf("#end of instance\n\n");
		find_max_min_sum(j,array);
		printf("a_1 = %d\n",max_n);
		ave = (double)sum_n/mc;
		L1 = max(max_n,ave);
		printf("average load = %lf\n",ave);
		L2 = johnson(j,array,t,mc);
		printf("L_1 = %lf\n",L1);
		printf("L_2 = %d\n",L2);
		L = max(L1,L2);
		printf("L = %lf\n",L);
		S = final_t(j,mc,array,t);//get into the LPT and johnson rules and print it out
		printf("LPT_Johnson schedule makespan = %d\n",S);
		printf("Calculate the ratio r = %lf\n",S/L);
		
	return 0;
	}
	
	//r parts for assignment
	if (!strcmp(argv[1],"-r")) {
		
		int L2,S;
		double L,L1,r,ave;
		int t = 0;
		int m[list_size];//number of machines in stage 1 
		int n[list_size];//number of jobs
		int t1[list_size], t2[list_size]; //the time interval
		int k[list_size];//the number of such instances
		int i,j,x,y,z,u,uu,uuu,uuuu,uuuuu,uuuuuu,a,b;
		int judge;
		double r_sum;
		
		
		printf("Generating random instance ...\n");
		printf("Enter the number of machines in stage 1 (max 10000 digits, each digit seperate with a space): ");
		
		for (i= 0;i < list_size;++i){
			//input the machine number
			scanf("%d", &m[i]);
			if (getchar() == '\n') break;

		}
		printf("Enter the number of jobs (max 10000 digits, each digit seperate with a space): ");
		for (j= 0;j < list_size;++j){
			//input the number of jobs
			scanf("%d", &n[j]);
			if (getchar() == '\n') break;
		}
		
		printf("Enter the processing time interval [t_1, t_2] \n");
		printf("First enter all the t_1 : ");
		for (x= 0;x < list_size;++x){
			//input the t1
			scanf("%d", &t1[x]);
			if (getchar() == '\n') break;
		}
		printf("Second enter all the t_2 : ");
		for (y= 0;y < list_size;++y){
			//input the t2
			scanf("%d", &t2[y]);
			if (getchar() == '\n') break;
		}		
		
		printf("Enter the number of instances to be generated : ");
		for (z= 0;z < list_size;++z){
			//input the number of instances 
			scanf("%d", &k[z]);
			if (getchar() == '\n') break;
		}
		printf("what kind of ratio do you want\n1.r(m, n)\n2.r(m, ¡¤)\n3.r(¡¤, n)\nEnter the order number : ");
		//choosing the type of ratio that you want
		scanf("%d",&judge);
		
		if (judge == 1){	//type1	
			FILE *rp=fopen("ratio_calculate.txt","w");//create a file that note down all the average ratio
			for (u = 0;u < i+1;++u){//the iteration of m
				for (uu = 0;uu < j+1;++uu){//the iteration of n
					int array[n[uu]][4];//create new list
					r_sum = 0;//reset the s_sum
					for (uuu = 0;uuu < x+1;++uuu){//the iteration of t1
						for (uuuu = 0;uuuu < y+1;++uuuu){//the iteration of t2
							for (uuuuu = 0;uuuuu < z+1;++uuuuu){//the iteration of k
								for (uuuuuu = 0;uuuuuu < k[uuuuu];++uuuuuu){//the iteration of from 0 to k nums
									
									char file[64] = {0};
									sprintf(file,"instance%d_%d_%d_%d_%d.txt", m[u], n[uu], t1[uuu], t2[uuuu], uuuuuu+1);// to set the title of the txt
									//write the file
									FILE *fp=fopen(file,"w");
									fprintf(fp,"#number of stage 1 machines\n%d\n", m[u]);
									fprintf(fp,"#number of jobs\n%d\n",n[uu]);
									fprintf(fp,"#job processing times\n");
									for (a = 0; a < n[uu]; ++a) {			
										for (b = 0; b < 3; ++b) {
											array[a][b] = rand()% (t2[uuuu]-t1[uuu]+1)+t1[uuu];	
											fprintf(fp,"%d ", array[a][b]);
										}
										fprintf(fp,"\n");
									}
									
									//this part have the function to generate the each instance ratio
									find_max_min_sum(n[uu],array);
									ave = (double)sum_n/m[u];
									L1 = max(max_n,ave);
									L2 = johnson(n[uu],array,t,m[u]);
									L = max(L1,L2);
									S = final_t(n[uu],m[u],array,t);
									r = S/L; 
									r_sum += r;//adding the ratio together								
									fprintf(fp,"#end of instance\n");
									fclose(fp);
								}
							}
						}
					}
				r_sum = r_sum/1000;//get the average ratio
				fprintf(rp,"The average ratio between %d %d : ", m[u], n[uu]);
				fprintf(rp,"%lf\n",r_sum);//write it down to the 
				}
			}
		fclose(rp);
		}
		else if (judge == 2){
			
			FILE *rp=fopen("ratio_calculate.txt","w");
			for (u = 0;u < i+1;++u){
				r_sum = 0;
				for (uu= 0;uu< j+1;++uu){
					int array[n[uu]][4];
					for (uuu = 0;uuu < x+1;++uuu){
						for (uuuu =0;uuuu < y+1;++uuuu){
							for (uuuuu =0;uuuuu < z+1;++uuuuu){
								for (uuuuuu =0;uuuuuu< k[uuuuu];++uuuuuu){
										
									char file[64] = {0};
									sprintf(file,"instance%d_%d_%d_%d_%d.txt", m[u], n[uu], t1[uuu], t2[uuuu], uuuuuu+1);
									FILE *fp=fopen(file,"w");
									fprintf(fp,"#number of stage 1 machines\n%d\n", m[u]);
									fprintf(fp,"#number of jobs\n%d\n",n[uu]);
									fprintf(fp,"#job processing times\n");
									for (a= 0; a< n[uu]; ++a) {			
										for (b= 0; b < 3; ++b) {
											array[a][b] = rand()% (t2[uuuu]-t1[uuu]+1)+t1[uuu];	
											fprintf(fp,"%d ", array[a][b]);
										}
										fprintf(fp,"\n");
									}
										
									find_max_min_sum(n[uu],array);
									ave = (double)sum_n/m[u];
									L1 = max(max_n,ave);
									L2 = johnson(n[uu],array,t,m[u]);
									L = max(L1,L2);
									S = final_t(n[uu],m[u],array,t);
									r = S/L; 
									r_sum += r;
										
									fprintf(fp,"#end of instance\n");
									fclose(fp);
								}
							}
						}
					}
				}
				r_sum = r_sum/20000;
				fprintf(rp,"The average ratio between %d %d : ", m[u], n[uu]);
				fprintf(rp,"%lf\n",r_sum);
			}	
			fclose(rp);	
		}
		else if (judge == 3){
			FILE *rp=fopen("ratio_calculate.txt","w");
			for (uu = 0;uu < i+1;++uu){
				r_sum= 0;
				for (u= 0;u< j+1;++u){
					int array[n[uu]][4];
					for (uuu = 0;uuu < x+1;++uuu){
						for (uuuu = 0;uuuu < y+1;++uuuu){
							for (uuuuu = 0;uuuuu < z+1;++uuuuu){
								for (uuuuuu = 0;uuuuuu < k[uuuuu];++uuuuuu){
										
									char file[64] = {0};
									sprintf(file,"instance%d_%d_%d_%d_%d.txt", m[u], n[uu], t1[uuu], t2[uuuu], uuuuuu+1);
									FILE *fp=fopen(file,"w");
									fprintf(fp,"#number of stage 1 machines\n%d\n", m[u]);
									fprintf(fp,"#number of jobs\n%d\n",n[uu]);
									fprintf(fp,"#job processing times\n");
									for (a = 0; a < n[uu]; ++a) {			
										for (b = 0; b < 3; ++b) {
											array[a][b] = rand()% (t2[uuuu]-t1[uuu]+1)+t1[uuu];	
											fprintf(fp,"%d ", array[a][b]);
										}
										fprintf(fp,"\n");
									}
										
									find_max_min_sum(n[uu],array);
									ave = (double)sum_n/m[u];
									L1 = max(max_n,ave);
									L2 = johnson(n[uu],array,t,m[u]);
									L = max(L1,L2);
									S = final_t(n[uu],m[u],array,t);
									r = S/L; 
									r_sum += r;
										
									fprintf(fp,"#end of instance\n");
									fclose(fp);
								}
							}
						}
					}
				}
				r_sum = r_sum/20000;
				fprintf(rp,"The average ratio between %d %d : ", m[u], n[uu]);
				fprintf(rp,"%lf\n",r_sum);
			}
			fclose(rp);		
		}
	return 0;	
	}

	printf("\n./assignment -i | -r\n");
	return 0;	
}
