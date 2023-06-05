import java.util.ArrayList;

/**
 * INTERFACE for classes to observe a dataset
 */
public interface Observer {
  /**
   * {@summary} Sends a message to all the observer instances that a new entry has been added
   *            and adds the new entry to all the relevant observers lists
   * @param ogEntries The original list of media entries
   */
  public void add_message(ArrayList<MediaEntry> ogEntries);

  /**
   * {@summary} Sends a message to all the observer instances that anentry has been removed
   *            and removes the entry from all the relevant observers lists
   * @param ogEntries The original list of media entries
   */
  public void remove_message(ArrayList<MediaEntry> ogEntries);

  /**
   * {@summary} sends a message that an observer has been deregistered from a set and
   *            refreshes(clears) its playing/viewing list
   * ***When an observer is deregistered from a set, it no longer recieves updates or list of items
   *    therefore the lsit of items is also cleared form its list
   * @param obs Observer object
   */
  public void deregister_message();

  /**
   * {@summary} Prints the entries in the observers list
   */
  public void show_list();

  /**
   * {@summary} Jumps to the next media entry in the media list
   * @param type Type of media ("audio", "video", "text", "image")
   */
  public void next(String type);

  /**
   * {@summary} Jumps to the previous media entry in the media list
   * @param type Type of media ("audio", "video", "text", "image")
   */
  public void previous(String type);
}
