class SomeClass:
    pass

def func(someClass):

    someClass.a=10
    print id(someClass)

    return someClass


if __name__ == '__main__':
    a = SomeClass
    b = func(a)
    print a.a, id(a)
    print id(b)
