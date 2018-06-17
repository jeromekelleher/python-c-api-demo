This is a simple demonstration of the Python mechanism for exporting a 
C API from an extension module (like numpy).

See [here](
https://docs.python.org/3.5/extending/extending.html#providing-a-c-api-for-an-extension-module)
for details.

Here we have two modules, demo and consumer. The demo module compiles 
some C code for fancy_algorithm, and it exports this using the Capsule
API. The consumer module then loads the demo module dynamically and 
dereferences a pointer to the function fancy_algorithm when it calls
it (via a neat preprocessor trick).

What this example doesn't show is how to package the header files that are 
needed to make this work. This must be done using setuptools, etc.

**WARNING** There is lots of error checking left out here, so it is *not* a good example to 
base real code on. I put this together to try and figure out how this worked in as simple 
a way as possible; it might help other people trying to figure it out too.
