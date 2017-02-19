from mpi4py import MPI

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
stat = MPI.Status()


MESSAGE=comm.recv(source=rank-1)
comm.send(MESSAGE,dest=(rank+1)%(size)



if rank == 0:
	message = rank
else:
	message = None

