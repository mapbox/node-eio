# node-eio

Control libeio from JavaScript

# Usage

* `libeio.setMinParallel(threads)`: Sets the available number of threads. node's default is 4. Use this function for increasing the number of threads.
* `libeio.setMaxParallel(threads)`: Sets the maximum number of threads. This does *only* cap the number of threads and expires existing threads that are bigger than the maximum.
* `libeio.usage()`: Returns an object with thread usage information.

# Credits

Based on [polotek's thread branch](https://github.com/polotek/node/compare/2c1ca4078d12ea62745d0f3f72c0909befe86399...threads).