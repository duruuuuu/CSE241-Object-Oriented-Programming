import java.util.ArrayList;

/**
 * Player class represents a player that observers a list of media entries that are PLAYABLE
 */
public class Player implements Observer {

  // Represents the index of the currently playing media entry
  private int currentIndex = 0;
  private ArrayList<MediaEntry> playList = new ArrayList<MediaEntry>();

  /**
   * Constructs a new default Player object
   */
  public Player() {
    // Intentionally left empty
  }

  @Override
  public void add_message(ArrayList<MediaEntry> ogEntries) {
    playList.clear();
    for (MediaEntry entry : ogEntries) {
      if (entry instanceof Playable) playList.add(entry);
    }
  }

  @Override
  public void remove_message(ArrayList<MediaEntry> ogEntries) {
    playList.clear();
    for (MediaEntry entry : ogEntries) {
      if (entry instanceof Playable) playList.add(entry);
    }
    //If the last entry is removed, set the current playing to the 2nd last
    if (currentIndex == playList.size()) currentIndex -= 1;
  }

  @Override
  public void show_list() {
    System.out.println("PLAYLIST:");
    for (MediaEntry entry : playList) System.out.println(entry.get_name());
  }

  @Override
  public void next(String type) {
    if (playList.isEmpty()) {
      System.out.println("Play list is empty! (next)");
      return;
    }

    int startIndex = currentIndex + 1;
    int endIndex = playList.size();

    if (type.equals("audio")) currentIndex =
      find_next_index(
        startIndex,
        endIndex,
        Playable.class,
        NonVisual.class
      ); else if (type.equals("video")) currentIndex =
      find_next_index(startIndex, endIndex, Playable.class, Visual.class);
  }

  /**
   * {@summary} Finds the next media entry of the same type as given in the parameter
   * @param startI Starting index
   * @param endI Ending index
   * @param playable Playable interface
   * @param type Visual/Non-Visual interface
   * @return array index of the next media entry
   */
  private int find_next_index(
    int startI,
    int endI,
    Class<?> playable,
    Class<?> type
  ) {
    int size = playList.size();
    for (int i = startI;; i++) {
      if (i >= endI) {
        // Wrap around to the beginning of the list
        i = i % size;
        continue;
      }
      if (
        playable.isInstance(playList.get(i)) && type.isInstance(playList.get(i))
      ) {
        return i;
      }
    }
  }

  @Override
  public void previous(String type) {
    if (playList.isEmpty()) {
      System.out.println("Play list is empty! (Previous command)");
      return;
    }

    int startIndex = currentIndex - 1;
    int endIndex = -1;

    if (type.equals("audio")) {
      currentIndex =
        findPreviousIndex(
          startIndex,
          endIndex,
          Playable.class,
          NonVisual.class
        );
    } else if (type.equals("video")) {
      currentIndex =
        findPreviousIndex(startIndex, endIndex, Playable.class, Visual.class);
    }
  }

  /**
   * {@summary} Finds the previous media entry of the same type as given in the parameter
   * @param startI Starting index
   * @param endI Ending index
   * @param playable Playable interface
   * @param type Visual/Non-Visual interface
   * @return array index of the previous media entry
   */
  private int findPreviousIndex(
    int startIndex,
    int endIndex,
    Class<?> playable,
    Class<?> type
  ) {
    int size = playList.size();
    int i = startIndex;
    do {
      if (i < 0) {
        // Wrap around to the end of the list
        i = size - 1;
        continue;
      }
      if (
        playable.isInstance(playList.get(i)) && type.isInstance(playList.get(i))
      ) {
        return i;
      }
      i--;
    } while (i != startIndex);

    return -1;
  }

  /**
   * Finds the item currently being played
   * @return Playable object currently being played
   */
  public Playable currently_playing() {
    int i = 0;
    for (MediaEntry entry : playList) {
      if (i == currentIndex) return ((Playable) entry);
      i++;
    }
    return null;
  }
}
