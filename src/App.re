let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self => <div> <Welcome /> </div>,
};

/* Wrapping Reason component for JS world. Required only for JS import */

[@bs.deriving abstract]
type jsProps = {message: string};

let default = ReasonReact.wrapReasonForJs(~component, _props => make([||]));