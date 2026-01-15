import java.io.IOException;

public class Main {
public static void main(String[] args) {
System.out.println("\n Process ID is: " + ProcessHandle.current().pid());
try {
ProcessBuilder pb = new ProcessBuilder("whoami");
Process p = pb.start();
p.waitFor();
} catch (IOException | InterruptedException ex) {
System.out.println("Failed to start process: " + ex.getMessage());
System.exit(1);
}
System.exit(0);
}
}