let component = ReasonReact.statelessComponent("InitialScreen");
let make = (~onStartFetching, _children) => {
  let click = _e => onStartFetching();
  {
    ...component,

    render: _self =>
      <div>
        <Title>
          {ReasonReact.string({j|Pomyślnie zalogowano do konta Spotify!|j})}
        </Title>
        <Text>
          {
            ReasonReact.string(
              {j|Przejście dalej spowoduję połączenie się z API spotify w celu pobrania twoich ulubionych utworów|j},
            )
          }
        </Text>
        <Button
          buttonType=Primary
          text="Rozpocznij pobieranie"
          onClick=click
        />
      </div>,
  };
};