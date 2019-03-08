def generate_power(number):
    """
    Examples of use:

    >>> raise_two = generate_power(2)
    >>> raise_three = generate_power(3)
    >>> print(raise_two(7))
    128
    >>> print(raise_three(5))
    243
    """

    # define the inner function ...
    def nth_power(power):
        print "number %s" % number
        return number ** power
    # ... which is returned by the factory function

    number = number+1

    return nth_power


if __name__ == '__main__':
    a = generate_power(2)
    print a(2)
