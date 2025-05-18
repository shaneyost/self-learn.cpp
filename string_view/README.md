# string_view

Imagine, for a moment, you've decided to sketch the Millennium Falcon. You don't own one so what do
you do? You could travel to Corellia and buy your very own Falcon. Owning the Falcon has its perks.
You control it, you can upgrade it with the latest hyperdrive and you can fly it whenever you want.

However, ownership comes at a price with responsibilities. You maintain the ship including the crew
(Chewie isn't cheap) and you have to refuel it all the time. You also have to repair it after every
imperial entanglement and it needs a hanger which likely will have high docking fees.

This is like a `std::string` in that you own the data, manage its lifetime and pay the cost of 
copying or modifying it. However, you could just fly to Chalmun's Cantina at the Mos Eisley
Spaceport on Tatooine where Han Solo parks the Millennium Falcon. You can then view it for free!

You don't have to pay for anything, no maintaining a ship of your own or risk bounty hunters 
chasing you. You don't control it though. Han might fly it away. You can't modify it and you can
only see what is visible from your seat.

This is like `std::string_view` a view type we call it. You have a lightweight cheap view of
existing data, but no ownership or control. If Han takes off, your "view" is gone.

## Key Characteristics

- Non-Owning: Does not manage or own the data it references
- Read-Only: Provides immutable access to the character sequence
- Lightweight: Comprises a pointer and a size; copying is inexpensive
- Versatile: Can be constructed from C-style strings, std::string or other string_view instances

## Important Considerations

- Lifetime Management: Ensure the referenced data outlives the `string_view` to avoid dangling 
references
- Modification of Source: Altering the original string (e.g. resizing) can invalidate the
`string_view`.
- Null-Termination: Unlike C-style strings, `string_view` does not guarantee null-termination; use
`.data()` and `.size()` accordingly.

Most common pitfalls I can see from forums are dangling views. Users did not avoid returning 
`string_view` to local variables that will go out of scope. Implicity conversions were another one
that occurred frequently. `string_view` can be implicitly constructed from various string types,
but concerting back to `std::string` requires an explicit cast or constructor call.

## Practical Uses

Due to what I've seen people do wrong from various forumns there appears to be a practical trend
to when people suggest using it. The most common is when mutability isn't needed.

- Function Parameters: Prefer `std::string_view` over `const std::string&` for read-only access.
- Parsing and Tokenization: Efficiently handle substrings without copying
