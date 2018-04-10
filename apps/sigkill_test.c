#include <stdio.h>
#include <stdlib.h> 
#include <signal.h> // sigaction(), sig*()
#include <unistd.h>

void handle_signal(int signal);

/* Usage example
 * 
 * First, compile and run this program:
 *     $ gcc signal.c
 *     $ ./a.out
 * 
 * It will print out its pid. Use it from another terminal to send signals
 *     $ kill -HUP <pid>
 *     $ kill -USR1 <pid>
 *     $ kill -ALRM <pid>
 *
 * Exit the process with ^C ( = SIGINT) or SIGKILL, SIGTERM
 */
int main() {
    struct sigaction sa;

    // Print pid, so that we can send signals from other shells
    printf("My pid is: %d\n", getpid());

    // Setup the sighub handler
    sa.sa_handler = &handle_signal;

    // Restart the system call, if at all possible
    sa.sa_flags = SA_RESTART;

    // Block every signal during the handler
    sigfillset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error: cannot handle SIGINT"); // Should not happen
    }

    for (;;) {
        printf("Hello World\n"); 
        sleep(1);
    }
}

void handle_signal(int signal) {
    // Find out which signal we're handling
    switch (signal) {
        case SIGINT:
            printf("Caught SIGINT, exiting now\n");
            exit(0);
        default:
            fprintf(stderr, "Caught wrong signal: %d\n", signal);
            return;
    }
}
