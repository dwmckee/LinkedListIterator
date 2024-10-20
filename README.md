# LinkedListIterator

A C++ iterator over plain C linked lists.

## WHy this?

The algorithms headers is cool, but it expects iterators (or later on
ranges), and linked list types you inherit from a C codebase or
C-centric API don't come with iterators. Obviously, if you're starting
from scratch you'll just use `std::list` or some other library type
that comes with suitable iterators out of the box.

This is an effort to provide a general-enough templated solution for
just dropping in whenever you want to algorithm a linked list.

## Where do we stand?

While the basics now work, there is much that can be improved. We'll see
how it goes and, as always, your milage may vary.

Still to do:

* More tests.
* Another sample in C which violates the common naming convention, so we
  have to model writing alternate advance functors.
* Try to support TAD better. Right now, I have to write way too may explicit
  angle brackets for my tastes.
* Explicit rbegin and rend.
* Insert iterators?
* Bi-driectional where supported? Presumably with two advance functors.
* Decide exactly what standard to support, then make it efficient and
  ergonomic with all supported standards.
* Support for ranges (C++20) and views (C++23)?
