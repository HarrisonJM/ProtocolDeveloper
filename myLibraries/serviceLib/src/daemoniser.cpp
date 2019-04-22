/*!
 * @brief Handles creating the daemon process in accordance with "Advanced Programming in the UNIX Environment, 3rd edition"
 *, Chapter 13
 * @author hmarcks
 * @date 14/04/19
 * @addtogroup serviceLib
 * @{
 */

#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <signal.h>
#include <sys/stat.h>
#include <zconf.h>
#include <cstdlib>
#include <csignal>

#include "serviceLib/daemoniser.h"
#include "serviceLib_exceptions.h"

namespace serviceLib
{

Daemoniser::Daemoniser()
{

}

Daemoniser::~Daemoniser()
{

}

void Daemoniser::Daemonise(const char* cmd)
{
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit r1;
    struct sigaction sa;

    /* Clear the file mask */
    umask(0);

    /* Find our resource limits */
    if(getrlimit(RLIMIT_NOFILE, &r1) < 0)
    {
        throw serviceLib_exception_getrlimit();
    }

    /* Become session leader to lose TTY */
    if((pid = fork()) < 0)
    {
        throw serviceLib_exception_pidlessthan0();
    }
    else if (pid != 0)
    {
        // Child PID is 0, so kill parent
        exit(0);
    }

    /* Sets the process groupID (session ID) */
    setsid();

    /* Handle signal actions */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if(sigaction(SIGHUP, &sa, NULL) < 0)
    {
        throw serviceLib_exception_ignoreSIGHUP();
    }

    /* Actually fork */
    if((pid = fork()) < 0)
    {
        throw serviceLib_exception_pidlessthan0();
    }
    else if (pid != 0)
    {
        exit(0);
    }

    /*
     * Change current workign directory to the root so we won't prevent
     * file systems from being unmounted
     */
    if(chdir("/") < 0)
    {
        throw serviceLib_exception_cdRootDir();
    }

    /* Close all open FDs */
    if(r1.rlim_max == RLIM_INFINITY)
    {
        r1.rlim_max = 1024;
    }

    for(i = 0; i < r1.rlim_max; ++i)
    {
        close(i);
    }

    /* Attach FD 0,1,2 to /dev/null */
    /*! @todo Attach to not /dev/null */
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    /* Initialise the log file */
    if(fd0 != 0 || fd1 != 0 || fd2 != 0 )
    {
        throw serviceLib_exception_unexpectedFD();
    }
}

} /* namespace serviceLib */
/*! @} */