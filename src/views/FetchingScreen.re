open Belt;

type track = {
  id: string,
  name: string,
};

type state = {
  percent: int,
  tracks: array(track),
};
type percent = int;

type action =
  | SetTracks(array(track))
  | SetPercent(int)
  | Noop;

let reducer = (action, state) =>
  switch (action) {
  | SetPercent(percent) => ReasonReact.Update({...state, percent})

  | SetTracks(tracks) => ReasonReact.Update({...state, tracks})

  | Noop => ReasonReact.NoUpdate
  };

let initialState = () => {percent: 0, tracks: [||]};

let startOffset = "1";
let limit = "50";

let saveAccessData = () => {
  let params = Api.getUrlParams();
  Js.log(params);
  LocalStorage.save(params);
  ();
};

module Track = {
  open Json.Decode;

  let track = json => {
    id: json |> field("id", string),
    name: json |> field("name", string),
  };

  let payloadDecoder = json => {
    tracks: json |> field("tracks", array(track)),
    percent: json |> field("percent", int),
  };

  payloadDecoder;
};

module Api = {
  let getTracks = offset =>
    Api.get("/tracks?" ++ "limit=" ++ limit ++ "&" ++ "offset=" ++ offset)
    |> RePromise.andThen(result => Result.map(result, Track.payloadDecoder));
};

let fetchTracks = offset => Api.getTracks(offset);
/* |> RePromise.andThen(Result.map(_, decoder)); */

let initialFetchTracks = () => fetchTracks(startOffset);

let renderPercent = p => ReasonReact.string(Js.Int.toString(p) ++ "%");

let component = ReasonReact.reducerComponent("FetchingScreen");

let make = _children => {
  ...component,
  reducer,
  initialState,
  didMount: self => {
    saveAccessData();
    initialFetchTracks()
    |> RePromise.andThen(
         fun
         | Result.Ok(payload) => {
             self.send(SetTracks(payload.tracks));
             self.send(SetPercent(payload.percent));
           }
         | Result.Error(_) => (),
       )
    |> ignore;
  },

  render: self =>
    <div> <Title> {renderPercent(self.state.percent)} </Title> </div>,
};