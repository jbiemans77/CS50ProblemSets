SELECT songs.name
  FROM songs, artists
 WHERE artists.name = "Post Malone"
   AND artists.id = songs.artist_id