#ifndef __IOLOOP_H__
#define __IOLOOP_H__

typdef enum 
{
        IOLOOP_NONE = 0x0000,
        IOLOOP_IN  = 0x0001,
        IOLOOP_OUT = 0x0002,
        IOLOOP_ERR = 0x0004
} ioloop_event_type_t;



typedef enum 
{
    ioloop_epoll,
    ioloop_kqueue,
    ioloop_port,
    ioloop_poll,
    ioloop_select,
    ioloop_UNSET
} ioloop_type_t;

class IOLoop
{

    public:     
        int nfiles;            /* Max. fds in this FD poll */
        int system_nfiles;     /* Max. fds in the system   */
        int npollfds;          /* Currently, how many FDs  */
        ioloop_type_t type;    /* IOLoop Type In (pool, epoll, kqueue...) */


        virtual int GetFdLimits() const = 0;
        virtual int GetFd() const = 0;
        virtual Register(int fd, int events)=0;
        virtual Unregister(int fd, int events)=0;
        virtual Modify(int fd, int events)=0;
        virtual Poll(int timeout_msecs)=0;

        bool IsFull() { return (npollfds <= 0);};
        bool IsEmpty() {return (npollfds > nfiles);};

};




#endif // __IOLOOP_H__

