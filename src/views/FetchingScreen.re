open Belt;

type track = {
  id: string,
  name: string,
};

type action =
  | UpdateData(array(track), int, int, int)
  | SetOffset(int);

let startOffset = 1;
let limit = 50;

let saveAccessData = () => {
  let params = Api.getUrlParams();
  Js.log(params);
  LocalStorage.save(params);
};

module Api = {
  open Json.Decode;

  let track = json => {
    id: json |> field("id", string),
    name: json |> field("name", string),
  };

  type payload = {
    total: int,
    percent: int,
    tracks: array(track),
  };

  let payloadDecoder = json: payload => {
    tracks: json |> field("tracks", array(track)),
    percent: json |> field("percent", int),
    total: json |> field("total", int),
  };

  let getTracks = offset =>
    Api.get(
      "/tracks?"
      ++ "limit="
      ++ Js.Int.toString(limit)
      ++ "&"
      ++ "offset="
      ++ Js.Int.toString(offset),
    )
    |> RePromise.andThen(result => Result.map(result, payloadDecoder));

  let initialFetchTracks = () => getTracks(startOffset);
  let fetchTracks = offset => getTracks(offset);
};

let renderPercent = p => ReasonReact.string(Js.Int.toString(p) ++ "%");

type state = {
  percent: int,
  total: int,
  offset: int,
  tracks: array(track),
};

let initialState = () => {
  percent: 0,
  total: 0,
  tracks: [||],
  offset: startOffset,
};

let reducer = (action, state) =>
  switch (action) {
  | UpdateData(tracks, percent, total, offset) =>
    ReasonReact.UpdateWithSideEffects(
      {
        ...state,
        tracks: Js.Array.concat(state.tracks, tracks),
        percent,
        total,
      },
      (self => self.send(SetOffset(offset))),
    )

  | SetOffset(offset) => ReasonReact.Update({...state, offset})
  };

let component = ReasonReact.reducerComponent("FetchingScreen");

let rec fetchTracksUntilAllGetLoaded = (send, state, offset) =>
  Api.fetchTracks(offset)
  |> RePromise.andThen(
       fun
       | Result.Ok((payload: Api.payload)) => {
           let newOffset = offset + limit;
           send(
             UpdateData(
               payload.tracks,
               payload.percent,
               payload.total,
               newOffset,
             ),
           );
           if (payload.total > newOffset) {
             fetchTracksUntilAllGetLoaded(send, state, newOffset) |> ignore;
           };
         }
       | Result.Error(_) => (),
     );
let make = _children => {
  ...component,
  reducer,
  initialState,
  didMount: self => {
    saveAccessData();
    fetchTracksUntilAllGetLoaded(self.send, self.state, self.state.offset)
    |> ignore;
  },

  render: self =>
    <div> <Title> {renderPercent(self.state.percent)} </Title> </div>,
};