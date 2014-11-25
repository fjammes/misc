/*
g++ -c -g -pedantic -Wall -Wno-long-long -Wno-variadic-macros -fPIC
-D_FILE_OFFSET_BITS=64 -fPIC
-I/home/fjammes/stack/Linux64/mysql/5.1.65/include
-I/home/fjammes/stack/Linux64/boost/master-g2e1a7fad74/include
-I/home/fjammes/stack/Linux64/antlr/2.7.7/include
-I/home/fjammes/stack/Linux64/xrootd/4.0.0rc4-qsClient2/include/xrootd
-I/home/fjammes/stack/Linux64/log/1.1.1+5/include
-I/home/fjammes/stack/Linux64/protobuf/2.4.1/include
-I/home/fjammes/stack/Linux64/zookeeper/3.4.6/c-binding/include
-I/home/fjammes/stack/Linux64/log4cxx/0.10.0.lsst1/include -Ibuild
-I/home/fjammes/stack/Linux64/anaconda/1.8.0/include/python2.7 test.cc
 */

#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"

class A {
   public:
     static boost::shared_ptr<A> Create();

   private:
     A() {}

     struct MakeSharedEnabler;   
};

struct A::MakeSharedEnabler : public A {
    MakeSharedEnabler() : A() {
    }
};


boost::shared_ptr<A> A::Create() {
    return boost::make_shared<A::MakeSharedEnabler>();
}
