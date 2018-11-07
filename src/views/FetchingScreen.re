open Belt;

type state = {percent: int};

type action =
  | SetPercent(int)
  | Noop;

let reducer = (action, _state) =>
  switch (action) {
  | SetPercent(percent) => ReasonReact.Update({percent: percent})
  | Noop => ReasonReact.NoUpdate
  };
let initialState = () => {percent: 0};

let startOffset = "1";
let limit = "50";

let saveAccessData = () => {
  let params = Api.getUrlParams();
  Js.log(params);
  LocalStorage.save(params);
  ();
};

let fetchTracks = () =>
  Api.get("/tracks?" ++ "limit=" ++ limit ++ "&" ++ "offset=" ++ startOffset);
/* |> RePromise.andThen(Result.map(_, decoder)); */

let initialFetchTracks = () =>
  fetchTracks()
  |> RePromise.andThen(
       fun
       | Result.Ok(percent) => Js.log(percent)
       | Result.Error(_) => (),
     );

let renderPercent = p => ReasonReact.string(Js.Int.toString(p) ++ "%");

let component = ReasonReact.reducerComponent("FetchingScreen");

let make = _children => {
  ...component,
  reducer,
  initialState,
  didMount: _self => {
    saveAccessData();
    initialFetchTracks();
    ();
  },

  render: self =>
    <div> <Title> {renderPercent(self.state.percent)} </Title> </div>,
};