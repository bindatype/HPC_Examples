
from mpi4py import MPI

comm = MPI.COMM_WORLD  
size = comm.Get_size() 
rank = comm.Get_rank()  
stat = MPI.Status()

if rank == 0:
   fp = open("/groups/dats6402_10/maclach/python/gettysburg_address.txt", "r")
   message = fp.read()
else:
   message = None
message = comm.bcast(message, root=0)
print rank, message
