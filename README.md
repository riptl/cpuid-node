cpuid-git
==========

cpuid is a simple to user wrapper around [LibCPUID](http://libcpuid.sourceforge.net/) for [Node.js](http://www.nodejs.org). It's so simple in fact, it's exactly one function, which returns a very easy to use object graph.

cpuid has been tested on Windows 64-bit, Macintosh OSX (Darwin) 64-bit and Linux 3.x 64-bit. All 32-bit platforms should work, but I have not tested them. If you do and it does not work, please file a bug report.

cpuid requires a natively compiled binary component, so it is not suitable for usage in the browser environment.

cpuid's most useful feature for many Node users will be it's detailed overview of the logical versus physical cores. As things like [cluster](http://www.nodejs.org/api/cluster.html) come to the forefront, and "multi-threaded Node" becomes a reality, this information can be invaluable for worker pool performance.

Updated version by terorie supporting the newest processor instructions.

Now based on a git submodule of the original libcpuid.

usage
==========

```JavaScript
const cpuid = require('cpuid-git');
const cpuidInfo = cpuid();
```

cpuid is one function, which takes no arguments, and returns an object with properties representing the CPUID data.
