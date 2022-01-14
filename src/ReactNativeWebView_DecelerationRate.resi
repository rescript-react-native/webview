type t

external value: float => t = "%identity"

@inline("normal")
let normal: t

@inline("fast")
let fast: t
