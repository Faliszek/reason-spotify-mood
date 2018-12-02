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
      selector(
        "> div",
        [
          maxHeight(pct(100.0)),
          margin2(px(0), `auto),
          width(pct(95.0)),
        ],
      ),
    ]);
  let input = style([flex(4)]);
};

module Api = Playlist_Api;

let renderBtn = (sended, order, playlist, onCreate, onRemove) =>
  switch (sended, order) {
  | (false, 1) =>
    <Button
      className=Styles.btn
      buttonType=Round
      icon=Add
      onClick=(
        _e =>
          Api.createPlaylist("/playlist", playlist)
          |> RePromise.andThen(
               fun
               | Result.Ok(playlistId) => onCreate(playlist.uid, playlistId)
               | Result.Error(_) => (),
             )
          |> ignore
      )
    />

  | (false, 2) =>
    <Button
      className=Styles.btn
      buttonType=Round
      icon=Minus
      onClick=(_e => onRemove(playlist.uid))
    />

  | (true, 1) =>
    <Button
      className=Styles.btn
      buttonType=Round
      icon=CloudUpload
      onClick=(
        _e =>
          Api.updatePlaylist("/playlist", playlist.id, playlist)
          |> RePromise.andThen(
               fun
               | Result.Ok(_) => Js.log("work")
               | Result.Error(_) => (),
             )
          |> ignore
      )
    />

  | _ => ReasonReact.null
  };

let make =
    (
      ~onPlayListNameChange,
      ~name,
      ~playlist,
      ~sended,
      ~onPlaceholderClick,
      ~onTrackRemove,
      ~onCreate,
      ~onRemove,
      ~tracks: array(Domain.track),
      _children,
    ) => {
  ...component,
  render: _self => {
    let tracksList =
      Array.mapWithIndex(tracks, (index, t) =>
        <Track
          key={t.id}
          id={t.id}
          number={index + 1}
          name={t.name}
          artistName={t.artist.name}
          onRemove={() => onTrackRemove(t.id)}
        />
      );

    let emptyArray = Array.length(tracks) == 0;

    <div>
      <div className=Styles.wrap>
        <Input
          value=name
          onChange=onPlayListNameChange
          className=Styles.input
        />
        <div className=Styles.btnRow>
          {renderBtn(sended, 1, playlist, onCreate, onRemove)}
          {renderBtn(sended, 2, playlist, onCreate, onRemove)}
        </div>
      </div>
      {
        sended ?
          <div
            className=Styles.artistWrap
            onClick={_e => emptyArray ? onPlaceholderClick() : ()}>
            {
              emptyArray ?
                <BigText>
                  {
                    ReasonReact.string(
                      {j|Kliknij wybranego artyste, a następnie w tą listę|j},
                    )
                  }
                </BigText> :
                <div> ...tracksList </div>
            }
          </div> :
          ReasonReact.null
      }
    </div>;
  },
};