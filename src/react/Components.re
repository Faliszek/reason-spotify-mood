external toJsUnsafe: 'a => 'b = "%identity";

let unwrapValue =
  fun
  | `String((s: string)) => toJsUnsafe(s)
  | `Bool((b: bool)) => toJsUnsafe(b)
  | `Float((f: float)) => toJsUnsafe(f)
  | `Int((i: int)) => toJsUnsafe(i)
  | `Date(d) => toJsUnsafe(d)
  | `Callback(c) => toJsUnsafe(c)
  | `Element(e) => toJsUnsafe(e)
  | `StringArray((sa: array(string))) => toJsUnsafe(sa)
  | `IntArray((ia: array(int))) => toJsUnsafe(ia)
  | `FloatArray((fa: array(float))) => toJsUnsafe(fa)
  | `ObjectGeneric(og) => toJsUnsafe(og)
  | `ArrayGeneric(ag) => toJsUnsafe(ag)
  | `Object(_) => assert(false)
  | `Enum(_) => assert(false)
  | `EnumArray(_) => assert(false);