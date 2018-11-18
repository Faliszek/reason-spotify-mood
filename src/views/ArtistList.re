let component = ReasonReact.statelessComponent("ArtistList");

open Domain;

module Styles = {
  open Css;
  let wrap = showed =>
    style([
      width(vw(100.0)),
      position(`absolute),
      transitionProperty("bottom"),
      transitionDuration(300),
      bottom(
        if (showed) {
          rem(5.0);
        } else {
          rem(0.0);
        },
      ),
    ]);

  let header =
    style([
      backgroundColor(Theme.gray),
      width(pct(90.0)),
      padding2(px(0), vw(5.0)),
      display(`flex),
      minHeight(rem(2.5)),
      justifyContent(`spaceBetween),
      alignItems(`center),
      cursor(`pointer),
      borderRadius(rem(0.5)),
    ]);

  let scroll = style([]);
  let listWrap = style([]);
};

let iconType = showed => if (showed) {Icon.ArrowDown} else {Icon.ArrowUp};
let make = (~artists: list(Domain.artist), ~showed, ~onToggle, _children) => {
  ...component,

  render: _self => {
    let arrow = showed => if (showed) {Icon.ArrowDown} else {Icon.ArrowUp};
    /* let artistList: list(Domain.artist) =
        Belt.List.map(artists, a => <Artist name={a.name} />)
       */
    <div className={Styles.wrap(showed)}>
      <div className=Styles.header onClick=onToggle>
        <Text marginT=0.0 marginB=0.0>
          {ReasonReact.string({j|Lista artystów|j})}
        </Text>
        <Icon iconType={arrow(showed)} />
      </div>
      <div className=Styles.scroll> <div className=Styles.listWrap /> </div>
    </div>;
  },
};