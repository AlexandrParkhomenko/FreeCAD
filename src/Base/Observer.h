/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2002                        *   
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 *   Juergen Riegel 2002                                                   *
 ***************************************************************************/


#ifndef BASE_OBSERVER_H
#define BASE_OBSERVER_H

// Std. configurations

#include <assert.h>
#include <set>
#include <cstring>
#include <cstdio>
#include <exception>
#include "Exception.h"
#include "Console.h"

namespace Base
{

template <class MessageType> class Subject;


/** Observer class
 *  Implementation of the well known Observer Design Pattern.
 *  The observed object, which inherit FCSubject, will call all
 *  its observers in case of changes. A observer class has to 
 *  Attach itself to the observed object.
 *  @see FCSubject
 */
template <class _MessageType>
class Observer
{
public:

  /**
   * A constructor.
   * No special function so far.
   */
  Observer(){}

  /**
   * A destructor.
   * No special function so far.
   */
  virtual ~Observer(){}

  /**
   * This method need to be reimplemented from the concrete Observer
   * and get called by the observed class
   * @param rCaller a reference to the calling object
   * @param rcReason
   * \todo undocumented parameter 2
   */
  virtual void OnChange(Subject<_MessageType>& rCaller,_MessageType rcReason)=0;

  /**
   * This method need to be reimplemented from the concrete Observer
   * and get called by the observed class
   * @param rCaller a reference to the calling object
   */
  virtual void OnDestroy(Subject<_MessageType> & rCaller) {
    (void)rCaller;
  }

  /**
   * This method can be reimplemented from the concrete Observer
   * and returns the name of the observer. Needed to use the Get 
   * Method of the Subject.
   */
  virtual const char *Name(void){return 0L;}
};

/** Subject class
 *  Implementation of the well known Observer Design Pattern.
 *  The observed object, which inherit FCSubject, will call all
 *  its observers in case of changes. A observer class has to 
 *  Attach itself to the observed object.
 *  @see FCObserver
 */
template <class _MessageType>
class Subject
{
public:

  typedef  Observer<_MessageType> ObserverType;
  typedef  _MessageType             MessageType;
  typedef  Subject<_MessageType>  SubjectType;   
     
  /**
   * A constructor.
   * No special function so far.
   */
  Subject(){}

  /**
   * A destructor.
   * No special function so far.
   */
  virtual ~Subject()
  {
    if (_ObserverSet.size() > 0)
    {
      printf("Not detached all observers yet\n");
      assert(0);
    }
  }

  /** Attach an Observer
   * Attach an Observer to the list of Observers which get   
   * called when Notify is called.
   * @param ToObserv A pointer to a concrete Observer
   * @see Notify
   */
  void Attach(Observer<_MessageType> *ToObserv)
  {
#ifdef FC_DEBUG
    size_t count = _ObserverSet.size();
    //printf("Attach observer %p\n", ToObserv);
    _ObserverSet.insert(ToObserv);
    if ( _ObserverSet.size() == count )
      printf("Observer %p already attached\n", ToObserv);
#else
    _ObserverSet.insert(ToObserv);
#endif
  }

  /** Detach an Observer
   * Detach an Observer from the list of Observers which get   
   * called when Notify is called.
   * @param ToObserv A pointer to a concrete Observer
   * @see Notify
   */
  void Detach(Observer<_MessageType> *ToObserv)
  {
#ifdef FC_DEBUG
    size_t count = _ObserverSet.size();
    //printf("Detach observer %p\n", ToObserv);
    _ObserverSet.erase(ToObserv);
    if ( _ObserverSet.size() == count )
      printf("Observer %p already detached\n", ToObserv);
#else
    _ObserverSet.erase(ToObserv);
#endif
  }

  /** Notify all Observers
   * Send a message to all Observers attached to this subject.
   * The Message depends on the implementation of a concrete 
   * Oberserver and Subject.
   * @see Notify
   */
  void Notify(_MessageType rcReason)
  {
    for(typename std::set<Observer<_MessageType> * >::iterator Iter=_ObserverSet.begin();Iter!=_ObserverSet.end();++Iter)
    {
      try {
        (*Iter)->OnChange(*this,rcReason);   // send OnChange-signal
      } catch (Base::Exception &e) {
        Base::Console().Error("Unhandled Base::Exception caught when notifying observer.\n"
                              "The error message is: %s\n", e.what());
      } catch (std::exception &e) {
        Base::Console().Error("Unhandled std::exception caught when notifying observer\n"
                              "The error message is: %s\n", e.what());
      } catch (...) {
        Base::Console().Error("Unhandled unknown exception caught in when notifying observer.\n");
      }
    }
  }

  /** Get an Observer by name
   * Get a observer by name if the observer reimplements the Name() mthode.
   * @see Observer
   */
  Observer<_MessageType> * Get(const char *Name)
  {
    const char* OName;
    for(typename std::set<Observer<_MessageType> * >::iterator Iter=_ObserverSet.begin();Iter!=_ObserverSet.end();++Iter)
    {
      OName = (*Iter)->Name();   // get the name
      if(OName && strcmp(OName,Name) == 0)
        return *Iter;
    }

    return 0L;
  }

  /** Clears the list of all registered observers. 
   * @note Using this function in your code may be an indication of design problems.
   */
  void ClearObserver()
  {
    _ObserverSet.clear();
  }


protected:
  /// Vector of attached observers
  std::set<Observer <_MessageType> *> _ObserverSet;
};


} //namespace Base


#endif // BASE_OBSERVER_H
