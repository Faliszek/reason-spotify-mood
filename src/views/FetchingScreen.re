open Belt;

type track = {
  id: string,
  name: string,
};

type action =
  | SetTracks(array(track))
  | SetPercent(int)
  | SetTotal(int)
  | SetOffset(int)
  | Noop;

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

  let fetchTracks = offset => getTracks(offset);
  /* |> RePromise.andThen(Result.map(_, decoder)); */
  /* let initialFetchTracks = (offset) => fetchTracks(startOffset); */
};

let renderPercent = p => ReasonReact.string(Js.Int.toString(p) ++ "%");

type state = {
  percent: int,
  total: int,
  offset: int,
  tracks: array(track),
};
let component = ReasonReact.reducerComponent("FetchingScreen");

let initialState = () => {
  percent: 0,
  total: 0,
  tracks: [||],
  offset: startOffset,
};

let reducer = (action, state) =>
  switch (action) {
  | SetPercent(percent) => ReasonReact.Update({...state, percent})
  | SetTracks(tracks) => ReasonReact.Update({...state, tracks})
  | SetTotal(total) => ReasonReact.Update({...state, total})
  | SetOffset(offset) => ReasonReact.Update({...state, offset})
  | Noop => ReasonReact.NoUpdate
  };

let make = _children => {
  ...component,
  reducer,
  initialState,
  didMount: self => {
    saveAccessData();
    Api.fetchTracks(self.state.offset)
    |> RePromise.andThen(
         fun
         | Result.Ok((payload: Api.payload)) => {
             let newOffset = self.state.offset + limit;
             self.send(SetTracks(payload.tracks));
             self.send(SetPercent(payload.percent));
             self.send(SetTotal(payload.total));
             self.send(SetOffset(newOffset));
             Js.log2(payload.total > self.state.offset, self.state.offset);
             if (payload.total > self.state.offset) {
               Api.fetchTracks(newOffset);
               ();
             };
           }
         | Result.Error(_) => (),
       )
    |> ignore;
  },

  render: self =>
    <div> <Title> {renderPercent(self.state.percent)} </Title> </div>,
};