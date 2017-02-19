from mpi4py import MPI

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
stat = MPI.Status()


message = rank**2
print "Before Gather ",rank, message

message = comm.gather(message, root=0)

comm.barrier()
if rank == 0:
	print "After Gather ",rank,message
