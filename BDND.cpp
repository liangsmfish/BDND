/* implementation of "A Switching Median Filter With Boundary Discriminative Noise Detection 
					  for Extremely Corrupted Images(BDND)"	  
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
using namespace std;

void quicksort(int arr[], int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
 
      /* partition */
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };
 
      /* recursion */
      if (left < j)
            quicksort(arr, left, j);
      if (i < right)
            quicksort(arr, i, right);
}

void swap(int*  a, int*  b)
{
    int temp = * a;
    * a =*  b;
    * b = temp;
    
}

int BDND(int input[], int size)
{
	int vo [size], vo_index = 0;		
	int is_corrupted = 1;
	int is_all_0=0;
	
	for (int i=0; i<size; i++)
	{
		vo[vo_index] = input[i];	
		vo_index++;	
	}
	
	for (int i= 0;i<size;i++)
	{	
		vo[i]!=vo[i+1];
		is_all_0=1;		
	}
	
	// all the same -> "uncorrupted"
	if (is_all_0==0)
	{
		cout<<"Sucess!! The med "<<vo[12]<<" is uncorrupted" <<endl;
		is_corrupted = 0;		
		return is_corrupted	;	
	}	
	
	else
	{		
		int ogi_med = vo[size/2];		
		cout<<"center pixel = "<<ogi_med<<endl;
		
		// create sorted vo
   		quicksort(vo, 0, size-1);   		
    	cout<<"\nvo : ";    
    	for (int a = 0; a < size; a++)    	
    	{    	
        	cout<<vo[a]<<", ";        
    	}
       
        // find med_num
		int med = vo[size/2];  
    	cout<<"\nmed_num”µ”µ = "<<med<<endl;
    
    	int vd[size], vd_index;
    	
    	cout<<"\nvd : ";
    	//step2 create unsorted vd
    	for (int i = 0; i <size ; i++)
    	{    	                       
    		vd_index = i;
    		vd[vd_index]= vo[i+1]-vo[i];    	
    		cout<<vd[vd_index]<<", ";
    		vd_index++;    	
    	}
    
    	int vdmax_0_med= 0, vdmax_med_255 = 0;
    
  		int vd_copy[size] ;  	
  		for (int i=0;i<size;i++)
  		{
  			vd_copy[i] = vd[i];  		
  		} 	
  	
		
		cout<<""<<endl;
		int vd_0_to_med[size/2], vd_med_to_255[size/2];	
	
		for (int i=0;i<size/2;i++)
		{
			vd_0_to_med[i] = vd[i];
			vd_med_to_255[i] = vd[i+size/2];					
		}
		
		for (int i=0;i<size/2;i++)
		{		
			cout<<vd_0_to_med[i]<<", ";			
		}
		
		for (int i=0;i<size/2;i++)
		{		
			cout<<vd_med_to_255[i]<<", ";			
		}
	
	    // find max 0~med & max med~255
		quicksort(vd_0_to_med, 0, size/2-1);
		quicksort(vd_med_to_255, 0, size/2-1);		
		
		vdmax_0_med = vd_0_to_med[size/2-1];	   
    	cout<<"\nvdmax_0_to_med is "<<vdmax_0_med<<endl;   
		vdmax_med_255 = vd_med_to_255[size/2-1];	
    	cout<<"vdmax_med_to_255 is "<<vdmax_med_255<<endl;  
      
    	int b1_index,b2_index;
   	 	for (int n1 = 0; n1 <size ; n1++)
    	{
    		if (vd_copy[n1] == vdmax_0_med)
    		{    	
   				b1_index=n1;
    		}	    	
    	}
    
    
    	for (int n2 = 0; n2<size ; n2++)
    	{    
    		if (vd_copy[n2] == vdmax_med_255)
    		{    	
    			b2_index=n2;		   
			}    
		}	
		
  		int b1= vo[b1_index], b2 = vo[b2_index];
  		if (b1>b2)  			
  			swap(&b1, &b2);  		
    	  	  	
  		cout<<"b1 = "<<b1<<" ,"<<"b2 = "<<b2<<endl;
  		
  		int t1=0, t2=0, t3=0;;
    	int cluster_low [size] , cluster_med[size], cluster_high[size];
    	cout<<"\ncluster_low is :";
		for (int n = 0 ; n<size; n++)
		{
			if (vo[n] <= b1)
			{		
				cluster_low [t1]= vo[n];			
				cout<<cluster_low[t1]<<" ,";
				t1++;
			}			
		}
     
    	cout<<"\ncluster_med is :";
    
    
    	for (int n = 0 ; n<size; n++)
		{
			if (vo[n] > b1 && vo[n] <= b2)
			{
				cluster_med [t2]= vo[n];			
				cout<<cluster_med[t2]<<" ,";
				t2++;
			}
		}
    
    	cout<<"\ncluster_high is :";
    
    	for (int n = 0 ; n<size; n++)
		{
			if (vo[n] > b2)
			{			
				cluster_high[t3]= vo[n];			
				cout<<cluster_high[t3]<<" ,";
				t3++;
			}
		}
    
    	int med_in_cluster_med = 0 ;
    
    	for (int i= 0; i<size; i++)
    	{   		
    		if (ogi_med==cluster_med[i])    		  		
    			med_in_cluster_med= 1;    		   	
    	}
    
    	if (med_in_cluster_med == 1)
    	{    	
    		cout<<""<<endl;
    		cout<<"Sucess!! The med "<<ogi_med<<" is uncorrupted" <<endl;
			is_corrupted = 0;
			return is_corrupted;    	   	
    	}    	
    	else 
		{    	
    		cout<<""<<endl;
    		cout<<"Unsucess!! The med "<<ogi_med<<" is need second stage check" <<endl;			
			return is_corrupted;    	   	
    	} 		
	}
}


