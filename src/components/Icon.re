let component = ReasonReact.statelessComponent("Icon");

module Styles = {
  /*Open the Css module, so we can access the style properties below without prefixing them with Css.*/
  open Css;
  let icon = (c, size) => style([color(c), fontSize(rem(size))]);
};

type iconType =
  | Spotify;

let typeOfIcon = (t: iconType) =>
  switch (t) {
  | Spotify => "fab fa-spotify"
  };

let make = (~iconType, ~color, ~size, ~className, _children) => {
  ...component,
  render: _self =>
    <i
      className={
        Cn.make([typeOfIcon(iconType), Styles.icon(color, size), className])
      }
    />,
};