let component = ReasonReact.statelessComponent("Playlist");
open Belt;

module Styles = {
  open Css;
  let wrap =
    style([
      width(pct(100.0)),
      display(`flex),
      alignItems(`center),
      justifyContent(`spaceBetween),
      marginBottom(rem(1.0)),
    ]);

  let btn = style([marginLeft(rem(1.0))]);
  let btnRow = style([flex(1), display(`flex), justifyContent(`center)]);
  let artistWrap =
    style([
      width(pct(100.0)),
      border(px(1), `dashed, Theme.lightGray),
      overflowY(`scroll),
      height(rem(12.5)),
      display(`flex),
      alignItems(`center),
      selector("> div", [maxHeight(pct(100.0))]),
    ]);
  let input = style([flex(4)]);
};

let renderBtn = (sended, order) =>
  switch (sended, order) {
  | (true, 1) =>
    <Button
      className=Styles.btn
      buttonType=Round
      icon=CloudUpload
      onClick=(_e => ())
    />

  | (true, 2) =>
    <Button
      className=Styles.btn
      buttonType=Round
      icon=Trash
      onClick=(_e => ())
    />

  | (false, 1) =>
    <Button
      className=Styles.btn
      buttonType=Round
      icon=Add
      onClick=(_e => ())
    />

  | (false, 2) =>
    <Button
      className=Styles.btn
      buttonType=Round
      icon=Minus
      onClick=(_e => ())
    />

  | _ => ReasonReact.null
  };

let make =
    (
      ~onPlayListNameChange,
      ~name,
      ~sended,
      ~onPlaceholderClick,
      ~tracks: array(Domain.track),
      _children,
    ) => {
  ...component,
  render: _self => {
    let tracksList = Array.map(tracks, t => <Track name={t.name} />);

    <div>
      <div className=Styles.wrap>
        <Input
          value=name
          onChange=onPlayListNameChange
          className=Styles.input
        />
        <div className=Styles.btnRow>
          {renderBtn(sended, 1)}
          {renderBtn(sended, 2)}
        </div>
      </div>
      <div className=Styles.artistWrap onClick={_e => onPlaceholderClick()}>
        {
          Array.length(tracks) == 0 ?
            <BigText>
              {
                ReasonReact.string(
                  {j|Kliknij wybranego artyste, a następnie w tą listę|j},
                )
              }
            </BigText> :
            <div> ...tracksList </div>
        }
      </div>
    </div>;
  },
};