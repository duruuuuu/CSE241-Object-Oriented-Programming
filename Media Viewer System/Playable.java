/**
 * Interface for PLAYABLE Media Entries AKA recordings of any type
 */
public interface Playable {
  /**
   * @return Returns the duration of the recording*/
  public double get_duration();

  //Mutator functions
  public void set_duration(double s);

  /**
   * Prints all the information about the object*/
  public void info();
}
