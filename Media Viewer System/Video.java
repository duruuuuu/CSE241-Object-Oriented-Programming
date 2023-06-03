public class Video extends MediaEntry implements Playable, Visual {

  /**
   * Duration of the video recording*/
  private double duration;

  public Video(String __name, double __duration, double __size) {
    super(__name, __size);
    duration = __duration;

    System.out.println(name + " created succesfully");
  }

  @Override
  public double get_duration() {
    return duration;
  }

  @Override
  public void info() {
    System.out.println(
      "VIDEO\nName: " +
      name +
      "\nDuration: " +
      duration +
      "\nSize: " +
      size +
      "\n"
    );
  }
}
