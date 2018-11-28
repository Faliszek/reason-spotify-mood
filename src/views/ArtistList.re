open Belt;

let component = ReasonReact.statelessComponent("ArtistList");

module Styles = {
  open Css;
  let wrap = showed =>
    style([width(vw(100.0)), position(`absolute), bottom(rem(0.0))]);

  let header =
    style([
      backgroundColor(Theme.gray),
      width(pct(90.0)),
      padding2(px(0), vw(5.0)),
      display(`flex),
      height(rem(2.5)),
      justifyContent(`spaceBetween),
      alignItems(`center),
      cursor(`pointer),
      borderRadius(rem(0.5)),
    ]);

  let scroll = showed =>
    style([
      overflowY(`scroll),
      transitionProperty("height"),
      transitionDuration(300),
      height(
        if (showed) {
          vh(30.0);
        } else {
          rem(0.0);
        },
      ),
    ]);
  let listWrap =
    style([
      padding2(rem(0.0), rem(1.0)),
      backgroundColor(Theme.lightBlack),
    ]);
};

let iconType = showed => if (showed) {Icon.ArrowDown} else {Icon.ArrowUp};
let make =
    (
      ~artists: array(Domain.artist),
      ~showed,
      ~onToggle,
      ~onArtistClick,
      ~selectedArtists,
      _children,
    ) => {
  ...component,

  render: _self => {
    let arrow = showed => if (showed) {Icon.ArrowDown} else {Icon.ArrowUp};
    let artistList =
      Array.map(artists, a =>
        <Artist
          id={a.id}
          name={a.name}
          imageSrc={a.image.url}
          clicked={Array.some(selectedArtists, s => s == a.id)}
          onArtistClick
        />
      );
    <div className={Styles.wrap(showed)}>
      <div className=Styles.header onClick=onToggle>
        <Text marginT=0.0 marginB=0.0>
          {ReasonReact.string({j|Lista artystów|j})}
        </Text>
        <Icon iconType={arrow(showed)} />
      </div>
      <div className={Styles.scroll(showed)}>
        <div className=Styles.listWrap> ...artistList </div>
      </div>
    </div>;
  },
};