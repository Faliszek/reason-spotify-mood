open Belt;

module Encode = {
  let parseCreatePayload = (singlePlaylist: Domain.playlist) =>
    Json.Encode.(
      object_([
        ("name", singlePlaylist.name |> string),
        ("description", singlePlaylist.description |> string),
        ("public", singlePlaylist.public |> bool),
        ("collaborative", singlePlaylist.collaborative |> bool),
      ])
    );

  let parseUpdatePayload = (singlePlaylist: Domain.playlist) =>
    Json.Encode.(
      object_([
        (
          "uris",
          Array.map(singlePlaylist.tracks, t => t.uri) |> array(string),
        ),
      ])
    );
};

open Json.Decode;
/*
 type playlistPayload = {
   name: string,
   public: bool,
   collaborative: bool,
   description: string,
 };

 let playlistPayload = json: playlistPayload => {
   name: json |> field("name", string),
   public: json |> field("public", bool),
   description: json |> field("description", string),
   collaborative: json |> field("collaborative", bool),
 }; */

let updatePlaylist = (~baseUrl, ~id, payload) => {
  let payload = Encode.parseUpdatePayload(payload);

  {j|$baseUrl/$id|j} |> Api.put(_, Some(payload));
};

let createPlaylist = (~baseUrl, payload) => {
  let decode = json => json |> field("id", string);

  Api.post(baseUrl, Encode.parseCreatePayload(payload))
  |> RePromise.andThen(Result.map(_, decode));
};
/* |> RePromise.andThen(result => Result.map(result, payloadDecoder)); */