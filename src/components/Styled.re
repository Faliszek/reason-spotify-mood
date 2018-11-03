open Css;

let view =
  style([
    display(flexBox),
    height(vh(100.00)),
    width(vw(100.00)),
    alignItems(center),
    justifyContent(center),
    backgroundColor(Theme.lightBlack),
  ]);

let wrap = style([maxWidth(px(320)), textAlign(center)]);