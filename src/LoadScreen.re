let component = ReasonReact.statelessComponent("Icon");

let make = _children => {
  ...component,
  render: _self => <div> {ReasonReact.string("Loading ...")} </div>,
};