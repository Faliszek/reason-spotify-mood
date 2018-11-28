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
      justifyContent(`spaceBetween),
    ]);

  let text = style([fontSize(rem(0.875))]);

  let smallText = style([fontSize(rem(0.75)), opacity(0.75)]);
  let number = style([fontSize(rem(0.75))]);

  let textWrap =
    style([display(`flex), flexDirection(`column), marginLeft(rem(1.0))]);

  let textAndNumber = style([display(`flex), alignItems(`center)]);
};

type state = {clicked: bool};

let component = ReasonReact.statelessComponent("Track");

let make = (~id, ~number, ~name, ~artistName, ~onRemove, _children) => {
  ...component,
  render: _self =>
    <div>
      <div className=Styles.wrap>
        <div className=Styles.textAndNumber>
          <span className=Styles.number>
            {ReasonReact.string(Js.Int.toString(number) ++ ". ")}
          </span>
          <div className=Styles.textWrap>
            <div className=Styles.text> {ReasonReact.string(name)} </div>
            <div className=Styles.smallText>
              {ReasonReact.string(artistName)}
            </div>
          </div>
        </div>
        <span
          onClick={
            e => {
              onRemove();
              ReactEvent.Synthetic.stopPropagation(e);
            }
          }>
          <Icon iconType=Trash />
        </span>
      </div>
    </div>,
};