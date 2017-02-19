from mpi4py import MPI

comm = MPI.COMM_WORLD  
size = comm.Get_size() 
rank = comm.Get_rank()  
stat = MPI.Status()

if rank == 0:
   message = [(x+1)**3 for x in range(size)]
else:
   message = None
message = comm.scatter(message, root=0)
print rank, message
