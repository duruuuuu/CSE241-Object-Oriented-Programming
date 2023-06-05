public class Audio extends MediaEntry implements NonVisual, Playable {

  /**
   * Duration of the audio recording
   */
  private double duration;

  public Audio(String __name, double __duration, double __size) {
    super(__name, __size);
    duration = __duration;

    System.out.println(name + " created succesfully");
  }

  public Audio() {
    //intentionally left empty
  }

  @Override
  public double get_duration() {
    return duration;
  }

  @Override
  public void set_duration(double s) {
    duration = s;
  }

  @Override
  public void info() {
    System.out.println(
      "AUDIO\nName: " +
      name +
      "\nDuration: " +
      duration +
      "\nSize: " +
      size +
      "\n"
    );
  }
}