int main(void)
{
	//  test input
	//	int W [5][5] = { 255,255,47,255,39,50,255,255,0,0,0,0,202,224,205,62,255,0,0,255,255,72,81,0,179};
	//	int W [5][5] = { 123,123,123,132,123 ,123,123,124,123,123,124,124,255,124,123, 123,123,124,123,124 ,114,123,114,124,124};
	//	int W [5][5] = { 183,182,193,183,193,193,183,183,194,183,193,183,193,193,182,194,183,193,183,194,183,183,183,193,182};

	//  int W [5][5] = { 255,255,255,255,255,   255,250,250,250,255,   255,250,250,250,255,  255,250,250,250,255, 255,255,255,255,255} ;
	//	int W [5][5] = { 73,45,27,22,18,58,39,22,18,17,39,27,22,18,23,27,22,17,23,27,22,18,22,28,33};
	 
	int W[25] = {	255 , 255 , 47  , 255 , 39,
					50  , 255 , 255 , 0   , 0,
					0   , 0   , 202 , 224 , 205,
					62  , 255 , 0   , 0   , 255,
					255 , 72  , 81  , 0   , 179 } ;
	int W_5X5[5][5] = {	255 , 255 , 47  , 255 , 39,
					50  , 255 , 255 , 0   , 0,
					0   , 0   , 202 , 224 , 205,
					62  , 255 , 0   , 0   , 255,
					255 , 72  , 81  , 0   , 179 } ;
	
	int W_3x3[9],W_3x3_index=0  ;
	for (int j =1 ;j<4;j++)
		for (int i=1;i<4;i++)
		{
			W_3x3[W_3x3_index]= W_5X5[i][j];
			cout<<W_3x3[W_3x3_index]<<", ";
			W_3x3_index++;
		}
		
    int iscorrupted = BDND(W,25);
    
    if (iscorrupted == 1)
    	BDND(W_3x3,9);
	system("pause");	
	return 0;
}

