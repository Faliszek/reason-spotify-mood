open Belt;
open Domain;

type action =
  | UpdateTracks(list(track))
  | InitPlaylist
  | UpdatePlaylistName(string, int)
  | ToggleArtistList;

type playlist = {
  uid: int,
  name: string,
  description: string,
  public: bool,
  sended: bool,
  loading: bool,
};

let initialedPlaylist = uid => {
  uid,
  name: "",
  description: "",
  public: false,
  sended: false,
  loading: false,
};

type state = {
  countList: int,
  tracks: list(track),
  playlists: list(playlist),
  showList: bool,
};

let initialState = () => {
  countList: 0,
  tracks: [],
  playlists: [],
  showList: false,
};

let reducer = (action, state) =>
  switch (action) {
  | UpdateTracks(tracks) => ReasonReact.Update({...state, tracks})
  | InitPlaylist =>
    ReasonReact.Update({
      ...state,
      playlists:
        List.add(state.playlists, initialedPlaylist(state.countList)),
      countList: state.countList + 1,
    })
  | UpdatePlaylistName(name, uid) =>
    let playlist = List.getBy(state.playlists, p => p.uid === uid);
    let updatedPlaylist =
      switch (playlist) {
      | Some(p) => {...p, name}
      | _ => initialedPlaylist(state.countList)
      };

    ReasonReact.Update({
      ...state,
      playlists:
        Belt.List.map(state.playlists, p =>
          p.uid === uid ? updatedPlaylist : p
        ),
    });
  | ToggleArtistList =>
    ReasonReact.Update({...state, showList: !state.showList})
  | _ => ReasonReact.NoUpdate
  };

let component = ReasonReact.reducerComponent("PlaylistCreator");

module Styles = {
  /*Open the Css module, so we can access the style properties below without prefixing them with Css.*/
  open Css;
  let wrap = style([padding2(vh(2.0), vw(5.0)), width(vw(90.0))]);
  let titleWrap =
    style([
      display(`flex),
      height(px(48)),
      width(pct(100.0)),
      justifyContent(`spaceAround),
      alignItems(`center),
      marginBottom(rem(1.5)),
    ]);
};
let make = _children => {
  ...component,
  reducer,
  initialState,
  didMount: self => {
    open LocalStorage;

    let tracks =
      switch (Dom.Storage.(localStorage |> getItem(storeTracks))) {
      | None => []
      | Some(tracks) => unsafeJsonParse(tracks)
      };
    self.send(UpdateTracks(tracks));
  },

  render: self => {
    let {tracks, playlists} = self.state;
    let playlistsItems =
      Belt.List.map(playlists, p =>
        <Playlist
          name={p.name}
          sended={p.sended}
          onPlayListNameChange={
            e =>
              self.send(
                UpdatePlaylistName(ReactEvent.Form.target(e)##value, p.uid),
              )
          }
        />
      )
      ->List.toArray
      ->Array.reverse
      ->ReasonReact.array;

    Js.log(tracks);
    let artists =
      Belt.List.map(
        tracks,
        t => {
          Js.log(t);
          t.artist;
        },
      );
    Js.log(artists);

    <div>
      <div className=Styles.wrap>
        <div className=Styles.titleWrap>
          <Text marginB=0.0 marginT=0.0 fontS=1.5>
            {ReasonReact.string("Dodaj Playliste")}
          </Text>
          <Button
            buttonType=Round
            onClick={_e => self.send(InitPlaylist)}
            icon=Plus
          />
        </div>
        playlistsItems
      </div>
      <ArtistList
        artists
        showed={self.state.showList}
        onToggle={_e => self.send(ToggleArtistList)}
      />
    </div>;
  },
};