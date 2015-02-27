// Third party headers
#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"

#include <vector>

template <class C>
struct Ptr 
{
        typedef std::vector<boost::shared_ptr<C> > Vector;
};

int main() {
    typedef Ptr<int>::Vector PtrVector;
    Ptr<int>::Vector v;
}
