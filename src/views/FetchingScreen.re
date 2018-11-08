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

/* let mockData =

   {
      "album": {
        "id": "5jzohQ50TA36qTumAG1rEA",
        "name": "Elements (Deluxe)"
      },
      "artist": {
        "id": "2uFUBdaVGtyMqckSeCl0Qj",
        "image": {
          "height": 160,
          "url": "https://i.scdn.co/image/f0242adeb3c7400d88a5ff4bb1119eb4b5d586d2",
          "width": 160
        },
        "name": "Ludovico Einaudi"
      },
      "duration_ms": 198829,
      "genres": [
        "bow pop",
        "compositional ambient"
      ],
      "id": "0ZJYxs4ukXlrFymGFpEUL3",
      "image": {
        "height": 640,
        "url": "https://i.scdn.co/image/7ed9c4863f2aaaaf390650c3aec5acf445f10a34",
        "width": 640
      },
      "name": "Song For Gavin",
      "url": "https://api.spotify.com/v1/tracks/0ZJYxs4ukXlrFymGFpEUL3"
    } */

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

let fetchTracksUntilAllGetLoaded = (send, state, offset) =>
  Api.fetchTracks(offset)
  |> RePromise.andThen(
       fun
       | Result.Ok((payload: Api.payload)) => {
           let newOffset = state.offset + limit;
           send(
             UpdateData(
               payload.tracks,
               payload.percent,
               payload.total,
               newOffset,
             ),
           );
         }
       | Result.Error(_) => (),
     );

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

  | SetOffset(offset) =>
    ReasonReact.UpdateWithSideEffects(
      {...state, offset},
      (
        self =>
          if (self.state.total > self.state.offset) {
            fetchTracksUntilAllGetLoaded(
              self.send,
              self.state,
              self.state.offset,
            )
            |> ignore;
          }
      ),
    )
  };

let component = ReasonReact.reducerComponent("FetchingScreen");

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