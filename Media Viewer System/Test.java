public class Test {

  public static void main(String[] args) {
    System.out.println("\nPROGRAM START\n====================\n");
    // This is our dataset. We have only one dataset
    Dataset ds = new Dataset();

    /* CREATING DIFFERENT OBSERVERS */
    Player p1 = new Player();
    Player p2 = new Player();

    Viewer v1 = new Viewer();
    Viewer v2 = new Viewer();

    /* REGISTERING OBSERVERS TO DATA SET */
    ds.register(p1);
    ds.register(p2);
    ds.register(v1);
    ds.register(v2);

    /* REMOVING OBSERVER FROM DATA SET */
    //ds.deregister(p1);
    //p1 no longer recieves any update or list of items

    /* CREATING DIFFERENT OBJECTS */
    ds.add(new Image("image1", 1, 9.9));
    ds.add(new Image("image2", 7, 19.9));
    ds.add(new Image("image3", 4, 8.9));

    ds.add(new Audio("audio1", 4.4, 2.2));
    ds.add(new Audio("audio2", 5.4, 8.2));
    ds.add(new Audio("audio3", 43.14, 90.12));

    ds.add(new Text("text1", 5.5));
    ds.add(new Text("text2", 51.5));
    ds.add(new Text("text3", 51.11));

    ds.add(new Video("video1", 3.3, 10));
    ds.add(new Video("video2", 13.43, 5));

    /* TESTING PLAYER OBSERVER */

    System.out.println(
      "\n===TESTING PLAYER===.\nPlayer Observer List: \np1\np2"
    );

    System.out.println("\n(p1.show_list)");
    p1.show_list();

    System.out.println("\n(p2.show_list)");
    p2.show_list();

    //Prints info about the playing object
    System.out.println("\nCurrently Playing:");
    Playable p0 = p1.currently_playing();
    p0.info();

    //Remove p1 from the dataset. it will no longer recieve any updates
    ds.deregister(p1);
    System.out.println("Observer p1 Removed from the dataset");
    System.out.println("\nPlayer Observer List:\np2");

    //Remove current entry from the dataset. All interested observers will get this update
    ds.remove(p0);
    System.out.println("\naudio1 Removed from the dataset.");

    //display the new current platying
    p0 = p2.currently_playing();
    System.out.println("\nNew Currently Playing:");
    p0.info();

    //Showing that the removed observer does not change
    System.out.println(
      "\n(p1.show_list) *p1 deregistered from the dataset so it does not get notified of any changes"
    );
    p1.show_list();

    //Printing the modified playing list
    System.out.println("\n(p2.show_list)");
    p2.show_list();

    //Creating a new player observer
    Player mixtape1 = new Player();
    ds.register(mixtape1);
    System.out.println("\nNew player observer created.");

    //Listing alla active observers
    System.out.println("\nPlayer Observer List:\np2\nmixtape1");

    //Printing new observer list (lists created after data has been added still inherit all the data)
    System.out.println("\n(mixtape1.show_list)");
    mixtape1.show_list();

    //Testing next and previous functions
    System.out.println("\nJumping to next audio (p2 player)");
    p2.next("audio");
    p0 = p2.currently_playing();
    System.out.println("currently playing:");
    p0.info();

    //Next audio
    System.out.println("\nJumping to previous audio (p2 player)");
    p2.previous("audio");
    p0 = p2.currently_playing();
    System.out.println("currently playing:");
    p0.info();

    //Next video
    System.out.println("\nJumping to next video(p2 player)");
    p2.next("video");
    p0 = p2.currently_playing();
    System.out.println("currently playing:");
    p0.info();

    //Previous video (while the current video is the first video entry)
    System.out.println(
      "\nJumping to previous video(p2 player)\t**Jumping to the previous data while the current one is first in the list makes it jump to the last entry"
    );
    p2.previous("video");
    p0 = p2.currently_playing();
    System.out.println("currently playing:");
    p0.info();

    //next video (while the current video is the last video entry)
    System.out.println(
      "\nJumping to next video(p2 player)\t**Jumping to the next data while the current one is last in the list makes it jump to the first entry"
    );
    p2.next("video");
    p0 = p2.currently_playing();
    System.out.println("currently playing:");
    p0.info();
    /*=====*/
    /*=====*/

    /* TESTING VIEWER OBSERVER */
    System.out.println(
      "\n===TESTING PLAYER===.\nViewer Observer List: \nv1\nv2"
    );

    //Displaying v1 observer lsit
    System.out.println("\n(v1.show_list)");
    v1.show_list();

    //Displaying v2 observer list
    System.out.println("\n(v2.show_list)");
    v2.show_list();

    //Prints information about the viewing object
    System.out.println("\nCurrently Viewing");
    NonPlayable np = v1.currently_viewing();
    np.info();

    //Remove v1 from the dataset. It will no longer reviece any notifications of change
    ds.deregister(v1);
    System.out.println("Observer v1 removed from the dataset");
    System.out.println("Viewer Observer List:\nv2");

    //Remove current np entry from the dataset
    ds.remove(np);
    System.out.println("\nimage1 Removed from dataset");

    //Showing that the removed observer does not change
    System.out.println("\nv1.show_list");
    v1.show_list();

    //Printing the modified viewing list
    System.out.println("\n(v2.show_list)");
    v2.show_list();

    //Creating a new viewer observer
    Viewer docViewer = new Viewer();
    ds.register(docViewer);
    System.out.println("\nNew viewer observer list:\nv2\ndocViewer");

    //Printing the new observer list
    System.out.println("\n(docViewer.show_list)");
    docViewer.show_list();

    //Testing next and previous functions
    System.out.println("\nJumping to next text (v2)");
    v2.next("text");
    np = v2.currently_viewing();
    System.out.println("Currently viewing:");
    np.info();

    //Previous image (while curr image is the first in the lsit)
    System.out.println("\nJumping to previous image (v2 viewer)");
    v2.previous("image");
    np = v2.currently_viewing();
    System.out.println("currently viewing:");
    np.info();

    //next text
    System.out.println("\nJumping to next text(v2 viewer)");
    v2.next("text");
    np = v2.currently_viewing();
    System.out.println("currently viewing:");
    np.info();

    //prev text
    System.out.println("\nJumping to previous text(v2 viewer)");
    v2.previous("text");
    np = v2.currently_viewing();
    System.out.println("currently viewing:");
    np.info();

    //Deleting the currently playing entry that happens to be the last entry of the list
    System.out.println("\nDeleting Currently Viewed data from the set");
    ds.remove(np);

    //displaying observer lsit
    System.out.println("\n(v2.show_list)");
    v2.show_list();

    //displaying second observer list
    System.out.println("\n(doViewer.show_list)");
    docViewer.show_list();

    //Displaying the new currently viewing item
    System.out.println("\ncurrently viewing: (v2)");
    np = v2.currently_viewing();
    np.info();
  }
}
