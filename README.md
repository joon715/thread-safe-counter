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

