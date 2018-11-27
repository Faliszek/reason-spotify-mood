module Styles = {
  open Css;
  let wrap =
    style([
      margin2(rem(1.0), rem(0.0)),
      padding2(rem(0.25), rem(1.0)),
      display(`flex),
      alignItems(`center),
      transition(~duration=200, ~delay=0, "all"),
      borderRadius(rem(2.0)),
    ]);

  let text = style([]);
};

type state = {clicked: bool};

let component = ReasonReact.statelessComponent("Track");

let make = (~name, _children) => {
  ...component,
  render: _self =>
    <div>
      <div className=Styles.wrap>
        <div className=Styles.text> {ReasonReact.string(name)} </div>
      </div>
    </div>,
};