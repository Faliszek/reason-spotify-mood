let component = ReasonReact.statelessComponent("Icon");

let make = (~iconType, _children) => {
  ...component,
  render: _self => <i className={j|fab fa-$iconType|j} />,
};