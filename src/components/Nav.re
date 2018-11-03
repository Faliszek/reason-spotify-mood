let component = ReasonReact.statelessComponent("Nav");

let make = _children => {
  ...component,
  render: _self => <nav> {ReasonReact.string("Nav")} </nav>,
};

/* Wrapping Reason component for JS world. Required only for JS import */