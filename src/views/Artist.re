module Styles = {
  open Css;
  let wrap = clicked =>
    style([
      margin2(rem(1.0), rem(0.0)),
      padding2(rem(0.25), rem(1.0)),
      display(`flex),
      alignItems(`center),
      transition(~duration=200, ~delay=0, "all"),
      borderRadius(rem(2.0)),
      clicked ?
        boxShadow(
          ~x=px(0),
          ~y=px(0),
          ~blur=px(1),
          ~spread=px(3),
          Theme.lightViolet,
        ) :
        boxShadow(
          ~x=px(0),
          ~y=px(0),
          ~spread=px(0),
          ~blur=px(0),
          Theme.lightViolet,
        ),
    ]);
  let imgWrap =
    style([
      width(rem(3.0)),
      height(rem(3.0)),
      display(`flex),
      alignItems(`center),
      justifyContent(`center),
      selector(
        "> img",
        [
          maxWidth(pct(100.0)),
          maxHeight(pct(100.0)),
          display(`block),
          borderRadius(pct(50.0)),
          marginRight(rem(1.0)),
        ],
      ),
    ]);
  let text = style([]);
};

type state = {clicked: bool};

let component = ReasonReact.statelessComponent("Artist");

let make = (~id, ~name, ~imageSrc, ~onArtistClick, ~clicked, _children) => {
  ...component,
  render: _self =>
    <div onClick={_e => onArtistClick(id, !clicked)}>
      <div className={Styles.wrap(clicked)}>
        <div className=Styles.imgWrap> <img src=imageSrc /> </div>
        <div className=Styles.text> {ReasonReact.string(name)} </div>
      </div>
    </div>,
};