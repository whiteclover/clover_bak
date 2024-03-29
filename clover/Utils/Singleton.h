#ifndef __SINGLETON_H__
#define __SINGLETON_H__

class Singleton
{
    public:
        static Singleton& Instance()
        {
            static Singleton    instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }
    private:
        Singleton() {};  // Constructor? (the {} brackets) are needed here.
        // Dont forget to declare these two. You want to make sure they
        // are unaccessable otherwise you may accidently get copies of
        // your singleton appearing.
        Singleton(Singleton const&);              // Don't Implement
        void operator=(Singleton const&); // Don't implement
};


#endif