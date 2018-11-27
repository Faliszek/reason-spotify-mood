open Belt;
open Domain;

type action =
  | UpdateTracks(array(track))
  | InitPlaylist
  | UpdatePlaylistName(string, int)
  | ToggleArtistList
  | OnArtistClick(string, bool)
  | AddArtistToPlaylist(int);

type playlist = {
  uid: int,
  name: string,
  description: string,
  public: bool,
  sended: bool,
  loading: bool,
  tracks: array(track),
};

let initialedPlaylist = uid => {
  uid,
  name: "",
  description: "",
  public: false,
  sended: false,
  loading: false,
  tracks: [||],
};

type state = {
  countList: int,
  tracks: array(track),
  playlists: list(playlist),
  showList: bool,
  selectedArtists: array(string),
};

let initialState = () => {
  countList: 0,
  tracks: [||],
  playlists: [],
  showList: false,
  selectedArtists: [||],
};

let setSelectedArtists = (artists: array(string), id, clicked) =>
  if (clicked) {
    Array.concat(artists, [|id|]);
  } else {
    Array.keep(artists, aId => aId != id);
  };

let addTracksToPlaylistByArtist = (playlistId, playlists, artistIds, tracks) => {
  Js.log3(playlistId, List.toArray(playlists), artistIds);
  let pickedTracks =
    Array.keep(tracks, t => Array.some(artistIds, a => a == t.artist.id));
  let arrayPlaylists = List.toArray(playlists);

  let newPlaylist =
    Array.keep(arrayPlaylists, p => p.uid == playlistId)->Array.get(0);

  let updatedArrayPlaylists =
    switch (newPlaylist) {
    | Some(playlist) =>
      Array.map(arrayPlaylists, p =>
        p.uid === playlistId ? {...playlist, tracks: pickedTracks} : p
      )
    | None => arrayPlaylists
    };

  List.fromArray(updatedArrayPlaylists);
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
  | OnArtistClick(id, clicked) =>
    ReasonReact.Update({
      ...state,
      selectedArtists: setSelectedArtists(state.selectedArtists, id, clicked),
    })
  | AddArtistToPlaylist(playlistId) =>
    ReasonReact.Update({
      ...state,
      selectedArtists: [||],
      playlists:
        addTracksToPlaylistByArtist(
          playlistId,
          state.playlists,
          state.selectedArtists,
          state.tracks,
        ),
    })
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
      | None => [||]
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
          onPlaceholderClick={_e => self.send(AddArtistToPlaylist(p.uid))}
          tracks={p.tracks}
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
    let artists = Array.map(tracks, t => t.artist);
    let artistsFiltered: array(artist) =
      Array.reduce(
        artists,
        [||],
        (acc: array(artist), a) => {
          let findId = Array.some(acc, f => f.id == a.id);
          !findId ? Array.concat(acc, [|a|]) : acc;
        },
      );
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
        artists=artistsFiltered
        selectedArtists={self.state.selectedArtists}
        showed={self.state.showList}
        onToggle={_e => self.send(ToggleArtistList)}
        onArtistClick={
          (id, clicked) => self.send(OnArtistClick(id, clicked))
        }
      />
    </div>;
  },
};