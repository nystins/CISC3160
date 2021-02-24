import csv
import operator

# function for getting the unique artist list
def unique(list):
  list_of_unique_artist = []
  # insert the list to the set
  list_set = set(list)
  for unique_list in list_set:
    list_of_unique_artist.append(unique_list)
  return list_of_unique_artist

with open('regional-global-weekly-latest.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    artist_list = []
    for row in csv_reader:
        if line_count == 0:
          line_count += 1
        else:
          # csv file heading
          # row[0] = position, row[1] = Track Name, row[2] = Artist Name, row[3] = Streams, row[4] = URL
          # get artist name
          artist_list.append(row[2])
          # get the average stream per song
          print(row[1], int(row[3]) / 7)
          line_count += 1
    print("----------------------Unique artist name-----------------------")
    print(unique(artist_list))
