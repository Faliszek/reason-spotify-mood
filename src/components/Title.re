let component = ReasonReact.statelessComponent("Title");

module Styles = {
  open Css;

  let title =
    style([
      color(Theme.white),
      fontSize(rem(2.0)),
      marginTop(rem(1.5)),
      marginBottom(rem(2.5)),
    ]);
};

let make = (~className="", children) => {
  ...component,
  render: _self =>
    <h1 className={Cn.make([Styles.title, className])}> ...children </h1>,
};