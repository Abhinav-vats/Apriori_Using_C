#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

static int csgo=0;   // 
static int counter=0;
static int ctr=0;
char **main_array;
int m=0;
 struct sb1            // structure to store charaters of string and flag
 {
 	char *arr1;						//array to store element of subset
 	int flg;							//flag to indicate occurence of element 
 };
 struct sb2			  //structure to store subset and its attributes
 {
 	struct sb1 *arr2;					// array to store different subset of sb1 structure with flag
 	int sbstcntr;						// flag to count no of times a particular subset occured
	 int ln;							//count the of subset
 };
 
 	
 	struct sb2 p1[1000];				//declare an array of structure sb2
 	



void printD(char **arr,int n)				// 	distinct element eleminating function
{	 int i,j;
    for(i=0;i<n;i++)
    {
        int flag=1;
        for(j=i+1;j<n;j++)
            if(strcmp(arr[i],arr[j])==0)
                flag=0;
        for(j=0;j<counter;j++)
        {
            if(strcmp(arr[i],main_array[j])==0)
                 flag=0;
        }
        if(flag==1)
            strcpy(main_array[counter++],arr[i]);
    }

}
void addDistinct(char **arr,int n)           // function to add distinct item in main_array array
{	int i,j;
      for(i=0;i<n;i++)
      {
        int flag=1;
        for(j=i+1;j<n;j++)
            if(strcmp(arr[i],arr[j])==0)      //if element is present in both i and j  flag will become 0
                flag=0;
        if(flag==1)
            strcpy(main_array[counter++],arr[i]);   //if flag is 1 copy element  to main_array array

    }
}

void sortString(char **items, int len)             // sort using bubble sort
{
	int i,j;		//declare integer variable
	 char temp[30];		//declare character array
    for(i=0;i<len;i++)
    {
        for(j=0;j<len-1-i;j++)
        {
            if(strcmp(items[j],items[j+1])>0)
            {
               
                strcpy(temp,items[j]);				//copy string of item to temp variable
                strcpy(items[j],items[j+1]);		// copy string of item to previous index of item
                strcpy(items[j+1],temp);			// copy string of temp to j+1 index of item
            }
        }
    }
}
void print_items(char **items, int len, FILE *fl)   // function to print itemsets in txt file
{
	int i;
   sortString(items,len);    // call sortstring function
   if(ctr==0)
   {
   	addDistinct(items,len);   // call addDistinct() function
   	ctr++;
   }
   else
   {
   	 printD(items,len);		//call printD() function
   }
   
    for(i=0;i<len;i++)
    {
      // printf("%s,",items[i]);
         fprintf(fl, "%s,",items[i]);    //print itemsets in file indicated by f1
    }
     fputc('\n',fl);  //print next line indicator in it too
       
}

void subset(char **arr, char **data, int start, int end, int index, int k)   // function to create subsets
{
    int j, i;
    if (index == k)
	{
	    for (j = 0; j < k; j++)
		{
	       	p1[m].arr2[j].arr1=data[j]; 						// if index equals k copy value of data into arr1 of arr2 of p1 array
			p1[m].ln++;	   											// increment value of lenght of that array
		}
	    m++;												// increment m as it keeps record of no. of subsets created
	
	    return;
	}
	for (i = start; i <= end && end - i + 1 >= k - index; i++)
	{
		data[index]=arr[i];
	    subset(arr, data, i+1, end, index+1, k);				// recursive function subset if index value not equal k value
	}
	  
    
}
//  End of subset()  

void printsubset(char **arr, int n, int r)             //function to redirect to subset function with a 2D array
{
    char **data;										// declare pointer 2D  array data
    data=(char **)malloc(20*sizeof(char *));			// allocate 1st dimension memory it data
    int i;
   
    for(i=0;i<100;i++)
    {
        data[i]=(char*)malloc(20*sizeof(char *));			// allocate 2nd dimension memory it data
    }

    subset(arr, data, 0, n - 1, 0, r);					//call subset() function
}


void cmpr_to_sbst(char **items, int len)				//compare subsets to each element of array
{
	int i,j,k;
//	printf("\ntest");
	
		for(j=0;j<m;j++)
		{
			for(k=0;k<p1[j].ln;k++)
			{
				p1[j].arr2[k].flg=0; 				// allot 0 value to each flag
			}
			
		}
	
	for(i=0;i<m;i++)
	{
		for(j=0;j<p1[i].ln;j++)
		{
			for(k=0;k<len;k++)
			{
				if(strcmp(items[k],p1[i].arr2[j].arr1)==0)				
						p1[i].arr2[j].flg=1;						//if itemsets array have element of subset array set flag value for that element as 1
			}
			
		}
	}
	
	for(j=0;j<m;j++)
		{
			for(k=0;k<p1[j].ln;k++)
			{
				if(p1[j].arr2[k].flg==0)
				{
					goto l1;						//if any of the flag value of that subset is 0 jump to l1 label
				}
			}
			p1[j].sbstcntr++;						// iff all the flag value of the elements of that subset is 1 then only increment the subset-counter sbstcntr 
				l1: continue;
			
		}
}


