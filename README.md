
# Welcome to the LIBPL Project #

_Libpl_ is a small C library that supplies some level of support for certain capabilities found in Apple's _os.activity_
library. Apple's operating systems have the notions of _activities_ and _scopes_, neither of which even remotely exist
on Linux. Activities are NOT threads; at least, they do not map directly to a single thread. The implementation of
_Libpl_ is an attempt to emulate activity identifiers, opaque unsigned integers that are managed by the operating system
and are available to Swift code without needing to be carried around from function to function, class to class,
etc. **Be Aware**: _Libpl_ is **not** a port of _os.activity_; the implementation is frankly a crap shoot that hopefully
will prove reliable on Linux.

## Availability ##

_Libpl_ is provided via Debian packages compiled for two Linux architectures: _amd64_ and _arm64_ (_aarch64_). Ubuntu
20.04 LTS was the baseline distribution used for building. The library was built using the GNU _gcc_ tool suite; no
other compilers are supported.

## Usage ##

You should be able to use the Swift Package Manager (SPM) to import _Libpl_ into your Swift application or library. For
an example of how to assemble a Swift system library, please see the [CLibpl](https://github.com/youngde811/CLibpl)
project. To see how *CLibpl* is imported into a Swift application, see our [opentelemetry-swift](https://github.com/youngde811/opentelemetry-swift)
fork; any of this project's _Package.swift_ files (yeah, there are several) will show you.

Prior to building a Swift application needing _Libpl_, ensure the appropriate Debian package has been
installed. Typically, you'll use the _dpkg_ command as so: `dpkg --install libpl_1.0-1_aarch.deb`
for ARM64 processors, or `dpkg --install --force-architecture libpl_1.0-1_x86_64.deb` for amd64 and x86_64 machines.

**NB**: The `--force-architecture` flag is only required when installing on a container running under _qemu_ emulation
on ARM MacOS. Apple just **has** to be different...

### Example Package.swift ###

These examples apply only to Swift libraries that require access to _Libpl_ when compiling; client packages must only
ensure that they link to _libpl.so_.

#### Swift Package Manager ####

**NB**: Remember, this section applies **only** to Swift libraries requiring direct access to _Libpl_ when compiling. At
present, the only package we have that requires a dependency is our _opentelemetry-swift_ fork.

In your _Sources_ directory, create the directory _CLibpl_.

In _CLibpl_, create these two files with the indicated contents:

_module.modulemap_:

```
module CLibpl [system] {
    umbrella header "libpl_umbrella.h"
    link "pl"
    export *
}
```

*libpl_umbrella.h*
```
#include </usr/include/plogic/libpl.h>
```

Now, in your _Package.swift_ file, add a _systemLibrary_ target:

```
.systemLibrary(
        name: "CLibpl",
        pkgConfig: "libpl",
        providers: [.apt(["libpl_1.0-1_x86_64.deb"])]
      ),
```

Then, whatever target depends on _CLibpl_, add its dependency. In our example, we only require the dependency on Linux:

```
.target(
  name: "TaskSupport",
  dependencies: [
    .product(name: "CLibpl", condition: .when(platforms: [.linux]))
  ]
),
```

#### Makefiles ####

Client executables using Swift libraries employing _Libpl_ must link their executable targets to _libpl.so_. I generally
do not use XCode, much preferring GNU Make; folks who use the former can likely figure out the linkage issue from the
following Makefile example:

```
link_flags := -Xlinker -L/usr/lib/plogic -Xlinker -lpl
...
$(SWIFT) build -v $(CC_FLAGS) $(LINKER_FLAGS) $(SWIFTC_FLAGS) $(SWIFT_FLAGS) --product $(build_target) $(link_flags)
```

## Caveat Emptor ##

I cannot stress enough that _Libpl_ is an educated attempt at offering some measure of support for _os.activity_
identifiers. This library should be considered experimental, and is very likely to prove insufficient for certain use
cases (eg. in the presence of Swift Tasks). A more thorough implementation will require research of both _os.activity_,
and quite possibly Linux kernel capabilities.

On a more positive note, since Linux has no notion of activities, _Libpl_ will most likely be very useful unless Swift
Tasks are being heavily used. Even in that case, if a task does not span multiple threads then _Libpl_ should still
prove useful.

## Author ##

[David E. Young](youngde811@pobox.com)
