let component = ReasonReact.statelessComponent("Icon");

let make = (~iconType, _children) => {
  ...component,
  render: _self => <i className={j|fas fa-$iconType|j} />,
};