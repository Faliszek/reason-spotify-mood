let component = ReasonReact.statelessComponent("BigText");

module Styles = {
  open Css;

  let text = (~marginT, ~marginB) =>
    style([
      color(Theme.lightGray),
      fontSize(rem(1.2)),
      marginTop(rem(marginT)),
      marginBottom(rem(marginB)),
      textAlign(`center),
    ]);
};

let make = (~className="", ~marginT=2.0, ~marginB=2.0, children) => {
  ...component,
  render: _self =>
    <p className={Cn.make([Styles.text(marginT, marginB), className])}>
      ...children
    </p>,
};