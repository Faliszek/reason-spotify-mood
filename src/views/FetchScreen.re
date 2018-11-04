type state = {fetching: bool};

let initialState = () => {fetching: false};

type action =
  | StartFetching
  | Noop;

let reducer = (action, _state) =>
  switch (action) {
  | StartFetching => ReasonReact.Update({fetching: true})
  | Noop => ReasonReact.NoUpdate
  };

let component = ReasonReact.reducerComponent("FetchScreen");

module Styles = {
  /*Open the Css module, so we can access the style properties below without prefixing them with Css.*/
  open Css;

  let entered =
    style([
      marginTop(rem(2.0)),
      marginBottom(rem(1.0)),
      marginLeft(auto),
      marginRight(auto),
    ]);
};

let make = _children => {
  ...component,
  reducer,
  initialState,
  didMount: _self => Api.getUrlParams(),
  render: self =>
    <div className=Styled.view>
      <div className=Styled.wrap>
        {
          self.state.fetching ?
            <FetchingScreen /> :
            <InitialFetchingScreen
              onStartFetching={_e => self.send(StartFetching)}
            />
        }
      </div>
    </div>,
};