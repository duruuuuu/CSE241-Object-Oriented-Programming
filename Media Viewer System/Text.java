public class Text extends MediaEntry implements NonPlayable, NonVisual {

  /**
   * Constructor creates a Text object
   * @param __name Name of the file
   * @param __size size of the file
   */
  public Text(String __name, double __size) {
    super(__name, __size);
    System.out.println(name + " created succesfully");
  }

  public Text() {
    //intentionally left empty
  }

  @Override
  public double get_size() {
    return size;
  }

  @Override
  public void info() {
    System.out.println("TEXT\nName: " + name + "\nSize: " + size + "\n");
  }
}
