# Lazy lists

This is an implementation of lazy lists in Reason using closures. It's not going to be very performant, but it's fun to play with and can come in useful in some situations.

# Overview

The functions provided are lazy where possible. There are two versions of the right fold, `foldr` and `foldr_l`, the latter of which is lazy, and, as a consequence, has a slightly different type signature. Remaining functions are lazy unless they "can't", e.g. `length` and `reverse` are **not** lazy.

# Examples
Definitions used:
```
let nats = iterate((a) => a + 1, 0)
let nats_list = iterate((a) => from_list([head(a) + 1]), from_list([0]))
let is_even = (x) => x mod 2 == 0
```
```	
repeat(1)|>take(5)	
[ 1, 1, 1, 1, 1 ]
```
```	
nats|>map((a) => 3*a)|>filter(is_even)|>take(5)		
[ 0, 6, 12, 18, 24 ]
```
```	
nats|>all((x) => x < 10)	
false
```
```	
zip_with((+), nats, nats)|>take(5)		
[ 0, 2, 4, 6, 8 ]
```
```	
zip(nats, nats)|>unzip|>fst|>take(5)		
[ 0, 1, 2, 3, 4 ]
```
```	
concat(from_list([nats|>take(5), nats]))|>take(6)		
[ 0, 1, 2, 3, 4, 0 ]
```
```	
concat_map((_) => nats, nats)|>take(5)		
[ 0, 1, 2, 3, 4 ]
```
```	
cycle(from_list([1]))|>take(5)		
[ 1, 1, 1, 1, 1 ]
```
```	
intercalate(from_list([0]), nats_list|>drop(1)|>take(3))		
[ 1, 0, 2, 0, 3 ]
```
```	
nats|>take(5)|>reverse		
[ 4, 3, 2, 1, 0 ]