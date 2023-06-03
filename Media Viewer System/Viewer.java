import java.util.ArrayList;

/**
 * Viewer class represents a displayer of a list of media entries that are VISUAL
 */
public class Viewer implements Observer {

  // Represents the index of the currently viewing media entry
  private int currentIndex = 0;
  private ArrayList<MediaEntry> viewList = new ArrayList<MediaEntry>();

  /**
   * Constructs a new default Viewer object
   */
  public Viewer() {
    // Intentionally left empty
  }

  @Override
  public void add_message(ArrayList<MediaEntry> ogEntries) {
    viewList.clear();
    for (MediaEntry entry : ogEntries) {
      if (entry instanceof NonPlayable) viewList.add(entry);
    }
  }

  @Override
  public void remove_message(ArrayList<MediaEntry> ogEntries) {
    viewList.clear();
    for (MediaEntry entry : ogEntries) {
      if (entry instanceof NonPlayable) viewList.add(entry);
    }
    //If the last entry is removed, set the current viewing to the 2nd last
    if (currentIndex == viewList.size()) currentIndex -= 1;
  }

  @Override
  public void show_list() {
    System.out.println("VIEWING LIST:");
    for (MediaEntry entry : viewList) System.out.println(entry.get_name());
  }

  @Override
  public void next(String type) {
    if (viewList.isEmpty()) {
      System.out.println("Viewing list is empty! (next)");
      return;
    }
    int startIndex = currentIndex + 1;
    int endIndex = viewList.size();

    if (type.equals("text")) currentIndex =
      find_next_index(
        startIndex,
        endIndex,
        NonPlayable.class,
        Text.class
      ); else if (type.equals("image")) currentIndex =
      find_next_index(startIndex, endIndex, NonPlayable.class, Image.class);
  }

  /**
   * {@summary} Finds the next media entry of the same type as given in the parameter
   * @param startI Starting index
   * @param endI Ending index
   * @param visual Visual interface
   * @param type Visual/Non-Visual interface
   * @return array index of the next media entry
   */
  private int find_next_index(
    int startI,
    int endI,
    Class<?> nonPlay,
    Class<?> type
  ) {
    int size = viewList.size();
    for (int i = startI;; i++) {
      if (i >= endI) {
        // Wrap around to the beginning of the list
        i = i % size;
        continue;
      }
      if (
        nonPlay.isInstance(viewList.get(i)) && type.isInstance(viewList.get(i))
      ) {
        return i;
      }
    }
  }

  @Override
  public void previous(String type) {
    if (viewList.isEmpty()) {
      System.out.println("Viewing list is empty! (Previous)");
      return;
    }

    int startIndex = currentIndex - 1;
    int endIndex = -1;
    if (currentIndex == 0) {
      currentIndex = viewList.size();
    }

    if (type.equals("image")) {
      currentIndex =
        findPreviousIndex(startIndex, endIndex, NonPlayable.class, Image.class);
    } else if (type.equals("text")) {
      currentIndex =
        findPreviousIndex(startIndex, endIndex, NonPlayable.class, Text.class);
    }
  }

  /**
   * {@summary} Finds the previous media entry of the same type as given in the parameter
   * @param startI Starting index
   * @param endI Ending index
   * @param visual Visual interface
   * @param type Visual/Non-Visual interface
   * @return array index of the previous media entry
   */
  private int findPreviousIndex(
    int startIndex,
    int endIndex,
    Class<?> nonPlayClass,
    Class<?> type
  ) {
    int size = viewList.size();
    int i = startIndex;
    do {
      if (i < 0) {
        // Wrap around to the end of the list
        i = size - 1;
        continue;
      }
      if (
        nonPlayClass.isInstance(viewList.get(i)) &&
        type.isInstance(viewList.get(i))
      ) {
        return i;
      }
      i--;
    } while (i != startIndex);

    return -1;
  }

  /**
   * Finds the item being viewed
   * @return anonymous NonPlayable object currently being viewed
   */
  public NonPlayable currently_viewing() {
    int i = 0;
    for (MediaEntry entry : viewList) {
      if (i == currentIndex) return ((NonPlayable) entry);
      i++;
    }
    return null;
  }
}
