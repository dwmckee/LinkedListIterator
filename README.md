# LinkedListIterator

A C++11 iterator over plain C linked lists.

## Why this?

Ranged for loops and the algorithms headers are cool, but they expect
iterators (or later-on ranges), and linked list types you inherit from a
C codebase or [C-centric
API](https://nibblestew.blogspot.com/2024/04/c-is-dead-long-live-c-apis.html)
don't come with iterators. This is an effort to provide a general-enough
templated solution for just dropping in whenever you want to use modern
C++ idioms with a C linked list.

Obviously, if you're starting from scratch you'll just use `std::list`
or some other library type that comes with suitable iterators out of the
box.

## How to use it?

This is a header-only library, so including the project on you
pre-processor search path (`-I...`) will let you `#include
"linkedlistiterator.h"` and go to town.

The rest of the project is code to demonstrate that the header does what
it says on the tin.  It builds with [meson](https://mesonbuild.com/) for
now, and you run the three `test-*` executables.

You'll want `using namespace lli;` in files that make use of the project
(so that the `lli::begin`, `lli::end`, and variations thereof can be
found by polymorphic name resolution). If you have to create
specializations of the template for your list type, you'll still need to
be explicit about the namespace of the templates you're specializing
(see, for instance, `lli::begin` in `test-main.cpp`).

## Where does the project stand?

While the basics now work, there is much that can be improved. We'll see
how it goes and, as always, your milage may vary.

Still to do:

* More tests.
* Another sample in C which violates the common naming convention, so we
  have to model writing alternate advance functors.
* Try to support [C]TAD better. Right now, I have to write way too may explicit
  angle brackets for my tastes.
* Insert iterators?
* Bi-driectional where supported? Presumably with two advance functors.
* Decide exactly what standards to support, then make it efficient and
  ergonomic with all supported standards.
* Support for ranges (C++20) and views (C++23)?
* Provide installation support in the build, FindLinkListIterator.cmake,
  and LinkedListIterator.wrap, and so on to make this easy for other to use.
