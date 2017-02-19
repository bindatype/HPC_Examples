from mpi4py import MPI

comm = MPI.COMM_WORLD  
size = comm.Get_size() 
rank = comm.Get_rank()  
stat = MPI.Status()

message = rank

message = comm.reduce(message, op=MPI.SUM,root=0)

print rank, message
