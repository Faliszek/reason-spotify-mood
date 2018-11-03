include Js.Promise;

let andThen = fn => then_(a => fn(a) |> resolve);

let catch = fn => catch(a => fn(a) |> resolve);

[@bs.send]
external _finally: (Js.Promise.t('a), unit => unit) => unit = "finally";

let finally = (fn, promise) => _finally(promise, fn);