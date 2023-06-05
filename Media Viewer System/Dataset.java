import java.util.ArrayList;

public class Dataset {

  /**
   * List of observers registered to the dataset */
  public ArrayList<Observer> observerList = new ArrayList<Observer>();

  /**
   * List of media entries registered to the dataset */
  public ArrayList<MediaEntry> entryList = new ArrayList<MediaEntry>();

  /**
   * {@summary} Registering/Adding an instance of an  Observer to the dataset
   * @param toAdd observer object that will be added to the dataset
   */
  public void register(Observer toAdd) {
    observerList.add(toAdd);
    toAdd.add_message(entryList);
  }

  /**
   * {@summary} Removing an instance of an  Observer from the dataset
   * Deregistering an observer from a set completely removes the observer from the set
   * and vice versa.
   * A deregistered observer no longer recieves any data and its list is also cleared
   * as it also does not recieve a list of items
   * @param toAdd observer object that will be removed from the datase
   */
  public void deregister(Observer toRemove) {
    toRemove.deregister_message();
    observerList.remove(toRemove);
  }

  /**
   * Adds a new media entry to the dataset
   * @param newEntry The entry to be added to the dataset
   */
  public void add(MediaEntry newEntry) {
    entryList.add(newEntry);

    //Notify the relevant (Playable/Viewer) observerList that there is a new entry
    if (newEntry instanceof Playable) {
      notifyPlayer_ADD();
    } else if (newEntry instanceof NonPlayable) {
      notifyViewer_ADD();
    }
  }

  /**
   * Function removes a Playable entry from the dataset and notifies all Players
   * @param toRemove Playable object that holds the item to be removed
   */
  public void remove(Playable toRemove) {
    entryList.remove((MediaEntry) toRemove);
    notifyPlayer_REMOVE();
  }

  /**
   * Function removes a Non-Playable entry from the set and all Viewing lists
   * @param toRemove NonPlayable instance that holds the item to be removed
   */
  public void remove(NonPlayable toRemove) {
    entryList.remove((MediaEntry) toRemove);
    notifyViewer_REMOVE();
  }

  /**
   *{@summary} Notify the Player Observer that a new entry has been added
   */
  private void notifyPlayer_ADD() {
    for (Observer obs : observerList) {
      if (obs instanceof Player) obs.add_message(entryList);
    }
  }

  /**
   * {@summary} Notify the player Observer that an entry has been removed
   */
  private void notifyPlayer_REMOVE() {
    for (Observer obs : observerList) {
      if (obs instanceof Player) obs.remove_message(entryList);
    }
  }

  /**
   * {@summary} Notify the Viewer Observer that a new entry has been added
   */
  private void notifyViewer_ADD() {
    for (Observer obs : observerList) {
      if (obs instanceof Viewer) obs.add_message(entryList);
    }
  }

  /**
   * {@summary} Notify the Viewer Observer that an entry has been removed
   */
  private void notifyViewer_REMOVE() {
    for (Observer obs : observerList) {
      if (obs instanceof Viewer) obs.remove_message(entryList);
    }
  }
}
