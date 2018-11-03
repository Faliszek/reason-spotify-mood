let component = ReasonReact.statelessComponent("Icon");

module Styles = {
  open Css;

  let text =
    style([
      color(Theme.white),
      fontSize(rem(1.0)),
      marginTop(rem(2.0)),
      marginBottom(rem(2.5)),
    ]);
};
let make = (~className="", children) => {
  ...component,
  render: _self =>
    <p className={Cn.make([Styles.text, className])}> ...children </p>,
};