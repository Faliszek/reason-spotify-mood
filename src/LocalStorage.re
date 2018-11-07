[@bs.val] external unsafeJsonParse: string => 'a = "JSON.parse";

let localStorageNamespace = "reason-spotify-mood";

let save = accessData =>
  switch (Js.Json.stringifyAny(accessData)) {
  | None => ()
  | Some(stringifiedAccessData) =>
    Dom.Storage.(
      localStorage |> setItem(localStorageNamespace, stringifiedAccessData)
    )
  };

let get = key => {
  let localDataString =
    switch (Dom.Storage.(localStorage |> getItem(localStorageNamespace))) {
    | None => Js.Dict.empty()
    | Some(accessData) => unsafeJsonParse(accessData)
    };

  switch (Js.Dict.get(localDataString, key)) {
  | None => ""
  | Some(data) => data
  };
};