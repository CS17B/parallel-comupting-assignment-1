#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>

int main(int argc,char **argv)
{
  int N=4;
  struct timeval start, stop;
  FILE *fptr;
  int np;
  int rank;
  int i,j,k,l,m;
  int s=0,d=3;
  int source,dest;
  int length=1;
  int rows;
  int offset=0;
  MPI_Status status;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);
 
  int A[N][N];
  int Ak[N][N];
 
   rows=N/np;
   if((fptr= fopen("matrix.txt","r")) == NULL)
   {
   	printf("Eror ! opening file");
   	exit(1);
   }
   if(rank == 0)
   {
     srand(time(NULL));
   for(i=0;i<rows;i++)
        {
           for( j=0;j<N;j++)
           {
             fscanf(fptr,"%d",&A[i][j]);
           }
         printf("\n");
        }
        
        printf("\n");
       
       for(i=0;i<rows;i++)
        {
           for( j=0;j<N;j++)
           {
             Ak[i][j]=A[i][j];
           }
         
        }
       
    for(i=0;i<rows;i++)
        {
           for(j=0;j<N;j++)
           {
            printf("%d ",Ak[i][j]);
           }
         printf("\n");
        }
   
   }

    if(rank == 1)
    {
      srand(time(NULL));
      fseek( fptr, 15, SEEK_SET );
   for(i=rows;i<N;i++)
        {
           for( j=0;j<N;j++)
           {
             fscanf(fptr,"%d",&A[i][j]);
           }
           printf("\n");
         
        }
        printf("\n");
       
        for(i=rows;i<N;i++)
        {
           for( j=0;j<N;j++)
           {
             Ak[i][j]=A[i][j];
           }
         
        }
       
    for(i=rows;i<N;i++)
        {
           for(j=0;j<N;j++)
           {
            printf("%d ",Ak[i][j]);
           }
         printf("\n");
        }
    
    
    }
   
  
    fclose(fptr);
    if(rank == 0)
    {
    
        int C[rows][N];
        int arr[N];
           
           
    while(Ak[s][d] == 0 && length != N)
    {
     for(l=0;l<N;l++)
     {
        for(i=0;i<N;i++)
        {
            arr[i]=0;
        }
         j=l;
         for(i=0;i<rows;i++)
            {
                arr[i] =Ak[i][j];        
            }
            printf("\n");
            
             dest=1;
            MPI_Send(&rows,1,MPI_INT,dest,2,MPI_COMM_WORLD);
            MPI_Send(&arr,rows,MPI_INT,dest,2,MPI_COMM_WORLD);
           
        
           
        offset =0;
        
         source =1;
       
         MPI_Recv(&rows,1,MPI_INT,source,1,MPI_COMM_WORLD,&status);
          MPI_Recv(&arr[rows],rows,MPI_INT,source,1,MPI_COMM_WORLD,&status);
          
         offset = offset+rows;
        printf("\n");
         
           
            k=l;
            for(i=0;i<rows;i++)
            {
              C[i][k] =0;
            for(j=0;j<N;j++)
            {
                C[i][k] = C[i][k]+A[i][j]*arr[j];
               
            }
             
            
         
            }
            
          
           
     }
     for(i=0;i<rows;i++)
            {
                for(j=0;j<N;j++)
                {
                    Ak[i][j]=C[i][j];
                    
                }
                
            }
            length=length+1;
           
    }
   

    }
   if(rank ==1)
   {
   
       int C[rows][N];
        int arr[N];
           
           
     while(length != N)
     {  
     for(m=0;m<N;m++)
     {
        for(i=0;i<N;i++)
        {
            arr[i]=0;
        }
         j=m;
         
         for(i=rows;i<N;i++)
            {
                arr[i] =Ak[i][j]; 
                
                    
            }
           
           
            dest =0;
            MPI_Send(&rows,1,MPI_INT,dest,1,MPI_COMM_WORLD);
            MPI_Send(&arr[rows],rows,MPI_INT,dest,1,MPI_COMM_WORLD);
            
        
           
        offset =0;
        
         source =0;
       
         MPI_Recv(&rows,1,MPI_INT,source,2,MPI_COMM_WORLD,&status);
          MPI_Recv(&arr,rows,MPI_INT,source,2,MPI_COMM_WORLD,&status);
          
         offset = offset+rows;
        
        
            k=m;
            for(i=rows;i<N;i++)
            {
               C[i][k]=0;
            for(j=0;j<N;j++)
            {
                C[i][k] = C[i][k]+A[i][j]*arr[j];
            }
               
            }
            
   	}
   	for(i=rows;i<N;i++)
            {
                for(j=0;j<N;j++)
                {
                    Ak[i][j]=C[i][j];
                    
                }
                
            }
   	length= length+1;
   }
   }

   
   if(rank  == 0)
   {
       if(Ak[s][d] != 0)
       {
           printf("shortest path between source and destination is :%d\n",length);
       }
       if(length == N)
       {
           printf("there is no path between source and destination");
       }
   }
   MPI_Finalize();
 
}
