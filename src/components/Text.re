let component = ReasonReact.statelessComponent("Text");

module Styles = {
  open Css;

  let text = (~marginT, ~marginB, ~fontS) =>
    style([
      color(Theme.white),
      fontSize(rem(fontS)),
      marginTop(rem(marginT)),
      marginBottom(rem(marginB)),
    ]);
};

let make = (~className="", ~marginT=1.0, ~marginB=2.5, ~fontS=1.0, children) => {
  ...component,
  render: _self =>
    <p
      className={Cn.make([Styles.text(marginT, marginB, fontS), className])}>
      ...children
    </p>,
};