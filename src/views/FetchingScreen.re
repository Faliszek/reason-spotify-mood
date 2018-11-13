open Belt;

type image = {
  width: int,
  url: string,
  height: int,
};
type album = {
  id: string,
  name: string,
};
type artist = {
  id: string,
  name: string,
  image,
};
type track = {
  id: string,
  name: string,
  url: string,
  duration_ms: int,
  genres: array(string),
  image,
  album,
  artist,
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
  let image = json => {
    width: json |> field("width", int),
    url: json |> field("url", string),
    height: json |> field("width", int),
  };

  let artist = json => {
    id: json |> field("id", string),

    name: json |> field("name", string),
    image: json |> field("image", image),
  };
  let album = json => {
    id: json |> field("id", string),
    name: json |> field("name", string),
  };

  let track = json => {
    id: json |> field("id", string),
    name: json |> field("name", string),
    url: json |> field("url", string),
    duration_ms: json |> field("duration_ms", int),
    genres: json |> field("genres", array(string)),
    artist: json |> field("artist", artist),
    image: json |> field("image", image),
    album: json |> field("album", album),
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

module Styles = {
  /*Open the Css module, so we can access the style properties below without prefixing them with Css.*/
  open Css;

  let wrap = style([maxWidth(px(200))]);
};

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
    <div>
      <div className=Styles.wrap>
        <CircularProgress
          percentage={self.state.percent}
          text={renderPercent(self.state.percent)}
          strokeWidth=4
          backgroundPadding=10
          styles={
            "background": ReactDOMRe.Style.make(~fill="#444444", ()),
            "stroke": ReactDOMRe.Style.make(~stroke="#7500a8", ()),
            "text": ReactDOMRe.Style.make(~fill="#fff", ()),
            "path": ReactDOMRe.Style.make(~stroke="#7500a8", ()),
            "trail": ReactDOMRe.Style.make(~stroke="#444444", ()),
          }
        />
      </div>
    </div>,
};