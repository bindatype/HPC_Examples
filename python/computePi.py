#Solution adapted from http://www.mcs.anl.gov/research/projects/mpi/tutorial/mpiexmpl/src/pi/C/main.html
from mpi4py import MPI
import math
import sys

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
	
numIntervals = int(sys.argv[1])
h = 1.0 / numIntervals
sum = 0.0

for i in range(rank,numIntervals,size):
	partial = 0.0
	x = h * (i + 0.5)
	sum += 4.0 / (1.0 + x**2)

mypi = h*sum
error = abs(mypi - math.pi)
print ("pi from rank %d is approximately %.16f, error is %.16f" % (rank, mypi, error))
pi = comm.reduce(mypi, op=MPI.SUM, root=0)
	
if rank == 0:
	error = abs(pi - math.pi)
	print ("pi is approximately %.16f, error is %.16f" % (pi, error))
