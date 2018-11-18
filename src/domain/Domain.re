type image = {
  width: int,
  url: string,
  height: int,
};
type album = {
  id: string,
  name: string,
};
type artist = {
  id: string,
  name: string,
  image,
};

type track = {
  id: string,
  name: string,
  url: string,
  uri: string,
  duration_ms: int,
  genres: array(string),
  image,
  album,
  artist,
};

type artistWithTrackUri = {
  id: string,
  name: string,
  image,
  tracksUri: string,
};