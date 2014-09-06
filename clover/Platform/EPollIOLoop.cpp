
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "EPollIOLoop.h"
#include "../Utils/Logger.h"

EPollIOLoop::EPollIOLoop(int sys_fd_limit, int fd_limit):
{
    system_nfiles = sys_fd_limit //sysconf(_SC_OPEN_MAX);
    type = ioloop_epoll;
    nfiles = fd_limit;
    npollfds = 0;
    _ep_fd = -1;
    _ep_nrevents = 0;

    _ep_events = (struct epoll_event *) malloc(nfiles, sizeof(struct epoll_event));
    if (_ep_events == NULL) 
    {   CLOVER_ELOG("Malloc Failed")
        return 
    }

    _epoll_fd2idx = (int*) malloc(system_nfiles, sizeof(int));
    if (_epoll_fd2idx == NULL)
    {
        free(_ep_events);
        return;
    }

    _ep_fd = epoll_create(nfiles);
    if (_ep_fd < 0)
    {
        return 
    }

    res = fcntl(_ep_fd, F_SETFD, FD_CLOEXEC);
    if (res < 0)
    {
        return;
    }
}

EPollIOLoop::~EPollIOLoop()
{
    if (_ep_fd >= 0) 
    {
        close(_ep_fd);
    }
    free(_ep_events);
    free(_epoll_fd2idx);
}

int EPollIOLoop::Register(int fd, int events)
{
    if (isFull())
    {
        CLOVER_ELOG("EPollIOLoop is full");
        return 0;
    }

    struct epoll_event ev;
    /* Add the new descriptor
     */
    memset(&ev, 0, sizeof(struct epoll_event));
    ev.data.u64 = 0;
    ev.data.fd = fd;
    switch (events) 
    {
        case IOLOOP_IN:
            ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
            break;
        case IOLOOP_OUT:
            ev.events = EPOLLOUT | EPOLLERR | EPOLLHUP;
            break;
        default:
            ev.events = 0;
            return 0;
    }

    if (epoll_ctl (_ep_fd, EPOLL_CTL_ADD, fd, &ev) < 0) 
    {
        CLOVER_ELOG("Register Failed");
        return 0
    }

    npollfds++;
    return 1
}

int EPollIOLoop::Unregister(int fd, int events)
{
    struct epoll_event ev;

    ev.events   = 0;
    ev.data.u64 = 0;  /* <- I just wanna be sure there aren't */
    ev.data.fd  = fd; /* <- 4 bytes uninitialized */

    /* Check the fd limit
     */
    if (isEmpty())
    {
        CLOVER_ELOG("EPollIOLoop is empty");
        return 0;
    }


    if (epoll_ctl(_ep_fd, EPOLL_CTL_DEL, fd, &ev) < 0)
    {
        CLOVER_ELOG ("Unregister Failed");
        return 0;
    }

    npollfds--;
    return 1;
}


int EPollIOLoop::Modify(int fd, int events)
{
    struct epoll_event ev;

    ev.data.u64 = 0;
    ev.data.fd  = fd;

    switch (events) 
    {
        case IOLOOP_IN:
            ev.events = EPOLLIN;
            break;
        case IOLOOP_OUT:
            ev.events = EPOLLOUT;
            break;
        default:
            ev.events = 0;
            return 0;
    }

    if (epoll_ctl(fdp->ep_fd, EPOLL_CTL_MOD, fd, &ev) < 0) 
    {
        CLOVER_ELOG("Modify Failed")
        return 0;
    }
    return 1;
}


int EPollIOLoop::Poll(int timeout_msecs)
{
    _ep_nrevents = epoll_wait (_ep_fd, _ep_events, _nfiles, timeout_msecs);
    if (_ep_nrevents < 1)
    {
        return _ep_nrevents;
    }
        

    for (int i = 0; i < _ep_nrevents; ++i)
    {
        _epoll_fd2idx[fdp->ep_events[i].data.fd] = i;
    }

    return _ep_nrevents;
}




