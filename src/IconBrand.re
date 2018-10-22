let component = ReasonReact.statelessComponent("Icon");

type iconType =
  | Spotify;

let typeOfIcon = (t: iconType) =>
  switch (t) {
  | Spotify => "fab fa-spotify"
  };

let make = (~iconType: iconType, _children) => {
  ...component,
  render: _self => <div> <i className={typeOfIcon(iconType)} /> </div>,
};