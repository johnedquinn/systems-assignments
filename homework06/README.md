# Homework 06

## Activity 1 - Questions

1. What is the difference between a shared library such as `libstr.so` and a
   static library such as `libstr.a`?
	Shared libraries connect to the program at run-time. With this in mind, shared libraries are usually larger files because they need the necessary information to perform this connection. It is overhead. The static library is directly embedded into a program, and therefore the .o file is approximately the same size as the .a static library. Static libraries are safer because they cannot be changed once compiled. Dynamic libraries are useful because you can have one copy of the library with several programs utilizing its information.

2. Compare the sizes of `libstr.so` and `libstr.a`, which one is larger? Why?
	I touched upon this in the question above, but the .so file is larger because it contains overhead information that allows the computer to connect the shared library to the program. Static libraries are embedded into the very program, so they are around the same size as the .o file. The shared library is larger.

## Activity 2 - Questions

1. What is the difference between a static executable such as `str-static`
   and a dynamic executable such as `str-dynamic`?
	The static executable contains copies of libraries at compile time. Dynamic executables create links to libraries.

2. Compare the sizes of `str-static` and `str-dynamic`, which one is larger?
   Why?
	Since dynamic executables only contain links to libraries, there is no need to load in the entire library into the file. Therefore, the file is smaller. The static executable loads the entire library into the file so that it can run effectively.

3. Login into a new shell and try to execute `str-dynamic`.  Why doesn't
   `str-dynamic` work?  Explain what you had to do in order for `str-dynamic`
   to actually run.
	str-dynamic does not work, because the computer searches for the dynamic library within the environmental variable  $LD_LIBRARY_PATH. If we open up a new session, the LD_LIBRARY_PATH won't have the path to the str library. In order to allow the computer to find the library, you must export the current path to the LD_LIBRARY_PATH.

4. Login into a new shell and try to execute `str-static`.  Why does
   `str-static` work, but `str-dynamic` does not in a brand new shell session?
	The executable str-static contains a copy of the str library; therefore, it is able to run on its own without searching the computer for the library. This is also why the executable is so large.
