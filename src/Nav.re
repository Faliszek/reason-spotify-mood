let component = ReasonReact.statelessComponent("Nav");

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div> <div> <h2> {ReasonReact.string(message)} </h2> </div> </div>,
};

/* Wrapping Reason component for JS world. Required only for JS import */

[@bs.deriving abstract]
type jsProps = {message: string};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(~message=jsProps->messageGet, [||])
  );