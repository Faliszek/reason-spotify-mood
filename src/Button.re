let component = ReasonReact.statelessComponent("Button");

let make = (~text, _children) => {
  ...component,
  render: _self => <button> {ReasonReact.string(text)} </button>,
};

/* Wrapping Reason component for JS world. Required only for JS import */