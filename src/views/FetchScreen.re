let component = ReasonReact.statelessComponent("FetchScreen");

let make = _children => {
  ...component,
  render: _self => <div> {ReasonReact.string("Loading ...")} </div>,
};