let component = ReasonReact.statelessComponent("Button");
type buttonType =
  | Primary
  | Round;

module Styles = {
  open Css;
  let button =
    style([
      display(flexBox),
      alignItems(center),
      justifyContent(center),
      borderStyle(none),
      textTransform(uppercase),
      fontWeight(700),
      transition(~duration=200, ~delay=0, "all"),
      hover([backgroundColor(Theme.lightViolet), cursor(`pointer)]),
      outlineStyle(none),
    ]);

  let buttonSize = buttonType =>
    switch (buttonType) {
    | Primary =>
      style([
        minHeight(px(50)),
        minWidth(px(320)),
        borderRadius(px(32)),
        fontSize(rem(1.00)),
      ])

    | Round =>
      style([
        height(px(36)),
        width(px(36)),
        borderRadius(pct(50.0)),
        fontSize(rem(2.00)),
      ])
    };
  let buttonColors = buttonType =>
    switch (buttonType) {
    | Primary => style([background(Theme.violet), color(Theme.white)])
    | Round => style([background(Theme.violet), color(Theme.white)])
    };
};

let make = (~text=?, ~buttonType, ~onClick, ~icon=?, ~className=?, _children) => {
  ...component,
  render: _self =>
    <button
      onClick
      className={
        Cn.make([
          Styles.buttonColors(buttonType),
          Styles.buttonSize(buttonType),
          Styles.button,
          Cn.unpack(className),
        ])
      }>
      {
        switch (icon) {
        | Some(icon) => <Icon iconType=icon />
        | _ => ReasonReact.null
        }
      }
      {
        switch (text) {
        | Some(text) => ReasonReact.string(text)
        | _ => ReasonReact.null
        }
      }
    </button>,
};

/* Wrapping Reason component for JS world. Required only for JS import */