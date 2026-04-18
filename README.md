# Cache-Simulator

## How to build 
```
g++ -o cachesim main.cpp cache_class.cpp
```

## How to Run
```
./cachesim num_entries associativity block_size input_file
```

## description
cache simulator that takes a number of entries and associativity as input, then reports HIT or MISS for each address.
**Includes implementations for multi-word blocks and multi-level cache (L1 & L2)**