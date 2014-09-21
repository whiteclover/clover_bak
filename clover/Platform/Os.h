
#ifndef __OS_H__
#define __OS_H__ 

##include "../Common.h"
#include "../Utils/SingletonT.h"

class Os
{
    friend class SingletonT< Os >;

    private:
        Os() {} 
        virtual ~Os() {}

    public:
        int32 SyncAdd(volatile int32 *data, int32 value);
        int32 SyncSub(volatile int32 *data, int32 value);
};


#define sOs SingletonT< Os >

#endif