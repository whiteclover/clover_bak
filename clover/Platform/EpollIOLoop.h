#ifndef __EPOLLIOLOOP_H__
#define __EPOLLIOLOOP_H__

#include "IOLoop.h"
#include <sys/epoll.h>

class EPollIOLoop: public IOLoop {

    public:
        EPollIOLoop();
        virtual ~EPollIOLoop();

        virtual int GetFdLimits() const;
        virtual int GetFd() const;
        virtual int Register(int fd, int events);
        virtual int Unregister(int fd, int events);
        virtual int Modify(int fd, int events);
        virtual int Poll(int timeout_msecs);
        
    private:
        int                    _ep_fd;
        struct epoll_event    *_ep_events;
        int                    _ep_nrevents;
        int                   *_epoll_fd2idx;

};

#endif //__EPOLLIOLOOP__