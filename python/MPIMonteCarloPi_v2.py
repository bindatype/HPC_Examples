from mpi4py import MPI
import math
import random
import sys

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
stat = MPI.Status()

offset = 1.0*rank/size
width = 1.0/size
print offset,width

keep=0
n=int(sys.argv[1])
for i in range(1,n+1):
	x=width*random.random()+offset
	y=random.random()
	if math.sqrt(x*x+y*y)<=1:
		keep+=1
pi=4.0*keep/n
error = abs(pi - math.pi)
print ("pi from rank %d is approximately %.16f, error is %.16f" % (rank, pi, error))

message = comm.reduce(pi, op=MPI.SUM, root=0)
if rank ==0:
	pi = message/size
	error = abs(pi - math.pi)
	print ("Final pi from rank %d is approximately %.16f, error is %.16f" % (rank, pi, error))

