let component = ReasonReact.statelessComponent("Nav");

open Theme;

module Styles = {
  /*Open the Css module, so we can access the style properties below without prefixing them with Css.*/
  open Css;

  let view =
    style([
      display(flexBox),
      height(vh(100.00)),
      width(vw(100.00)),
      alignItems(center),
      justifyContent(center),
      backgroundColor(Theme.lightBlack),
    ]);

  let wrap = style([maxWidth(px(320)), textAlign(center)]);

  let title = style([marginTop(rem(1.0)), marginBottom(rem(2.5))]);
  let text = style([marginTop(rem(1.0)), marginBottom(rem(1.5))]);
  let actionButton = disabled =>
    style([
      background(disabled ? darkgray : white),
      color(black),
      border(px(1), solid, black),
      borderRadius(px(3)),
    ]);

  let icon =
    style([
      marginTop(rem(1.0)),
      marginBottom(rem(1.0)),
      marginLeft(auto),
      marginRight(auto),
    ]);
};

let make = _children => {
  ...component,
  render: _self =>
    <div className=Styles.view>
      <div className=Styles.wrap>
        <Icon className=Styles.icon iconType=Spotify color=violet size=6.0 />
        <Title className=Styles.title>
          {ReasonReact.string("Witaj w Spotify Mood")}
        </Title>
        <Text className=Styles.text>
          {
            ReasonReact.string(
              {j|Aplikacja ta pozwoli ci na słuchanie twoich ulubionych utworów w zależnosci od twojego nastroju!|j},
            )
          }
        </Text>
        <Button text="Start" />
      </div>
    </div>,
};