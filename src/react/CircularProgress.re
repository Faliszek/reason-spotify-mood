type styles = {
  .
  "background": ReactDOMRe.Style.t,
  "text": ReactDOMRe.Style.t,
  "stroke": ReactDOMRe.Style.t,
  "path": ReactDOMRe.Style.t,
  "trail": ReactDOMRe.Style.t,
};

[@bs.deriving abstract]
type jsProps = {
  percentage: int,
  text: ReasonReact.reactElement,
  strokeWidth: int,
  backgroundPadding: int,
  styles,
};

[@bs.module "react-circular-progressbar"]
external component: ReasonReact.reactClass = "default";

let make =
    (~percentage, ~text, ~styles, ~strokeWidth, ~backgroundPadding, _children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=component,
    ~props=
      jsProps(~percentage, ~text, ~strokeWidth, ~backgroundPadding, ~styles),
    [||],
  );