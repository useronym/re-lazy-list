type unit = ()
type lazyList('a) =
  | Nil
  | Cons('a, unit => lazyList('a))

exception Head_Nil;
let head = (xs) => switch xs {
  | Nil => raise(Head_Nil)
  | Cons(x, _) => x
};

exception Tail_Nil;
let tail = (xs) => switch xs {
  | Nil => raise(Tail_Nil)
  | Cons(_, xs') => xs'()
};

let rec to_list = (xs) => switch xs {
  | Nil => []
  | Cons(x, xs') => [x, ...to_list(xs'())]
};

let rec from_list = (xs) => switch xs {
  | [] => Nil
  | [x, ...xs'] => Cons(x, () => from_list(xs'))
};

let to_array = (xs) => Array.of_list(to_list(xs))

let rec repeat = (x) => Cons(x, () => repeat(x))

let rec iterate = (f, init) => Cons(init, () => iterate(f, f(init)))

let rec take = (n, xs) => switch n {
  | 0 => Nil
  | 1 => Cons(head(xs), () => Nil)
  | n => Cons(head(xs), () => take(n - 1, tail(xs)))
};

let rec drop = (n, xs) => switch n {
  | 0 => xs
  | n => drop(n - 1, tail(xs))
};

// NOT lazy
let rec foldl = (f, acc	, xs) => switch xs {
  | Nil => acc	
  | Cons(x, xs') => foldl(f, f(acc, x), xs'())
};

// NOT lazy
let rec foldr = (f, init, xs) => switch xs {
  | Nil => init
  | Cons(x, xs') => f(x, foldr(f, init, xs'()))
};

// Lazy
let rec foldr_l = (f, init, xs) => switch xs {
  | Nil => init
  | Cons(x, xs') => f(x, () => foldr_l(f, init, xs'()))
};

let map = (f) => foldr_l((x, acc) => Cons(f(x), () => acc()), Nil)

let filter = (f) => foldr_l((x, acc) => if (f(x)) {Cons(x, acc)} else {acc()}, Nil)

// This will blow if you give it an infinite list of empty lists!
let rec concat1 = (xs, xss) => switch (xs, xss) {
  | (Nil, Nil) => Nil
  | (Nil, Cons(xs', xss')) => concat1(xs', xss'())
  | (Cons(x, xs'), _) => Cons(x, () => concat1(xs'(), xss))
};
let concat = (xs) => concat1(Nil, xs)

let concat_map = (f, xs) => concat(map(f, xs))

let cycle = (xs) => concat(repeat(xs))

let rec intersperse = (x, ys) => switch ys {
  | Nil => Nil
  | Cons(y, ys') => Cons(y, () => switch (ys'()) {
    | Nil => Nil
    | rest => Cons(x, () => intersperse(x, rest))
  })
};

let intercalate = (xs, yss) => concat(intersperse(xs, yss))

let rec zip_with = (f, xs, ys) => switch (xs, ys) {
  | (Cons(x, xs'), Cons(y, ys')) => Cons(f(x, y), () => zip_with(f, xs'(), ys'()))
  | _ => Nil
};

// Can't be written point-free because the type system can't handle it :|
let zip = (xs, ys) => zip_with((x, y) => (x, y), xs, ys)

// This looks bad, but can we do better?
// But! It is all lazy, so performance should be more-or-less unaffected
let rec unzip = (xys) => switch (xys) {
  | Nil => (Nil, Nil)
  | Cons((x, y), xys') => (Cons(x, () => unzip(xys'())|>fst), Cons(y, () => unzip(xys'())|>snd))
};

let all = (p) => foldr_l((x, acc) => p(x) && acc(), true)

let any = (p) => foldr_l((x, acc) => p(x) || acc(), false)

let and_ = all((==)(true))

let or_ = any((==)(true))

let rec find = (p, xs) => switch (xs) {
  | Nil => None
  | Cons(x, xs') => if (p(x)) {Some(x)} else {find(p, xs'())}
};

let rec lookup = (x, ps) => switch (ps) {
  | Nil => None
  | Cons((a, b), ps') => if (x == a) {Some(b)} else {lookup(x, ps'())}
};

let elem = (x, xs) => switch (find(x, xs)) {
  | None => false
  | _ => true
};

let length = (xs) => foldl((n, _) => n + 1, 0, xs)

let reverse = (xs) => foldl((acc, x) => Cons(x, () => acc), Nil, xs)