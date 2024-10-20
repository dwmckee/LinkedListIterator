project('LinkedListIterator', ['c', 'cpp'],
        default_options : ['cpp_std=c++11', 'c_std=c99'],
        version: '0.1.0',
        license: 'MIT')

# doctest_proj = subproject('doctest')
# doctest_dep = doctest_proj.get_variable('doctest_dep')
# # NB: Doctest dependency is needed on anything that includes doctest.h even if
# # we use DOCTEST_CONFIG_DISABLE


# This is a header-only library, so there is no library to link.
# Everything we build is test.
#
# First show the all the parts of the C code do what is expected...
c_stack_test_exe = executable('test-c-stack',
                              ['c-stack-test-main.c',
                               'c_stack.c',
                               'test_infrastructure.c'])
test('c stack tests', c_stack_test_exe, args: [])

c_deque_test_exe = executable('test-c-deque',
                              ['c-deque-test-main.c',
                               'c_deque.c',
                               'test_infrastructure.c'])
test('c deque tests', c_deque_test_exe, args: [])


# Then show that the C++ interface imports that functionality...
test_files = ['c_stack.c', 'c_deque.c']
test_exe = executable('test-LinkedListIterator',
                      ['test-main.cpp'] + test_files)

