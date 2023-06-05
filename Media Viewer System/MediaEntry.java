/**
 * Base class for Media Entries
 */
public class MediaEntry {

  /**
   * NAme of the file*/
  protected String name;
  /**
   * Size of the file,, lets assume it is kB for the sake of the simulation*/
  protected double size;

  /**
   * Constructor creates a MediaEntry object
   * @param name Name of the entry
   */
  public MediaEntry(String name, double size) {
    this.name = name;
    this.size = size;
  }

  /**
   * @return Returns name of the class as a string*/
  public String get_name() {
    return name;
  }

  /**
   * @return Returns size of the class as a string */
  public double get_size() {
    return size;
  }

  /**
   * Default Constructor
   */
  public MediaEntry() {
    //Intentionally left empty
  }

  /* Mutator functions:  */
  public void set_name(String s) {
    name = s;
  }

  public void set_size(double s) {
    size = s;
  }
}
