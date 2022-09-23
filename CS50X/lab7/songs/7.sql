SELECT AVG(songs.energy)
  FROM songs, artists
 WHERE artists.name = "Drake"
   AND artists.id = songs.artist_id