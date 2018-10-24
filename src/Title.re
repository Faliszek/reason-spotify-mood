let component = ReasonReact.statelessComponent("Icon");

module Styles = {
  open Css;

  let title = style([color(Theme.white), fontSize(rem(2.0))]);
};

let make = (~className, children) => {
  ...component,
  render: _self =>
    <h1 className={Cn.make([Styles.title, className])}> ...children </h1>,
};