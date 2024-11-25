# Alpaca Core Local SDK Swift Wrapper

Here we have both a high level and low level wrapper.

## `AlpacaCoreSwift`

A high level wrapper. It's interface should feel as idiomatic Swift. `Dict` is passed as `Dictionary`.

It's implemented via...

## `CxxAlpacaCore`

A low-level wrapper which exposes more C++ internals in the pseudo-structure `AC`.

`Dict` is accessible as `AC.DictRoot` and `AC.DictRef` in a manner similar to the C API.

## Build

Only macOS is currently officially supported. We do run builds on other operating systems, but official support for them is not currently a priority.

* You need Swift 6.0.0 or later.
* On macOS only the clang compiler which comes with `$ xcode-select --install` can work.
* On non-macOS systems you need to configure with the clang compiler shipped with your swift installation.

### Development environment

Here's the recommended way to setup a development environment for building this project:

First, cover the basic setup from [ac-local Development environment doc](https://github.com/alpaca-core/ac-local/blob/master/doc/dev/dev-env.md)

Aditionally:

* Arch Linux
    * `$ pamac build swift-bin`
    * Note that to build the swift wrapper, you will have to configure with `-DCMAKE_CXX_COMPILER=/usr/lib/swift/bin/clang++ -DCMAKE_C_COMPILER=/usr/lib/swift/bin/clang`
* Windows
    * Install Swift in any of the ways described [here](https://www.swift.org/install/windows)
    * Note that on you need to use the clang compiler shipped with your swift installation
    * Also note that installing the Swift will add clang++ to your system path. If you also use other clang compilers, you will have to juggle the system path around accorting to what you currently need.
