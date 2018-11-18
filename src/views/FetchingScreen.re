open Belt;
open Domain;

type status =
  | Waiting
  | Done;

type action =
  | UpdateData(array(track), int, int, int)
  | SetOffset(int)
  | UpdateInfo(status);

let startOffset = 1;
let limit = 50;

let saveAccessData = () => {
  open LocalStorage;
  let params = Api.getUrlParams();
  save(storeAuth, {"auth": params});
};

module Api = {
  open Json.Decode;

  let imageDecoder = json => {
    width: json |> field("width", int),
    url: json |> field("url", string),
    height: json |> field("width", int),
  };

  let artistDecoder = json => {
    id: json |> field("id", string),

    name: json |> field("name", string),
    image: json |> field("image", imageDecoder),
  };
  let albumDecoder = json => {
    id: json |> field("id", string),
    name: json |> field("name", string),
  };

  let trackDecoder = json => {
    id: json |> field("id", string),
    name: json |> field("name", string),
    url: json |> field("url", string),
    uri: json |> field("uri", string),
    duration_ms: json |> field("duration_ms", int),
    genres: json |> field("genres", array(string)),
    artist: json |> field("artist", artistDecoder),
    image: json |> field("image", imageDecoder),
    album: json |> field("album", albumDecoder),
  };

  type tracksPayload = {
    total: int,
    percent: int,
    tracks: array(track),
  };

  type moodPayload = {
    moodProposition: string,
    city: string,
    code: int,
  };

  let payloadDecoder = json: tracksPayload => {
    tracks: json |> field("tracks", array(trackDecoder)),
    percent: json |> field("percent", int),
    total: json |> field("total", int),
  };

  let moodDecoder = json: moodPayload => {
    moodProposition: json |> field("moodProposition", string),
    city: json |> field("city", string),
    code: json |> field("code", int),
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
  status,
};

let initialState = () => {
  percent: 0,
  total: 0,
  tracks: [||],
  offset: startOffset,
  status: Waiting,
};

let fetchTracksUntilAllGetLoaded = (send, state, offset) =>
  Api.fetchTracks(offset)
  |> RePromise.andThen(
       fun
       | Result.Ok((payload: Api.tracksPayload)) => {
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
      (
        self => {
          self.send(SetOffset(offset));
          LocalStorage.save(LocalStorage.storeTracks, self.state.tracks);
        }
      ),
    )

  | SetOffset(offset) =>
    ReasonReact.UpdateWithSideEffects(
      {...state, offset},
      (
        self => {
          if (self.state.total > self.state.offset) {
            fetchTracksUntilAllGetLoaded(
              self.send,
              self.state,
              self.state.offset,
            )
            |> ignore;
          };
          if (self.state.percent >= 100) {
            self.send(UpdateInfo(Done));
          };
        }
      ),
    )
  | UpdateInfo(status) => ReasonReact.Update({...state, status})
  };

let typeOfIcon = t: Icon.iconType =>
  switch (t) {
  | Done => Check
  | Waiting => Circle
  };

let typeOfText = s =>
  switch (s) {
  | Done => {j|Pomyślnie pobrano wszystkie twoje utwory|j}
  | Waiting => {j|Trwa pobieranie ...|j}
  };

let component = ReasonReact.reducerComponent("FetchingScreen");

module Styles = {
  /*Open the Css module, so we can access the style properties below without prefixing them with Css.*/
  open Css;

  let wrap = style([maxWidth(px(200)), margin2(px(0), `auto)]);

  let progress = {
    "background": ReactDOMRe.Style.make(~fill="#444444", ()),
    "stroke": ReactDOMRe.Style.make(~stroke="#7500a8", ()),
    "text": ReactDOMRe.Style.make(~fill="#fff", ()),
    "path": ReactDOMRe.Style.make(~stroke="#7500a8", ()),
    "trail": ReactDOMRe.Style.make(~stroke="#444444", ()),
  };

  let subtitle =
    style([
      display(`flex),
      alignItems(`center),
      margin2(rem(2.0), `auto),
      width(px(240)),
      selector(
        "> i",
        [
          width(rem(2.0)),
          fontSize(rem(2.0)),
          marginRight(rem(1.0)),
          color(Theme.success),
        ],
      ),
      selector(
        "> p",
        [width(pct(70.0)), textAlign(`center), margin2(px(0), `auto)],
      ),
    ]);
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
          styles=Styles.progress
        />
      </div>
      <div>
        <div className=Styles.subtitle>
          {
            switch (self.state.status) {
            | Done =>
              <Icon
                iconType={typeOfIcon(self.state.status)}
                color=Theme.white
                size=1.0
              />

            | _ => ReasonReact.null
            }
          }
          <Text marginT=0.0 marginB=0.0>
            {ReasonReact.string(typeOfText(self.state.status))}
          </Text>
        </div>
        {
          switch (self.state.status) {
          | Done =>
            <Button
              text={j|Przejdź do kreatora|j}
              onClick=(_e => ReasonReact.Router.push("/create-playlists"))
              buttonType=Primary
            />
          | _ => ReasonReact.null
          }
        }
      </div>
    </div>,
};