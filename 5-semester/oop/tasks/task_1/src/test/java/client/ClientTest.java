package client;


import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.channels.ServerSocketChannel;

public class ClientTest {

    private final String TEST_HOST = "localhost";
    private final int TEST_PORT = 9888;

    private Client testClient;

    @Before
    public void clientSetup() {
        testClient = new Client();
    }

    @Test(expected = java.net.ConnectException.class)
    public void checkNoConnection() throws IOException {
        testClient.run(TEST_HOST, TEST_PORT);
    }

    /** @brief This test tests almost nothing due to my infirmity in mocking static methods
     *  @throws IOException
     */

    @Test
    public void testSuccessfulRun() throws IOException {
        ServerSocketChannel serverChannel = ServerSocketChannel.open();
        serverChannel.socket().bind(new InetSocketAddress(TEST_HOST, TEST_PORT + 1));
        serverChannel.configureBlocking(false);

        testClient.run(TEST_HOST, TEST_PORT + 1);
    }
}
