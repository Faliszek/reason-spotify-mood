let component = ReasonReact.statelessComponent("FetchingScreen");
let make = _children => {
  ...component,

  render: _self =>
    <div> <Title> {ReasonReact.string({j|0%|j})} </Title> </div>,
};