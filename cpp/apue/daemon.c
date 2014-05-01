#include <apue.h>
#include <syslog.h>
#include <sys/resource.h>

void daemonize(const char* cmd)
{
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rl;
	struct sigaction sa;

	//Clear fle createion mask
	umask(0);
	//Get maxium number of file description
	if(getrlimit(RLIMIT_NOFILE, &r1) < 0)
		err_quit("%s: can not get file limit", cmd);
	//Become a session leader to lose controlling TTY
	if((pid = fork()) < 0)
		err_quit("%s: cannot fork", cmd);
	else if(pid != 0)
		exit(0);
	setsid();
	//Ensure future opens wont allocate controlling TTYs
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGHUP, &sa, NULL) < 0)
		err_quit("%s: cannot ignore SIGHUP");
	if((pid = fork()) < 0)
		err_quit("%s: cannot fork", cmd);
	else if(pid != 0)
		exit(0);

	//Change the current working directory to the root
	if(chdir("/") < 0)
		err_quit("%s: canonot change directory to /");
	//Close all open file descriptors
	if(r1.rlim_max == RLIM_INFINITY)
		r1.rlim_max = 1024;
	for(i = 0; i < r1.rlim_max; i++)
		close(i);

	//Attach file descriptors 0, 1, 2 to /dev/null
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);
	//Initialize the log file
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if(fd0 != 0 || fd1 != 1 || fd2 != 2)
	{
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
		exit(1);
	}
}
