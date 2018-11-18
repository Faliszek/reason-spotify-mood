let component = ReasonReact.statelessComponent("Icon");

module Styles = {
  /*Open the Css module, so we can access the style properties below without prefixing them with Css.*/
  open Css;
  let icon = (c, size) => style([color(c), fontSize(rem(size))]);
};

type iconType =
  | Spotify
  | Circle
  | Check
  | Plus
  | Minus
  | Trash
  | Save
  | Update
  | CloudUpload
  | Add
  | ArrowUp
  | ArrowDown;

let typeOfIcon = (t: iconType) =>
  switch (t) {
  | Spotify => "fab fa-spotify"
  | Circle => "zmdi zmdi-circle"
  | Check => "zmdi zmdi-check"
  | Plus => "zmdi zmdi-plus"
  | Minus => "zmdi zmdi-minus"
  | Trash => "zmdi zmdi-delete"
  | Save => "zmdi zmdi-check"
  | Update => "zmdi zmdi-refresh"
  | CloudUpload => "zmdi zmdi-upload"
  | Add => "zmdi zmdi-file-plus"
  | ArrowUp => "zmdi zmdi-chevron-up"
  | ArrowDown => "zmdi zmdi-chevron-down"
  };

let make = (~iconType, ~color=Theme.white, ~size=1.0, ~className=?, _children) => {
  ...component,
  render: _self =>
    <i
      className={
        Cn.make([
          typeOfIcon(iconType),
          Styles.icon(color, size),
          Cn.unpack(className),
        ])
      }
    />,
};