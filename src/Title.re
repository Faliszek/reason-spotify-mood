let component = ReasonReact.statelessComponent("Icon");

let make = children => {
  ...component,
  render: _self => <h1> ...children </h1>,
};