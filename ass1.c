#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>

int main(int argc,char **argv)
{
  int N=8;
  struct timeval start, stop;
  int np;
  int rank;
  int i,j,k;
  int s=0,d=7;
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
  
 
  if(rank==0)
  { 
   srand(time(NULL));
   for(i=0;i<N;i++)
        {
           for( j=0;j<N;j++)
           {
             A[i][j]=rand()%2;
           }
          
        }
        
        for(i=0;i<N;i++)
        {
           for(j=0;j<N;j++)
           {
           	printf("%d ",A[i][j]);
           }
         printf("\n");
          
        
        }
        printf("\n");
        printf("\n");
        
        
 
        for(i=0;i<N;i++)
        {
           for( j=0;j<N;j++)
           {
             Ak[i][j]=A[i][j];
            
           }
          
        }
     gettimeofday(&start, 0);   
       
 while(Ak[s][d] == 0 && length != N)
 {
    offset =0;
 
    int C[rows][N];  
     
     for(k=0;k<N;k++)
     {
   for(i=0;i<rows;i++)
   {
       C[i][k]=0;
         for(j=0;j<N;j++)
         {
             C[i][k]=C[i][k]+Ak[i][j]*A[j][k];  
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

     
     offset=offset+rows;
    
     for(dest=1;dest<np;dest++)
     {
     	
         MPI_Send(&offset,1,MPI_INT,dest,1,MPI_COMM_WORLD);
         MPI_Send(&rows,1,MPI_INT,dest,1,MPI_COMM_WORLD);
         MPI_Send(&Ak[offset][0],rows*N,MPI_INT,dest,1,MPI_COMM_WORLD);
         MPI_Send(&A,N*N,MPI_INT,dest,1,MPI_COMM_WORLD);
         offset=offset+rows;
     }
     
   
     
     
     
     for(i=1;i<np;i++)
     {
         source =i;
         MPI_Recv(&offset,1,MPI_INT,source,2,MPI_COMM_WORLD,&status);
         MPI_Recv(&rows,1,MPI_INT,source,2,MPI_COMM_WORLD,&status);
         MPI_Recv(&Ak[offset][0],rows*N,MPI_INT,source,2,MPI_COMM_WORLD,&status);
     }
     
     
        
     length= length+1;
     for(i=0;i<N;i++)
        {
           for(j=0;j<N;j++)
           {
           	printf("%d ",Ak[i][j]);
           }
         printf("\n");
         
        }
     
     printf("\n");
     printf("\n");
  }
  gettimeofday(&stop, 0);
 
 }
  if(rank > 0)
  {
  while(length != N)
 {
     source =0;
     
     MPI_Recv(&offset,1,MPI_INT,source,1,MPI_COMM_WORLD,&status);
     MPI_Recv(&rows,1,MPI_INT,source,1,MPI_COMM_WORLD,&status);
     MPI_Recv(&Ak,rows*N,MPI_INT,source,1,MPI_COMM_WORLD,&status);
     MPI_Recv(&A,N*N,MPI_INT,source,1,MPI_COMM_WORLD,&status);
     
     
     int C[rows][N];
     for(k=0;k<N;k++)
     {
      for(i=0;i<rows;i++)
      {
       C[i][k]=0;
         for(j=0;j<N;j++)
         {
             C[i][k]=C[i][k]+Ak[i][j]*A[j][k];  
             
             
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
  
  
  MPI_Send(&offset,1,MPI_INT,0,2,MPI_COMM_WORLD);
  MPI_Send(&rows,1,MPI_INT,0,2,MPI_COMM_WORLD);
  MPI_Send(&Ak,rows*N,MPI_INT,0,2,MPI_COMM_WORLD);
 }
  
  }
 
  if(rank == 0)
  {
     if(Ak[s][d] != 0)
     {
        
     	printf("shortest path :%d\n",length);
     }
     else
     {
     	printf("no path between source and destination");
     }
  }

   
  fprintf(stdout,"Time = %.6f\n\n",
         (stop.tv_sec+stop.tv_usec*1e-6)-(start.tv_sec+start.tv_usec*1e-6));
 
   MPI_Finalize();

}
































