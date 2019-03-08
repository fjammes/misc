
class Testable {
    bool ok_;
    typedef void (Testable::*bool_type)() const;
  public:
    void this_type_does_not_support_comparisons() const {}
    explicit Testable(bool b=true):ok_(b) {}
 
    operator bool_type() const {
      return ok_ ? 
        &Testable::this_type_does_not_support_comparisons : 0;
    }
};

/*
template <typename T>
bool operator!=(const Testable& lhs, const T&) {
    lhs.this_type_does_not_support_comparisons();	
    return false;
}

template <typename T>
bool operator==(const Testable& lhs, const T&) {
    lhs.this_type_does_not_support_comparisons();
    return false;
}
*/

class AnotherTestable { // Identical to Testable.
    bool ok_;
    typedef void (AnotherTestable::*bool_type)() const;
  public:
    void this_type_does_not_support_comparisons() const {}
    explicit AnotherTestable(bool b=true):ok_(b) {}
 
    operator bool_type() const {
      return ok_ ? 
        &AnotherTestable::this_type_does_not_support_comparisons : 0;
    }
};

int main (void)
{
  Testable t1;
  AnotherTestable t2;
  if (t1) {} // Works as expected
  if (t1 == t2) {} // Fails to compile
//  if (t2 == t1) {} // Fails to compile
//  if (t1 < 0) {} // Fails to compile
 
  return 0;
}
