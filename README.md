# thread-safe-counter

Developed by Woojoong Kim (20153330).<br/>
Developed in WSL2 environment.<br/>

"Upgrade list"<br/>

##1. Create semaphore.c from copy of tscounter.c<br/>
-> Understand the structure of tscounter.c<br/>
-> Be ready to make semaphore.c file using semaphore.<br/>

##2. Edit semaphore.c to lock the thread with semaphore<br/>
-> Alternate Mutex part with Semaphore.<br/>
-> Use IPC_PRIVATE to create key.<br/>
-> Create sema_lock, sema_unlock function to lock the threads more simple.<br/>

##3. Update semaphore.c and tscounter.c can use clock function to measure the execution time<br/>
-> Use <time.h> header file and clock_t variable to measure the exection time in main function.<br/>

##Result<br/>
-> I measured the execution time for semaphore.c and tscounter.c and results are as follows.<br/>
semaphore : 7.877sec<br/>
tscounter : 0.022sec<br/>
(The above result is the result of setting the count to 100000 when I execute.)<br/>

-> This result shows that semaphore takes longer to execute than mutex.<br/>
-> In my opinion, the reason why semaphore takes longer than tsconter is semaphore needs to set the sem_op value to distinguish lock version or unlock version of semaphore. Because semaphore can have much state(more than 2 state) so we needs to decide which state is lock or unlock version of semaphore.<br/>
 Also semaphore needs more values than mutex like sem_num, sem_flg, semid... and semid even needs to get additional key from semget fuction. Otherwise mutex is much simple than semaphore. It just needs pthread_mutex_t variable to lock the thread. I think these differences between semaphore and mutex make a big difference in execution time.<br/>

