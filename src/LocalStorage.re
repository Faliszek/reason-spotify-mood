[@bs.val] external unsafeJsonParse: string => 'a = "JSON.parse";

let storeAuth = "reason-spotify-mood-auth";
let storeTracks = "reason-spotify-mood-tracks";

let save = (keyStore: string, data) =>
  switch (Js.Json.stringifyAny(data)) {
  | None => ()
  | Some(stringifiedAccessData) =>
    Dom.Storage.(localStorage |> setItem(keyStore, stringifiedAccessData))
  };

let get = (keyStore, key) => {
  let localDataString =
    switch (Dom.Storage.(localStorage |> getItem(keyStore))) {
    | None => Js.Dict.empty()
    | Some(accessData) => unsafeJsonParse(accessData)
    };

  switch (Js.Dict.get(localDataString, key)) {
  | None => Js.Dict.empty()
  | Some(data) => data
  };
};