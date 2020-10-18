# parallel-comupting-assignment-1

1)In first question taking input from the matrix.txt
description:
	if a adjacency matrix is given then it will do multiplication
to compute the shortest path.
here total adjacency matrix is kept on base processor intially then from
there it is send to remaning processors.
when multiplying we parallizing the code.by dividing the rows depending
on no of processors.so that each processor will have a part one matrix and
a full matrix.
computation is done on each processor then the output values ae send to base
processor so that it can check the source and destination location.if not zero
it will do the same process.

2)In second question taking input from the matrix.txt
descritpion:
	here the adjacency is divided and different parts are placed in differernt 
processors.
constraints:Only two processors i am using(rank=0 and rank=1)
Any sized matrix divded into two halves.
for getting the output first row first element i have to get remaining half column 
from rank1.and i am maintainig extra array on each processor.to store the buffer
values.so that i can refresh from every column and to do the computation on each
processor.
output is also there in two processors as parts.we will check the source and
destination loation then if it is other than zero we will stop.or we will repeat the 
process.

compiling:mpicc filename.c -0 excutablefilename
runnung:mpirun -np 2 ./excutablefilename
