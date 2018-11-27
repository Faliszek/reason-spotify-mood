let component = ReasonReact.statelessComponent("Input");

module Styles = {
  open Css;

  let wrap =
    style([
      backgroundColor(`transparent),
      borderLeftStyle(`none),
      borderRightStyle(`none),
      borderTopStyle(`none),
      borderBottom(px(1), `solid, Theme.white),
      padding2(rem(0.5), rem(1.0)),
      color(Theme.white),
      outlineStyle(`none),
      fontSize(rem(1.0)),
    ]);
};

let make = (~value, ~onChange, ~className=?, _children) => {
  ...component,
  render: _self =>
    <input
      className={Cn.make([Styles.wrap, Cn.unpack(className)])}
      value
      onChange
    />,
};