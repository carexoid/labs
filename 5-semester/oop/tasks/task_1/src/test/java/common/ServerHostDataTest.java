package common;

import org.junit.Test;
import static org.junit.Assert.*;

public class ServerHostDataTest {

    @Test
    public void TestHost() {
        assertEquals(ServerHostData.ADDRESS, "localhost");
    }
    
    @Test
    public void TestPort() {
        assertEquals(ServerHostData.PORT, 7779);
    }
}
