
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

### Example Package.swift ###

First, add the _CLibpl_ project as a global dependency: `.package(url: "https://github.com/youngde811/CLibpl.git", from: "0.1.2"),`

Next, add the _CLibpl_ package as a target dependency:

```
.target(
  name: "TaskSupport",
  dependencies: [
    .product(name: "CLibpl", package: "CLibpl", condition: .when(platforms: [.linux]))
  ]
),
```

## Caveat Emptor ##

I cannot stress enough that _Libpl_ is an educated attempt at offering some measure of support for _os.activity_
identifiers. This library should be considered experimental, and is very likely to prove insufficient for certain use
cases. A more thorough implementation will require research of both _os.activity_, and quite possibly Linux kernel
capabilities.

## Author ##

[David E. Young](youngde811@pobox.com)
