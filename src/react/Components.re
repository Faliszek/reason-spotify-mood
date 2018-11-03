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

module Grow = {
  [@bs.deriving jsConverter]
  type timeoutShape = {
    enter: int,
    exit: int,
  };
  [@bs.deriving jsConverter]
  type timeout = [ | [@bs.as "auto"] `Auto];
  [@bs.module "@material-ui/core/Grow"]
  external reactClass: ReasonReact.reactClass = "default";
  [@bs.obj]
  external makeProps:
    (
      ~_in: bool=?,
      ~onEnter: unit => unit=?,
      ~onExit: unit => unit=?,
      ~theme: Js.t({..}),
      ~timeout: 'union_1=?,
      ~style: ReactDOMRe.style=?,
      unit
    ) =>
    _ =
    "";
  let make =
      (
        ~_in: option(bool)=?,
        ~onEnter: option(unit => unit)=?,
        ~onExit: option(unit => unit)=?,
        ~theme: Js.t({..}),
        ~timeout:
           option(
             [
               | `Int(int)
               | `Float(float)
               | `Object(timeoutShape)
               | `Enum(timeout)
             ],
           )=?,
        ~style: option(ReactDOMRe.style)=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=
        makeProps(
          ~_in?,
          ~onEnter?,
          ~onExit?,
          ~theme,
          ~timeout=?
            Js.Option.map(
              (. v) =>
                switch (v) {
                | `Enum(v) => unwrapValue(`String(timeoutToJs(v)))
                | `Object(v) => unwrapValue(`Element(timeoutShapeToJs(v)))
                | v => unwrapValue(v)
                },
              timeout,
            ),
          ~style?,
          (),
        ),
      children,
    );
};