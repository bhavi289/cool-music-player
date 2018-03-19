Cool Music Player

Features 
		Account based login:
			You can create an account from where you can get personalised feed.

		Top 10 songs:
			See what's going hot around the world in this top 10 song list.

		Latest:
			See what's new in world of music.

		Your favorite playist(automatically generated):
			Based on what you play the most we create a playlist for you.

		Suggestions for you:
			Based on your plays we find up more songs for you to enhance your listening experience.
			`
		Search:
			Search our huge database of songs and you can refine you searches to search by song name , artist , album or genre.

	Existence of SuperUser/ADMIN:
		Admin is a privilage not an account.
		Only superuser has the privilege to 
			1> add songs in our huge song database.
			2> delete songs in our huge song database.
			3> modify songs in our huge song database.



The Backend Stuff
	1> Our mini application makes a seperate file for every user in which the first line is the password and rest contains the data of the songs you play.
	2> In our song database,each line is of the form Song Name^Artist^Album^Genre^ #number_of_times_played.
	3>We use linked list to load:

		1>Facilities
		2>For our top 10 songs
		3>Favorite Playist
		4>Suggestions
		5>For all songs (used by admin) to add,delete or modify song's data.
	4> We have used a linked list mainly because all the list of songs are short lists (top ten has 10 songs, latest has 15 songs etc.)
	5> Everytime a user plays a song the count of the song increases in his personal file and also increases in the file which has count of all the users(global.txt).
	6> This count is used to give the favourites of the user( most played at the top )
		This is also used to give the "Top Ten" which is the most played songs by all the users.

