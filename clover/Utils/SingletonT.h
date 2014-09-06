#ifndef __SINGLETONT__
#define __SINGLETONT_H__
#include <stddef.h>  // defines NULL

template <class T>
class SingletonT
{
public:
  static T* Instance() {
      if(!_instacne) _instacne = new T;
      assert(_instacne != NULL);
      return _instacne;
  }
protected:
  SingletonT();
  ~SingletonT();
private:
  SingletonT(SingletonT const&);
  SingletonT& operator=(SingletonT const&);
  static T* _instacne;
};

template <class T> T* SingletonT<T>::_instacne=NULL;


#endif
