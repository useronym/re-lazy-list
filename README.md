# Lazy lists

This is an implementation of lazy lists in Reason using closures. It's not going to be very performant, but it's fun to play with and can come in useful in some situations.

# Overview

The functions provided are lazy where possible. There are two versions of the right fold, `foldr` and `foldr_l`, the latter of which is lazy, and, as a consequence, has a slightly different type signature. Remaining functions are lazy unless they "can't", e.g. `length` and `reverse` are **not** lazy.