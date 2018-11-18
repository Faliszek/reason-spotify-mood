let component = ReasonReact.statelessComponent("Artist");

module Styles = {
  open Css;
  let wrap = style([]);
  let imgWrap = style([]);
  let text = style([]);
};
let make = (~name, _children) => {
  ...component,
  render: _self =>
    <div>
      <div className=Styles.wrap>
        <div className=Styles.imgWrap> <img src="" /> </div>
        <div className=Styles.text> name </div>
      </div>
    </div>,
};