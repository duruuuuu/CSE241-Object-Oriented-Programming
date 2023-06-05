public class Image extends MediaEntry implements Visual, NonPlayable {

  /**
   * Dimension of the image. Lets assume it is the number of pixels for the sake of the simulation
   */
  private int dimension;

  /**
   * Constructor creates an Image object
   * @param __name Name of the entry
   * @param __dimension one dimension of the entry
   * @param __size size of the entry, assume it is in kB
   */
  public Image(String __name, int __dimension, double __size) {
    super(__name, __size);
    dimension = __dimension;

    System.out.println(name + " created succesfully");
  }

  public Image() {
    //Intentionally left empty
  }

  /**
   * @return Returns the dimension of the image
   */
  public int get_dimension() {
    return dimension;
  }

  public void set_dimension(int d) {
    dimension = d;
  }

  @Override
  public void info() {
    System.out.println(
      "IMAGE\nName: " +
      name +
      "\nDimension: " +
      dimension +
      "\nSize: " +
      size +
      "\n"
    );
  }
}
