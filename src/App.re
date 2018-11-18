type route =
  | Welcome
  | FetchScreen
  | PlaylistCreator;

type state = {route};

type action =
  | ChangeRoute(route);

let reducer = (action, _state) =>
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | ["fetching"] => FetchScreen
  | ["create-playlists"] => PlaylistCreator
  | _ => Welcome
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {route: Welcome},
  reducer,
  didMount: self => {
    ReasonReact.Router.dangerouslyGetInitialUrl()
    ->mapUrlToRoute
    ->ChangeRoute
    ->(self.send);

    let watchId =
      ReasonReact.Router.watchUrl(url =>
        self.send(ChangeRoute(url->mapUrlToRoute))
      );

    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watchId));
  },
  render: self =>
    switch (self.state.route) {
    | Welcome => <Welcome />
    | FetchScreen => <FetchScreen />
    | PlaylistCreator => <PlaylistCreator />
    },
};

/* Wrapping Reason component for JS world. Required only for JS import */

[@bs.deriving abstract]
type jsProps = {message: string};

let default = ReasonReact.wrapReasonForJs(~component, _props => make([||]));