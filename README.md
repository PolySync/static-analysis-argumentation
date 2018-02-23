# Static Analysis Argumentation

Evaluation of the efficacy of static analysis tooling for C
and the Rust compiler in catching software errors pre-runtime.

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->


- [C static analysis tooling](#c-static-analysis-tooling)
- [Rust tooling](#rust-tooling)
- [C examples](#c-examples)
  - [alias.c](#aliasc)
  - [constant.c](#constantc)
  - [pattern.c](#patternc)
  - [thread.c](#threadc)
- [Rust examples](#rust-examples)
  - [alias.rs](#aliasrs)
  - [constant.rs](#constantrs)
  - [pattern.rs](#patternrs)
  - [thread.rs](#threadrs)
- [Usage](#usage)
  - [C](#c)
  - [Rust](#rust)
- [Results](#results)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## C static analysis tooling

- [scan-build](https://clang-analyzer.llvm.org/scan-build.html)
- [cppcheck](https://github.com/danmar/cppcheck)
- [flawfinder](https://www.dwheeler.com/flawfinder/)
- [flint++](http://l2program.co.uk/category/flint)
- [frama-c](http://frama-c.com/)
- [oclint](https://github.com/oclint/oclint)
- [scan-build clang](https://clang-analyzer.llvm.org/scan-build.html)
- [splint](https://linux.die.net/man/1/splint)
- [vera++](https://bitbucket.org/verateam/vera/wiki/Introduction)

## Rust tooling

- `rustc`

## C examples

### [alias.c](./c_examples/alias.c)

Dangerous aliasing behavior resulting in unsafe memory access.

### [constant.c](./c_examples/constant.c)

Discarding type qualification resulting in unsafe memory access.

### [pattern.c](./c_examples/pattern.c)

Ambiguity of enumerations resulting in unsafe memory access.

### [thread.c](./c_examples/thread.c)

Data race resulting in unsafe memory access.

## Rust examples

### [alias.rs](./rust_examples/alias.rs)

An attempt to implement the dangerous behavior of the corresponding [alias.c](./c_examples/alias.c).

### [constant.rs](./rust_examples/constant.rs)

An attempt to implement the dangerous behavior of the corresponding [constant.c](./c_examples/constant.c).

### [pattern.rs](./rust_examples/pattern.rs)

An attempt to implement the dangerous behavior of the corresponding [pattern.c](./c_examples/pattern.c).

### [thread.rs](./rust_examples/thread.rs)

An attempt to implement the dangerous behavior of the corresponding [thread.c](./c_examples/thread.c).

## Usage

### C

Each of the C examples should compile with `gcc` or `clang`. They should also result in a
`Segmentation fault` report. Because access to the intentionally corrupted data represents undefined
behavior, they may not always crash. Running any example a few times will likely reproduce the crash
if the first try doesn't.

### Rust

Each of the examples should fail to compile with `rustc`

## Results

See [./report-alias.txt](./report-alias.txt), [./report-const.txt](./report-const.txt), [./report-pattern.txt](./report-pattern.txt), [./report-thread.txt](./report-thread.txt) for result details for each example.
