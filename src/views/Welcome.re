let component = ReasonReact.statelessComponent("Nav");

open Theme;

module Styles = {
  /*Open the Css module, so we can access the style properties below without prefixing them with Css.*/
  open Css;

  let icon =
    style([
      marginTop(rem(2.0)),
      marginBottom(rem(1.0)),
      marginLeft(auto),
      marginRight(auto),
    ]);
};

let redirectToLoginPage = () => Api.redirect(Api.url ++ "/login");

let make = _children => {
  ...component,
  didMount: _self => [%bs.raw {| console.log(process.env) |}],
  render: _self =>
    <div className=Styled.view>
      <div className=Styled.wrap>
        <Icon className=Styles.icon iconType=Spotify color=violet size=6.0 />
        <Title> {ReasonReact.string("Witaj w Spotify Mood")} </Title>
        <Text>
          {
            ReasonReact.string(
              {j|Aplikacja ta pozwoli ci na słuchanie twoich ulubionych utworów w zależnosci od twojego nastroju!|j},
            )
          }
        </Text>
        <Text>
          {
            ReasonReact.string(
              {j|Po kliknięciu start zostaniesz przeniesiony do autoryzacji z twoim kontem spotify|j},
            )
          }
        </Text>
        <Button
          buttonType=Primary
          text="Start"
          onClick={_e => redirectToLoginPage()}
        />
      </div>
    </div>,
};