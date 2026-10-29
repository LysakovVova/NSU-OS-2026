#define MAXARGS 256
#define MAXCMDS 50

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

struct command {
    char *cmdargs[MAXARGS];
    char cmdflag;
};

/*  cmdflag's  */
#define OUTPIP 01
#define INPIP 02

extern struct command cmds[];
extern char *infile, *outfile, *appfile;
extern char bkgrnd;

enum process_state { RUNNING, STOPPED, DONE };
typedef struct {
    int used;
    int id;

    pid_t pgid;

    int nprocesses;
    pid_t pids[MAXCMDS];
    enum process_state state[MAXCMDS];

    struct termios tmodes;
    int saved_modes;

    char name[128];
} Job;

int parseline(char *);
int promptline(char *, char *, int);

void init_shell(void);
void standart_shell_signals();
void return_terminal(void);
bool is_job_done(Job *job);
void check_zombie_processes(void);
Job *find_job(const char *arg);
bool is_job_stopped(Job *job);
void mark_job_running(Job *job);
void builtin_bg(Job *job);
void builtin_fg(Job *job);
bool special_command(int ncmds);
int add_group(pid_t pid, pid_t pgid);
void wait_foreground(Job *job);
void execute_command(int ncmds);
int redirect_file(const char *path, int flags, int target);
void launch_pipeline(int first, int last, int ncmds);
void update_process_state(Job *job, pid_t pid, int status);