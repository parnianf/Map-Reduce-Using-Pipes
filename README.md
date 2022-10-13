# Map-Reduce-Using-Pipes

The purpose of this project is to learn how to manage processes and the communication between them by implementing a word counter using the Map-Reduce model.

**MapReduce** is a framework for processing parallelizable problems across large datasets using a large number of computers (nodes), collectively referred to as a cluster or a grid.

### System architecture
In this system, there are three types of processes:
* Main process: This process is considered the parent process of the system and its task is to create reduction and mapping processes. There is only one main process in the system. `Unnamed pipe` must be used to transfer the file name to the mapping process. Also, a reduction type process is also created in this process, which sends the final output to the main process.
* Map process: Each of the mapping processes received the name of the file on which they should perform operations. At this stage, each process counts the number of word occurrences in the corresponding file. The output of this part is a number of keys and their corresponding values, i.e. words and the number of their repetitions. Each mapping process sends its output to the reduce process using a `named pipe`.
* Reduction process: This process which is created by the main process, waits to receive the output of all mapping processes. In this step, the outputs are combined and the number of occurrences of each word among all files is calculated. Finally, this output is sent to the main process using an `unnamed pipe`.


