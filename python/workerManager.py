from mpi4py import MPI

comm = MPI.COMM_WORLD  
size = comm.Get_size() 
rank = comm.Get_rank()  
stat = MPI.Status()

message =  "Hello world, I am  process %s of %s!" % (rank,size)

if rank == 0:
    print message
    for i in range(size - 1):
        message = comm.recv(source=MPI.ANY_SOURCE, tag=MPI.ANY_TAG, status=stat)
        print message
    
else:
    comm.send(message, dest = 0)

