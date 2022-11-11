#include<stdio.h>
#include<string.h>
#include<stdlib.h>
FILE *Reading_File;
FILE *Writing_File;
int i, j, tot = 0,for_numeric[10000],numOne=0;
void quickSort(int left, int right);
void quickSortMain();
char nameAll[10000][500], nameOne[500];
void selectionSort(char arr[][500], int n);
void numerical_sort(int arr[],int);

//handling numerical sorts
void read_num_file_output(char *file_path, char *file_mode);
void num_bubble_sort();
void num_sort_order(int rev);
void suppress_repetition_int();
void ignore_blank_start();
void read_file_output(char *file_path,char *file_mode);
void bubble_sort();
void sort_order(int rev);
void suppress_repetition();

//-b ignore blank //-r reverse srting // -o output file // -n numerical sort -u suppress repeated keys
int main(int args,char **argv)
{
	int size = args;
	char *path= "./out.txt",*in_path="./alo.txt";
	int blank = 0;
	int reverse = 0;
	int suppress=0;
	int numerical = 0;
	int sort_algo = 0;
	char *alg = "1";
	//Writing_File = fopen("./out.txt","w+");
	//printf("%d",size);
	if (size>=2){
		for(j=1; j<size;j++){
			if (strcmp(argv[j],"-o")==0){
				path = *(argv+(1+j));
				j++;
			}
			if (strcmp(argv[j],"-i")==0){
				in_path = *(argv+(j+1));
				j++;
			}
			if(strcmp(argv[j],"-r")==0){
				reverse=1;
			}
			if(strcmp(argv[j],"-b")==0){
				blank=1;
			}
			if(strcmp(argv[j],"-u")==0){
				suppress=1;
			}
			if(strcmp(argv[j],"-n")==0){
				numerical=1;
			}
			if(strcmp(argv[j],"-s")==0){
				sort_algo=1;
				alg = argv[j+1];
				//printf("%s\n",alg);
				j++;
			}
			if(strcmp(argv[j],"-h")==0){
				printf("HELP MENU\n \t-b ignore blank \n\t-r reverse srting\n\t-o output file \n\t-n numerical sort \n\t-u suppress repeated keys\n\t-s sort algorithm 1(quick) 2(selection) else(bubble) \n\t-i input file");
				exit(0);
			}
		}
	}
	Writing_File = fopen(path,"w+");
	if(numerical==0)
	{
		read_file_output(in_path,"r");
		if(blank==1) ignore_blank_start();
		if(suppress==1) suppress_repetition();
		if(strcmp(alg,"1")==0){
			quickSortMain();
		}else if(strcmp(alg,"2")==0){
			selectionSort(nameAll,tot);
		}
		else{
			bubble_sort();
		}
		if(reverse==1) sort_order(3);
		else sort_order(0);
	}else{
		read_num_file_output(in_path,"r");
		if(suppress==1) suppress_repetition_int();
		num_bubble_sort();
		if(reverse==1)num_sort_order(2);
		else num_sort_order(0);
		
	}
	fclose(Writing_File);
	return 0;
}
void read_num_file_output(char *file_path,char *file_mode){
	Reading_File = fopen(file_path,file_mode);
	while(fscanf(Reading_File,"%d",&numOne)==1){
		//status = fgets(nameOne,255/*sizeof(Reading_File)*/,Reading_File);
		for_numeric[tot]=numOne;
		tot++;
	}
	fclose(Reading_File);
}
void read_file_output(char *file_path,char *file_mode){
	Reading_File = fopen(file_path,file_mode);
	while(fgets(nameOne,500/*sizeof(Reading_File)*/,Reading_File)!=NULL){
		//status = fgets(nameOne,255/*sizeof(Reading_File)*/,Reading_File);
		if (tot>=0){
			if (nameOne!="\0"){
				strcpy(nameAll[tot],nameOne);
				tot++;
			}else{
				if(tot>0){
					tot--;
				}
			}
		}else{
			tot++;
		}
	}
	fclose(Reading_File);
}

