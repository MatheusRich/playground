# Portal

<p align="center">
  <img src="elixir-portal.png" width=400>
</p>

This is my implementation of José Valim's Elixir tutorial ["How I start"](https://howistart.org/posts/elixir/1/).

The code simulates the Portal Game. You can create portals, and transfer data between them.


## Installation
Make sure you have Elixir version 1.9 or later installed. You can find installation guides [here](https://elixir-lang.org/install.html).


## Usage
* First, load the code on a new `iex` session:
```bash
iex -S mix
```

* Shoot two portals:
```elixir
iex(1)> Portal.shoot(:orange)
{:ok, #PID<0.152.0>}

iex(2)> Portal.shoot(:blue)
{:ok, #PID<0.156.0>}
```

* Start transferring data between the portals:
```elixir
iex(3)> portal = Portal.transfer(:orange, :blue, [1,2,3,4,5])
#Portal<
          :orange <=> :blue
  [1, 2, 3, 4, 5] <=> []
>
```

* Use `Portal.push_right` to transfer data from orange to blue:
```elixir
iex(4)> Portal.push_right(portal)                            
#Portal<
       :orange <=> :blue
  [1, 2, 3, 4] <=> [5]
>
iex(5)> Portal.push_right(portal)
#Portal<
    :orange <=> :blue
  [1, 2, 3] <=> [4, 5]
>
```

* You can use `Portal.push_left` to transfer data from blue to orange:
```elixir
iex(6)> Portal.push_left(portal)   
#Portal<
       :orange <=> :blue
  [1, 2, 3, 4] <=> [5]
>
```

## Test
TO DO
<!-- If [available in Hex](https://hex.pm/docs/publish), the package can be installed
by adding `portal` to your list of dependencies in `mix.exs`:

```elixir
def deps do
  [
    {:portal, "~> 0.1.0"}
  ]
end
```

Documentation can be generated with [ExDoc](https://github.com/elixir-lang/ex_doc)
and published on [HexDocs](https://hexdocs.pm). Once published, the docs can
be found at [https://hexdocs.pm/portal](https://hexdocs.pm/portal). -->

