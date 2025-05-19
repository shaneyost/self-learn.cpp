# string_view

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
