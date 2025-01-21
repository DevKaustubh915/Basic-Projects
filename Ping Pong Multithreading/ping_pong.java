import javax.sound.sampled.*;
import java.io.File;
import java.io.IOException;

public class ping_pong {
    private static final Object lock = new Object();
    private static boolean isPingTurn = true;
    private static SoundPlayerEnhanced pingSound;
    private static SoundPlayerEnhanced pongSound;

    public static void main(String[] args) {
        // Initialize sound players with the paths to your audio files
        pingSound = new SoundPlayerEnhanced("C:\\Users\\Server\\Desktop\\java fullstack\\Multithreading\\ping.wav",
                -10.0f); // Volume in decibels
        pongSound = new SoundPlayerEnhanced("C:\\Users\\Server\\Desktop\\java fullstack\\Multithreading\\pong.wav",
                -10.0f);

        Thread pingThread = new Thread(() -> ping(), "PingThread");
        Thread pongThread = new Thread(() -> pong(), "PongThread");

        pingThread.start();
        pongThread.start();
    }

    public static void ping() {
        for (int i = 0; i < 5; i++) {
            synchronized (lock) {
                while (!isPingTurn) {
                    try {
                        lock.wait();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        return;
                    }
                }
                System.out.println("Ping");
                pingSound.play(); // Play Ping sound
                isPingTurn = false;
                lock.notifyAll();
            }
            try {
                Thread.sleep(2000); // Optional: Delay between pings
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
        }
    }

    public static void pong() {
        for (int i = 0; i < 5; i++) {
            synchronized (lock) {
                while (isPingTurn) {
                    try {
                        lock.wait();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        return;
                    }
                }
                System.out.println("Pong");
                pongSound.play(); // Play Pong sound
                isPingTurn = true;
                lock.notifyAll();
            }
            try {
                Thread.sleep(2000); // Optional: Delay between pongs
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
        }
    }
}

class SoundPlayerEnhanced {
    private Clip clip;
    private FloatControl volumeControl;

    public SoundPlayerEnhanced(String soundFilePath, float volume) {
        try {
            // Obtain an audio input stream from the provided file path
            AudioInputStream audioInputStream = AudioSystem
                    .getAudioInputStream(new File(soundFilePath).getAbsoluteFile());

            // Get a sound clip resource
            clip = AudioSystem.getClip();

            // Open audio clip and load samples from the audio input stream
            clip.open(audioInputStream);

            // Obtain the volume control
            volumeControl = (FloatControl) clip.getControl(FloatControl.Type.MASTER_GAIN);
            volumeControl.setValue(volume); // Set volume (e.g., -10.0f decibels)
        } catch (UnsupportedAudioFileException | IOException | LineUnavailableException e) {
            System.err.println("Error loading sound file: " + soundFilePath);
            e.printStackTrace();
        }
    }

    public void play() {
        if (clip == null)
            return;

        // Stop the clip if it's already running
        if (clip.isRunning()) {
            clip.stop();
        }

        // Rewind to the beginning
        clip.setFramePosition(0);

        // Start playing the clip
        clip.start();
    }
}