void largestsbst()								// print largest occurring subset
{
	int i,j,largest;
	largest= p1[0].sbstcntr;					// assign initial arrays elements  sbstcntr value to largest 
		for(i=1;i<m;i++)
		{
			if(largest<p1[i].sbstcntr)				
				largest=p1[i].sbstcntr;				// if any of the sbstcntr value is greater then largest assign it to largest
				
		}
		
			for(i=0;i<m;i++)
			{
				printf("\n%d\t",p1[i].sbstcntr);				// print the subset-counter value in case you want to know
				for(j=0;j<p1[i].ln;j++)
				{
					printf("%s\t",p1[i].arr2[j].arr1);			// print the corresponding subset element
				}
			}
			printf("\n\n");
		
				
		for(i=0;i<m;i++)
		{
			if((largest)==p1[i].sbstcntr)
			{
				for(j=0;j<p1[i].ln;j++)
				{
					printf("%s\t",p1[i].arr2[j].arr1);				// print the subset's elements with largest no of occurrence
				}
			printf("is subset with largest occurrence value = %d\n",largest ); 			//print the value of largest
			}
		}
}


int main()					
{
	
    int i=0, j=0, len[5];								//declaration and initialisation  of integer type variable and arrays
    
    char ch , file_name[25], **itm;  //declaration of character type variable and arrays
    
    itm=(char **)malloc(100*sizeof(char *));  //memory allocation of itm array
    
    for(i=0;i<100;i++)
    {
        itm[i]=(char*)malloc(100*sizeof(char ));    //   memory allocation of 2nd dimension itm array
    }
    
	main_array=(char **)malloc(100*sizeof( char *));    // //memory allocation of main_array array
 	for(i=0;i<100;i++)
	{
        main_array[i]=(char*)malloc(100*sizeof(char ));      //   memory allocation of 2nd dimension itm array
    }
	
    FILE *fp, *fptr;                                         //  file pointer  declaration
    printf("Enter name of file you wish to see \n");
    gets(file_name);										// input file name with extention

    fptr=fopen("item_list.txt","w+");						//Open a txt file in read and write mode in one of the pointer
    fp=fopen(file_name,"rt");						//Open the  txt file whose name is entered previously in console in read and write mode in one of the pointer
    if(fp==NULL)								
    {
        perror("Error while opening  the file ");		// error print if file doesnt exist 
        exit(EXIT_FAILURE);
    }
    int c=0;
    //printf("Sorted Grocery list is \n");   
    do{
        i=0;
        j=0;
        
       while((ch=fgetc(fp))!=',');
        while((ch=fgetc(fp))!=',');    // to replace unwanted content and commas

        while((ch=fgetc(fp))!='\n')
        {
            if(ch==EOF)               // if End of file comes in ch then break the inner loop
                break;
            if(ch!=','&&ch!='\n')			// store character by character untill comma or next line indication comes
            {
                itm[i][j]=ch;
                j++;
            }
            else                                           //if comma or next line indicator come 
            {
                itm[i][j]='\0';                  //initialize null to  that index
                j=0; 								//update j to 0
                i++;													//increment i by 1
            }
        }
        itm[i][j]='\0';										// initialize null to  that index as due break statement else part cannot be executed in the last
        print_items(itm,i+1, fptr);						// call print_items function
 

    }while((ch=fgetc(fp))!=EOF);									//end of do-while loop
    
     printf("\n\nList of distinct items:-\n");
     sortString(main_array, counter);					//sorted distinct items array
     for(i=0;i<counter;i++)
        printf("\n %s",main_array[i]);				//print distinct items
    printf("\n\nDistinct Elements are %d\n",counter);				//print no of distinct item
    
 
 	
 	for(i=0;i<1000;i++)
 	{
 	
 		p1[i].arr2=(struct sb1 *)malloc(5*sizeof(struct sb1 ));				//memory allocation to arr2 of p1
 		p1[i].ln=0;																							
 		for(j=0;j<5;j++)
 			{
 				p1[i].arr2[j].arr1=(char *)malloc(15*sizeof(char));			//memory allocation to arr1 of arr2 of p1
 
			 }
	}
 
    
    int w;
  
     for(w=2;w<=3;w++)
	 {
        printsubset(main_array, counter, w);					// print subset of 2 and 3 element
     }                                           //

    for(i=0;i<m;i++)
	{
																//   	for(j=0;j<p1[i].ln;j++)
		p1[i].sbstcntr=0;										//		{
		csgo++;	
	}															//			if(p1[i].arr2[j].arr1!='\0')
																//    		printf("%s\t",p1[i].arr2[j].arr1);
																//   		 			
																//	      
																//	    }    		
	
    printf("\ntotal subset=%d",csgo);			// print no of total subset created
   // int k=0;
    FILE *fj;
    fj=fopen(file_name,"rt");    //open file in read mode
       
    do{
        i=0;
        j=0;
        
       while((ch=fgetc(fj))!=',');
        while((ch=fgetc(fj))!=',');		 // to replace unwanted content and commas

        while((ch=fgetc(fj))!='\n')
        {
            if(ch==EOF)
                break;							// if End of file comes in ch then break the inner loop
            if(ch!=','&&ch!='\n')
            {
                itm[i][j]=ch;						// store character by character untill comma or next line indication comes
                j++;
            }
            else										//if comma or next line indicator come
            {
                itm[i][j]='\0';			   //initialize null to  that index
                j=0; 				//update j to 0
                i++;										//increment i by 1
            }
        }
        itm[i][j]='\0';										// initialize null to  that index as due break statement else part cannot be executed in the last
        cmpr_to_sbst(itm, i+1);				//call cmpr_to_sbst() function
        
    }while((ch=fgetc(fj))!=EOF);				//while statement with condition to run loop untill End Of File comes
        
    printf("\n");
    printf("\n");
    
    largestsbst();   					// call largestsbst() function

    fclose(fptr);
    fclose(fp);
    fclose(fj);					// close all the file used 
	return 0;
}
