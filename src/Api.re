open Belt;

[@bs.scope ("process", "env")] [@bs.val]
external url: string = "REACT_APP_API";

[@bs.scope ("window", "location")] [@bs.val]
external assign: string => unit = "assign";

let redirect = (path: string) => assign(path);

type result = Result.t(Js.Json.t, (int, string));
let getHeaders = () =>
  Fetch.HeadersInit.make({
    "Content-Type": "application/json",
    "Accept": "application/json",
  });

let fetch = (path: string, params): RePromise.t(result) =>
  Fetch.fetchWithInit(url ++ path, params)
  |> RePromise.then_(res => {
       open Result;
       let status = Fetch.Response.status(res);
       if (status === 200 || status === 201) {
         res |> Fetch.Response.json |> RePromise.andThen(json => Ok(json));
       } else {
         res
         |> Fetch.Response.text
         |> RePromise.andThen(text => Error((status, text)));
       };
     });

let createBody = body => body |> Js.Json.stringify |> Fetch.BodyInit.make;

let get = path =>
  fetch(
    path,
    Fetch.RequestInit.make(~method_=Get, ~headers=getHeaders(), ()),
  );