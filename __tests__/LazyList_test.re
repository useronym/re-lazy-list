open Jest;
open Expect;
open LazyList;

describe("LazyList", () => {

  //let toBeList = (l, xs) => to_list(xs) |> toBe(l)
  let nats = iterate((a) => a + 1, 0)
  let nats_list = iterate((a) => from_list([head(a) + 1]), from_list([0]))
  let is_even = (x) => x mod 2 == 0
  
  test("head", () => expect(head(nats)) |> toBe(0))
  test("tail", () => expect(head(tail(tail(nats)))) |> toBe(2))
  test("take", () => expect(nats|>take(3)|>to_list) |> toEqual([0,1,2]))
  test("repeat", () => expect(repeat(1)|>take(5)|>to_list) |> toEqual([1,1,1,1,1]))	
  test("map", () => expect(nats|>map((a) => 3*a)|>filter(is_even)|>take(5)|>to_list) |> toEqual([0,6,12,18,24]))	
  test("all", () => expect(nats|>all((x) => x < 10)) |> toBe(false))	
  test("zip_with", () => expect(zip_with((+), nats, nats)|>take(5)|>to_list) |> toEqual([0,2,4,6,8]))	
  test("zip", () => expect(zip(nats, nats)|>unzip|>fst|>take(5)|>to_list) |> toEqual([0,1,2,3,4]))	
  test("concat", () => expect(concat(from_list([nats|>take(5), nats]))|>take(6)|>to_list) |> toEqual([0,1,2,3,4,0]))	
  test("concat_map", () => expect(concat_map((_) => nats, nats)|>take(5)|>to_list) |> toEqual([0,1,2,3,4]))	
  test("cycle", () => expect(cycle(from_list([0,1]))|>take(5)|>to_list) |> toEqual([0,1,0,1,0]))	
  test("intercalate", () => expect(intercalate(from_list([0]), nats_list|>drop(1)|>take(3))|>to_list) |> toEqual([1,0,2,0,3]))	
  test("reverse", () => expect(nats|>take(5)|>reverse|>to_list) |> toEqual([4,3,2,1,0]))	
  test("length", () => expect(nats|>take(5)|>length) |> toBe(5))	
});