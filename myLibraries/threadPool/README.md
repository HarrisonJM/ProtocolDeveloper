#Library: threadPool

__Description__
Implements a thread pool that can be used to exactly limit how many concurrent threads can be running in the program at 
any one time.

__Gotchas__

__How to use__

After instantiation, each component that needs to spawn threads should be given a reference to the thread pool. 
The AddTaskToQueue method derives all parameters and return types at compile time. The task is then added to a queue and 
will eventually be picked up by any free threads. 


__Method__