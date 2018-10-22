let component = ReasonReact.statelessComponent("Nav");

module Styles = {
  /*Open the Css module, so we can access the style properties below without prefixing them with Css.*/
  open Css;

  let card =
    style([
      display(flexBox),
      flexDirection(column),
      alignItems(stretch),
      backgroundColor(white),
      boxShadow(~y=px(3), ~blur=px(5), rgba(0, 0, 0, 0.3)),
    ]);

  let title = style([fontSize(rem(1.5))]);
  let actionButton = disabled =>
    style([
      background(disabled ? darkgray : white),
      color(black),
      border(px(1), solid, black),
      borderRadius(px(3)),
    ]);
};

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <IconBrand iconType=Spotify />
      <Title> {ReasonReact.string("Witaj w Spotify Mood")} </Title>
      <Text>
        {
          ReasonReact.string(
            "Aplikacja ta pozwoli ci na słuchanie twoich ulubionych utworów w zależnosci od twojego nastroju!"
          )
        }
      </Text>
      <Button text="Start" />
    </div>,
};