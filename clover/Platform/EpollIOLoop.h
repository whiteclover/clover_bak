#ifndef __EPOLLIOLOOP__
#define __EPOLLIOLOOP__

#include "../IOLoop.h"
#include <sys/epoll.h>

class EPollIOLoop: public IOLoop {

    public:
        EPollIOLoop();
        virtual ~EPollIOLoop();

        virtual int GgetFdLimits() const;
        virtual int GetFd() const;
        virtual int Register(int fd, int events);
        virtual int Unregister(int fd, int events);
        virtual int Modify(int fd, int events);
        virtual int Poll(int timeout_msecs);

        virtual bool IsFull() const = 0;
        virtual bool IsEmpty() const = 0;

    private:
        int                    _ep_fd;
        struct epoll_event    *_ep_events;
        int                    _ep_nrevents;
        int                   *_epoll_fd2idx;

};

#endif //__EPOLLIOLOOP__