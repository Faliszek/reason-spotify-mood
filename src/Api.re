open Belt;

[@bs.scope ("process", "env")] [@bs.val]
external url: string = "REACT_APP_API";

[@bs.scope ("window", "location")] [@bs.val]
external assign: string => unit = "assign";

[@bs.scope ("window", "location")] [@bs.val] external hash: string = "hash";

let redirect = (path: string) => assign(path);

type result = Result.t(Js.Json.t, (int, string));

let getToken = () => {
  open LocalStorage;
  let auth = get(storeAuth, "auth");
  Js.Dict.unsafeGet(auth, "access_token");
};
let getHeaders = () =>
  Fetch.HeadersInit.make({
    "Content-Type": "application/json",
    "Accept": "application/json",
    "Authorization": "Bearer " ++ getToken(),
  });

let parseUrlParams = urlString => {
  let params =
    Js.String.replace("?", "", Js.String.replace("#", "", urlString));
  let listParams = Js.String.split("&", params);
  let toPairs = Js.Array.map(x => Js.String.split("=", x), listParams);
  let keys = Js.Array.map(x => x[0], toPairs);
  let values = Js.Array.map(x => x[1], toPairs);

  let dict =
    Belt.Array.zip(keys, values)
    ->Belt.Array.reduce(
        Js.Dict.empty(),
        (dict, (k, v)) => {
          let key =
            switch (k) {
            | None => ""
            | Some(actualKey) => actualKey
            };

          dict->Js.Dict.set(key, v);
          dict;
        },
      );
  dict;
};
let getUrlParams = () => parseUrlParams(hash);

let fetch = (path: string, params): RePromise.t(result) =>
  Fetch.fetchWithInit(url ++ "/api" ++ path, params)
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

let createBody = body => body |> Json.stringify |> Fetch.BodyInit.make;

let get = path =>
  fetch(
    path,
    Fetch.RequestInit.make(~method_=Get, ~headers=getHeaders(), ()),
  );

let put = (path, body) => {
  let params = Fetch.RequestInit.make(~method_=Put, ~headers=getHeaders());
  fetch(
    path,
    switch (body) {
    | Some(body) => params(~body=createBody(body), ())
    | None => params()
    },
  );
};

let post = (path, body) =>
  fetch(
    path,
    Fetch.RequestInit.make(
      ~body=createBody(body),
      ~method_=Post,
      ~headers=getHeaders(),
      (),
    ),
  );