// BUBBLE SORT
void bubble_sort()
{
	for(i=0; i<tot; i++)
	{
		for(j=1; j<tot; j++)
		{
			if(strcmp(nameAll[j-1], nameAll[j])>0)
			{
				strcpy(nameOne, nameAll[j-1]);
				strcpy(nameAll[j-1], nameAll[j]);
				strcpy(nameAll[j], nameOne);
			}
		}
	}
}
void num_bubble_sort()
{
	for(i=0; i<tot; i++)
	{
		for(j=1; j<tot; j++)
		{
			if(for_numeric[j-1]> for_numeric[j])
			{
				numOne = for_numeric[j-1];
				for_numeric[j-1] = for_numeric[j];
				for_numeric[j] = numOne;
			}
		}
	}
}
//Selection sort
void selectionSort(char arr[][500], int n)
{
	int min_index;
	
	
	char minstring[500];
	for (i = 0; i < n-1; i++)
	{
		
		min_index = i;
		strcpy(minstring, arr[i]);
		for (j = i+1; j < n; j++)
		{
			
			if (strcmp(minstring, arr[j]) > 0)
			{
				
				strcpy(minstring, arr[j]);
				min_index = j;
			}
		}
		
		// Swap the found minimum element with the first element
		if (min_index != i)
		{
			char temp[500];
			strcpy(temp, arr[i]); 
			strcpy(arr[i], arr[min_index]);
			strcpy(arr[min_index], temp);
		}
	}
}
// quicksort algo
void quickSortMain()
{	
	quickSort(0, tot-1);
}
void quickSort(int left, int right)

{
	int i, j;
	char *x;
	char temp[500];
	
	i = left;
	j = right;
	x = nameAll[(left+right)/2];
	
	do {
		while((strcmp(nameAll[i],x) < 0) && (i < right)) {
			i++;
		}
		while((strcmp(nameAll[j],x) > 0) && (j > left)) {
			j--;
		}
		if(i <= j) {
			//swapping
			strcpy(temp, nameAll[i]);
			strcpy(nameAll[i], nameAll[j]);
			strcpy(nameAll[j], temp);
			i++;
			j--;
		}
	} while(i <= j);
	
	if(left < j) {
		quickSort(left, j);
	}
	if(i < right) {
		quickSort(i, right);
	}
}
// sorting order
void num_sort_order(int rev){
	if (rev==0){
		for(i=0; i<tot; i++){
			numOne=for_numeric[i];
			if(for_numeric[i]=='\0'|| for_numeric[i]=='\t'){
				continue;
			}
			else{
				printf("%d\n",for_numeric[i]);
				fprintf(Writing_File,"%d\n",for_numeric[i]);
			}
		}
	}
	else{
		for(i=tot; i>=0; i--){
			numOne=for_numeric[i];
			if(for_numeric[i]=='\0'|| for_numeric[i]=='\t'){
				continue;
			}
			else{
				printf("%d\n",for_numeric[i]);
				fprintf(Writing_File,"%d",for_numeric[i]);
			}
		}
		
	}
}
void sort_order(int rev){
	if (rev==0){
		for(i=0; i<tot; i++){
			strcpy(nameOne,nameAll[i]);
			if(strcmp(nameOne,"")==0 || *(nameOne+1) == '\0'){
				continue;
			}
			else{
				printf("%s\n",nameAll[i]);
				fprintf(Writing_File,"%s",nameAll[i]);
			}
		}
	}
	else{
		for(i=tot; i>=0; i--){
			strcpy(nameOne, nameAll[i]);
			if(strcmp(nameOne,"")==0 || *(nameOne+1) == '\0'){
				continue;
			}
			else{
				printf("%s\n",nameAll[i]);
				fprintf(Writing_File,"%s",nameAll[i]);
			}
		}
		
	}
}
void suppress_repetition(){
	int count = 0;
	for(j=0;j<tot;j++){
		for(i=j+1; i<tot; i++){
			strcpy(nameOne, nameAll[i]);
			if (strcmp(nameAll[j],nameOne)==0){
				strcpy(nameAll[i],"");
				count++;
			}
		}
	}
}
void suppress_repetition_int(){
	int count = 0;
	for(j=0;j<tot;j++){
		for(i=j+1; i<tot; i++){
			numOne = for_numeric[i];
			if (numOne==for_numeric[i]){
				for_numeric[i] = '\0';
				count++;
			}
		}
	}
}
void ignore_blank_start(){
	for (j=0;j<tot;j++){
		if(nameAll[j][0]=='\t' || nameAll[j][0]=='\n' || nameAll[j][0]=='\0'){
			*nameAll[j]=(char) *"";
		}
	}
}
